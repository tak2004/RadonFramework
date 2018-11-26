#ifndef RF_CORE_TYPES_ATOMICUINT64_HPP
#define RF_CORE_TYPES_ATOMICUINT64_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt64.hpp>

namespace RadonFramework::Core::Types
{
struct AtomicUInt64
{
public:
  typedef UInt64 DataType;
  AtomicUInt64(DataType Value = 0);
  AtomicUInt64(const AtomicUInt64& Other);

  DataType Increment();
  DataType Decrement();
  DataType FetchAndAdd(DataType Addend);
  DataType FetchAndExchange(DataType Value);
  /// Returns the initial value.
  DataType CompareAndExchange(DataType Compare, DataType Value);
  DataType Add(DataType Value);

  operator UInt64() const;
  bool operator!() const;
  bool operator!=(DataType Value) const;
  AtomicUInt64& operator=(DataType Value);
  AtomicUInt64& operator=(const AtomicUInt64& Other);
  bool operator==(DataType Value) const;
  AtomicUInt64& operator++();
  AtomicUInt64 operator++(Int32);
  AtomicUInt64& operator--();
  AtomicUInt64 operator--(Int32);

protected:
  DataType m_Data;
};

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::AtomicUInt64;
#endif

#endif  // RF_CORE_TYPES_ATOMICUINT64_HPP