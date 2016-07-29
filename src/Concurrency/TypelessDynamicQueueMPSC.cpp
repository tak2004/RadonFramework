#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Concurrency/TypelessDynamicQueueMPSC.hpp"
#include "RadonFramework/Memory/SystemAllocator.hpp"
#include "RadonFramework/System/Threading/Interlocked.hpp"

struct Node
{
    Node* m_Next;
    void* m_Data;
};

namespace RadonFramework { namespace Concurrency {

TypelessDynamicQueueMPSC::TypelessDynamicQueueMPSC(
    RadonFramework::Memory::AllocatorBase* Arena /*= nullptr*/)
:m_Arena(Arena)
{
    if(m_Arena == nullptr)
    {
        m_Arena = RF_Pattern::Singleton<RF_Mem::SystemAllocator>::Instance();
    }
    m_Stub = RF_New(Node, *m_Arena);
    Clear();
}

TypelessDynamicQueueMPSC::~TypelessDynamicQueueMPSC()
{
    RF_Delete(m_Stub, *m_Arena);
}

void TypelessDynamicQueueMPSC::Clear()
{
    m_Stub->m_Next = 0;
    m_Head = m_Stub;
    m_Tail = m_Stub;
}

void TypelessDynamicQueueMPSC::Enqueue(void* Data)
{
    RF_Mem::AllocatorBase& all = *m_Arena;
    Node* node = nullptr;//RF_New(Node, all);
    node = ::new( reinterpret_cast<Node*>((*m_Arena).Allocate(sizeof(Node), __alignof(Node))) ) Node();
    node->m_Data = Data;
    node->m_Next = 0;
    Node* prev = reinterpret_cast<Node*>(RF_SysThread::Interlocked::InterlockedExchangePointer(
        reinterpret_cast<void *volatile*>(&m_Head), reinterpret_cast<void*>(node)));
    prev->m_Next = node;
}

void* TypelessDynamicQueueMPSC::Dequeue()
{
    Node* tail = m_Tail;
    Node* next = tail->m_Next;
    if(next)
    {
        m_Tail = next;
        tail->m_Data = next->m_Data;
        return m_Tail;
    }
    return nullptr;
}

RF_Type::Bool TypelessDynamicQueueMPSC::IsEmpty()const
{
    return m_Head == m_Tail;
}

RadonFramework::Memory::AllocatorBase& TypelessDynamicQueueMPSC::GetArena() const
{
    return *m_Arena; 
}

} }