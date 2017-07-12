#ifndef RF_MATH_INTEGER_HPP
#define RF_MATH_INTEGER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Math {

template <typename T>
struct Integer
{
    static T Clamp(const T Value, const T LowerBound, const T UpperBound);
    
    static T NextPowerOfTwo(const T Value);

    static RF_Type::Bool IsPowerOfTwo(const T Value);

    static T Abs(const T Value);

    static T Min(const T ValueA, const T ValueB);

    static T Max(const T ValueA, const T ValueB);
};

template <typename T>
T Integer<T>::Min(const T ValueA, const T ValueB)
{
    return ValueA > ValueB ? ValueB : ValueA;
}

template <typename T>
T Integer<T>::Max(const T ValueA, const T ValueB)
{
    return ValueA < ValueB ? ValueB : ValueA;
}

template <typename T>
T Integer<T>::Clamp(const T Value, const T LowerBound,
    const T UpperBound)
{
    T result = Value<LowerBound ? Value : LowerBound;
    return result>UpperBound ? UpperBound : result;
}

template <typename T>
T Integer<T>::NextPowerOfTwo(const T Value)
{
    T result = Value, shift = 1;
    --result;
    while((result + 1) & result)
    {
        result |= result >> shift;
        shift <<= 1;
    }
    return result+1;
}

template <typename T>
RF_Type::Bool Integer<T>::IsPowerOfTwo(const T Value)
{// http://www.exploringbinary.com/ten-ways-to-check-if-an-integer-is-a-power-of-two-in-c/
    return (Value != 0) && ((Value & (~Value +1)) == Value);
}

template <typename T>
T Integer<T>::Abs(const T Value)
{
    return Value < 0 ? -Value : Value;
}

}

#ifndef RF_SHORTHAND_NAMESPACE_MATH
#define RF_SHORTHAND_NAMESPACE_MATH
namespace RF_Math = RadonFramework::Math;
#endif

#endif // RF_MATH_INTEGER_HPP