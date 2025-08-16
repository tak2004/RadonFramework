import rf.ui;
import rf.core.collections;
import rf.core.cpu;
import rf.core.memory;
import rf.core.math.hashes;
import rf.core.threading;
import rf.core.system;
import rf.core.io;
import rf.core.types;
import rf.core.os;
import rf.pixels;
#include <cassert>
#include <cmath>
#include <intrin.h>
#include <stdio.h>

using namespace rf;

// rendergraph:
// normal buffer -> emission buffer \
// albedo buffer                    -mix- out buffer
// ui buffer
enum Buffers { Normal = 0, Color = 1, UI = 2, Emission = 3 };

struct GameData {
  Window *window{nullptr};
  u64 gamestart{0};
  u64 lastTimestamp{0};
  Buffer image[6];
  f32v4 lpos;
  Buffer buffers[4];
};

i32 min(i32 A, i32 B) { return A < B ? A : B; }
i32 max(i32 A, i32 B) { return A > B ? A : B; }

struct Rectangle {
  int x1, y1;
  int x2, y2;
};

bool findIntersection(const Rectangle &r1, const Rectangle &r2,
                      Rectangle &result) {
  if (r1.x1 >= r2.x2 || r2.x1 >= r1.x2 || r1.y1 >= r2.y2 || r2.y1 >= r1.y2) {
    return false;
  }
  result.x1 = max(r1.x1, r2.x1);
  result.y1 = max(r1.y1, r2.y1);
  result.x2 = min(r1.x2, r2.x2);
  result.y2 = min(r1.y2, r2.y2);
  return true;
}

void copyMaskedLine128(u8 *Target, u8 *Source, size Bytes, u8 *Mask,
                       size BytesPerPixel) {
  assert((reinterpret_cast<ptrdiff>(Source) & 15) == 0);
  assert((reinterpret_cast<ptrdiff>(Target) & 15) == 0);
  __m128i *src = reinterpret_cast<__m128i *>(Source);
  __m128i *dst = reinterpret_cast<__m128i *>(Target);
  auto pixels = Bytes / BytesPerPixel;
  for (size i = 0; i < pixels; ++i)
    if (Mask[i]) {
      auto pixel = _mm_load_si128(src + i);
      _mm_store_si128(dst + i, pixel);
    }
}

void copyLine128(u8 *Target, u8 *Source, size Bytes, size BytesPerPixel) {
  assert((reinterpret_cast<ptrdiff>(Source) & 15) == 0);
  assert((reinterpret_cast<ptrdiff>(Target) & 15) == 0);
  __m128i *src = reinterpret_cast<__m128i *>(Source);
  __m128i *dst = reinterpret_cast<__m128i *>(Target);
  auto pixels = Bytes / BytesPerPixel;
  for (size i = 0; i < pixels; ++i){
      auto pixel = _mm_load_si128(src + i);
      _mm_store_si128(dst + i, pixel);
    }
}

void drawTexture(Buffer &Out, const Buffer &Texture, i32 X, i32 Y,
                 const Buffer &Mask) {
  Rectangle intersection;
  if (findIntersection({0, 0, Out.width, Out.height},
                       {X, Y, X + Texture.width, Y + Texture.height},
                       intersection)) {
    u8 bytesPerPixel = Formats[Texture.format].bitsPerPixel / 8;
    u64 offsetOut = intersection.x1 * bytesPerPixel;
    u64 offsetIn = (intersection.x2 - intersection.x1) * bytesPerPixel;
    u64 offsetMask = (intersection.x2 - intersection.x1);
    u64 lineBytes = (intersection.x2 - intersection.x1) * bytesPerPixel;
    u64 texHeight = intersection.y2 - intersection.y1;
    offsetIn += (Texture.height - texHeight) * Texture.width * bytesPerPixel;
    offsetOut += intersection.y1 * Out.width * bytesPerPixel;
    offsetMask += (Texture.height - texHeight) * Texture.width;
    for (u16 y = 0; y < texHeight; ++y) {
      copyMaskedLine128(Out.data + offsetOut, Texture.data + offsetIn,
                        lineBytes,
           Mask.data + offsetMask, bytesPerPixel);
      offsetOut += Out.width * bytesPerPixel;
      offsetIn += Texture.width * bytesPerPixel;
      offsetMask += Texture.width;
    }
  }
}

