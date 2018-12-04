#ifndef RF_CORE_TYPES_VEC_HPP
#define RF_CORE_TYPES_VEC_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/MemoryRange.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/System/CompilerConfig.hpp>

namespace RadonFramework::Core::Types
{
template <typename T, int C>
struct RF_ALIGN(16) Vec
{
  T m_Vector[C];

  T& operator[](const MemoryRange Index)
  {
    Assert(static_cast<UInt32>(Index) < static_cast<UInt32>(C),
           "Index out of bound.");
    return m_Vector[Index];
  }

  T operator[](const MemoryRange Index) const
  {
    Assert(static_cast<UInt32>(Index) < static_cast<UInt32>(C),
           "Index out of bound.");
    return m_Vector[Index];
  }

  using ValueType = T;
};

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#endif  // RF_CORE_TYPES_VEC_HPP