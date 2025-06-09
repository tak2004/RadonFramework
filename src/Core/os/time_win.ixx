module;
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>
export module rf.core.os:time;
import rf.core.types;

export namespace rf {
timeval getSystemTime();
timeval getMinutesWestOfGMT();
u64 getHighResolutionCounter();
u64 getHighResolutionCounterFrequency();
bool isHighResolutionCounterSupported();

timeval getSystemTime() { return ::GetTickCount64(); }

u64 getMinutesWestOfGMT() {
  TIME_ZONE_INFORMATION tz;
  if (::GetTimeZoneInformation(&tz) != TIME_ZONE_ID_INVALID) {
    return ((tz.Bias + (tz.Bias >> 31)) ^ (tz.Bias >> 31)) * 600000000LL;
  } else {
    return 0;
  }
}

u64 getHighResolutionCounter() {
  u64 result;
  if (::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER *>(&result))) {
  } else {
    result = ::GetTickCount64();
  }
  return result;
}

u64 getHighResolutionCounterFrequency() {
  LARGE_INTEGER frequency;
  if (::QueryPerformanceFrequency(&frequency)) {
  } else {
    frequency.QuadPart = 10000000;
  }
  return frequency.QuadPart;
}

bool isHighResolutionCounterSupported() {
  i64 tmp;
  return ::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER *>(&tmp)) !=
         0;
}
} // namespace rf
