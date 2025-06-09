module;
#include <Windows.h>
#include <intrin.h>
#include <profileapi.h>
#include <winnt.h>
#pragma intrinsic(_InterlockedExchangePointer)
#pragma intrinsic(_InterlockedIncrement16)
#pragma intrinsic(_InterlockedIncrement)
#pragma intrinsic(_InterlockedIncrement64)
#pragma intrinsic(_InterlockedDecrement16)
#pragma intrinsic(_InterlockedDecrement)
#pragma intrinsic(_InterlockedDecrement64)
#pragma intrinsic(_InterlockedExchangeAdd16)
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(_InterlockedExchangeAdd64)
#pragma intrinsic(_InterlockedCompareExchange16)
#pragma intrinsic(_InterlockedCompareExchange)
#pragma intrinsic(_InterlockedCompareExchange64)
#pragma intrinsic(_InterlockedCompareExchangePointer)
#pragma intrinsic(_InterlockedExchange16)
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_InterlockedExchange64)

export module rf.core.cpu:intrinsics;
import rf.core.types;
// An abstraction layer to the CPU intrinsics of the current processor
// architecture. The functions are used by higher level code to optimize code.

export namespace rf {

/// <summary>
/// This function stores the current value of the specified Target
/// and exchange it by the specified Value.
/// This happens in one step without interfering of other operation processor or
/// threads.
/// </summary>
/// <param name="Target">A pointer to a memory address which isn't allowed to be
/// cached.</param> <param name="Value">The new memory address which should be
/// stored at the Target.</param> <returns>The memory address value which was
/// replaced by the new Value.</returns>
ptr fetchAndExchange(ptr volatile *Target, ptr Value);
i16 fetchAndExchange(i16 volatile *Target, i16 Value);
u16 fetchAndExchange(u16 volatile *Target, u16 Value);
i32 fetchAndExchange(i32 volatile *Target, i32 Value);
u32 fetchAndExchange(u32 volatile *Target, u32 Value);
i64 fetchAndExchange(i64 volatile *Target, i64 Value);
u64 fetchAndExchange(u64 volatile *Target, u64 Value);

/// <summary>
/// This function increase a 16bit integer by one.
/// </summary>
/// <param name="Addend">The atomic 16bit integer to increment by one.</param>
/// <returns></returns>
i16 increase(i16 volatile *Addend);
u16 increase(u16 volatile *Addend);
/// <summary>
/// This function increase a 32bit integer by one.
/// </summary>
/// <param name="Addend">The atomic 32bit integer to increment by one.</param>
/// <returns></returns>
i32 increase(i32 volatile *Addend);
u32 increase(u32 volatile *Addend);
/// <summary>
/// This function increase a 64bit integer by one.
/// </summary>
/// <param name="Addend">The atomic 64bit integer to increment by one.</param>
/// <returns></returns>
i64 increase(i64 volatile *Addend);
u64 increase(u64 volatile *Addend);

/// <summary>
/// This function decrease a 16bit integer by one.
/// </summary>
/// <param name="Addend">The atomic 16bit integer to decrement by one.</param>
/// <returns></returns>
i16 decrease(i16 volatile *Minuend);
u16 decrease(u16 volatile *Minuend);
/// <summary>
/// This function decrease a 32bit integer by one.
/// </summary>
/// <param name="Addend">The atomic 32bit integer to decrement by one.</param>
/// <returns></returns>
i32 decrease(i32 volatile *Minuend);
u32 decrease(u32 volatile *Minuend);
/// <summary>
/// This function decrease a 64bit integer by one.
/// </summary>
/// <param name="Addend">The atomic 64bit integer to decrement by one.</param>
/// <returns></returns>
i64 decrease(i64 volatile *Minuend);
u64 decrease(u64 volatile *Minuend);

i16 fetchAndAdd(i16 volatile *Addend1, i16 Addend2);
i32 fetchAndAdd(i32 volatile *Addend1, i32 Addend2);
i64 fetchAndAdd(i64 volatile *Addend1, i64 Addend2);
u16 fetchAndAdd(u16 volatile *Addend1, u16 Addend2);
u32 fetchAndAdd(u32 volatile *Addend1, u32 Addend2);
u64 fetchAndAdd(u64 volatile *Addend1, u64 Addend2);

ptr compareAndExchange(ptr volatile *Destination, ptr Exchange, ptr Comparand);
i16 compareAndExchange(i16 volatile *Destination, i16 Exchange, i16 Comperand);
i32 compareAndExchange(u16 volatile *Destination, u16 Exchange, u16 Comperand);
i64 compareAndExchange(i32 volatile *Destination, i32 Exchange, i32 Comperand);
u16 compareAndExchange(u32 volatile *Destination, u32 Exchange, u32 Comperand);
u32 compareAndExchange(i64 volatile *Destination, i64 Exchange, i64 Comperand);
u64 compareAndExchange(u64 volatile *Destination, u64 Exchange, u64 Comperand);

/// <summary>
/// This function will wait till all memory load and store operations are
/// complete till it will continue.
/// </summary>
void memoryFence();

/// <summary>
/// This function will wait till all memory load operations are complete till it
/// will continue.
/// </summary>
void loadFence();

/// <summary>
/// This function will wait till all memory store operations are complete till
/// it will continue.
/// </summary>
void storeFence();

void cpuid(i32 FunctionID, i32 SubFunctionID, i32 Output[4]);

// The conversion value to get the time in seconds.
u64 queryPerformanceFrequency();
// Current time value.
u64 queryPerformanceCounter();
// Fastest Radon Framework API to return a cpu timestamp and logical processor
// id.
u64 queryLogicalProcessorPerformanceCounter(u32 &TSC_AUX);

ptr fetchAndExchange(ptr volatile *Target, ptr Value) {
  return _InterlockedExchangePointer(Target, Value);
}

i16 fetchAndExchange(i16 volatile *Target, i16 Value) {
  return _InterlockedExchange16(Target, Value);
}

u16 fetchAndExchange(u16 volatile *Target, u16 Value) {
  return _InterlockedExchange16(reinterpret_cast<i16 volatile *>(Target),
                                Value);
}

i32 fetchAndExchange(i32 volatile *Target, i32 Value) {
  return _InterlockedExchange(reinterpret_cast<u32 volatile *>(Target), Value);
}

u32 fetchAndExchange(u32 volatile *Target, u32 Value) {
  return _InterlockedExchange(Target, Value);
}

i64 fetchAndExchange(i64 volatile *Target, i64 Value) {
  return _InterlockedExchange64(Target, Value);
}

u64 fetchAndExchange(u64 volatile *Target, u64 Value) {
  return _InterlockedExchange64(reinterpret_cast<i64 volatile *>(Target),
                                Value);
}

i16 increase(i16 volatile *Addend) { return _InterlockedIncrement16(Addend); }

u16 increase(u16 volatile *Addend) {
  return _InterlockedIncrement16(reinterpret_cast<i16 volatile *>(Addend));
}

i32 increase(i32 volatile *Addend) {
  return _InterlockedIncrement(reinterpret_cast<u32 volatile *>(Addend));
}

u32 increase(u32 volatile *Addend) { return _InterlockedIncrement(Addend); }

i64 increase(i64 volatile *Addend) { return _InterlockedIncrement64(Addend); }

u64 increase(u64 volatile *Addend) {
  return _InterlockedIncrement64(reinterpret_cast<i64 volatile *>(Addend));
}

i16 decrease(i16 volatile *Minuend) { return _InterlockedDecrement16(Minuend); }

u16 decrease(u16 volatile *Minuend) {
  return _InterlockedDecrement16(reinterpret_cast<i16 volatile *>(Minuend));
}

i32 decrease(i32 volatile *Minuend) {
  return _InterlockedDecrement(reinterpret_cast<u32 volatile *>(Minuend));
}

u32 decrease(u32 volatile *Minuend) { return _InterlockedDecrement(Minuend); }

i64 decrease(i64 volatile *Minuend) { return _InterlockedDecrement64(Minuend); }

u64 decrease(u64 volatile *Minuend) {
  return _InterlockedDecrement64(reinterpret_cast<i64 volatile *>(Minuend));
}

i16 fetchAndAdd(i16 volatile *Addend1, const i16 Addend2) {
  return _InterlockedExchangeAdd16(Addend1, Addend2);
}

i32 fetchAndAdd(i32 volatile *Addend1, const i32 Addend2) {
  return _InterlockedExchangeAdd(reinterpret_cast<u32 volatile *>(Addend1),
                                 static_cast<u32>(Addend2));
}

i64 fetchAndAdd(i64 volatile *Addend1, const i64 Addend2) {
  return _InterlockedExchangeAdd64(Addend1, Addend2);
}

u16 fetchAndAdd(u16 volatile *Addend1, const u16 Addend2) {
  return _InterlockedExchangeAdd16(reinterpret_cast<i16 volatile *>(Addend1),
                                   static_cast<i16>(Addend2));
}

u32 fetchAndAdd(u32 volatile *Addend1, const u32 Addend2) {
  return _InterlockedExchangeAdd(Addend1, Addend2);
}

u64 fetchAndAdd(u64 volatile *Addend1, const u64 Addend2) {
  return _InterlockedExchangeAdd64(reinterpret_cast<i64 volatile *>(Addend1),
                                   Addend2);
}

ptr compareAndExchange(ptr volatile *Destination, ptr Exchange, ptr Comparand) {
  return _InterlockedCompareExchangePointer(Destination, Exchange, Comparand);
}

i16 compareAndExchange(i16 volatile *Destination, i16 Exchange, i16 Comperand) {
  return _InterlockedCompareExchange16(Destination, Exchange, Comperand);
}

i32 compareAndExchange(u16 volatile *Destination, u16 Exchange, u16 Comperand) {
  return _InterlockedCompareExchange16(
      reinterpret_cast<i16 volatile *>(Destination), Exchange, Comperand);
}

i64 compareAndExchange(i32 volatile *Destination, i32 Exchange, i32 Comperand) {
  return _InterlockedCompareExchange(
      reinterpret_cast<u32 volatile *>(Destination), Exchange, Comperand);
}

u16 compareAndExchange(u32 volatile *Destination, u32 Exchange, u32 Comperand) {
  return _InterlockedCompareExchange(Destination, Exchange, Comperand);
}

u32 compareAndExchange(i64 volatile *Destination, i64 Exchange, i64 Comperand) {
  return _InterlockedCompareExchange64(Destination, Exchange, Comperand);
}

u64 compareAndExchange(u64 volatile *Destination, u64 Exchange, u64 Comperand) {
  return _InterlockedCompareExchange64(
      reinterpret_cast<i64 volatile *>(Destination), Exchange, Comperand);
}

void memoryFence() { _mm_mfence(); }

void loadFence() { _mm_lfence(); }

void storeFence() { _mm_sfence(); }

void cpuid(const i32 FunctionID, i32 SubFunctionID, i32 Output[4]) {
  __cpuidex(reinterpret_cast<int *>(Output), FunctionID, SubFunctionID);
}

u64 queryPerformanceFrequency() {
  static u64 frequency = []() {
    LARGE_INTEGER t;
    QueryPerformanceFrequency(&t);
    return t.QuadPart;
  }();
  return frequency;
}

u64 queryPerformanceCounter() {
  LARGE_INTEGER t;
  QueryPerformanceCounter(&t);
  return t.QuadPart;
}

u64 queryLogicalProcessorPerformanceCounter(u32 &TSC_AUX) {
  return __rdtscp(&TSC_AUX);
}



} // namespace rf