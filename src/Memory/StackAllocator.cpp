#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Memory/StackAllocator.hpp"

using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;

StackAllocator::StackAllocator(Size ReservedMemorySize)
:m_AllocatedMemorySize(0)
,m_ZeroFreedMemory(false)
,m_ZeroPopedMemory(false)
{
    m_ReservedMemory=AutoPointerArray<UInt8>(new UInt8[ReservedMemorySize], ReservedMemorySize);
}

void StackAllocator::Clear()
{
    if (m_ZeroFreedMemory)
        RFMEM::Set(m_ReservedMemory.Get(), 0, m_ReservedMemory.Size());
    m_AllocatedMemorySize=0;
}

/**
 * Memory layout: [reserved memory chunk|n-bytes][size of chunk|sizeof(void*)-bytes]
 * The pointer to the reserved memory pool + size of user reserved memory
 * point to the up comming memory block and -sizeof(void*) point to the size
 * of the last chunk.
 */
void* StackAllocator::Push(Size MemorySize)
{
    void* result=0;
    Size neccessarySpace=MemorySize+m_AllocatedMemorySize+sizeof(Size);
    if (neccessarySpace<m_ReservedMemory.Size())
    {
        result=m_ReservedMemory.Get()+m_AllocatedMemorySize;
        Size* ptr=reinterpret_cast<Size*>(reinterpret_cast<UInt8*>(result)+MemorySize);
        *ptr=MemorySize;
        (m_AllocatedMemorySize+=MemorySize)+=sizeof(Size);
    }
    return result;
}

Size* StackAllocator::GetSize()const
{
    return reinterpret_cast<Size*>(m_ReservedMemory.Get()+m_AllocatedMemorySize-sizeof(Size));
}

void StackAllocator::Pop()
{
    Size* ptr=GetSize();
    if (m_ZeroPopedMemory)
        RFMEM::Set(ptr-(*ptr),0,(size_t)(*ptr));
    (m_AllocatedMemorySize-=(*ptr))-=sizeof(Size);
}

void* StackAllocator::Peek()const
{
    void* result=0;
    if (m_AllocatedMemorySize>0)
    {
        Size* ptr=GetSize();
        result=reinterpret_cast<void*>(reinterpret_cast<UInt8*>(ptr)-*ptr);
    }
    return result;
}

Size StackAllocator::PeekSize()const
{
    return *GetSize();
}