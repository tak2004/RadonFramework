#ifndef RF_MATH_LAZY_TYPES_HPP
#define RF_MATH_LAZY_TYPES_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Math::Lazy {

template<typename T>
struct NumericLiteral
{
    typedef T Type;

    NumericLiteral(const T Value)
        :m_Value(Value)
    {}

    const T m_Value;
};

template<typename T>
struct Numeric
{
    typedef T Type;

    Numeric(const T& V)
        :m_Value(V)
    {}

    const T& m_Value;
};

template<typename L, typename R>
struct LazyFunction
{
    typedef typename std::result_of<L(typename R::Type)>::type Type;

    const L m_Function;
    const R& m_Parameter;

    LazyFunction(const L Function, const R& Parameter)
        :m_Function(Function)
        , m_Parameter(Parameter)
    {}
};

}

#ifndef RF_SHORTHAND_NAMESPACE_LAZY
#define RF_SHORTHAND_NAMESPACE_LAZY
namespace RF_Lazy = RadonFramework::Math::Lazy;
#endif

#endif // !RF_MATH_LAZY_TYPES_HPP