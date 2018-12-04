#ifndef RF_CORE_TYPES_ATOMICINT64_HPP
#define RF_CORE_TYPES_ATOMICINT64_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/Int64.hpp>

namespace RadonFramework::Core::Types
{
struct AtomicInt64
{
public:
  using DataType = RF_Type::Int64;
  AtomicInt64(DataType Value = 0);
  AtomicInt64(const AtomicInt64& Other) = default;

  DataType Increment();
  DataType Decrement();
  DataType FetchAndAdd(DataType Addend);
  DataType FetchAndExchange(DataType Value);
  DataType CompareAndExchange(DataType Compare, DataType Value);
  DataType Add(DataType Value);

  operator Int64() const;
  bool operator!() const;
  bool operator!=(DataType Value) const;
  AtomicInt64& operator=(DataType Value);
  AtomicInt64& operator=(const AtomicInt64& Other) = default;
  bool operator==(DataType Value) const;
  AtomicInt64& operator++();
  AtomicInt64 operator++(Int32);
  AtomicInt64& operator--();
  AtomicInt64 operator--(Int32);

protected:
  DataType m_Data;
};

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::AtomicInt64;
#endif

#endif  // RF_CORE_TYPES_ATOMICINT64_HPP