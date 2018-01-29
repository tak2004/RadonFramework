#ifndef RF_MATH_LAZY_RETURN_TYPE_HPP
#define RF_MATH_LAZY_RETURN_TYPE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Math::Lazy {

template<typename L, typename R>
struct ReturnType
{};

template<typename T>
struct ReturnType<T, T>
{
    typedef T Type;
};

template<>
struct ReturnType<RF_Type::Float32, RF_Type::UInt8>
{
    typedef RF_Type::Float32 Type;
};

template<>
struct ReturnType<RF_Type::Float32, RF_Type::UInt16>
{
    typedef RF_Type::Float32 Type;
};

template<>
struct ReturnType<RF_Type::Float32, RF_Type::UInt32>
{
    typedef RF_Type::Float32 Type;
};

template<>
struct ReturnType<RF_Type::Float32, RF_Type::UInt64>
{
    typedef RF_Type::Float32 Type;
};

template<>
struct ReturnType<RF_Type::Float32, RF_Type::Int8>
{
    typedef RF_Type::Float32 Type;
};

template<>
struct ReturnType<RF_Type::Float32, RF_Type::Int16>
{
    typedef RF_Type::Float32 Type;
};

template<>
struct ReturnType<RF_Type::Float32, RF_Type::Int32>
{
    typedef RF_Type::Float32 Type;
};

template<>
struct ReturnType<RF_Type::Float32, RF_Type::Int64>
{
    typedef RF_Type::Float32 Type;
};

template<>
struct ReturnType<int, float>
{
    typedef float Type;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_LAZY
#define RF_SHORTHAND_NAMESPACE_LAZY
namespace RF_Lazy = RadonFramework::Math::Lazy;
#endif

#endif // !RF_MATH_LAZY_RETURN_TYPE_HPP