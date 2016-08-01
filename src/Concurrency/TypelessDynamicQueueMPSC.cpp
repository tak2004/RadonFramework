#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Concurrency/TypelessDynamicQueueMPSC.hpp"
#include "RadonFramework/Memory/SystemAllocator.hpp"
#include "RadonFramework/System/Threading/Interlocked.hpp"

namespace RadonFramework { namespace Concurrency {

struct TypelessDynamicQueueMPSC::Node
{
    Node* m_Next;
    void* m_Data;
};

TypelessDynamicQueueMPSC::TypelessDynamicQueueMPSC(
    RadonFramework::Memory::AllocatorBase* Arena /*= nullptr*/)
:m_Arena(Arena ? Arena : RF_Pattern::Singleton<RF_Mem::SystemAllocator>::Instance())
,m_NodeAllocator(sizeof(Node), alignof(Node), Arena ? Arena : RF_Pattern::Singleton<RF_Mem::SystemAllocator>::Instance())
{
    m_Stub = RF_New(Node, m_NodeAllocator);
    Clear();
}

TypelessDynamicQueueMPSC::~TypelessDynamicQueueMPSC()
{
    RF_Delete(m_Stub, m_NodeAllocator);
}

void TypelessDynamicQueueMPSC::Clear()
{
    m_Stub->m_Next = 0;
    m_Head = m_Stub;
    m_Tail = m_Stub;
}

void TypelessDynamicQueueMPSC::Enqueue(void* Data)
{
    Node* node = RF_New(Node, m_NodeAllocator);
    node->m_Data = Data;
    node->m_Next = nullptr;
    Node* prev = reinterpret_cast<Node*>(RF_SysThread::Interlocked::InterlockedExchangePointer(
        reinterpret_cast<void *volatile*>(&m_Head), reinterpret_cast<void*>(node)));
    prev->m_Next = node;
}

void* TypelessDynamicQueueMPSC::Dequeue()
{
    Node* tail = m_Tail;
    Node* next = tail->m_Next;
    if(tail == m_Stub)
    {
        if(nullptr == next)
        {
            return nullptr;
        }
        m_Tail = next;
        tail = next;
        next = next->m_Next;
    }

    if(next)
    {
        m_Tail = next;
        void* result = tail->m_Data;
        RF_Delete(tail, m_NodeAllocator);
        return result;
    }

    Node* head = m_Head;
    if(tail != head)
    {
        return nullptr;
    }

    m_Stub->m_Next = nullptr;
    Node* prev = reinterpret_cast<Node*>(RF_SysThread::Interlocked::InterlockedExchangePointer(
        reinterpret_cast<void *volatile*>(&m_Head), reinterpret_cast<void*>(m_Stub)));
    prev->m_Next = m_Stub;

    next = tail->m_Next;
    if(next)
    {
        m_Tail = next;
        void* result = tail->m_Data;
        RF_Delete(tail, m_NodeAllocator);
        return result;
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