void drawUIImage(Buffer &Out, const Buffer &Texture, i32 X, i32 Y) {
  X = min(X, Out.width - Texture.width);
  X = max(X, 0);
  Y = min(Y, Out.height - Texture.height);
  Y = max(Y, 0);
  u8 bytesPerPixel = Formats[Texture.format].bitsPerPixel / 8;
  u64 lineBytes = Texture.width * bytesPerPixel;
  u64 offsetOut = ((Y*Out.width)+X) * bytesPerPixel;
  u64 offsetIn = 0;
  for (u16 y = 0; y < Texture.height; ++y) {
    copyLine128(Out.data + offsetOut, Texture.data + offsetIn, lineBytes,
                bytesPerPixel);
    offsetOut += Out.width * bytesPerPixel;
    offsetIn += lineBytes;
  }
}

void overlay128(const Buffer &A, Buffer &Out) {
  auto ptr = reinterpret_cast<float const *>(A.data);
  auto cptr = reinterpret_cast<u8 const *>(Out.data);
  auto zero = _mm_set_ps1(0.0f);
  auto norm = _mm_set_ps1(255.0f);
  for (size i = 0; i < Out.width * Out.height; i += 4) {
    _mm_prefetch(reinterpret_cast<const char *>(ptr + (i + 4) * 4),
                 _MM_HINT_T0);
    _mm_prefetch(reinterpret_cast<const char *>(cptr + (i + 4) * 3),
                 _MM_HINT_T0);
    for (auto n = 0; n < 4; ++n) {
      auto blend = ptr[(i + n) * 4 + 0];
      Out.data[(n + i) * 3] = u8(
          blend * ptr[(i + n) * 4 + 1]*255.0 + Out.data[(n + i) * 3] * (1 - blend));
      Out.data[(n + i) * 3 + 1] = u8(
          blend * ptr[(i + n) * 4 + 2]*255.0 + Out.data[(n + i) * 3+1] * (1 - blend));
      Out.data[(n + i) * 3 + 2] = u8(
          blend * ptr[(i + n) * 4 + 3]*255.0 + Out.data[(n + i) * 3+2] * (1 - blend));
    }
  }
}

void mix128(const Buffer &A, const Buffer &B, Buffer &Out) {
  auto lptr = reinterpret_cast<float const *>(A.data);
  auto cptr = reinterpret_cast<float const *>(B.data);
  auto zero = _mm_set_ps1(0.0f);
  auto norm = _mm_set_ps1(255.0f);
  for (size i = 0; i < Out.width * Out.height; i += 4) {
    _mm_prefetch(reinterpret_cast<const char *>(lptr + (i + 4) * 4),
                 _MM_HINT_T0);
    _mm_prefetch(reinterpret_cast<const char *>(cptr + (i + 4) * 4),
                 _MM_HINT_T0);
    for (auto n = 0; n < 4; ++n) {
      auto light = _mm_load_ps(lptr + (n + i) * 4);
      auto fRGBA = _mm_load_ps(cptr + (n + i) * 4);
      fRGBA = _mm_max_ps(
          _mm_min_ps(_mm_mul_ps(_mm_mul_ps(light, fRGBA), norm), norm), zero);
      auto rgba = _mm_cvtps_epi32(fRGBA);
      Out.data[(n + i) * 3] = u8(rgba.m128i_u8[4]);
      Out.data[(n + i) * 3 + 1] = u8(rgba.m128i_u8[8]);
      Out.data[(n + i) * 3 + 2] = u8(rgba.m128i_u8[12]);
    }
  }
}

