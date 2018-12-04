#ifndef RF_CORE_TYPES_ATOMICUINT32_HPP
#define RF_CORE_TYPES_ATOMICUINT32_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt32.hpp>

namespace RadonFramework::Core::Types
{
struct AtomicUInt32
{
public:
  using DataType = RF_Type::UInt32;
  AtomicUInt32(DataType Value = 0);
  AtomicUInt32(const AtomicUInt32& Other) = default;

  DataType Increment();
  DataType Decrement();
  DataType FetchAndAdd(DataType Addend);
  DataType FetchAndExchange(DataType Value);
  DataType CompareAndExchange(DataType Compare, DataType Value);
  DataType Add(DataType Value);

  operator UInt32() const;
  bool operator!() const;
  bool operator!=(DataType Value) const;
  AtomicUInt32& operator=(DataType Value);
  AtomicUInt32& operator=(const AtomicUInt32& Other) = default;
  bool operator==(DataType Value) const;
  AtomicUInt32& operator++();
  AtomicUInt32 operator++(int);
  AtomicUInt32& operator--();
  AtomicUInt32 operator--(int);

protected:
  DataType m_Data;
};

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::AtomicUInt32;
#endif

#endif  // RF_CORE_TYPES_ATOMICUINT32_HPP