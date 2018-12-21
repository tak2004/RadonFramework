#ifndef RF_MATH_LAZY_RETURN_TYPE_HPP
#define RF_MATH_LAZY_RETURN_TYPE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Math::Lazy
{
template <typename L, typename R>
struct ReturnType
{
};

template <typename T>
struct ReturnType<T, T>
{
  using Type = T;
};

template <>
struct ReturnType<RF_Type::Float32, RF_Type::UInt8>
{
  using Type = RF_Type::Float32;
};

template <>
struct ReturnType<RF_Type::Float32, RF_Type::UInt16>
{
  using Type = RF_Type::Float32;
};

template <>
struct ReturnType<RF_Type::Float32, RF_Type::UInt32>
{
  using Type = RF_Type::Float32;
};

template <>
struct ReturnType<RF_Type::Float32, RF_Type::UInt64>
{
  using Type = RF_Type::Float32;
};

template <>
struct ReturnType<RF_Type::Float32, RF_Type::Int8>
{
  using Type = RF_Type::Float32;
};

template <>
struct ReturnType<RF_Type::Float32, RF_Type::Int16>
{
  using Type = RF_Type::Float32;
};

template <>
struct ReturnType<RF_Type::Float32, RF_Type::Int32>
{
  using Type = RF_Type::Float32;
};

template <>
struct ReturnType<RF_Type::Float32, RF_Type::Int64>
{
  using Type = RF_Type::Float32;
};

template <>
struct ReturnType<int, float>
{
  using Type = float;
};

}  // namespace RadonFramework::Math::Lazy

#ifndef RF_SHORTHAND_NAMESPACE_LAZY
#define RF_SHORTHAND_NAMESPACE_LAZY
namespace RF_Lazy = RadonFramework::Math::Lazy;
#endif

#endif  // !RF_MATH_LAZY_RETURN_TYPE_HPP