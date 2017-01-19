#ifndef RF_MEMORY_ALLOCATORS_HPP
#define RF_MEMORY_ALLOCATORS_HPP

#include <RadonFramework/Core/Meta/If.hpp>
#include <RadonFramework/Memory/FixSizeStackAllocator.hpp>
#include <RadonFramework/Memory/HeapAllocator.hpp>

namespace RadonFramework { namespace Memory {

template<class TRAITCLASS>
struct AllocatorSelector
{
    typedef typename RF_Meta::If<TRAITCLASS::AllocatorTraits::HeapAllocation, HeapAllocator,
        FixSizeStackAllocator<TRAITCLASS::AllocatorTraits::StackSize, 
            TRAITCLASS::AllocatorTraits::AlignSize> >::Value BaseAllocator;
    typedef BaseAllocator Type;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif // RF_MEMORY_ALLOCATORS_HPP