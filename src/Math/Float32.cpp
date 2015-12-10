#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Float32.hpp"
#include <limits>

namespace RadonFramework { namespace Math {

const RF_Type::Float32 Float32::TWO_PI = static_cast<RF_Type::Float32>(8.0*atan(1.0));
const RF_Type::Float32 Float32::PI = static_cast<RF_Type::Float32>(4.0*atan(1.0));
const RF_Type::Float32 Float32::HALF_PI = static_cast<RF_Type::Float32>(2.0*atan(1.0));
const RF_Type::Float32 Float32::QUATER_PI = static_cast<RF_Type::Float32>(atan(1.0));
const RF_Type::Float32 Float32::INV_QUATER_PI = static_cast<RF_Type::Float32>(1.0 - (8.0*atan(1.0)));
const RF_Type::Float32 Float32::INV_HALF_PI = static_cast<RF_Type::Float32>(1.0 - (4.0*atan(1.0)));
const RF_Type::Float32 Float32::INV_PI = static_cast<RF_Type::Float32>(1.0 - (2.0*atan(1.0)));
const RF_Type::Float32 Float32::INV_TWO_PI = static_cast<RF_Type::Float32>(1.0 - (atan(1.0)));
const RF_Type::Float32 Float32::DEG_TO_RAD = static_cast<RF_Type::Float32>((4.0*atan(1.0)) / 180.0);
const RF_Type::Float32 Float32::RAD_TO_DEG = static_cast<RF_Type::Float32>(180.0 / (4.0*atan(1.0)));
const RF_Type::Float32 Float32::EPSILION = std::numeric_limits<float>::epsilon();
const RF_Type::Float32 Float32::POS_INFINITY = std::numeric_limits<float>::infinity();
const RF_Type::Float32 Float32::NEG_INFINITY = -std::numeric_limits<float>::infinity();
const RF_Type::Float32 Float32::QUITE_NAN = std::numeric_limits<float>::quiet_NaN();
const RF_Type::Float32 Float32::SIGNALING_NAN = std::numeric_limits<float>::signaling_NaN();
const RF_Type::UInt32 Float32::FRACTION_BITS = 23;
const RF_Type::UInt32 Float32::EXPONENT_BITS = 8;
RF_Type::Bool Float32::WasInitialized = false;
RF_Type::Float32 Float32::FastSinArray[FastSinArrayLen];

const RF_Type::Float32 ONE = static_cast<RF_Type::Float32>(1);
const RF_Type::Float32 ZERO = static_cast<RF_Type::Float32>(0);

RF_Type::Float32 Float32::DegToRad(const RF_Type::Float32 X)
{
    return X*Float32::DEG_TO_RAD;
}

RF_Type::Float32 Float32::RadToDeg(const RF_Type::Float32 X)
{
    return X*Float32::RAD_TO_DEG;
}

RF_Type::Float32 Float32::ACos(const RF_Type::Float32 X)
{
    return acos(X);
}

RF_Type::Float32 Float32::ASin(const RF_Type::Float32 X)
{
    return asin(X);
}

RF_Type::Float32 Float32::ATan(const RF_Type::Float32 X)
{
    return atan(X);
}

RF_Type::Float32 Float32::ATan2(const RF_Type::Float32 X, const RF_Type::Float32 Y)
{
    return atan2(X, Y);
}

RF_Type::Float32 Float32::Ceil(const RF_Type::Float32 X)
{
    return ceil(X);
}

RF_Type::Float32 Float32::Cos(const RF_Type::Float32 X)
{
    return cos(X);
}

RF_Type::Float32 Float32::Exp(const RF_Type::Float32 X)
{
    return exp(X);
}

RF_Type::Float32 Float32::Floor(const RF_Type::Float32 X)
{
    return floor(X);
}

RF_Type::Float32 Float32::FMod(const RF_Type::Float32 X, const RF_Type::Float32 Y)
{
    return fmod(X,Y);
}

RF_Type::Float32 Float32::InvSqrt(const RF_Type::Float32 X)
{
    return ONE / sqrt(X);
}

RF_Type::Float32 Float32::Log(const RF_Type::Float32 X)
{
    return log(X);
}

RF_Type::Float32 Float32::Pow(const RF_Type::Float32 X)
{
    return pow(X, 2);
}

RF_Type::Float32 Float32::Tan(const RF_Type::Float32 X)
{
    return tan(X);
}

RF_Type::Float32 Float32::Sqr(const RF_Type::Float32 X)
{
    return X*X;
}

RF_Type::Float32 Float32::Sqrt(const RF_Type::Float32 X)
{
    return sqrt(X);
}

RF_Type::Float32 Float32::Sign(const RF_Type::Float32 X)
{
    return signbit(X);
}

RF_Type::Float32 Float32::FastSin0(const RF_Type::Float32 Angle)
{
    return GetFastSinArrayElement(Angle);
}

RF_Type::Float32 Float32::FastCos0(const RF_Type::Float32 Angle)
{
    return FastSin0(Angle - static_cast<RF_Type::Float32>(90));
}

RF_Type::Float32 Float32::FastInvSin0(const RF_Type::Float32 Angle)
{
    return ONE / FastSin0(Angle);
}

RF_Type::Float32 Float32::FastInvCos0(const RF_Type::Float32 Angle)
{
    return ONE / FastSin0(Angle - static_cast<RF_Type::Float32>(90));
}

RF_Type::Bool Float32::IsPowerOfTwo(const RF_Type::Float32 Value)
{
    int exp;
    return frexp(Value, &exp) == 0.5;
}

RF_Type::Float32 Float32::NextPowerOfTwo(const RF_Type::Float32 Value)
{
    int exp;
    if(frexp(Value, &exp) == 0.5) {
        return Value;
    }
    return ldexp(1.0, exp);
}

RF_Type::Float32 Float32::Sin(const RF_Type::Float32 Value)
{
    return sin(Value);
}

RF_Type::Float32 Float32::FAbs(const RF_Type::Float32 Value)
{
    return fabs(Value);
}

RF_Type::Float32 Float32::Abs(const RF_Type::Float32 Value)
{
    return abs(Value);
}

RF_Type::Float32 Float32::Min(const RF_Type::Float32 A, const RF_Type::Float32 B)
{
    return A < B ? A : B;
}

RF_Type::Float32 Float32::Max(const RF_Type::Float32 A, const RF_Type::Float32 B)
{
    return A > B ? A : B;
}

RF_Type::Float32 Float32::Clamp(const RF_Type::Float32 Value, const RF_Type::Float32 Min, const RF_Type::Float32 Max)
{
    if(Value < Min) return Min;
    if(Value > Max) return Max;
    return Value;
}

RF_Type::Float32 Float32::Round(const RF_Type::Float32 Value)
{
    return nearbyint(Value);
}

RF_Type::Bool Float32::IsAlmostEqual(const RF_Type::Float32* a, const RF_Type::Float32* b,
                                     RF_Type::UInt32 ElementCount)
{
    for(RF_Type::UInt32 i = 0; i<ElementCount; ++i)
        if(FAbs(a[i] - b[i])>EPSILION)
            return false;
    return true;
}

RF_Type::Bool Float32::IsAlmostEqual(const RF_Type::Float32 a, const RF_Type::Float32 b)
{
    return (FAbs(a - b) <= EPSILION);
}

RF_Type::Bool Float32::IsNaN(const RF_Type::Float32 Value)
{// NAN is never equal, try equal it self
    return Value != Value; //-V501
}

RF_Type::Bool Float32::IsInfinity(const RF_Type::Float32 Value)
{
    return Value == INFINITY || Value == NEG_INFINITY;
}

RF_Type::UInt32 Float32::GetFastSinArrayElement(const RF_Type::Float32 Angle)
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

void Float32::Init()
{
    RF_Type::Float32 steps = (PI / static_cast<RF_Type::Float32>(180)) / FastSinArrayLen;
    for(RF_Type::UInt32 i = 0; i < FastSinArrayLen; ++i)
        FastSinArray[i] = Sin(i*steps);
    WasInitialized = true;
}

} }