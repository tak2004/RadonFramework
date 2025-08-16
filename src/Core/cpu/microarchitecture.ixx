export module rf.core.cpu:microarchitecture;
import rf.core.types;
import :intrinsics;
import :math;

rf::u8 getVendorID() noexcept;

export namespace rf {
/// <summary>
/// Some Microarchitectures support different load/store channel setup for
/// different data types. E.g Zen3 can supports following. load 3x 1-16Byte, 2x
/// 32Byte store 2x 1-16Byte, 1x 32Byte
/// </summary>
struct LoadStoreChannel {
  u16 byteWidth;
  u8 maxParallelCalls;
};

// SSE read/store channel
LoadStoreChannel DefaultLoad[] = {{16, 1}};
LoadStoreChannel DefaultStore[] = {{16, 1}};

struct Microarchitecture {
  LoadStoreChannel *loadChannels = DefaultLoad;
  LoadStoreChannel *storeChannels = DefaultStore;

  struct View {
    u32 ID;
    u8 vendor;
    u8 loadChannelCount;
    u8 storeChannelCount;
  } view;

  Microarchitecture &detect();
  //  Microarchitecture &loadFrom(mem &Memory);

  /// Returns the LoadStoreChannel info best fitting for the specified
  /// BytesToLoad value.
  const LoadStoreChannel &
  getLoadChannelInfo(const size BytesToLoad) const noexcept;
  /// Returns the LoadStoreChannel info best fitting for the specified
  /// BytesToStore value.
  const LoadStoreChannel &
  getStoreChannelInfo(const size BytesToStore) const noexcept;

  template <size N> bool isMicroArchitecture(const u32 (&Value)[N]);

private:
  void lookupChannelInfos() noexcept;
};

/// The vendor is straight forward to distinguish. Each vendor use a unique ID.
namespace VendorID {
    constexpr u8 Unknown = 0;
    constexpr u8 Intel = 1;
    constexpr u8 AMD = 2;
} // namespace VendorID

/// To distinguish between the microarchitectures following id is assembled.
/// 0x[VendorID][ExtendedFamily+Family][(ExtendedModel<<4) + Model][Stepping]

namespace MicroarchitectureID {
    constexpr u32 Undetected[1] = { 0x00000000 };
}

namespace MicroarchitectureID::AMD {
    constexpr u32 Zen[4] = { 0x02172000, 0x02171800, 0x02171100, 0x02170100 };
} // namespace MicroarchitectureID::AMD

namespace MicroarchitectureID::Intel {
    constexpr u32 CoffeeLake[5] = { 0x01068e0A, 0x01069e0A, 0x01069e0B, 0x01069e0C,
                                                  0x01069e0D };
} // namespace MicroarchitectureID::Intel

Microarchitecture &Microarchitecture::detect() {
  this->view.vendor = ::getVendorID();
  i32 reg[4];
  // reg[0] == 20-27 extended family
  //           16-19 extended model
  //           12-13 type
  //           8-11 family
  //           4-7 model
  //           0-3 stepping
  cpuid(1, 0, reg);
  u32 familyEx = reg[0] >> 20 & 255;
  u32 family = reg[0] >> 8 & 15;
  u32 modelEx = reg[0] >> 16 & 15;
  u32 model = (reg[0] >> 4) & 15;
  u32 stepping = reg[0] & 15;
  this->view.ID = (this->view.vendor << 24) + ((familyEx + family) << 16) +
         ((model + (modelEx << 4)) << 8) + stepping;
  lookupChannelInfos();
  return *this;
}

const LoadStoreChannel &
Microarchitecture::getLoadChannelInfo(const size BytesToLoad) const noexcept {
  i32 left = 0;
  i32 right = this->view.loadChannelCount - 1;
  while (left < right) {
    f32 mf= (left + right) / 2.0f;
    size m = fastmath(mf).floor();
    if (this->loadChannels[m].byteWidth > BytesToLoad) {
      left = m + 1;
    } else {
      right = m;
    }
  }
  return this->loadChannels[left];
}

const LoadStoreChannel &
Microarchitecture::getStoreChannelInfo(const size BytesToStore) const noexcept {
  i32 left = 0;
  i32 right = this->view.storeChannelCount - 1;
  while (left < right) {
      f32 mf = (left + right) / 2.0f;
      size m = fastmath(mf).floor();
    if (this->storeChannels[m].byteWidth > BytesToStore) {
      left = m + 1;
    } else {
      right = m;
    }
  }
  return this->storeChannels[left];
}

template <size N>
inline bool Microarchitecture::isMicroArchitecture(const u32(&Value)[N]) {
    bool result = false;
    for (auto i = 0; i < N; ++i) {
        if (this->view.ID == Value[i]) {
            result = true;
            break;
        }
    }
    return result;
}

void Microarchitecture::lookupChannelInfos() noexcept {
  // 2xAVX load and 1xAVX store channel
  LoadStoreChannel Load2x32B[] = {{32, 2}};
  LoadStoreChannel Store1x32B[] = {{32, 1}};
  if (isMicroArchitecture(MicroarchitectureID::Intel::CoffeeLake)) {
    this->view.loadChannelCount = sizeof(Load2x32B) / sizeof(LoadStoreChannel);
    this->view.storeChannelCount =
        sizeof(Store1x32B) / sizeof(LoadStoreChannel);
    this->loadChannels = Load2x32B;
    this->storeChannels = Store1x32B;
  }
}

} // namespace rf

rf::u8 getVendorID() noexcept {
  rf::u8 result = rf::VendorID::Unknown;
  rf::i32 reg[4];
  // reg[0] == max supported standard level for cpuid call
  // reg[1] == first 4 bytes of vendor string
  // reg[2] == last 4 bytes of vendor string
  // reg[3] == next 4 bytes of vendor string
  rf::cpuid(0, 0, reg);
  if (reg[1] == 'uneG' && reg[3] == 'Ieni' && reg[2] == 'letn') {
    result = rf::VendorID::Intel;
  }
  if (reg[1] == 'htuA' && reg[3] == 'itne' && reg[2] == 'DMAc') {
    result = rf::VendorID::AMD;
  }
  return result;
}