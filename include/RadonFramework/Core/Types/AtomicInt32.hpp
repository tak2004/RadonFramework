#ifndef RF_CORE_TYPES_ATOMICINT32_HPP
#define RF_CORE_TYPES_ATOMICINT32_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Int32.hpp>

namespace RadonFramework::Core::Types
{
struct AtomicInt32
{
public:
  typedef RF_Type::Int32 DataType;
  AtomicInt32(DataType Value = 0);
  AtomicInt32(const AtomicInt32& Other);

  DataType Increment();
  DataType Decrement();
  DataType FetchAndAdd(DataType Addend);
  DataType FetchAndExchange(DataType Value);
  DataType CompareAndExchange(DataType Compare, DataType Value);
  DataType Add(DataType Value);

  operator Int32() const;
  bool operator!() const;
  bool operator!=(DataType Value) const;
  AtomicInt32& operator=(DataType Value);
  AtomicInt32& operator=(const AtomicInt32& Other);
  bool operator==(DataType Value) const;
  AtomicInt32& operator++();
  AtomicInt32 operator++(Int32);
  AtomicInt32& operator--();
  AtomicInt32 operator--(Int32);

protected:
  DataType m_Data;
};

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::AtomicInt32;
#endif

#endif  // RF_CORE_TYPES_ATOMICINT_HPP