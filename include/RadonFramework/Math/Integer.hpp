#ifndef RF_MATH_INTEGER_HPP
#define RF_MATH_INTEGER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/Int8.hpp>
#include <RadonFramework/Core/Types/UInt16.hpp>
#include <RadonFramework/Core/Types/Int16.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/UInt64.hpp>
#include <RadonFramework/Core/Types/Int64.hpp>

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

typedef Integer<RF_Type::UInt8> UInt8;
typedef Integer<RF_Type::UInt16> UInt16;
typedef Integer<RF_Type::UInt32> UInt32;
typedef Integer<RF_Type::UInt64> UInt64;
typedef Integer<RF_Type::Int8> Int8;
typedef Integer<RF_Type::Int16> Int16;
typedef Integer<RF_Type::Int32> Int32;
typedef Integer<RF_Type::Int64> Int64;

}

#ifndef RF_SHORTHAND_NAMESPACE_MATH
#define RF_SHORTHAND_NAMESPACE_MATH
namespace RF_Math = RadonFramework::Math;
#endif

#endif // RF_MATH_INTEGER_HPP