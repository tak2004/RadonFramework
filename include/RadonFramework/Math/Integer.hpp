#ifndef RF_MATH_INTEGER_HPP
#define RF_MATH_INTEGER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Math
    {
        template <typename T>
        struct Integer
        {
            static T Clamp(const T Value, const T LowerBound, const T UpperBound);
            static T ClampUpperBound(const T Value, const T UpperBound);
            static T ClampLowerBound(const T Value, const T LowerBound);
        };
    }
}

template <typename T>
T RadonFramework::Math::Integer<T>::Clamp( const T Value, const T LowerBound, 
    const T UpperBound)
{
    T result=Value<LowerBound?Value:LowerBound;
    return result>UpperBound?UpperBound:result;
}

template <typename T>
T RadonFramework::Math::Integer<T>::ClampUpperBound( const T Value, const T UpperBound )
{
    return Value>UpperBound?UpperBound:Value;
}

template <typename T>
T RadonFramework::Math::Integer<T>::ClampLowerBound( const T Value, const T LowerBound )
{
    return Value<LowerBound?LowerBound:Value;
}



#endif // RF_MATH_INTEGER_HPP