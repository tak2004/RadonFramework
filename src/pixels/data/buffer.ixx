export module rf.pixels.data:buffer;
import rf.core.types;
import rf.core.memory;

export namespace rf {
struct PixelFormat {
  u8 bitsPerPixel;
  u8 channels;
  bool signedValueRange;
  bool floatingPoint;
};

enum PixelFormats:u8 { RGBAf32=0, RGBu8=1, Ru8=2, RGBAu8=3 };

constexpr PixelFormat Formats[] = {
    {128, 4, true, true},//RGBAf32
    {24,3,false, false},//RGB24
    {8,1,false,false},//R8
    {32,4,false,false}//RGBAu8
};

struct Buffer {
  u8 *data;
  u16 width, height;
  PixelFormats format;
  u8 reerved[3];
};
static_assert(sizeof(Buffer) == 16);

template <IsAdvancedAllocator ALLOCATOR>
void createRenderTarget(Buffer& Self, u64 Width, u64 Height, PixelFormats Format,
                        ALLOCATOR& Allocator) {
  Self.format = Format;
  Self.width = Width;
  Self.height = Height;
  auto bytes = Width * Height * Formats[Format].bitsPerPixel >> 3;
  Self.data = reinterpret_cast<u8*>(Allocator.allocate(bytes,4096).address);
}
} // namespace rf