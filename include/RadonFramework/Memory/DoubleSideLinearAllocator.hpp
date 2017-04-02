#ifndef RF_MEMORY_DOUBLESIDESTACKALLOCATOR_HPP
#define RF_MEMORY_DOUBLESIDESTACKALLOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/MemoryBlock.hpp>

namespace RadonFramework { namespace Memory {

template<class ALLOCATOR, RF_Type::Size BLOCK_SIZE, RF_Type::Size BLOCK_ALIGN_SIZE>
class DoubleSideStackAllocator: private ALLOCATOR
{
public:
    DoubleSideStackAllocator();
    MemoryBlock Allocate(const RF_Type::Size Bytes);
    void Deallocate(const MemoryBlock& Block);
    RF_Type::Bool Owns(const MemoryBlock& Block)const;
    void DeallocateAll();
};



} }

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif // ! RF_MEMORY_DOUBLESIDESTACKALLOCATOR_HPP