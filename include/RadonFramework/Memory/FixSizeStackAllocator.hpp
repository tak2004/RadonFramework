#ifndef RF_MEMORY_FIXSIZESTACKALLOCATOR_HPP
#define RF_MEMORY_FIXSIZESTACKALLOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/MemoryBlock.hpp>

namespace RadonFramework { namespace Memory {

template<RF_Type::Size SIZE, RF_Type::Size ALIGN_SIZE = 16>
class FixSizeStackAllocator
{
public:
    FixSizeStackAllocator();
    MemoryBlock Allocate(const RF_Type::Size Bytes);
    void Deallocate(const MemoryBlock& Block);
    RF_Type::Bool Owns(const MemoryBlock& Block)const;
    void DeallocateAll();
private:
    RF_Type::UInt8 m_Data[SIZE];
    RF_Type::UInt8* m_Current;
    static RF_Type::Size RoundToNextAligned(RF_Type::Size Bytes);
};

template<RF_Type::Size SIZE, RF_Type::Size ALIGN_SIZE>
RF_Type::Size FixSizeStackAllocator<SIZE, ALIGN_SIZE>::RoundToNextAligned(RF_Type::Size Bytes)
{
    auto floor = (Bytes / ALIGN_SIZE) * ALIGN_SIZE;

    if(floor == Bytes) {
        return floor;
    }
    else 
    {
        return floor + ALIGN_SIZE;
    }
}

template<RF_Type::Size SIZE, RF_Type::Size ALIGN_SIZE>
void FixSizeStackAllocator<SIZE, ALIGN_SIZE>::Deallocate(const MemoryBlock& Block)
{
    if(Block.Data + RoundToNextAligned(Block.Bytes) == m_Current)
    {
        m_Current = Block.Data;
    }
}

template<RF_Type::Size SIZE, RF_Type::Size ALIGN_SIZE>
RF_Type::Bool FixSizeStackAllocator<SIZE, ALIGN_SIZE>::Owns(const MemoryBlock& Block) const
{
    return Block.Data >= m_Data && Block.Data < m_Data + SIZE;
}

template<RF_Type::Size SIZE, RF_Type::Size ALIGN_SIZE>
void FixSizeStackAllocator<SIZE, ALIGN_SIZE>::DeallocateAll()
{
    m_Current = m_Data;
}

template<RF_Type::Size SIZE, RF_Type::Size ALIGN_SIZE>
MemoryBlock FixSizeStackAllocator<SIZE, ALIGN_SIZE>::Allocate(const RF_Type::Size Bytes)
{
    MemoryBlock result={nullptr,0};
    auto next = RoundToNextAligned(Bytes);
    if(next > (m_Data + SIZE) - m_Current)
    {
        return result;
    }
    result = {m_Current, Bytes};
    m_Current += next;
    return result;
}

template<RF_Type::Size SIZE, RF_Type::Size ALIGN_SIZE>
FixSizeStackAllocator<SIZE, ALIGN_SIZE>::FixSizeStackAllocator()
:m_Current(m_Data)
{
}

} }

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif // RF_MEMORY_FIXSIZESTACKALLOCATOR_HPP