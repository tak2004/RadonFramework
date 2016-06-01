#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Float64.hpp"
#include <limits>
#include <math.h>

namespace RadonFramework { namespace Math {

const RF_Type::Float64 Float64::TWO_PI = static_cast<RF_Type::Float64>(8.0*atan(1.0));
const RF_Type::Float64 Float64::PI = static_cast<RF_Type::Float64>(4.0*atan(1.0));
const RF_Type::Float64 Float64::HALF_PI = static_cast<RF_Type::Float64>(2.0*atan(1.0));
const RF_Type::Float64 Float64::QUATER_PI = static_cast<RF_Type::Float64>(atan(1.0));
const RF_Type::Float64 Float64::INV_QUATER_PI = static_cast<RF_Type::Float64>(1.0 - (8.0*atan(1.0)));
const RF_Type::Float64 Float64::INV_HALF_PI = static_cast<RF_Type::Float64>(1.0 - (4.0*atan(1.0)));
const RF_Type::Float64 Float64::INV_PI = static_cast<RF_Type::Float64>(1.0 - (2.0*atan(1.0)));
const RF_Type::Float64 Float64::INV_TWO_PI = static_cast<RF_Type::Float64>(1.0 - (atan(1.0)));
const RF_Type::Float64 Float64::DEG_TO_RAD = static_cast<RF_Type::Float64>((4.0*atan(1.0)) / 180.0);
const RF_Type::Float64 Float64::RAD_TO_DEG = static_cast<RF_Type::Float64>(180.0 / (4.0*atan(1.0)));
const RF_Type::Float64 Float64::EPSILION = std::numeric_limits<double>::epsilon();
const RF_Type::Float64 Float64::POS_INFINITY = std::numeric_limits<double>::infinity();
const RF_Type::Float64 Float64::NEG_INFINITY = -std::numeric_limits<double>::infinity();
const RF_Type::Float64 Float64::QUITE_NAN = std::numeric_limits<double>::quiet_NaN();
const RF_Type::Float64 Float64::SIGNALING_NAN = std::numeric_limits<double>::signaling_NaN();
const RF_Type::UInt32 Float64::FRACTION_BITS = 52;
const RF_Type::UInt32 Float64::EXPONENT_BITS = 11;
RF_Type::Bool Float64::WasInitialized = false;
RF_Type::Float64 Float64::FastSinArray[FastSinArrayLen];

const RF_Type::Float64 ONE = static_cast<RF_Type::Float64>(1);
const RF_Type::Float64 ZERO = static_cast<RF_Type::Float64>(0);

RF_Type::Float64 Float64::DegToRad(const RF_Type::Float64 X)
{
    return X*Float64::DEG_TO_RAD;
}

RF_Type::Float64 Float64::RadToDeg(const RF_Type::Float64 X)
{
    return X*Float64::RAD_TO_DEG;
}

RF_Type::Float64 Float64::ACos(const RF_Type::Float64 X)
{
    return acos(X);
}

RF_Type::Float64 Float64::ASin(const RF_Type::Float64 X)
{
    return asin(X);
}

RF_Type::Float64 Float64::ATan(const RF_Type::Float64 X)
{
    return atan(X);
}

RF_Type::Float64 Float64::ATan2(const RF_Type::Float64 X, const RF_Type::Float64 Y)
{
    return atan2(X, Y);
}

RF_Type::Float64 Float64::Ceil(const RF_Type::Float64 X)
{
    return ceil(X);
}

RF_Type::Float64 Float64::Cos(const RF_Type::Float64 X)
{
    return cos(X);
}

RF_Type::Float64 Float64::Exp(const RF_Type::Float64 X)
{
    return exp(X);
}

RF_Type::Float64 Float64::Floor(const RF_Type::Float64 X)
{
    return floor(X);
}

RF_Type::Float64 Float64::FMod(const RF_Type::Float64 X, const RF_Type::Float64 Y)
{
    return fmod(X, Y);
}

RF_Type::Float64 Float64::InvSqrt(const RF_Type::Float64 X)
{
    return ONE / sqrt(X);
}

RF_Type::Float64 Float64::Log(const RF_Type::Float64 X)
{
    return log(X);
}

RF_Type::Float64 Float64::Pow(const RF_Type::Float64 X)
{
    return pow(X, 2);
}

RF_Type::Float64 Float64::Tan(const RF_Type::Float64 X)
{
    return tan(X);
}

RF_Type::Float64 Float64::Sqr(const RF_Type::Float64 X)
{
    return X*X;
}

RF_Type::Float64 Float64::Sqrt(const RF_Type::Float64 X)
{
    return sqrt(X);
}

RF_Type::Float64 Float64::Sign(const RF_Type::Float64 X)
{
    return signbit(X);
}

RF_Type::Float64 Float64::FastSin0(const RF_Type::Float64 Angle)
{
    return GetFastSinArrayElement(Angle);
}

RF_Type::Float64 Float64::FastCos0(const RF_Type::Float64 Angle)
{
    return FastSin0(Angle - static_cast<RF_Type::Float64>(90));
}

RF_Type::Float64 Float64::FastInvSin0(const RF_Type::Float64 Angle)
{
    return ONE / FastSin0(Angle);
}

RF_Type::Float64 Float64::FastInvCos0(const RF_Type::Float64 Angle)
{
    return ONE / FastSin0(Angle - static_cast<RF_Type::Float64>(90));
}

RF_Type::Bool Float64::IsPowerOfTwo(const RF_Type::Float64 Value)
{
    int exp;
    return frexp(Value, &exp) == 0.5;
}

RF_Type::Float64 Float64::NextPowerOfTwo(const RF_Type::Float64 Value)
{
    int exp;
    if(frexp(Value, &exp) == 0.5) {
        return Value;
    }
    return ldexp(1.0, exp);
}

RF_Type::Float64 Float64::Sin(const RF_Type::Float64 Value)
{
    return sin(Value);
}

RF_Type::Float64 Float64::FAbs(const RF_Type::Float64 Value)
{
    return fabs(Value);
}

RF_Type::Float64 Float64::Abs(const RF_Type::Float64 Value)
{
    return abs(Value);
}

RF_Type::Float64 Float64::Min(const RF_Type::Float64 A, const RF_Type::Float64 B)
{
    return A < B ? A : B;
}

RF_Type::Float64 Float64::Max(const RF_Type::Float64 A, const RF_Type::Float64 B)
{
    return A > B ? A : B;
}

RF_Type::Float64 Float64::Clamp(const RF_Type::Float64 Value, const RF_Type::Float64 Min, const RF_Type::Float64 Max)
{
    if(Value < Min) return Min;
    if(Value > Max) return Max;
    return Value;
}

RF_Type::Float64 Float64::Round(const RF_Type::Float64 Value)
{
    return nearbyint(Value);
}

RF_Type::Bool Float64::IsAlmostEqual(const RF_Type::Float64* a, const RF_Type::Float64* b,
                                     RF_Type::UInt32 ElementCount)
{
    for(RF_Type::UInt32 i = 0; i<ElementCount; ++i)
        if(FAbs(a[i] - b[i])>EPSILION)
            return false;
    return true;
}

RF_Type::Bool Float64::IsAlmostEqual(const RF_Type::Float64 a, const RF_Type::Float64 b)
{
    return (FAbs(a - b) <= EPSILION);
}

RF_Type::Bool Float64::IsNaN(const RF_Type::Float64 Value)
{// NAN is never equal, try equal it self
    return Value != Value; //-V501
}

RF_Type::Bool Float64::IsInfinity(const RF_Type::Float64 Value)
{
    return Value == INFINITY || Value == NEG_INFINITY;
}

RF_Type::UInt32 Float64::GetFastSinArrayElement(const RF_Type::Float64 Angle)
{
    RF_Type::UInt32 index = static_cast<RF_Type::UInt32>((FastSinArrayLen / 360.0)*Angle) % (360 * (FastSinArrayLen / 360));
    if(WasInitialized)
    {
    }
    else
    {
        Init();
    }
    return FastSinArray[index];
}

void Float64::Init()
{
    RF_Type::Float64 steps = (PI / static_cast<RF_Type::Float64>(180)) / FastSinArrayLen;
    for(RF_Type::UInt32 i = 0; i < FastSinArrayLen; ++i)
        FastSinArray[i] = Sin(i*steps);
    WasInitialized = true;
}

} }