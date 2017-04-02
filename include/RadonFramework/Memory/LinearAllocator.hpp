#ifndef RF_MEMORY_LINEARALLOCATOR_HPP
#define RF_MEMORY_LINEARALLOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/MemoryBlock.hpp>

namespace RadonFramework { namespace Memory {

template<class ALLOCATOR, RF_Type::Size BLOCK_SIZE, RF_Type::Size BLOCK_ALIGN_SIZE>
class LinearAllocator: private ALLOCATOR
{
public:
    LinearAllocator();
    explicit LinearAllocator(const RF_Type::Size Reserve);
    MemoryBlock Allocate(const RF_Type::Size Bytes);
    void Deallocate(const MemoryBlock& Block);
    RF_Type::Bool Owns(const MemoryBlock& Block)const;
    void DeallocateAll();
private:
    MemoryBlock m_Pool;
    RF_Type::UInt8* m_Current;
};

template<class ALLOCATOR, RF_Type::Size BLOCK_SIZE, RF_Type::Size BLOCK_ALIGN_SIZE>
void LinearAllocator<ALLOCATOR, BLOCK_SIZE, BLOCK_ALIGN_SIZE>::DeallocateAll()
{
    m_Current = m_Pool.Data;
}

template<class ALLOCATOR, RF_Type::Size BLOCK_SIZE, RF_Type::Size BLOCK_ALIGN_SIZE>
RF_Type::Bool LinearAllocator<ALLOCATOR, BLOCK_SIZE, BLOCK_ALIGN_SIZE>::Owns(const MemoryBlock& Block) const
{
    return (Block.Data >= m_Pool.Data) && (m_Pool.Data + m_Pool.Bytes < Block.Data);
}

template<class ALLOCATOR, RF_Type::Size BLOCK_SIZE, RF_Type::Size BLOCK_ALIGN_SIZE>
void LinearAllocator<ALLOCATOR, BLOCK_SIZE, BLOCK_ALIGN_SIZE>::Deallocate(const MemoryBlock& Block)
{

}

template<class ALLOCATOR, RF_Type::Size BLOCK_SIZE, RF_Type::Size BLOCK_ALIGN_SIZE>
MemoryBlock LinearAllocator<ALLOCATOR, BLOCK_SIZE, BLOCK_ALIGN_SIZE>::Allocate(const RF_Type::Size Bytes)
{
    MemoryBlock result={nullptr, 0};
    if(m_Current + Bytes < m_Pool.Data + m_Pool.Bytes)
    {
        result.Data = m_Current;
        result.Bytes = Bytes;
        m_Current += Bytes;
    }
    return result;
}

template<class ALLOCATOR, RF_Type::Size BLOCK_SIZE, RF_Type::Size BLOCK_ALIGN_SIZE>
LinearAllocator<ALLOCATOR, BLOCK_SIZE, BLOCK_ALIGN_SIZE>::LinearAllocator(const RF_Type::Size Reserve)
{
    m_Pool = ALLOCATOR::Allocate(Reserve);
    m_Current = m_Pool.Data;
}

template<class ALLOCATOR, RF_Type::Size BLOCK_SIZE, RF_Type::Size BLOCK_ALIGN_SIZE>
LinearAllocator<ALLOCATOR, BLOCK_SIZE, BLOCK_ALIGN_SIZE>::LinearAllocator()
:m_Current(nullptr)
{
    m_Pool.Data = nullptr;
    m_Pool.Bytes = 0;
}

} }

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif // ! RF_MEMORY_LINEARALLOCATOR_HPP