#ifndef RF_CORE_POLICIES_CPPALLOCATOR_HPP
#define RF_CORE_POLICIES_CPPALLOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <new>

namespace RadonFramework::Core::Policies
{
struct CPPAllocator
{
  template <typename T>
  static T* New()
  {
    return new(std::nothrow) T;
  }

  template <typename T>
  static T* NewArray(RF_Type::Size Length)
  {
    if(Length == 0)
    {
      return nullptr;
    }
    return new(std::nothrow) T[Length];
  }

  template <typename T>
  static void Free(T* p)
  {
    if(p)
      delete p;
  }

  template <typename T>
  static void FreeArray(T* p)
  {
    {
      delete[] p;
    }
  }
};

}  // namespace RadonFramework::Core::Policies

#endif  // RF_CORE_POLICIES_CPPALLOCATOR_HPP
