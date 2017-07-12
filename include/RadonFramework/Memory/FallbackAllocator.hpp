#ifndef RF_MEMORY_FALLBACKALLOCATOR_HPP
#define RF_MEMORY_FALLBACKALLOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/MemoryBlock.hpp>

namespace RadonFramework::Memory {

template<class PRIMARY, class FALLBACK>
class FallbackAllocator: private PRIMARY, private FALLBACK
{
public:
    MemoryBlock Allocate(const RF_Type::Size Bytes);
    void Deallocate(const MemoryBlock& Block);
    RF_Type::Bool Owns(const MemoryBlock& Block)const;
    void DeallocateAll();
};

template<class PRIMARY, class FALLBACK>
void FallbackAllocator<PRIMARY, FALLBACK>::DeallocateAll()
{
    PRIMARY::DeallocateAll();
    FALLBACK::DeallocateAll();
}

template<class PRIMARY, class FALLBACK>
void FallbackAllocator<PRIMARY, FALLBACK>::Deallocate(const MemoryBlock& Block)
{
    if (PRIMARY::Owns(Block))
    {
        PRIMARY::Deallocate(Block);
    }
    else
    {
        FALLBACK::Deallocate(Block);
    }
}

template<class PRIMARY, class FALLBACK>
RF_Type::Bool FallbackAllocator<PRIMARY, FALLBACK>::Owns(const MemoryBlock& Block) const
{
    return PRIMARY::Owns(Block) || FALLBACK::Owns(Block);
}

template<class PRIMARY, class FALLBACK>
inline MemoryBlock FallbackAllocator<PRIMARY, FALLBACK>::Allocate(const RF_Type::Size Bytes)
{
    auto result = PRIMARY::Allocate(Bytes);
    if (!result.Data)
    {
        result = FALLBACK::Allocate(Bytes);
    }
    return result;
}

}

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif // RF_MEMORY_FALLBACKALLOCATOR_HPP