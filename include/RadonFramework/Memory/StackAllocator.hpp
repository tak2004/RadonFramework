#ifndef RF_STACKALLOCATOR_HPP
#define RF_STACKALLOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/AutoPointerArray.hpp>

namespace RadonFramework { namespace Memory {

/** Push can be called from multiple threads at the same time but all other
 methods are not synchronized. This mean you have to call only one at the time.
**/
class StackAllocator
{
public:
    StackAllocator(RF_Type::Size ReservedMemorySize);
    void Clear();    
    void* Push(RF_Type::Size MemorySize);
    void Pop();
    void* Peek();
    RF_Type::Size PeekSize();

    void ZeroPopedMemory(RF_Type::Bool choice);
    void ZeroFreedMemory(RF_Type::Bool choice);
    RF_Type::Bool ZeroFreedMemory()const;
    RF_Type::Bool ZeroPopedMemory()const;
protected:
    Memory::AutoPointerArray<RF_Type::UInt8> m_ReservedMemory;
    RF_Type::AtomicInt64 m_AllocatedMemorySize;
    RF_Type::AtomicInt32 m_PushesInProgress;
    RF_Type::Bool m_ZeroFreedMemory;
    RF_Type::Bool m_ZeroPopedMemory;

    RF_Type::Size* GetSize()const;
    void Lock();
    void Unlock();
};

inline RF_Type::Bool StackAllocator::ZeroFreedMemory()const
{
    return m_ZeroFreedMemory;
}

inline RF_Type::Bool StackAllocator::ZeroPopedMemory()const
{
    return m_ZeroPopedMemory;
}

inline void StackAllocator::ZeroPopedMemory(RF_Type::Bool choice)
{
    m_ZeroPopedMemory=choice;
}

inline void StackAllocator::ZeroFreedMemory(RF_Type::Bool choice)
{
    m_ZeroFreedMemory=choice;
}

} }

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif
