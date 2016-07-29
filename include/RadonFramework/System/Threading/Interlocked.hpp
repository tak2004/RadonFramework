#ifndef RF_SYSTEM_THREADING_INTERLOCKED_HPP
#define RF_SYSTEM_THREADING_INTERLOCKED_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Int8.hpp>
#include <RadonFramework/Core/Types/Int16.hpp>
#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/Int64.hpp>

namespace RadonFramework { namespace System { namespace Threading {

struct Interlocked
{
    // Arithmetical operations
    /// Performs a atomic increase operation.
    static RF_Type::Int16 InterlockedInc16(
        RF_Type::Int16 volatile* Addend);

    /// Performs a atomic increase operation.
    static RF_Type::Int32 InterlockedInc32(
        RF_Type::Int32 volatile* Addend);

    /// Performs a atomic increase operation.
    static RF_Type::Int64 InterlockedInc64(
        RF_Type::Int64 volatile* Addend);

    /// Performs a atomic decrease operation.
    static RF_Type::Int16 InterlockedDec16(
        RF_Type::Int16 volatile* Addend);

    /// Performs a atomic decrease operation.
    static RF_Type::Int32 InterlockedDec32(
        RF_Type::Int32 volatile* Addend);

    /// Performs a atomic decrease operation.
    static RF_Type::Int64 InterlockedDec64(
        RF_Type::Int64 volatile* Addend);

    /// Performs a atomic addition operation.
    static RF_Type::Int16 InterlockedAdd16(
        RF_Type::Int16 volatile* Addend,
        RF_Type::Int16 Value);

    /// Performs a atomic addition operation.
    static RF_Type::Int32 InterlockedAdd32(
        RF_Type::Int32 volatile* Addend,
        RF_Type::Int32 Value);

    /// Performs a atomic addition operation.
    static RF_Type::Int64 InterlockedAdd64(
        RF_Type::Int64 volatile* Addend,
        RF_Type::Int64 Value);

    // Logical operations
    /// Performs an atomic AND operation on the specified Int8 values.
    static RF_Type::Int8 InterlockedAnd8(
        RF_Type::Int8 volatile* Destination, 
        RF_Type::Int8 Value);

    /// Performs an atomic AND operation on the specified Int16 values.
    static RF_Type::Int16 InterlockedAnd16(
        RF_Type::Int16 volatile* Destination, 
        RF_Type::Int16 Value);

    /// Performs an atomic AND operation on the specified Int32 values.
    static RF_Type::Int32 InterlockedAnd32(
        RF_Type::Int32 volatile* Destination, 
        RF_Type::Int32 Value);

    /// Performs an atomic AND operation on the specified Int64 values.
    static RF_Type::Int64 InterlockedAnd64(
        RF_Type::Int64 volatile* Destination, 
        RF_Type::Int64 Value);

    /// Performs an atomic OR operation on the specified Int8 values.
    static RF_Type::Int8 InterlockedOr8(
        RF_Type::Int8 volatile* Destination, 
        RF_Type::Int8 Value);

    /// Performs an atomic OR operation on the specified Int16 values.
    static RF_Type::Int16 InterlockedOr16(
        RF_Type::Int16 volatile* Destination, 
        RF_Type::Int16 Value);

    /// Performs an atomic OR operation on the specified Int32 values.
    static RF_Type::Int32 InterlockedOr32(
        RF_Type::Int32 volatile* Destination, 
        RF_Type::Int32 Value);

    /// Performs an atomic OR operation on the specified Int64 values.
    static RF_Type::Int64 InterlockedOr64(
        RF_Type::Int64 volatile* Destination, 
        RF_Type::Int64 Value);

    /// Performs an atomic XOR operation on the specified Int8 values.
    static RF_Type::Int8 InterlockedXor8(
        RF_Type::Int8 volatile* Destination, 
        RF_Type::Int8 Value);

    /// Performs an atomic XOR operation on the specified Int16 values.
    static RF_Type::Int16 InterlockedXor16(
        RF_Type::Int16 volatile* Destination, 
        RF_Type::Int16 Value);

    /// Performs an atomic XOR operation on the specified Int32 values.
    static RF_Type::Int32 InterlockedXor32(
        RF_Type::Int32 volatile* Destination, 
        RF_Type::Int32 Value);

    /// Performs an atomic XOR operation on the specified Int64 values.
    static RF_Type::Int64 InterlockedXor64(
        RF_Type::Int64 volatile* Destination, 
        RF_Type::Int64 Value);

    // Multi operations
    /** 
    * Performs an atomic compare-and-exchange operation on the 
    * specified values. The function compares two specified 32-bit 
    * values and exchanges with another 32-bit value based on the 
    * outcome of the comparison.
    **/
    static RF_Type::Int16 InterlockedCompareExchange16(
        RF_Type::Int16 volatile* Destination, 
        RF_Type::Int16 Exchange, RF_Type::Int16 Comparand);

    /** 
    * Performs an atomic compare-and-exchange operation on the 
    * specified values. The function compares two specified 32-bit 
    * values and exchanges with another 32-bit value based on the 
    * outcome of the comparison.
    **/
    static RF_Type::Int32 InterlockedCompareExchange32(
        RF_Type::Int32 volatile* Destination, 
        RF_Type::Int32 Exchange, RF_Type::Int32 Comparand);

    /** 
    * Performs an atomic compare-and-exchange operation on the 
    * specified values. The function compares two specified 64-bit 
    * values and exchanges with another 64-bit value based on the 
    * outcome of the comparison.
    **/
    static RF_Type::Int64 InterlockedCompareExchange64(
        RF_Type::Int64 volatile* Destination, 
        RF_Type::Int64 Exchange, RF_Type::Int64 Comparand);

    /**
    * Performs an atomic compare-and-exchange operation on the 
    * specified values. The function compares two specified pointer
    * values and exchanges with another pointer value based on the 
    * outcome of the comparison.
    **/
    static void* InterlockedCompareExchangePointer(
        void* volatile* Destination, void* Exchange, void* Comparand);

    /// Sets a 32-bit variable to the specified value as an atomic operation.
    static RF_Type::Int32 InterlockedExchange32(
        RF_Type::Int32 volatile* Target, RF_Type::Int32 Value);

    /// Sets a 64-bit variable to the specified value as an atomic operation.
    static RF_Type::Int64 InterlockedExchange64(
        RF_Type::Int64 volatile* Target, RF_Type::Int64 Value);

    /// Atomically exchanges a pair of addresses.
    static void* InterlockedExchangePointer(
        void* volatile* Target, void* Value);
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_SYSTHREAD
#define RF_SHORTHAND_NAMESPACE_SYSTHREAD
namespace RF_SysThread = RadonFramework::System::Threading;
#endif

#endif // RF_SYSTEM_THREADING_INTERLOCKED_HPP