void lightningRGBAf32(Buffer &NormalBuffer, Buffer &Emission,
                      const f32v4 &LightPos) {
  __m128 *target = reinterpret_cast<__m128 *>(Emission.data);
  __m128 *source = reinterpret_cast<__m128 *>(NormalBuffer.data);
  __m128 scale = _mm_set_ps(0.0f, 2.0f, -2.0f, -2.0f);
  __m128 shift = _mm_set_ps(0.0f, -1.0f, 1.0f, 1.0f);
  __m128 lightPos =
      _mm_set_ps(0.0, LightPos.raw[2], LightPos.raw[1], LightPos.raw[0]);
  for (auto y = 0; y < 480; y++) {
    for (auto x = 0; x < 640; x += 4) {
      // prefetch next cacheline
      _mm_prefetch((const char *)(source + x + 4), _MM_HINT_T0);
      for (auto i = 0; i < 4; ++i) {
        __m128 normal = _mm_load_ps((f32 *)(source + x + i));
        // convert 0 till 1 to -1 till 1
        normal = _mm_fmadd_ps(normal, scale, shift);
        // fragPos = {x,y,0}
        //auto fragPos = _mm_set_ps(0, y, x + i, 0);
        // Pointlight
        // lightDir = normalize(fragPos-lightPos)
        // Directional light
        // lightDir = normalize(lightPos)
        auto lightDir = lightPos;
        //lightDir = _mm_sub_ps(fragPos, lightPos);
        // normalize -> m=sqrt(x²+y²+z²) x=x/m, y=y/m, z=z/m
        /* sse2
        auto m = _mm_mul_ps(lightDir, lightDir);
        m = _mm_hadd_ps(m, m);
        m = _mm_hadd_ps(m, m);*/
        // sse4.1
        auto m = _mm_dp_ps(lightDir, lightDir, 0x7F);
        m = _mm_rsqrt_ps(m);
        lightDir = _mm_mul_ps(lightDir, m);
        // diffuse = dot(normal, lightDir)
        /* sse2
        auto light = _mm_mul_ps(normal, lightDir);
        light = _mm_hadd_ps(light, light);
        light = _mm_hadd_ps(light, light);*/
        // sse4.1
        auto diffuse = _mm_dp_ps(normal, lightDir, 0x7F);
        auto global = _mm_set_ps1(LightPos.raw[3]);
        diffuse = _mm_max_ps(diffuse, global);
        _mm_store_ps((f32 *)(target + x + i), diffuse);
      }
    }
    target += 640;
    source += 640;
  }
}

void cart2iso(i32 x, i32 y, i32 z, i32 &ix, i32 &iy) {
  static const f32 sqrt2 = sqrt(2);
  static const f32 sqrt3 = sqrt(3);
  static const f32 sqrt6 = sqrt(6);
  ix = i32(f32(x - y) / sqrt2);
  iy = i32(f32(x + y - 2 * z) / sqrt6);
}

void drawBoard(i32 OffsetX, i32 OffsetY, i32 TilesX, i32 TilesY, Buffer &Out,
               const Buffer &Texture, const Buffer &Mask) {
  i32 posX = OffsetX;
  i32 posY = OffsetY;
  i32 ix,iy;
  for (auto y = 0; y < TilesY; ++y) {
    for (auto x = 0; x < TilesX; ++x) {
      cart2iso(x * 91, y * 91, 0, ix, iy);
      drawTexture(Out, Texture, 256+ix, 128+iy, Mask);
    }
  }
}

void copyBuffer(const Buffer &In, Buffer &Out) {
  auto lptr = reinterpret_cast<float const *>(In.data);
  auto norm = _mm_set_ps1(255.0f);
  for (size i = 0; i < Out.width * Out.height; i += 4) {
    _mm_prefetch(reinterpret_cast<const char *>(lptr + (i + 4) * 4),
                 _MM_HINT_T0);
    for (auto n = 0; n < 4; ++n) {
      auto fRGBA = _mm_load_ps(lptr + (n + i) * 4);
      fRGBA = _mm_mul_ps(fRGBA, norm);
      auto rgba = _mm_cvtps_epi32(fRGBA);
      Out.data[(n + i) * 3] = u8(rgba.m128i_u8[4]);
      Out.data[(n + i) * 3 + 1] = u8(rgba.m128i_u8[8]);
      Out.data[(n + i) * 3 + 2] = u8(rgba.m128i_u8[12]);
    }
  }
}

void renderer(u8 *Out, u16 Width, u16 Height, ptr UserData) {
  GameData *gameData = reinterpret_cast<GameData *>(UserData);
  u64 now = queryPerformanceCounter();
  auto deltaMS =
      (now - gameData->gamestart) * 1000 / queryPerformanceFrequency();
  auto animationOffset = deltaMS;
  Buffer buffer{Out, Width, Height, PixelFormats::RGBu8};
  auto out = gameData->buffers[0].data;
  // normal pass
  drawBoard(0, 0, 3, 3, gameData->buffers[::Buffers::Normal],
            gameData->image[0], gameData->image[3]);
  // lighting pass
  gameData->lpos.raw[0] = sin(f32(animationOffset) / 500.0f);
  gameData->lpos.raw[2] = cos(f32(animationOffset) / 500.0f);
  gameData->lpos.raw[1] = -1.0f;
  gameData->lpos.raw[3] = 0.1;
  // max(sin(f32(animationOffset) / 500.0f), 0.0f);
  /*
  gameData->lpos.x = cos(f32(animationOffset) / 500.0f) * 100.0f + 320.0f;
  gameData->lpos.y = sin(f32(animationOffset) / 500.0f) * 100.0f + 170.0f;
  gameData->lpos.z = -100.0f;
  */
  lightningRGBAf32(gameData->buffers[::Buffers::Normal],
                   gameData->buffers[::Buffers::Emission], gameData->lpos);
  // albedo
  drawBoard(0, 0, 3, 3, gameData->buffers[::Buffers::Color],
            gameData->image[4], gameData->image[3]);
  mix128(gameData->buffers[::Buffers::Emission],
         gameData->buffers[::Buffers::Color], buffer);
  drawUIImage(gameData->buffers[::Buffers::UI], gameData->image[5], 100, 50);
  overlay128(gameData->buffers[::Buffers::UI], buffer);
  // debug rendering buffer
  //copyBuffer(gameData->buffers[::Buffers::Emission], buffer);
  gameData->lastTimestamp = now;
}

