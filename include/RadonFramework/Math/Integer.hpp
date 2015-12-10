#ifndef RF_MATH_INTEGER_HPP
#define RF_MATH_INTEGER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Math {

template <typename T>
struct Integer
{
    static T Clamp(const T Value, const T LowerBound, const T UpperBound);
    
    /// Equal to min.
    static T ClampUpperBound(const T Value, const T UpperBound);
    
    /// Equal to max.
    static T ClampLowerBound(const T Value, const T LowerBound);

    static T NextPowerOfTwo(const T Value);

    static RF_Type::Bool IsPowerOfTwo(const T Value);
};

template <typename T>
T Integer<T>::Clamp(const T Value, const T LowerBound,
    const T UpperBound)
{
    T result = Value<LowerBound ? Value : LowerBound;
    return result>UpperBound ? UpperBound : result;
}

template <typename T>
T Integer<T>::ClampUpperBound(const T Value, const T UpperBound)
{
    return Value > UpperBound ? UpperBound : Value;
}

template <typename T>
T Integer<T>::ClampLowerBound(const T Value, const T LowerBound)
{
    return Value < LowerBound ? LowerBound : Value;
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

} }

#ifndef RF_SHORTHAND_NAMESPACE_MATH
#define RF_SHORTHAND_NAMESPACE_MATH
namespace RF_Math = RadonFramework::Math;
#endif

#endif // RF_MATH_INTEGER_HPP