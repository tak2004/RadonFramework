#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Threading/Interlocked.hpp"

#if defined(RF_VISUALCPP)
    #include <intrin.h>
    #pragma intrinsic(_InterlockedIncrement16)
    #pragma intrinsic(_InterlockedIncrement)
    #pragma intrinsic(_InterlockedIncrement64)
    #pragma intrinsic(_InterlockedDecrement16)
    #pragma intrinsic(_InterlockedDecrement)
    #pragma intrinsic(_InterlockedDecrement64)
    #pragma intrinsic(_InterlockedExchangeAdd16)
    #pragma intrinsic(_InterlockedExchangeAdd)
    #pragma intrinsic(_InterlockedExchangeAdd64)
    #pragma intrinsic(_InterlockedAnd8)
    #pragma intrinsic(_InterlockedAnd16)
    #pragma intrinsic(_InterlockedAnd)
    #pragma intrinsic(_InterlockedAnd64)
    #pragma intrinsic(_InterlockedOr8)
    #pragma intrinsic(_InterlockedOr16)
    #pragma intrinsic(_InterlockedOr)
    #pragma intrinsic(_InterlockedOr64)
    #pragma intrinsic(_InterlockedXor8)
    #pragma intrinsic(_InterlockedXor16)
    #pragma intrinsic(_InterlockedXor)
    #pragma intrinsic(_InterlockedXor64)
    #pragma intrinsic(_InterlockedCompareExchange16)
    #pragma intrinsic(_InterlockedCompareExchange)
    #pragma intrinsic(_InterlockedCompareExchange64)
    #pragma intrinsic(_InterlockedCompareExchangePointer)
    #pragma intrinsic(_InterlockedExchange16)
    #pragma intrinsic(_InterlockedExchange)
    #pragma intrinsic(_InterlockedExchange64)
    #pragma intrinsic(_InterlockedExchangePointer)
#endif

using namespace RadonFramework::System::Threading;
using namespace RadonFramework::Core::Types;

Int16 Interlocked::InterlockedInc16(Int16 volatile* Addend)
{
#if defined(RF_VISUALCPP)
    return _InterlockedIncrement16((short volatile*)Addend);
#elif defined(RF_GCC)
    return __sync_fetch_and_add(Addend,1)+1;
#else
#endif
}

Int32 Interlocked::InterlockedInc32(Int32 volatile* Addend)
{
#if defined(RF_VISUALCPP)
    return _InterlockedIncrement((long volatile*)Addend);
#elif defined(RF_GCC)
    return __sync_fetch_and_add(Addend,1)+1;
#else
#endif
}

Int64 Interlocked::InterlockedInc64(Int64 volatile* Addend)
{
#if defined(RF_VISUALCPP)
    #if defined(RF_64BIT)
        return _InterlockedIncrement64((__int64 volatile*)Addend);
    #else
        RF_COMPILER_WARNING("Really bad idea to use it on 32Bit");
        return -1;
    #endif
#elif defined(RF_GCC)
    return __sync_fetch_and_add(Addend,1)+1;
#else
#endif
}

Int16 Interlocked::InterlockedDec16(Int16 volatile* Addend)
{
#if defined(RF_VISUALCPP)
    return _InterlockedDecrement16((short volatile*)Addend);
#elif defined(RF_GCC)
    return __sync_fetch_and_sub(Addend,1)-1;
#else
#endif
}

Int32 Interlocked::InterlockedDec32(Int32 volatile* Addend)
{
#if defined(RF_VISUALCPP)
    return _InterlockedDecrement((long volatile*)Addend);
#elif defined(RF_GCC)
    return __sync_fetch_and_sub(Addend,1)-1;
#else
#endif
}

Int64 Interlocked::InterlockedDec64(Int64 volatile* Addend)
{
#if defined(RF_VISUALCPP)
    #if defined(RF_64BIT)
        return _InterlockedDecrement64((__int64 volatile*)Addend);
    #else
        RF_COMPILER_WARNING("Really bad idea to use it on 32Bit");
        return -1;
    #endif
#elif defined(RF_GCC)
    return __sync_fetch_and_sub(Addend,1)-1;
#else
#endif
}

Int16 Interlocked::InterlockedAdd16(Int16 volatile* Addend, Int16 Value)
{
#if defined(RF_VISUALCPP)
    return _InterlockedExchangeAdd16((short volatile*)Addend, (short)Value);
#elif defined(RF_GCC)
    return __sync_fetch_and_add(Addend,Value);
#else
#endif
}

