#ifndef RF_MATH_LAZY_OPERATOR_HPP
#define RF_MATH_LAZY_OPERATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Lazy/ReturnType.hpp>

namespace RadonFramework::Math::Lazy {

enum class OperationType
{
    Multiplication,
    Divition,
    Addition,
    Substraction
};


template<typename L, typename R, OperationType Op>
struct Operator
{
    typedef typename ReturnType<typename L::Type, typename R::Type>::Type Type;

    const L& m_Left;
    const R& m_Right;

    Operator(const L& Left, const R& Right)
        :m_Left(Left)
        , m_Right(Right)
    {}
};

template<typename L, typename R>
inline auto operator*(const L& Left, const R& Right)
{
    return Operator<L, R, OperationType::Multiplication>(Left, Right);
}

template<typename L, typename R>
inline auto operator+(const L& Left, const R& Right)
{
    return Operator<L, R, OperationType::Addition>(Left, Right);
}

template<typename L, typename R>
inline auto operator-(const L& Left, const R& Right)
{
    return Operator<L, R, OperationType::Substraction>(Left, Right);
}

template<typename L, typename R>
inline auto operator/(const L& Left, const R& Right)
{
    return Operator<L, R, OperationType::Divition>(Left, Right);
}

}

#ifndef RF_SHORTHAND_NAMESPACE_LAZY
#define RF_SHORTHAND_NAMESPACE_LAZY
namespace RF_Lazy = RadonFramework::Math::Lazy;
#endif

#endif // !RF_MATH_LAZY_OPERATOR_HPP