void diagnostics(ptr Userdata) {
  GameData *gameData = reinterpret_cast<GameData *>(Userdata);
  printf("syncs: %llu\tframes: %llu\n", gameData->window->getData().syncIndex,
         gameData->window->getData().canvasData->frameIndex);
}

void renderLogic(ptr UserData) {
  auto canvas = reinterpret_cast<Canvas *>(UserData);
  while (true)
    canvas->processFrame();
}

#pragma pack(push, 2)
struct SimpleBinaryImage {
  u16 width;
  u16 height;
  u16 channels;
};
#pragma pack(pop)

u8* readSBI(mem Data, u16& Width, u16& Height, u16& Bits) {
  auto header =
      reinterpret_cast<SimpleBinaryImage *>(Data.address);
  Width = header->width;
  Height = header->height;
  Bits = header->channels * 8;
  return reinterpret_cast<u8 *>(header+1);
}

bool loadTexture(strview FilePath, Arena &Allocator, Buffer &Texture) {
  auto handle = openFile(FilePath, FileAccessMode::Read,
                         FileAccessPriority::ReadThroughput);
  auto bytes = seekFile(handle, 0, SeekOrigin::End);
  seekFile(handle, 0, SeekOrigin::Begin);
  auto buffer = Allocator.pushExtended(bytes, 64);
  u64 bytesWrittenToBuffer;
  readFile(handle, buffer, bytesWrittenToBuffer);
  closeFile(handle);
  u16 w, h;
  u16 bits;
  auto pixels = readSBI(buffer, w, h, bits);
  Texture.width = w;
  Texture.height = h;
  Texture.format = bits == 32 ? PixelFormats::RGBAu8 : PixelFormats::RGBu8;
  Texture.data = pixels;
  return true;
}

void generateTextureMask(const Buffer &Texture, Arena &Allocator,
                         Buffer &Mask) {
  auto mask = Allocator.pushExtended(Texture.width * Texture.height, 64);
  Mask.data = reinterpret_cast<u8 *>(mask.address);
  Mask.width = Texture.width;
  Mask.height = Texture.height;
  Mask.format = PixelFormats::Ru8;
  u8 *dst = Mask.data;
  u8 *src = Texture.data;
  for (size i = 0; i < Texture.height * Texture.width; ++i) {
    Mask.data[i] = src[i * 3] | src[i * 3 + 1] | src[i * 3 + 2] ? 255 : 0;
  }
}

void convertRGBToRGBAFloat(Buffer &In, Arena &Allocator, Buffer &Out) {
  auto mem = Allocator.pushExtended(In.width * In.height * 16, 64);
  Out.format = PixelFormats::RGBAf32;
  auto channels = Formats[In.format].channels; 
  Out.data = reinterpret_cast<u8 *>(mem.address);
  Out.height = In.height;
  Out.width = In.width;
  auto out = reinterpret_cast<float *>(Out.data);
  auto normalize = _mm_set_ps1(1.0f / 255.0f);
  for (auto i = 0; i < In.width * In.height; ++i) {
    __m128i p;
    if (channels == 3)
      p = _mm_set_epi32(In.data[i * 3], In.data[i * 3 + 1],
                              In.data[i * 3+2], 0);
    else
      p = _mm_set_epi32(In.data[i * 4], In.data[i * 4 + 1], In.data[i * 4 + 2],
                        In.data[i * 4 + 3]);
    auto fp = _mm_cvtepi32_ps(p);
    fp = _mm_mul_ps(fp, normalize);
    _mm_store_ps(out + i * 4, fp);
  }
}

