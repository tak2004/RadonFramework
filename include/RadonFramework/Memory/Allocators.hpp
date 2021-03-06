#ifndef RF_MEMORY_ALLOCATORS_HPP
#define RF_MEMORY_ALLOCATORS_HPP

#include <RadonFramework/Core/Meta/If.hpp>
#include <RadonFramework/Memory/FixSizeStackAllocator.hpp>
#include <RadonFramework/Memory/HeapAllocator.hpp>

namespace RadonFramework::Memory
{
template <class TRAITCLASS>
struct AllocatorSelector
{
  using BaseAllocator = typename RF_Meta::If<
      TRAITCLASS::AllocatorTraits::HeapAllocation,
      HeapAllocator,
      FixSizeStackAllocator<TRAITCLASS::AllocatorTraits::StackSize,
                            TRAITCLASS::AllocatorTraits::AlignSize>>::Value;
  using Type = BaseAllocator;
};

}  // namespace RadonFramework::Memory

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif  // RF_MEMORY_ALLOCATORS_HPP