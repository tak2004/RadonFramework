#ifndef RF_MEMORY_FREELISTALLOCATOR_HPP
#define RF_MEMORY_FREELISTALLOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/MemoryBlock.hpp>

namespace RadonFramework::Memory {

/// Use this class only for allocation of the same size and alignment.
/// It reserves a large chunk from the specified arena and split it up.
template<class ALLOCATOR, RF_Type::Size BLOCK_SIZE, RF_Type::Size BLOCK_ALIGN_SIZE>
class FreeListAllocator: private ALLOCATOR
{
public:
    FreeListAllocator();
    MemoryBlock Allocate(const RF_Type::Size Bytes);
    void Deallocate(MemoryBlock& Block);
    RF_Type::Bool Owns(const MemoryBlock& Block)const;
    void DeallocateAll();
protected:

private:
    struct Node
    {
        Node* Next;
    }* m_Root;
};

template<class ALLOCATOR, RF_Type::Size BLOCK_SIZE, RF_Type::Size BLOCK_ALIGN_SIZE>
void FreeListAllocator<ALLOCATOR, BLOCK_SIZE, BLOCK_ALIGN_SIZE>::DeallocateAll()
{
    ALLOCATOR::DeallocateAll();
    m_Root = nullptr;
}

template<class ALLOCATOR, RF_Type::Size BLOCK_SIZE, RF_Type::Size BLOCK_ALIGN_SIZE>
RF_Type::Bool FreeListAllocator<ALLOCATOR, BLOCK_SIZE, BLOCK_ALIGN_SIZE>::Owns(const MemoryBlock& Block) const
{
    return Block.Bytes == BLOCK_SIZE || ALLOCATOR::Owns(Block);
}

template<class ALLOCATOR, RF_Type::Size BLOCK_SIZE, RF_Type::Size BLOCK_ALIGN_SIZE>
void FreeListAllocator<ALLOCATOR, BLOCK_SIZE, BLOCK_ALIGN_SIZE>::Deallocate(MemoryBlock& Block)
{
    if(Block.Bytes != BLOCK_SIZE)
    {
        return ALLOCATOR::Deallocate(Block);
    }
    auto* p = (Node*)Block.Data;
    p->Next = m_Root;
    m_Root = p;
}

template<class ALLOCATOR, RF_Type::Size BLOCK_SIZE, RF_Type::Size BLOCK_ALIGN_SIZE>
MemoryBlock FreeListAllocator<ALLOCATOR, BLOCK_SIZE, BLOCK_ALIGN_SIZE>::Allocate(const RF_Type::Size Bytes)
{
    if(Bytes == BLOCK_SIZE && m_Root)
    {
        MemoryBlock result = {reinterpret_cast<RF_Type::UInt8*>(m_Root), Bytes};
        m_Root = m_Root->Next;
        return result;
    }
    return ALLOCATOR::Allocate(Bytes);
}

template<class ALLOCATOR, RF_Type::Size BLOCK_SIZE, RF_Type::Size BLOCK_ALIGN_SIZE>
FreeListAllocator<ALLOCATOR, BLOCK_SIZE, BLOCK_ALIGN_SIZE>::FreeListAllocator()
:m_Root(nullptr)
{
}

}

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif // ! RF_MEMORY_FREELISTALLOCATOR_HPP