int main() {
  CPUFeatures.detect();

  // configure the memory management
  Heap heap;
  auto stackMemory = heap.allocate(50_mb);
  Arena stack;
  stack.memory = stackMemory;
  AllocatorAdapter arenaWrapper{
      .alignedAllocateImplementation = [](size Bytes, size Alignment,
                                          ptr Allocator) -> mem {
        return reinterpret_cast<Arena *>(Allocator)->pushExtended(Bytes,
                                                                  Alignment);
      },
      .allocator = &stack};
  // By doing some exercises with the hardware and OS the traingins plan is
  // acomplished. It contains the results which will be used by the JIT to
  // generate system specific code.
  TrainingsPlan requirements;
  requirements.needSignedValues = true;
  requirements.needFloatingPointPrecission = true;
  requirements.limitCPUs = 1;
  RecommendedSettings recomendation;
  exercise(requirements, recomendation, arenaWrapper);

  GameData gameData;
  auto &app = Application::getInstance();
  Window mainWindow;
  gameData.window = &mainWindow;
  gameData.gamestart = queryPerformanceCounter();
  createRenderTarget(gameData.buffers[::Buffers::Normal], 640, 480,
                     PixelFormats::RGBAf32, arenaWrapper);
  createRenderTarget(gameData.buffers[::Buffers::Color], 640, 480,
                     PixelFormats::RGBAf32, arenaWrapper);
  createRenderTarget(gameData.buffers[::Buffers::Emission], 640, 480,
                     PixelFormats::RGBAf32, arenaWrapper);
  createRenderTarget(gameData.buffers[::Buffers::UI], 640, 480,
                     PixelFormats::RGBAf32, arenaWrapper);
  auto remember = stack.offset;
  Buffer normal;
  loadTexture(strview{"C:/Users/ms/Desktop/blender/normal0140.png.sbi"}, stack,
              normal);
  convertRGBToRGBAFloat(normal, stack, gameData.image[0]);
  loadTexture(strview{"C:/Users/ms/Desktop/blender/position0140.png.sbi"}, stack,
              gameData.image[1]);
  generateTextureMask(gameData.image[1], stack, gameData.image[3]);
  loadTexture(strview{"C:/Users/ms/Desktop/blender/albedo0140.png.sbi"}, stack,
              gameData.image[2]);
  convertRGBToRGBAFloat(gameData.image[2], stack, gameData.image[4]);
  Buffer ui;
  loadTexture(strview{"C:/Users/ms/Desktop/blender/text_bg_03.png.sbi"}, stack, ui);
  convertRGBToRGBAFloat(ui, stack, gameData.image[5]);

  Canvas canvas;
  canvas.setRenderer(renderer, &gameData);
  mainWindow.setCanvas(canvas);
  app.addWindow(mainWindow, true);

  Timer perSecond;
  perSecond.update(TimeSpan::CreateByTime(0, 0, 1),
                   TimeSpan::CreateByTime(0, 0, 1), &gameData, diagnostics);
  perSecond.start();

  // ThreadPool::GetInstance().queueWorkItem(renderLogic, &canvas);

  auto handler = createThread(
      &canvas, [](void *State) { renderLogic(State); }, nullptr, nullptr);
  setThreadAffinityMask(*handler, 0, 2);
  postThreadConfigurationComplete(*handler);

  app.run();
  destroyThread(handler);
  ThreadPool::GetInstance().shutdown();
  /*
  auto c_str = "/etc/dnsd";
  constmem memory = {"/etc/dnsd", sizeof("/etc/dnsd")};
  HashContextxxh3 *context = createContext64();
  updateContext64(context, memory);
  auto h32 = hash32(context);
  auto h64 = hash64(context);
  freeContext(context);
  auto h32b = hash32xxh3(memory);
  auto h64b = hash64xxh3(memory);
  auto h32c = "/etc/dnsd"_32_xxh3;
  auto h32d = "/etc/dnsd"_h32;
  auto h64d = "/etc/dnsd"_h64;

  auto screens = getAllScreens(stackAdapter);

  Hashlist<> hashes(heap, stackAdapter, 1_gib);
  hashes.set(1, stack.memory.address);
  hashes.set(2, stack.memory.address);
  hashes.set(1, stack.memory.address);
  auto isKeySet = hashes.containsKey(1);
  hashes.remove(1);
  auto isKeySetAfterRemove = hashes.containsKey(1);
  auto two = hashes.get(2);
  Hashlist<> otherHashes(heap, stackAdapter);
  hashes.clone(otherHashes);
  auto otherTwo = hashes.get(2);
  return two == otherTwo ? 0 : -1;*/
  return 0;
}