Int32 Interlocked::InterlockedAdd32(Int32 volatile* Addend, Int32 Value)
{
#if defined(RF_VISUALCPP)
    return _InterlockedExchangeAdd((long volatile*)Addend, (long)Value);
#elif defined(RF_GCC)
    return __sync_fetch_and_add(Addend,Value);
#else
#endif
}

Int64 Interlocked::InterlockedAdd64(Int64 volatile* Addend,Int64 Value)
{
#if defined(RF_VISUALCPP)
    #if defined(RF_64BIT)
    return _InterlockedExchangeAdd64((__int64 volatile*)Addend, (long long)Value);
    #else
        RF_COMPILER_WARNING("Really bad idea to use it on 32Bit");
        return -1;
    #endif
#elif defined(RF_GCC)
    return __sync_fetch_and_add(Addend,Value);
#else
#endif
}

Int8 Interlocked::InterlockedAnd8(Int8 volatile* Destination,Int8 Value)
{
#if defined(RF_VISUALCPP)
    return _InterlockedAnd8(reinterpret_cast<volatile char*>(Destination),(char)Value);
#elif defined(RF_GCC)
    return __sync_fetch_and_and(Destination,Value);
#else
#endif
}

Int16 Interlocked::InterlockedAnd16(Int16 volatile* Destination, Int16 Value)
{
#if defined(RF_VISUALCPP)
    return _InterlockedAnd16((short volatile*)Destination,(short)Value);
#elif defined(RF_GCC)
    return __sync_fetch_and_and(Destination,Value);
#else
#endif
}

Int32 Interlocked::InterlockedAnd32(Int32 volatile* Destination, Int32 Value)
{
#if defined(RF_VISUALCPP)
    return _InterlockedAnd((long volatile*)Destination,(long)Value);
#elif defined(RF_GCC)
    return __sync_fetch_and_and(Destination,Value);
#else
#endif
}

Int64 Interlocked::InterlockedAnd64(Int64 volatile* Destination, Int64 Value)
{
#if defined(RF_VISUALCPP)
    #if defined(RF_64BIT)
        return _InterlockedAnd64((__int64 volatile*)Destination,(__int64)Value);
    #else
        RF_COMPILER_WARNING("Really bad idea to use it on 32Bit");
        return -1;
    #endif
#elif defined(RF_GCC)
    return __sync_fetch_and_and(Destination,Value);
#else
    RF_COMPILER_WARNING("You are the happy one who can implement this feature");
    return -1;
#endif
}

Int8 Interlocked::InterlockedOr8(Int8 volatile* Destination, Int8 Value)
{
#if defined(RF_VISUALCPP)
    return _InterlockedOr8(reinterpret_cast<volatile char*>(Destination),(char)Value);
#elif defined(RF_GCC)
    return __sync_fetch_and_or(Destination, Value);
#else
#endif    
}

Int16 Interlocked::InterlockedOr16(Int16 volatile* Destination, Int16 Value)
{
#if defined(RF_VISUALCPP)
    return _InterlockedOr16((short volatile*)Destination,(short)Value);
#elif defined(RF_GCC)
    return __sync_fetch_and_or(Destination, Value);
#else
#endif 
}

Int32 Interlocked::InterlockedOr32(Int32 volatile* Destination, Int32 Value)
{
#if defined(RF_VISUALCPP)
    return _InterlockedOr((long volatile*)Destination,(long)Value);
#elif defined(RF_GCC)
    return __sync_fetch_and_or(Destination, Value);
#else
#endif 
}

Int64 Interlocked::InterlockedOr64(Int64 volatile* Destination, Int64 Value)
{
#if defined(RF_VISUALCPP)
    #if defined(RF_64BIT)
        return _InterlockedOr64((__int64 volatile*)Destination,(__int64)Value);
    #else
        RF_COMPILER_WARNING("Really bad idea to use it on 32Bit");
        return -1;
    #endif
#elif defined(RF_GCC)
    return __sync_fetch_and_or(Destination, Value);
#else
#endif 
}

Int8 Interlocked::InterlockedXor8(Int8 volatile* Destination, Int8 Value)
{
#if defined(RF_VISUALCPP)
    return _InterlockedXor8(reinterpret_cast<volatile char*>(Destination),(char)Value);
#elif defined(RF_GCC)
    return __sync_fetch_and_xor(Destination, Value);
#else
#endif 
}

Int16 Interlocked::InterlockedXor16(Int16 volatile* Destination, Int16 Value)
{
#if defined(RF_VISUALCPP)
    return _InterlockedXor16((short volatile*)Destination,(short)Value);
#elif defined(RF_GCC)
    return __sync_fetch_and_xor(Destination, Value);
#else
#endif 
}

