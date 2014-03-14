#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Memory/ManagedInstanceStackAllocator.hpp"

using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;

ManagedInstanceStackAllocator::ManagedInstanceStackAllocator(Size ReservedMemorySize)
:m_Allocator(ReservedMemorySize)
{
}

void ManagedInstanceStackAllocator::Clear()
{
    while (m_Allocator.Peek() != 0)
        m_Allocator.Pop();
}

void* ManagedInstanceStackAllocator::PushRaw(Size MemorySize)
{
    void* result=m_Allocator.Push(MemorySize+sizeof(DestructorCallback));
    SetDestructorCallback(result, MemorySize, 0);
    return result;
}

void ManagedInstanceStackAllocator::SetDestructorCallback(void* Buffer, Size MemorySize, DestructorCallback Destructor)
{
    *reinterpret_cast<DestructorCallback*>(reinterpret_cast<UInt8*>(Buffer)+MemorySize)=Destructor;
}

void ManagedInstanceStackAllocator::Pop()
{
    void* p=m_Allocator.Peek();
    Size pSize=m_Allocator.PeekSize();
    DestructorCallback* destructor=reinterpret_cast<DestructorCallback*>(reinterpret_cast<UInt8*>(p)+pSize-sizeof(DestructorCallback));
    if (*destructor)
        (*destructor)(p);
    m_Allocator.Pop();
}

void* ManagedInstanceStackAllocator::Peek()
{
    return m_Allocator.Peek();
}