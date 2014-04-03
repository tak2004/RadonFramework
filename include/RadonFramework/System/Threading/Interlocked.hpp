#ifndef RF_SYSTEM_THREADING_INTERLOCKED_HPP
#define RF_SYSTEM_THREADING_INTERLOCKED_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace System
    {
        namespace Threading
        {
            struct Interlocked
            {
                // Arithmetical operations
                /// Performs a atomic increase operation.
                static RFTYPE::Int16 InterlockedInc16(
                    RFTYPE::Int16 volatile* Addend);

                /// Performs a atomic increase operation.
                static RFTYPE::Int32 InterlockedInc32(
                    RFTYPE::Int32 volatile* Addend);

                /// Performs a atomic increase operation.
                static RFTYPE::Int64 InterlockedInc64(
                    RFTYPE::Int64 volatile* Addend);

                /// Performs a atomic decrease operation.
                static RFTYPE::Int16 InterlockedDec16(
                    RFTYPE::Int16 volatile* Addend);

                /// Performs a atomic decrease operation.
                static RFTYPE::Int32 InterlockedDec32(
                    RFTYPE::Int32 volatile* Addend);

                /// Performs a atomic decrease operation.
                static RFTYPE::Int64 InterlockedDec64(
                    RFTYPE::Int64 volatile* Addend);

                /// Performs a atomic addition operation.
                static RFTYPE::Int16 InterlockedAdd16(
                    RFTYPE::Int16 volatile* Addend,
                    RFTYPE::Int16 Value);

                /// Performs a atomic addition operation.
                static RFTYPE::Int32 InterlockedAdd32(
                    RFTYPE::Int32 volatile* Addend,
                    RFTYPE::Int32 Value);

                /// Performs a atomic addition operation.
                static RFTYPE::Int64 InterlockedAdd64(
                    RFTYPE::Int64 volatile* Addend,
                    RFTYPE::Int32 Value);

                // Logical operations
                /// Performs an atomic AND operation on the specified Int8 values.
                static RFTYPE::Int8 InterlockedAnd8(
                    RFTYPE::Int8 volatile* Destination, 
                    RFTYPE::Int8 Value);

                /// Performs an atomic AND operation on the specified Int16 values.
                static RFTYPE::Int16 InterlockedAnd16(
                    RFTYPE::Int16 volatile* Destination, 
                    RFTYPE::Int16 Value);

                /// Performs an atomic AND operation on the specified Int32 values.
                static RFTYPE::Int32 InterlockedAnd32(
                    RFTYPE::Int32 volatile* Destination, 
                    RFTYPE::Int32 Value);

                /// Performs an atomic AND operation on the specified Int64 values.
                static RFTYPE::Int64 InterlockedAnd64(
                    RFTYPE::Int64 volatile* Destination, 
                    RFTYPE::Int64 Value);

                /// Performs an atomic OR operation on the specified Int8 values.
                static RFTYPE::Int8 InterlockedOr8(
                    RFTYPE::Int8 volatile* Destination, 
                    RFTYPE::Int8 Value);

                /// Performs an atomic OR operation on the specified Int16 values.
                static RFTYPE::Int16 InterlockedOr16(
                    RFTYPE::Int16 volatile* Destination, 
                    RFTYPE::Int16 Value);

                /// Performs an atomic OR operation on the specified Int32 values.
                static RFTYPE::Int32 InterlockedOr32(
                    RFTYPE::Int32 volatile* Destination, 
                    RFTYPE::Int32 Value);

                /// Performs an atomic OR operation on the specified Int64 values.
                static RFTYPE::Int64 InterlockedOr64(
                    RFTYPE::Int64 volatile* Destination, 
                    RFTYPE::Int64 Value);

                /// Performs an atomic XOR operation on the specified Int8 values.
                static RFTYPE::Int8 InterlockedXor8(
                    RFTYPE::Int8 volatile* Destination, 
                    RFTYPE::Int8 Value);

                /// Performs an atomic XOR operation on the specified Int16 values.
                static RFTYPE::Int16 InterlockedXor16(
                    RFTYPE::Int16 volatile* Destination, 
                    RFTYPE::Int16 Value);

                /// Performs an atomic XOR operation on the specified Int32 values.
                static RFTYPE::Int32 InterlockedXor32(
                    RFTYPE::Int32 volatile* Destination, 
                    RFTYPE::Int32 Value);

                /// Performs an atomic XOR operation on the specified Int64 values.
                static RFTYPE::Int64 InterlockedXor64(
                    RFTYPE::Int64 volatile* Destination, 
                    RFTYPE::Int64 Value);

                // Multi operations
                /** 
                * Performs an atomic compare-and-exchange operation on the 
                * specified values. The function compares two specified 32-bit 
                * values and exchanges with another 32-bit value based on the 
                * outcome of the comparison.
                **/
                static RFTYPE::Int16 InterlockedCompareExchange16(
                    RFTYPE::Int16 volatile* Destination, 
                    RFTYPE::Int16 Exchange, RFTYPE::Int16 Comparand);

                /** 
                * Performs an atomic compare-and-exchange operation on the 
                * specified values. The function compares two specified 32-bit 
                * values and exchanges with another 32-bit value based on the 
                * outcome of the comparison.
                **/
                static RFTYPE::Int32 InterlockedCompareExchange32(
                    RFTYPE::Int32 volatile* Destination, 
                    RFTYPE::Int32 Exchange, RFTYPE::Int32 Comparand);

                /** 
                * Performs an atomic compare-and-exchange operation on the 
                * specified values. The function compares two specified 64-bit 
                * values and exchanges with another 64-bit value based on the 
                * outcome of the comparison.
                **/
                static RFTYPE::Int64 InterlockedCompareExchange64(
                    RFTYPE::Int64 volatile* Destination, 
                    RFTYPE::Int64 Exchange, RFTYPE::Int64 Comparand);

                /**
                * Performs an atomic compare-and-exchange operation on the 
                * specified values. The function compares two specified pointer
                * values and exchanges with another pointer value based on the 
                * outcome of the comparison.
                **/
                static void* InterlockedCompareExchangePointer(
                    void* volatile* Destination, void* Exchange, void* Comparand);

                /// Sets a 32-bit variable to the specified value as an atomic operation.
                static RFTYPE::Int32 InterlockedExchange32(
                    RFTYPE::Int32 volatile* Target, RFTYPE::Int32 Value);

                /// Sets a 64-bit variable to the specified value as an atomic operation.
                static RFTYPE::Int64 InterlockedExchange64(
                    RFTYPE::Int64 volatile* Target, RFTYPE::Int64 Value);

                /// Atomically exchanges a pair of addresses.
                static void* InterlockedExchangePointer(
                    void* volatile* Target, void* Value);
            };
        }
    }    
}

#endif // RF_SYSTEM_THREADING_INTERLOCKED_HPP
