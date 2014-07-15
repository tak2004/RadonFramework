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

} }

#ifndef RF_SHORTHAND_NAMESPACE_MATH
#define RF_SHORTHAND_NAMESPACE_MATH
namespace RF_Math = RadonFramework::Math;
#endif

#endif // RF_MATH_INTEGER_HPP