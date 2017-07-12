#ifndef RF_MATH_FLOAT64_HPP
#define RF_MATH_FLOAT64_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Math {

/** @brief This class support basic math functions.
*
* It supports constants and basic math functions.
* There are also faster implementation which use different algorithm, with
* less accuracy but shorter execution time.
*/
struct Float64
{
    static const RF_Type::Float64 QUATER_PI;
    static const RF_Type::Float64 HALF_PI;
    static const RF_Type::Float64 PI;
    static const RF_Type::Float64 TWO_PI;
    static const RF_Type::Float64 EPSILION;
    static const RF_Type::Float64 INV_QUATER_PI;
    static const RF_Type::Float64 INV_HALF_PI;
    static const RF_Type::Float64 INV_PI;
    static const RF_Type::Float64 INV_TWO_PI;
    static const RF_Type::Float64 DEG_TO_RAD;
    static const RF_Type::Float64 RAD_TO_DEG;
    static const RF_Type::Float64 POS_INFINITY;
    static const RF_Type::Float64 NEG_INFINITY;
    static const RF_Type::Float64 QUITE_NAN;
    static const RF_Type::Float64 SIGNALING_NAN;
    static const RF_Type::UInt32  FRACTION_BITS;
    static const RF_Type::UInt32  EXPONENT_BITS;

    static RF_Type::Float64 DegToRad(const RF_Type::Float64 Val);
    static RF_Type::Float64 RadToDeg(const RF_Type::Float64 Val);
    static RF_Type::Float64 ACos(const RF_Type::Float64 Value);
    static RF_Type::Float64 ASin(const RF_Type::Float64 Value);
    static RF_Type::Float64 ATan(const RF_Type::Float64 Value);
    static RF_Type::Float64 ATan2(const RF_Type::Float64 X, const RF_Type::Float64 Y);
    static RF_Type::Float64 Ceil(const RF_Type::Float64 Value);
    static RF_Type::Float64 Cos(const RF_Type::Float64 Value);
    static RF_Type::Float64 Exp(const RF_Type::Float64 Value);
    static RF_Type::Float64 FAbs(const RF_Type::Float64 Value);
    static RF_Type::Float64 Floor(const RF_Type::Float64 Value);
    static RF_Type::Float64 FMod(const RF_Type::Float64 X, const RF_Type::Float64 Y);
    static RF_Type::Float64 InvSqrt(const RF_Type::Float64 Value);
    static RF_Type::Float64 Log(const RF_Type::Float64 Value);
    static RF_Type::Float64 Pow(const RF_Type::Float64 Value);
    static RF_Type::Float64 Sin(const RF_Type::Float64 Value);
    static RF_Type::Float64 Sqr(const RF_Type::Float64 Value);
    static RF_Type::Float64 Sqrt(const RF_Type::Float64 Value);
    static RF_Type::Float64 Tan(const RF_Type::Float64 Value);
    static RF_Type::Float64 Abs(const RF_Type::Float64 Value);

    static RF_Type::Float64 Sign(const RF_Type::Float64 Value);

    static RF_Type::Float64 FastSin0(const RF_Type::Float64 Angle);
    static RF_Type::Float64 FastCos0(const RF_Type::Float64 Angle);
    static RF_Type::Float64 FastInvSin0(const RF_Type::Float64 Angle);
    static RF_Type::Float64 FastInvCos0(const RF_Type::Float64 Angle);

    static RF_Type::Bool IsPowerOfTwo(const RF_Type::Float64 Value);
    static RF_Type::Float64 NextPowerOfTwo(const RF_Type::Float64 Value);

    static RF_Type::Float64 Min(const RF_Type::Float64 A, const RF_Type::Float64 B);
    static RF_Type::Float64 Max(const RF_Type::Float64 A, const RF_Type::Float64 B);

    static RF_Type::Float64 Clamp(const RF_Type::Float64 Value, const RF_Type::Float64 Min, const RF_Type::Float64 Max);

    static RF_Type::Float64 Round(const RF_Type::Float64 Value);

    static RF_Type::Bool IsAlmostEqual(const RF_Type::Float64 a, const RF_Type::Float64 b);
    static RF_Type::Bool IsAlmostEqual(const RF_Type::Float64* a, const RF_Type::Float64* b,
                                       RF_Type::UInt32 ElementCount);

    static RF_Type::Bool IsNaN(const RF_Type::Float64 Value);
    static RF_Type::Bool IsInfinity(const RF_Type::Float64 Value);
protected:
    static const RF_Type::UInt32 FastSinArrayLen = 720;
    static RF_Type::Float64 FastSinArray[FastSinArrayLen];
    static RF_Type::UInt32 GetFastSinArrayElement(const RF_Type::Float64 Angle);
    static void Init();
    static RF_Type::Bool WasInitialized;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_MATH
#define RF_SHORTHAND_NAMESPACE_MATH
namespace RF_Math = RadonFramework::Math;
#endif

#endif // RF_MATH_FLOAT64_HPP
