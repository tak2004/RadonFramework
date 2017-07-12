#ifndef RF_MATH_FLOAT32_HPP
#define RF_MATH_FLOAT32_HPP
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
struct Float32
{
    static const RF_Type::Float32 QUATER_PI;
    static const RF_Type::Float32 HALF_PI;
    static const RF_Type::Float32 PI;
    static const RF_Type::Float32 TWO_PI;
    static const RF_Type::Float32 EPSILION;
    static const RF_Type::Float32 INV_QUATER_PI;
    static const RF_Type::Float32 INV_HALF_PI;
    static const RF_Type::Float32 INV_PI;
    static const RF_Type::Float32 INV_TWO_PI;
    static const RF_Type::Float32 DEG_TO_RAD;
    static const RF_Type::Float32 RAD_TO_DEG;
    static const RF_Type::Float32 POS_INFINITY;
    static const RF_Type::Float32 NEG_INFINITY;
    static const RF_Type::Float32 QUITE_NAN;
    static const RF_Type::Float32 SIGNALING_NAN;
    static const RF_Type::UInt32  FRACTION_BITS;
    static const RF_Type::UInt32  EXPONENT_BITS;

    static RF_Type::Float32 DegToRad(const RF_Type::Float32 Val);
    static RF_Type::Float32 RadToDeg(const RF_Type::Float32 Val);
    static RF_Type::Float32 ACos(const RF_Type::Float32 Value);
    static RF_Type::Float32 ASin(const RF_Type::Float32 Value);
    static RF_Type::Float32 ATan(const RF_Type::Float32 Value);
    static RF_Type::Float32 ATan2(const RF_Type::Float32 X, const RF_Type::Float32 Y);
    static RF_Type::Float32 Ceil(const RF_Type::Float32 Value);
    static RF_Type::Float32 Cos(const RF_Type::Float32 Value);
    static RF_Type::Float32 Exp(const RF_Type::Float32 Value);
    static RF_Type::Float32 FAbs(const RF_Type::Float32 Value);
    static RF_Type::Float32 Floor(const RF_Type::Float32 Value);
    static RF_Type::Float32 FMod(const RF_Type::Float32 X, const RF_Type::Float32 Y);
    static RF_Type::Float32 InvSqrt(const RF_Type::Float32 Value);
    static RF_Type::Float32 Log(const RF_Type::Float32 Value);
    static RF_Type::Float32 Pow(const RF_Type::Float32 Value);
    static RF_Type::Float32 Sin(const RF_Type::Float32 Value);
    static RF_Type::Float32 Sqr(const RF_Type::Float32 Value);
    static RF_Type::Float32 Sqrt(const RF_Type::Float32 Value);
    static RF_Type::Float32 Tan(const RF_Type::Float32 Value);
    static RF_Type::Float32 Abs(const RF_Type::Float32 Value);

    static RF_Type::Float32 Sign(const RF_Type::Float32 Value);

    static RF_Type::Float32 FastSin0(const RF_Type::Float32 Angle);
    static RF_Type::Float32 FastCos0(const RF_Type::Float32 Angle);
    static RF_Type::Float32 FastInvSin0(const RF_Type::Float32 Angle);
    static RF_Type::Float32 FastInvCos0(const RF_Type::Float32 Angle);

    static RF_Type::Bool IsPowerOfTwo(const RF_Type::Float32 Value);
    static RF_Type::Float32 NextPowerOfTwo(const RF_Type::Float32 Value);

    static RF_Type::Float32 Min(const RF_Type::Float32 A, const RF_Type::Float32 B);
    static RF_Type::Float32 Max(const RF_Type::Float32 A, const RF_Type::Float32 B);

    static RF_Type::Float32 Clamp(const RF_Type::Float32 Value, const RF_Type::Float32 Min, const RF_Type::Float32 Max);

    static RF_Type::Float32 Round(const RF_Type::Float32 Value);

    static RF_Type::Bool IsAlmostEqual(const RF_Type::Float32 a, const RF_Type::Float32 b);
    static RF_Type::Bool IsAlmostEqual(const RF_Type::Float32* a, const RF_Type::Float32* b,
        RF_Type::UInt32 ElementCount);

    static RF_Type::Bool IsNaN(const RF_Type::Float32 Value);
    static RF_Type::Bool IsInfinity(const RF_Type::Float32 Value);
protected:
    static const RF_Type::UInt32 FastSinArrayLen = 720;
    static RF_Type::Float32 FastSinArray[FastSinArrayLen];
    static RF_Type::UInt32 GetFastSinArrayElement(const RF_Type::Float32 Angle);
    static void Init();
    static RF_Type::Bool WasInitialized;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_MATH
#define RF_SHORTHAND_NAMESPACE_MATH
namespace RF_Math = RadonFramework::Math;
#endif

#endif // RF_MATH_FLOAT32_HPP
