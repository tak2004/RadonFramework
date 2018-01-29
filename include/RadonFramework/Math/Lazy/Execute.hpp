#ifndef RF_MATH_LAZY_EXECUTE_HPP
#define RF_MATH_LAZY_EXECUTE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Lazy/Operator.hpp>

namespace RadonFramework::Math::Lazy {

template<typename T>
inline T Execute(const NumericLiteral<T>& Value)
{
    return Value.m_Value;
}

template<typename T>
inline T Execute(const Numeric<T>& Value)
{
    return Value.m_Value;
}

template<typename L, typename R>
inline auto Execute(const Operator<L, R, OperationType::Multiplication>& Expression)
{
    return Execute(Expression.m_Left)*Execute(Expression.m_Right);
}

template<typename L, typename R>
inline auto Execute(const Operator<L, R, OperationType::Addition>& Expression)
{
    return Execute(Expression.m_Left) + Execute(Expression.m_Right);
}

template<typename L, typename R>
inline auto Execute(const Operator<L, R, OperationType::Substraction>& Expression)
{
    return Execute(Expression.m_Left) - Execute(Expression.m_Right);
}

template<typename L, typename R>
inline auto Execute(const Operator<L, R, OperationType::Divition>& Expression)
{
    return Execute(Expression.m_Left) / Execute(Expression.m_Right);
}

template<typename L, typename R>
inline auto Execute(const LazyFunction<L, R>& Expression)
{
    return Expression.m_Function(Execute(Expression.m_Parameter));
}

}

#ifndef RF_SHORTHAND_NAMESPACE_LAZY
#define RF_SHORTHAND_NAMESPACE_LAZY
namespace RF_Lazy = RadonFramework::Math::Lazy;
#endif

#endif // !RF_MATH_LAZY_EXECUTE_HPP