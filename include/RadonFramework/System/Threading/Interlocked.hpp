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
                static Core::Types::Int16 InterlockedInc16(
                    Core::Types::Int16 volatile* Addend);

                /// Performs a atomic increase operation.
                static Core::Types::Int32 InterlockedInc32(
                    Core::Types::Int32 volatile* Addend);

                /// Performs a atomic increase operation.
                static Core::Types::Int64 InterlockedInc64(
                    Core::Types::Int64 volatile* Addend);

                /// Performs a atomic decrease operation.
                static Core::Types::Int16 InterlockedDec16(
                    Core::Types::Int16 volatile* Addend);

                /// Performs a atomic decrease operation.
                static Core::Types::Int32 InterlockedDec32(
                    Core::Types::Int32 volatile* Addend);

                /// Performs a atomic decrease operation.
                static Core::Types::Int64 InterlockedDec64(
                    Core::Types::Int64 volatile* Addend);

                /// Performs a atomic addition operation.
                static Core::Types::Int16 InterlockedAdd16(
                    Core::Types::Int16 volatile* Addend,
                    Core::Types::Int16 Value);

                /// Performs a atomic addition operation.
                static Core::Types::Int32 InterlockedAdd32(
                    Core::Types::Int32 volatile* Addend,
                    Core::Types::Int32 Value);

                /// Performs a atomic addition operation.
                static Core::Types::Int64 InterlockedAdd64(
                    Core::Types::Int64 volatile* Addend,
                    Core::Types::Int32 Value);

                // Logical operations
                /// Performs an atomic AND operation on the specified Int8 values.
                static Core::Types::Int8 InterlockedAnd8(
                    Core::Types::Int8 volatile* Destination, 
                    Core::Types::Int8 Value);

                /// Performs an atomic AND operation on the specified Int16 values.
                static Core::Types::Int16 InterlockedAnd16(
                    Core::Types::Int16 volatile* Destination, 
                    Core::Types::Int16 Value);

                /// Performs an atomic AND operation on the specified Int32 values.
                static Core::Types::Int32 InterlockedAnd32(
                    Core::Types::Int32 volatile* Destination, 
                    Core::Types::Int32 Value);

                /// Performs an atomic AND operation on the specified Int64 values.
                static Core::Types::Int64 InterlockedAnd64(
                    Core::Types::Int64 volatile* Destination, 
                    Core::Types::Int64 Value);

                /// Performs an atomic OR operation on the specified Int8 values.
                static Core::Types::Int8 InterlockedOr8(
                    Core::Types::Int8 volatile* Destination, 
                    Core::Types::Int8 Value);

                /// Performs an atomic OR operation on the specified Int16 values.
                static Core::Types::Int16 InterlockedOr16(
                    Core::Types::Int16 volatile* Destination, 
                    Core::Types::Int16 Value);

                /// Performs an atomic OR operation on the specified Int32 values.
                static Core::Types::Int32 InterlockedOr32(
                    Core::Types::Int32 volatile* Destination, 
                    Core::Types::Int32 Value);

                /// Performs an atomic OR operation on the specified Int64 values.
                static Core::Types::Int64 InterlockedOr64(
                    Core::Types::Int64 volatile* Destination, 
                    Core::Types::Int64 Value);

                /// Performs an atomic XOR operation on the specified Int8 values.
                static Core::Types::Int8 InterlockedXor8(
                    Core::Types::Int8 volatile* Destination, 
                    Core::Types::Int8 Value);

                /// Performs an atomic XOR operation on the specified Int16 values.
                static Core::Types::Int16 InterlockedXor16(
                    Core::Types::Int16 volatile* Destination, 
                    Core::Types::Int16 Value);

                /// Performs an atomic XOR operation on the specified Int32 values.
                static Core::Types::Int32 InterlockedXor32(
                    Core::Types::Int32 volatile* Destination, 
                    Core::Types::Int32 Value);

                /// Performs an atomic XOR operation on the specified Int64 values.
                static Core::Types::Int64 InterlockedXor64(
                    Core::Types::Int64 volatile* Destination, 
                    Core::Types::Int64 Value);

                // Multi operations
                /** 
                * Performs an atomic compare-and-exchange operation on the 
                * specified values. The function compares two specified 32-bit 
                * values and exchanges with another 32-bit value based on the 
                * outcome of the comparison.
                **/
                static Core::Types::Int16 InterlockedCompareExchange16(
                    Core::Types::Int16 volatile* Destination, 
                    Core::Types::Int16 Exchange, Core::Types::Int16 Comparand);

                /** 
                * Performs an atomic compare-and-exchange operation on the 
                * specified values. The function compares two specified 32-bit 
                * values and exchanges with another 32-bit value based on the 
                * outcome of the comparison.
                **/
                static Core::Types::Int32 InterlockedCompareExchange32(
                    Core::Types::Int32 volatile* Destination, 
                    Core::Types::Int32 Exchange, Core::Types::Int32 Comparand);

                /** 
                * Performs an atomic compare-and-exchange operation on the 
                * specified values. The function compares two specified 64-bit 
                * values and exchanges with another 64-bit value based on the 
                * outcome of the comparison.
                **/
                static Core::Types::Int64 InterlockedCompareExchange64(
                    Core::Types::Int64 volatile* Destination, 
                    Core::Types::Int64 Exchange, Core::Types::Int64 Comparand);

                /**
                * Performs an atomic compare-and-exchange operation on the 
                * specified values. The function compares two specified pointer
                * values and exchanges with another pointer value based on the 
                * outcome of the comparison.
                **/
                static void* InterlockedCompareExchangePointer(
                    void* volatile* Destination, void* Exchange, void* Comparand);

                /// Sets a 32-bit variable to the specified value as an atomic operation.
                static Core::Types::Int32 InterlockedExchange32(
                    Core::Types::Int32 volatile* Target, Core::Types::Int32 Value);

                /// Sets a 64-bit variable to the specified value as an atomic operation.
                static Core::Types::Int64 InterlockedExchange64(
                    Core::Types::Int64 volatile* Target, Core::Types::Int64 Value);

                /// Atomically exchanges a pair of addresses.
                static void* InterlockedExchangePointer(
                    void* volatile* Target, void* Value);
            };
        }
    }    
}

#endif // RF_SYSTEM_THREADING_INTERLOCKED_HPP
