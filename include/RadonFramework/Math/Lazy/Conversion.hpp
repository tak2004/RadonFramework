#ifndef RF_MATH_LAZY_CONVERSION_HPP
#define RF_MATH_LAZY_CONVERSION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Lazy/Types.hpp>

namespace RadonFramework::Math::Lazy {

template<typename T>
inline auto Literal(const T Value)
{
    return NumericLiteral<T>(Value);
}

template<typename T>
inline auto Variable(const T& Value)
{
    return Numeric<T>(Value);
}

template<typename F, typename P>
inline auto Lazy(const F Func, const P& Value)
{
    return LazyFunction<F, P>(Func, Value);
}

inline auto operator "" _l8(unsigned long long int Value)
{
    return NumericLiteral<RF_Type::Int8>(Value);
}

inline auto operator "" _lu8(unsigned long long int Value)
{
    return NumericLiteral<RF_Type::UInt8>(Value);
}

inline auto operator "" _l16(unsigned long long int Value)
{
    return NumericLiteral<RF_Type::Int16>(Value);
}

inline auto operator "" _lu16(unsigned long long int Value)
{
    return NumericLiteral<RF_Type::UInt16>(Value);
}

inline auto operator "" _l32(unsigned long long int Value)
{
    return NumericLiteral<RF_Type::Int32>(Value);
}

inline auto operator "" _lu32(unsigned long long int Value)
{
    return NumericLiteral<RF_Type::UInt32>(Value);
}

inline auto operator "" _l64(unsigned long long int Value)
{
    return NumericLiteral<RF_Type::Int64>(Value);
}

inline auto operator "" _lu64(unsigned long long int Value)
{
    return NumericLiteral<RF_Type::UInt64>(Value);
}

inline auto operator "" _lf(long double Value)
{
    return NumericLiteral<RF_Type::Float32>(Value);
}

inline auto operator "" _ld(long double Value)
{
    return NumericLiteral<RF_Type::Float64>(Value);
}

}

#ifndef RF_SHORTHAND_NAMESPACE_LAZY
#define RF_SHORTHAND_NAMESPACE_LAZY
namespace RF_Lazy = RadonFramework::Math::Lazy;
#endif

#endif // !RF_MATH_LAZY_CONVERSION_HPP