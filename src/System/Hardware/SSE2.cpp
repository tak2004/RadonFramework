#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Hardware/Vec128Int.hpp"

#if RF_BUILD_INTRINSIC_SSE2
#include <xmmintrin.h>
#include <emmintrin.h>

namespace RadonFramework::System::Hardware::SSE2 {

void Vec128IntLoad(RF_Type::Vec128Int32* Destination,
    const RF_Type::Vec128Int32* Source, const RF_Type::Size Elements)
{
    for(RF_Type::Size i = 0; i < Elements; ++i)
        reinterpret_cast<__m128i*>(Destination)[i] = _mm_load_si128(reinterpret_cast<const __m128i*>(Source + i));
}

void Vec128IntSetInt32(RF_Type::Vec128Int32* Destination,
    const RF_Type::Int32 Source, const RF_Type::Size Elements)
{
    for(RF_Type::Size i = 0; i < Elements; ++i)
        reinterpret_cast<__m128i*>(Destination)[i] = _mm_set1_epi32(Source);
}

void Vec128IntCompareInt32(RF_Type::Vec128Int32* Destination,
    const RF_Type::Vec128Int32* SourceA, const RF_Type::Vec128Int32* SourceB,
    const RF_Type::Size Elements)
{
    for(RF_Type::Size i = 0; i < Elements; ++i)
        reinterpret_cast<__m128i*>(Destination)[i] = _mm_cmpeq_epi32(reinterpret_cast<const __m128i*>(SourceA)[i], reinterpret_cast<const __m128i*>(SourceB)[i]);
}

void Vec128IntMaskInt8(RF_Type::Int32* Masks,
    const RF_Type::Vec128Int32* Source, const RF_Type::Size Elements)
{
    for(RF_Type::Size i = 0; i < Elements; ++i)
        Masks[i] = _mm_movemask_epi8(reinterpret_cast<const __m128i*>(Source)[i]);
}

RF_Type::Int32 Vec128IntFindInt32(const RF_Type::Vec128Int32* Source, RF_Type::Int32 Value)
{
    __m128i a, b;
    a = _mm_load_si128(reinterpret_cast<const __m128i*>(Source));
    b = _mm_set1_epi32(Value);
    a = _mm_cmpeq_epi32(a,b);
    return _mm_movemask_epi8(a);
}

} 

namespace RadonFramework::System::Hardware {

void DispatchSSE2()
{
    Vec128IntLoad = SSE2::Vec128IntLoad;
    Vec128IntSetInt32 = SSE2::Vec128IntSetInt32;
    Vec128IntCompareInt32 = SSE2::Vec128IntCompareInt32;
    Vec128IntMaskInt8 = SSE2::Vec128IntMaskInt8;
    Vec128IntFindInt32 = SSE2::Vec128IntFindInt32;
}

}

#endif