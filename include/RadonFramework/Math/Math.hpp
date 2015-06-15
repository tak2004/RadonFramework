#ifndef RF_MATH_MATH_HPP
#define RF_MATH_MATH_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/Float32.hpp>
#include <RadonFramework/Core/Types/Float64.hpp>

#include <math.h>
// On some systems math.h defines INFINITY as macro !
#ifdef INFINITY
    #undef INFINITY
#endif

namespace RadonFramework { namespace Math {

/** @brief This class support basic math functions.
*
* The Math class can be used as Float32 and Float64 template.
* It support's consts and most basic math functions.
* There are also faster implementation which use different algorithm, with
* less accuracy but shorter execution time.
*/
template <class T>
class Math
{
public:
    static const T QUATER_PI;
    static const T HALF_PI;
    static const T PI;
    static const T TWO_PI;
    static const T EPSILION;
    static const T INV_QUATER_PI;
    static const T INV_HALF_PI;
    static const T INV_PI;
    static const T INV_TWO_PI;
    static const T DEG_TO_RAD;
    static const T RAD_TO_DEG;
    static const T INFINITY;
    static const T NEG_INFINITY;
    static const T QUITE_NAN;
    static const T SIGNALING_NAN;

    static T DegToRad(const T Val);
    static T RadToDeg(const T Val);
    static T ACos(const T Value);
    static T ASin(const T Value);
    static T ATan(const T Value);
    static T ATan2(const T Y, const T X);
    static T Ceil(const T Value);
    static T Cos(const T Value);
    static T Exp(const T Value);
    static T FAbs(const T Value);
    static T Floor(const T Value);
    static T FMod(const T Value);
    static T InvSqrt(const T Value);
    static T Log(const T Value);
    static T Pow(const T Value);
    static T Sin(const T Value);
    static T Sqr(const T Value);
    static T Sqrt(const T Value);
    static T Tan(const T Value);
    static T Abs(const T Value);

    static T Sign(const T Value);

    static T FastSin0(const T Angle);
    static T FastCos0(const T Angle);
    static T FastInvSin0(const T Angle);
    static T FastInvCos0(const T Angle);

    static T IsPowerOfTwo(const T Value);
    static T NextPowerOfTwo(const T Value);

    static T Min(const T A, const T B);
    static T Max(const T A, const T B);

    static T Clamp(const T Value, const T Min, const T Max);

    static T Round(const T Value);

    static RF_Type::Bool IsAlmostEqual(const T a, const T b);
    static RF_Type::Bool IsAlmostEqual(const T* a, const T* b,
        RF_Type::UInt32 ElementCount);

