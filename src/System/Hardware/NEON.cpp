#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Hardware/Vec128Int.hpp"

#if RF_BUILD_INTRINSIC_NEON
#include <arm_neon.h>

namespace RadonFramework { namespace System { namespace Hardware { namespace NEON {

void Vec128IntLoad(RF_Type::Vec128Int32* Destination,
    const RF_Type::Vec128Int32* Source, const RF_Type::Size Elements)
{
    for(RF_Type::Size i = 0; i < Elements; ++i)
        reinterpret_cast<int32x4_t*>(Destination)[i] = vld1q_s32(reinterpret_cast<const int32x4_t*>(Source + i));
}

void Vec128IntSetInt32(RF_Type::Vec128Int32* Destination,
    const RF_Type::Int32 Source, const RF_Type::Size Elements)
{
    for(RF_Type::Size i = 0; i < Elements; ++i)
        reinterpret_cast<int32x4_t*>(Destination)[i] = vdupq_n_s32(Source);
}

void Vec128IntCompareInt32(RF_Type::Vec128Int32* Destination,
    const RF_Type::Vec128Int32* SourceA, const RF_Type::Vec128Int32* SourceB,
    const RF_Type::Size Elements)
{
    for(RF_Type::Size i = 0; i < Elements; ++i)
        reinterpret_cast<int32x4_t*>(Destination)[i] = vceqq_s32(reinterpret_cast<const int32x4_t*>(SourceA)[i], reinterpret_cast<const int32x4_t*>(SourceB)[i]);
}

void Vec128IntMaskInt8(RF_Type::Int32* Masks,
    const RF_Type::Vec128Int32* Source, const RF_Type::Size Elements)
{
    for(RF_Type::Size i = 0; i < Elements; ++i)
    {
        uint8x16_t input = reinterpret_cast<const int32x4_t*>(Source)[i];
        const int8_t __attribute__((aligned(16))) xr[8] = {-7, -6, -5, -4, -3, -2, -1, 0};
        uint8x8_t mask_and = vdup_n_u8(0x80);
        int8x8_t mask_shift = vld1_s8(xr);

        uint8x8_t lo = vget_low_u8(input);
        uint8x8_t hi = vget_high_u8(input);

        lo = vand_u8(lo, mask_and);
        lo = vshl_u8(lo, mask_shift);

        hi = vand_u8(hi, mask_and);
        hi = vshl_u8(hi, mask_shift);

        lo = vpadd_u8(lo, lo);
        lo = vpadd_u8(lo, lo);
        lo = vpadd_u8(lo, lo);

        hi = vpadd_u8(hi, hi);
        hi = vpadd_u8(hi, hi);
        hi = vpadd_u8(hi, hi);

        Masks[i] = ((hi[0] << 8) | (lo[0] & 0xFF));
    }
}

RF_Type::Int32 Vec128IntFindInt32(const RF_Type::Vec128Int32* Source, RF_Type::Int32 Value)
{
    int32x4_t a, b;
    a = vld1q_s32(reinterpret_cast<const __m128i*>(Source));
    b = vdupq_n_s32(Value);
    a = vceqq_s32(a, b);
    const int8_t __attribute__((aligned(16))) xr[8] = {-7, -6, -5, -4, -3, -2, -1, 0};
    uint8x8_t mask_and = vdup_n_u8(0x80);
    int8x8_t mask_shift = vld1_s8(xr);
    uint8x8_t lo = vget_low_u8(a);
    uint8x8_t hi = vget_high_u8(a);
    lo = vand_u8(lo, mask_and);
    lo = vshl_u8(lo, mask_shift);
    hi = vand_u8(hi, mask_and);
    hi = vshl_u8(hi, mask_shift);
    lo = vpadd_u8(lo, lo);
    lo = vpadd_u8(lo, lo);
    lo = vpadd_u8(lo, lo);
    hi = vpadd_u8(hi, hi);
    hi = vpadd_u8(hi, hi);
    hi = vpadd_u8(hi, hi);
    return = ((hi[0] << 8) | (lo[0] & 0xFF));
}

}

void DispatchNEON()
{
    Vec128IntLoad = NEON::Vec128IntLoad;
    Vec128IntSetInt32 = NEON::Vec128IntSetInt32;
    Vec128IntCompareInt32 = NEON::Vec128IntCompareInt32;
    Vec128IntMaskInt8 = NEON::Vec128IntMaskInt8;
    Vec128IntFindInt32 = NEON::Vec128IntFindInt32;
}

} } }

#endif