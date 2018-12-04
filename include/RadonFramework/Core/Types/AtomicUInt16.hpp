#ifndef RF_CORE_TYPES_ATOMICUINT16_HPP
#define RF_CORE_TYPES_ATOMICUINT16_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt16.hpp>

namespace RadonFramework::Core::Types
{
struct AtomicUInt16
{
public:
  using DataType = RF_Type::UInt16;
  AtomicUInt16(DataType Value = 0);
  AtomicUInt16(const AtomicUInt16& Other) = default;

  DataType Increment();
  DataType Decrement();
  DataType FetchAndAdd(DataType Addend);
  DataType FetchAndExchange(DataType Value);
  DataType CompareAndExchange(DataType Compare, DataType Value);
  DataType Add(DataType Value);

  operator UInt16() const;
  bool operator!() const;
  bool operator!=(DataType Value) const;
  AtomicUInt16& operator=(DataType Value);
  AtomicUInt16& operator=(const AtomicUInt16& Other) = default;
  bool operator==(DataType Value) const;
  AtomicUInt16& operator++();
  AtomicUInt16 operator++(int);
  AtomicUInt16& operator--();
  AtomicUInt16 operator--(int);

protected:
  DataType m_Data;
};

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::AtomicUInt16;
#endif

#endif  // RF_CORE_TYPES_ATOMICUINT16_HPP