    static RF_Type::Bool IsNaN(const T Value);
    static RF_Type::Bool IsInfinity(const T Value);
protected:
    static const RF_Type::UInt32 FastSinArrayLen = 720;
    static const RF_Type::Float32 FastSinArray[FastSinArrayLen];
    static RF_Type::UInt32 GetFastSinArrayElement(const T Angle);
    static void Init();
    static RF_Type::Bool WasInitialized;
};

template<class T> T Math<T>::DegToRad(const T X)
{
    return X*Math<T>::DEG_TO_RAD;
}

template<class T> T Math<T>::RadToDeg(const T X)
{
    return X*Math<T>::RAD_TO_DEG;
}

template<class T> T Math<T>::ACos(const T X)
{
    return acos(X);
}

template<class T> T Math<T>::ASin(const T X)
{
    return asin(X);
}

template<class T> T Math<T>::ATan(const T X)
{
    return atan(X);
}

template<class T> T Math<T>::ATan2(const T Y, const T X)
{
    return atan2(Y, X);
}

template<class T> T Math<T>::Ceil(const T X)
{
    return ceil(X);
}

template<class T> T Math<T>::Cos(const T X)
{
    return cos(X);
}

template<class T> T Math<T>::Exp(const T X)
{
    return exp(X);
}

template<class T> T Math<T>::Floor(const T X)
{
    return floor(X);
}

template<class T> T Math<T>::FMod(const T X)
{
    return fmod(X);
}

template<class T> T Math<T>::InvSqrt(const T X)
{
    return (T)1 / sqrt(X);
}

template<class T> T Math<T>::Log(const T X)
{
    return log(X);
}

template<class T> T Math<T>::Pow(const T X)
{
    return pow(X, 2);
}

template<class T> T Math<T>::Tan(const T X)
{
    return tan(X);
}

template<class T> T Math<T>::Sqr(const T X)
{
    return X*X;
}

template<class T> T Math<T>::Sqrt(const T X)
{
    return sqrt(X);
}

template<class T> T Math<T>::Sign(const T X)
{
    return sign(X);
}

template<class T> T Math<T>::FastSin0(const T Angle)
{
    return GetFastSinArrayElement(Angle);
}

template<class T> T Math<T>::FastCos0(const T Angle)
{
    return FastSin0(Angle - (T)90);
}

template<class T> T Math<T>::FastInvSin0(const T Angle)
{
    return (T)1 / FastSin0(Angle);
}

template<class T> T Math<T>::FastInvCos0(const T Angle)
{
    return (T)1 / FastSin0(Angle - (T)90);
}

template<class T> T Math<T>::IsPowerOfTwo(const T Value)
{
    if(Value == (T)0)
        return (T)1;
    return (Value & (Value - (T)1)) == (T)0 ? (T)1 : (T)0;
}

template<class T> T Math<T>::NextPowerOfTwo(const T Value)
{
    const int BYTE_BITS = 8;
    T nextpot = Value;
    if(Value == (T)0)
        return (T)1;
    nextpot--;
    for(T i = 1; i < sizeof(T)*BYTE_BITS; i <<= 1)
        nextpot = nextpot | nextpot >> i;
    return nextpot + (T)1;
}

template<class T>T Math<T>::Sin(const T Value)
{
    return sin(Value);
}

template<class T>T Math<T>::FAbs(const T Value)
{
    return fabs(Value);
}

template<class T>T Math<T>::Abs(const T Value)
{
    return abs(Value);
}

template<class T> T Math<T>::Min(const T A, const T B)
{
    return A<B ? A : B;
}

template<class T> T Math<T>::Max(const T A, const T B)
{
    return A>B ? A : B;
}

template<class T> T Math<T>::Clamp(const T Value, const T Min, const T Max)
{
    if(Value < Min) return Min;
    if(Value > Max) return Max;
    return Value;
}

template<class T> T Math<T>::Round(const T Value)
{
    return nearbyint(Value);
}

template<class T>
RF_Type::Bool Math<T>::IsAlmostEqual(const T* a, const T* b,
    RF_Type::UInt32 ElementCount)
{
    for(RF_Type::UInt32 i = 0; i<ElementCount; ++i)
        if(FAbs(a[i] - b[i])>EPSILION)
            return false;
    return true;
}

template<class T>
RF_Type::Bool Math<T>::IsAlmostEqual(const T a, const T b)
{
    return (FAbs(a - b) <= EPSILION);
}

template<class T>
RF_Type::Bool Math<T>::IsNaN(const T Value)
{// NAN is never equal, try equal it self
    return Value != Value; //-V501
}

template<class T>
RF_Type::Bool Math<T>::IsInfinity(const T Value)
{
    return Value == INFINITY || Value == NEG_INFINITY;
}

template<class T>
RF_Type::UInt32 Math<T>::GetFastSinArrayElement(const T Angle)
{
    if(WasInitialized)
    {
        RF_Type::UInt32 index = (FastSinArrayLen / (T)360)*(Angle % 360);
        return FastSinArray[index];
    }
    else
    {
        Init();
        RF_Type::UInt32 index = (FastSinArrayLen / (T)360)*(Angle % 360);
        return FastSinArray[index];
    }
}

template<class T>
void Math<T>::Init()
{
    RF_Type::Float32 steps = (PI / 180.0f) / FastSinArrayLen;
    for(RF_Type::UInt32 i = 0; i < FastSinArrayLen; ++i)
        FastSinArray[i] = Sin(i*steps);
    WasInitialized = true;
}

typedef Math<RF_Type::Float32> MathF;
typedef Math<RF_Type::Float64> MathD;

} }

#ifndef RF_SHORTHAND_NAMESPACE_MATH
#define RF_SHORTHAND_NAMESPACE_MATH
namespace RF_Math = RadonFramework::Math;
#endif

#endif // RF_MATH_MATH_HPP
