#ifndef RF_CORE_POLICIES_CMEMORYOPERATION_HPP
#define RF_CORE_POLICIES_CMEMORYOPERATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/Size.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Defines.hpp>
#include <type_traits>
#include <RadonFramework/System/Memory.hpp>

namespace RadonFramework::Core::Policies
{
struct CMemoryOperation
{
  template <typename T>
  static RF_Type::Int32
  Compare(const T* P1, const T* P2, RF_Type::Size ElementCount)
  {
    return RF_SysMem::Compare(reinterpret_cast<const void*>(P1),
                              reinterpret_cast<const void*>(P2),
                              ElementCount * sizeof(T));
  }

  template <typename T>
  static T* Copy(T* Destination, const T* Source, RF_Type::Size ElementCount)
  {
    if(std::is_trivially_copyable<T>::value == false)
    {  // use assign operator to copy by value
      for(RF_Type::Size i = 0; i < ElementCount; ++i)
      {
        Destination[i] = Source[i];
      }
      return Destination;
    }
    else
    {  // use the fastest possible copy function(e.g. sse2)
      RF_SysMem::Copy(Destination, Source, ElementCount * sizeof(T));
      return Destination;
    }
  }

  template <typename T>
  static T* Move(T* Destination, const T* Source, RF_Type::Size ElementCount)
  {
    if(std::is_trivially_copyable<T>::value == false)
    {
      for(RF_Type::Size i = 0; i < ElementCount; ++i)
      {
        Destination[i] = Source[i];
      }
      return Destination;
    }
    else
    {
      RF_SysMem::Move(Destination, Source, ElementCount * sizeof(T));
      return Destination;
    }
  }

  template <typename T>
  static T* Set(T* Pointer, RF_Type::UInt32 Value, RF_Type::Size ElementCount)
  {
    RF_SysMem::Set(Pointer, Value, ElementCount * sizeof(T));
    return Pointer;
  }
};

}  // namespace RadonFramework::Core::Policies

#ifndef RF_SHORTHAND_NAMESPACE_POLICY
#define RF_SHORTHAND_NAMESPACE_POLICY
namespace RF_Policy = RadonFramework::Core::Policies;
#endif

#endif  // RF_CORE_POLICIES_CMEMORYOPERATION_HPP