Int32 Interlocked::InterlockedXor32(Int32 volatile* Destination, Int32 Value)
{
#if defined(RF_VISUALCPP)
    return _InterlockedXor((long volatile*)Destination,(long)Value);
#elif defined(RF_GCC)
    return __sync_fetch_and_xor(Destination, Value);
#else
#endif 
}

Int64 Interlocked::InterlockedXor64(Int64 volatile* Destination, Int64 Value)
{
#if defined(RF_VISUALCPP)
    #if defined(RF_64BIT)
        return _InterlockedXor64((__int64 volatile*)Destination,(__int64)Value);
    #else
        RF_COMPILER_WARNING("Really bad idea to use it on 32Bit");
        return -1;
    #endif
#elif defined(RF_GCC)
    return __sync_fetch_and_xor(Destination, Value);
#else
#endif 
}

Int16 Interlocked::InterlockedCompareExchange16(volatile Int16 *Destination,
                                                         Int16 Exchange, 
                                                         Int16 Comparand)
{
#if defined(RF_VISUALCPP)
    return _InterlockedCompareExchange16((short volatile*)Destination,(short)Exchange,(short)Comparand);
#elif defined(RF_GCC)
    return __sync_val_compare_and_swap(Destination,Exchange,Comparand);
#else
#endif 
}

Int32 Interlocked::InterlockedCompareExchange32(volatile Int32 *Destination,
                                                         Int32 Exchange, 
                                                         Int32 Comparand)
{
#if defined(RF_VISUALCPP)
    return _InterlockedCompareExchange((long volatile*)Destination,(long)Exchange,(long)Comparand);
#elif defined(RF_GCC)
    return __sync_val_compare_and_swap(Destination,Exchange,Comparand);
#else
#endif 
}

Int64 Interlocked::InterlockedCompareExchange64(volatile Int64 *Destination, 
                                                         Int64 Exchange, 
                                                         Int64 Comparand)
{
#if defined(RF_VISUALCPP)
    return _InterlockedCompareExchange64((__int64 volatile*)Destination,(__int64)Exchange,(__int64)Comparand);
#elif defined(RF_GCC)
    return __sync_val_compare_and_swap(Destination,Exchange,Comparand);
#else
#endif 
}

void* Interlocked::InterlockedCompareExchangePointer(void* volatile* Destination, 
                                                              void* Exchange,
                                                              void* Comparand)
{
#if defined(RF_VISUALCPP)
    #if defined(RF_64BIT)
        return _InterlockedCompareExchangePointer((void* volatile*)Destination,Exchange,Comparand);
    #else
        return reinterpret_cast<void*>(_InterlockedCompareExchange(reinterpret_cast<volatile long*>(Destination),
            reinterpret_cast<long>(Exchange),
            reinterpret_cast<long>(Comparand)));
    #endif
#elif defined(RF_GCC)
    return __sync_val_compare_and_swap(Destination,Exchange,Comparand);
#else
#endif
}

Int16 Interlocked::InterlockedExchange16(Int16 volatile* Target, Int16 Value)
{
#if defined(RF_VISUALCPP)
  return _InterlockedExchange16((short*)Target, (short)Value);
#elif defined(RF_GCC)
  return __sync_lock_test_and_set(Target, Value);
#else
#endif
}

Int32 Interlocked::InterlockedExchange32(Int32 volatile* Target, Int32 Value)
{
#if defined(RF_VISUALCPP)
    return _InterlockedExchange((long*)Target,(long)Value);
#elif defined(RF_GCC)
    return __sync_lock_test_and_set(Target,Value);
#else
#endif
}

Int64 Interlocked::InterlockedExchange64(Int64 volatile* Target, Int64 Value)
{
#if defined(RF_VISUALCPP)
    #if defined(RF_64BIT)
        return _InterlockedExchange64((__int64*)Target,(__int64)Value);
    #else
        RF_COMPILER_WARNING("Really bad idea to use it on 32Bit");
        return -1;
    #endif
#elif defined(RF_GCC)
    return __sync_lock_test_and_set(Target,Value);
#else
#endif
}

void* Interlocked::InterlockedExchangePointer(void* volatile* Target, 
                                              void* Value)
{
#if defined(RF_VISUALCPP)
    #if defined(RF_64BIT)
        return _InterlockedExchangePointer((void* volatile *)Target,(void*)Value);
    #else
        return reinterpret_cast<void*>(_InterlockedExchange(reinterpret_cast<volatile long*>(Target),
            reinterpret_cast<long>(Value)));
    #endif

#elif defined(RF_GCC)
    return __sync_lock_test_and_set(Target,Value);
#else
#endif
}
