#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Memory/StackAllocator.hpp"

using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;

StackAllocator::StackAllocator(Size ReservedMemorySize)
:m_AllocatedMemorySize(0)
,m_PushesInProgress(0)
,m_ZeroFreedMemory(false)
,m_ZeroPopedMemory(false)
{
    m_ReservedMemory=AutoPointerArray<UInt8>(ReservedMemorySize);
}

void StackAllocator::Clear()
{
    Lock();
    if (m_ZeroFreedMemory)
        RF_SysMem::Set(m_ReservedMemory.Get(), 0, m_ReservedMemory.Size());
    m_AllocatedMemorySize=0;
    Unlock();
}

/**
 * Memory layout: [reserved memory chunk|n-bytes][size of chunk|sizeof(void*)-bytes]
 * The pointer to the reserved memory pool + size of user reserved memory
 * point to the up comming memory block and -sizeof(void*) point to the size
 * of the last chunk.
 * The lock mechanic allows Push to stack up and prioritize it over all other
 * methods. Only if all Push calls are done the other methods are able to run.
 */
void* StackAllocator::Push(Size MemorySize)
{
    void* result=0;
    Size neccessarySpace=MemorySize+sizeof(Size);
    RF_Type::Int32 a = RF_Math::Integer<RF_Type::Int32>::Max(0, m_PushesInProgress), 
        b;
    b = a + 1;

    while(m_PushesInProgress.CompareAndExchange(a, b) != a)
    {
        a = RF_Math::Integer<RF_Type::Int32>::Max(0, m_PushesInProgress);
        b = a + 1;
    }

    auto offset = m_AllocatedMemorySize.FetchAndAdd(neccessarySpace);
    if (offset+neccessarySpace <= m_ReservedMemory.Size())
    {
        result=m_ReservedMemory.Get() + offset;
        Size* ptr=reinterpret_cast<Size*>(reinterpret_cast<UInt8*>(result)+MemorySize);
        *ptr=MemorySize;
    }
    else
    {
        m_AllocatedMemorySize.Add(-neccessarySpace);
    }
    m_PushesInProgress.Decrement();
    return result;
}

Size* StackAllocator::GetSize()const
{
    return reinterpret_cast<Size*>(m_ReservedMemory.Get()+m_AllocatedMemorySize-sizeof(Size));
}

void StackAllocator::Pop()
{
    Lock();
    Size* ptr=GetSize();
    if (m_ZeroPopedMemory)
        RF_SysMem::Set(ptr-(*ptr),0,(size_t)(*ptr));
    m_AllocatedMemorySize.Add(-(*ptr + sizeof(Size)));
    Unlock();
}

void* StackAllocator::Peek()
{
    void* result=0;
    Lock();
    if (m_AllocatedMemorySize>0)
    {
        Size* ptr=GetSize();
        result=reinterpret_cast<void*>(reinterpret_cast<UInt8*>(ptr)-*ptr);
    }
    Unlock();
    return result;
}

Size StackAllocator::PeekSize()
{
    Lock();
    Size result = *GetSize();
    Unlock();
    return result;
}

void StackAllocator::Lock()
{
    while(m_PushesInProgress.CompareAndExchange(0, -1) != 0)
    {
    }
}

void StackAllocator::Unlock()
{
    m_PushesInProgress = 0;
}
