#ifndef RF_CORE_TYPES_ATOMICINT16_HPP
#define RF_CORE_TYPES_ATOMICINT16_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Int16.hpp>

namespace RadonFramework::Core::Types
{
struct AtomicInt16
{
public:
  using DataType = RF_Type::Int16;
  AtomicInt16(DataType Value = 0);
  AtomicInt16(const AtomicInt16& Other) = default;

  DataType Increment();
  DataType Decrement();
  DataType FetchAndAdd(DataType Addend);
  DataType FetchAndExchange(DataType Value);
  DataType CompareAndExchange(DataType Compare, DataType Value);
  DataType Add(DataType Value);

  operator Int16() const;
  bool operator!() const;
  bool operator!=(DataType Value) const;
  AtomicInt16& operator=(DataType Value);
  AtomicInt16& operator=(const AtomicInt16& Other) = default;
  bool operator==(DataType Value) const;
  AtomicInt16& operator++();
  AtomicInt16 operator++(int);
  AtomicInt16& operator--();
  AtomicInt16 operator--(int);

protected:
  DataType m_Data;
};

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::AtomicInt16;
#endif

#endif  // RF_CORE_TYPES_ATOMICINT16_HPP