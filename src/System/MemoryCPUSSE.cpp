#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Memory.hpp"
#include "RadonFramework/Collections/List.hpp"
#include "RadonFramework/Defines.hpp"
#include "RadonFramework/Core/Types/UInt8.hpp"
#include "RadonFramework/Core/Types/MemoryRange.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;
using namespace RadonFramework::System::Memory;

#if RF_BUILD_INTRINSIC_SSE41 
#include <smmintrin.h>
#include <nmmintrin.h>

RF_Type::Int32 Compare_SSE4(const void* P1, const void* P2, RF_Type::Size Bytes)
{
    const __m128i* mp1 = reinterpret_cast<const __m128i*>(P1);
    const __m128i* mp2 = reinterpret_cast<const __m128i*>(P2);
    const RF_Type::UInt8 *p1 = reinterpret_cast<const RF_Type::UInt8*>(P1),
                      *p2 = reinterpret_cast<const RF_Type::UInt8*>(P2);
    __m128i a, b, cmp;
    const int mode = _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_EACH | _SIDD_NEGATIVE_POLARITY;
    int result = 16;

    // not aligned pointer compare bytewise
    while( Bytes && (reinterpret_cast<RF_Type::MemoryRange>(p1) & 0xf || reinterpret_cast<RF_Type::MemoryRange>(p2) & 0xf))
    {
        if (*p1 != *p2)
        {
            return *p1 - *p2;
        }
        else
        {
            ++p1;
            ++p2;
            --Bytes;
        }
    }

    // compare 16 byte wise
    mp1 = reinterpret_cast<const __m128i*>(p1);
    mp2 = reinterpret_cast<const __m128i*>(p2);
    while ( Bytes >= 16 && result == 16)
    {
        a = _mm_load_si128(mp1);
        b = _mm_load_si128(mp2);
        result = _mm_cmpestri(a, 16, b, 16, mode);
        Bytes -= sizeof(__m128i);
        ++mp1;
        ++mp2;
    }

    if (result < 16 && Bytes >= 16)
    {
        a = _mm_sub_epi8(a, b);
        return *(reinterpret_cast<RF_Type::UInt8*>(&a) + result) && 0xFF;
    }

    // compare trailing bytes
    p1 = reinterpret_cast<const RF_Type::UInt8*>(mp1);
    p2 = reinterpret_cast<const RF_Type::UInt8*>(mp2);
    while(Bytes--)
    {
        if (*p1 != *p2)
        {
            return *p1 - *p2;
        }
        else
        {
            ++p1;
            ++p2;
        }
    }

    return 0;
}
#endif

#if RF_BUILD_INTRINSIC_SSE2
#include <emmintrin.h>
void Set_SSE2(void* Pointer, RF_Type::Int32 Value, RF_Type::Size Bytes)
{
    RF_Type::UInt8* p = reinterpret_cast<RF_Type::UInt8*>(Pointer);
    RF_Type::Size* mp;
    RF_Type::Size size = Value;
    // not aligned pointer fill bytewise
    while( Bytes && reinterpret_cast<RF_Type::MemoryRange>(p) & 0xf)
    {
        *(p++) = static_cast<RF_Type::UInt8>(Value);
        --Bytes;
    }

    // aligned pointer fill 16byte pieces
    __m128i v;
    __m128i* m = reinterpret_cast<__m128i*>(p);
    RF_Type::UInt32 ui = static_cast<RF_Type::UInt32>(Value);
    ui = ui << 8 | ui;
    ui = ui << 16 | ui;
    v = _mm_set_epi32(ui,ui,ui,ui);
    while (Bytes >= 16)
    {
        _mm_store_si128(m, v);
        ++m;
        Bytes -= 16;
    }

    p = reinterpret_cast<RF_Type::UInt8*>(m);
    // fill up last unaligned bytes
    while(Bytes--)
    {
        *(p++) = static_cast<RF_Type::UInt8>(Value);
    }
}

void Copy_SSE2(void* Destination, const void* Source, Size Bytes)
{
    RF_Type::UInt8* dst = reinterpret_cast<RF_Type::UInt8*>(Destination);
    const RF_Type::UInt8* src = reinterpret_cast<const RF_Type::UInt8*>(Source);

    // not aligned pointer fill bytewise
    while( Bytes && (reinterpret_cast<RF_Type::MemoryRange>(dst) & 0xf ||
                     reinterpret_cast<RF_Type::MemoryRange>(src) & 0xf ))
    {
        *(dst++) = *(src++);
        --Bytes;
    }

    // aligned pointer fill 16byte pieces
    __m128i a;
    const __m128i* mSrc = reinterpret_cast<const __m128i*>(src);
    __m128i* mDst = reinterpret_cast<__m128i*>(dst);
    while (Bytes >= 16)
    {
        a = _mm_load_si128(mSrc++);
        _mm_store_si128(mDst++, a);
        Bytes -= 16;
    }

    dst = reinterpret_cast<RF_Type::UInt8*>(mDst);
    src = reinterpret_cast<const RF_Type::UInt8*>(mSrc);
    // fill up last unaligned bytes
    while(Bytes--)
    {
        *(dst++) = *(src++);
    }
}

void Swap_SSE2(void* P1, void* P2, Size Bytes)
{
    UInt8 tmp;
    UInt8 *p1 = reinterpret_cast<UInt8*>(P1);
    UInt8 *p2 = reinterpret_cast<UInt8*>(P2);
    if(p1 <= p2 || p1 >= (p2 + Bytes))
    {
        while(Bytes && (reinterpret_cast<RF_Type::MemoryRange>(P1)& (sizeof(RF_Type::Size) - 1) ||
            reinterpret_cast<RF_Type::MemoryRange>(P2)& (sizeof(RF_Type::Size) - 1)))
        {
            tmp = *p1;
            *(p1++) = *p2;
            *(p2++) = tmp;
            --Bytes;
        }

        // swap 16 byte wise
        __m128i* mp1 = reinterpret_cast<__m128i*>(p1);
        __m128i* mp2 = reinterpret_cast<__m128i*>(p2);
        __m128i a, b;
        while(Bytes >= 16)
        {
            a = _mm_load_si128(mp1);
            b = _mm_load_si128(mp2);
            _mm_store_si128(mp1++, b);
            _mm_store_si128(mp2++, a);
        }

        p1 = reinterpret_cast<RF_Type::UInt8*>(mp1);
        p2 = reinterpret_cast<RF_Type::UInt8*>(mp2);
        // swap last unaligned bytes
        while(Bytes--)
        {
            tmp = *p1;
            *(p1++) = *p2;
            *(p2++) = tmp;
        }
    }
}
#endif