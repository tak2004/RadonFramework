#ifndef RF_CORE_POLICIES_MALLOCALLOCATOR_HPP
#define RF_CORE_POLICIES_MALLOCALLOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Traits/AllocatorTraits.hpp>
#include <RadonFramework/Core/Common/Assert.hpp>
#include <cstdlib>

namespace RadonFramework::Core::Policies
{
struct MallocAllocator
{
  static void* Allocate(Traits::AllocatorTraits<void>::SizeType Size);
  static void
  Deallocate(void* Ptr, Traits::AllocatorTraits<void>::SizeType Size);
  static void* Reallocate(void* Ptr,
                          Traits::AllocatorTraits<void>::SizeType OldSize,
                          Traits::AllocatorTraits<void>::SizeType NewSize);
};

}  // namespace RadonFramework::Core::Policies

#ifndef RF_SHORTHAND_NAMESPACE_POLICY
#define RF_SHORTHAND_NAMESPACE_POLICY
namespace RF_Policy = RadonFramework::Core::Policies;
#endif

#endif  // RF_CORE_POLICIES_MALLOCALLOCATOR_HPP