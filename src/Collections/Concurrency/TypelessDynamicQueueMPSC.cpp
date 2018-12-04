#include "RadonFramework/Collections/Concurrency/TypelessDynamicQueueMPSC.hpp"
#include "RadonFramework/Core/Pattern/Singleton.hpp"
#include "RadonFramework/Memory/Allocators.hpp"
#include "RadonFramework/System/Threading/Interlocked.hpp"
#include "RadonFramework/precompiled.hpp"

namespace RadonFramework::Collections::Concurrency
{
struct TypelessDynamicQueueMPSC::Node
{
  Node* m_Next;
  void* m_Data;
};

struct TypelessDynamicQueueMPSC::AllocatorTraits
{
  enum
  {
    StackSize = 1024,
    BlockSize = sizeof(Node),
    AlignSize = alignof(Node),
    HeapAllocation = 1,
    FixedBlockCount = 0
  };
};

using Allocator = RF_Mem::AllocatorSelector<TypelessDynamicQueueMPSC>::Type;
Allocator* NodeAllocator = nullptr;

TypelessDynamicQueueMPSC::TypelessDynamicQueueMPSC()
{
  NodeAllocator = &RF_Pattern::Singleton<Allocator>::GetInstance();
  m_Stub = reinterpret_cast<Node*>(NodeAllocator->Allocate(sizeof(Node)).Data);
  Clear();
}

TypelessDynamicQueueMPSC::~TypelessDynamicQueueMPSC()
{
  RF_Mem::MemoryBlock block = {reinterpret_cast<RF_Type::UInt8*>(m_Stub),
                               sizeof(Node)};
  NodeAllocator->Deallocate(block);
}

void TypelessDynamicQueueMPSC::Clear()
{
  m_Stub->m_Next = nullptr;
  m_Head = m_Stub;
  m_Tail = m_Stub;
}

void TypelessDynamicQueueMPSC::Enqueue(void* Data)
{
  Node* node =
      reinterpret_cast<Node*>(NodeAllocator->Allocate(sizeof(Node)).Data);
  node->m_Data = Data;
  node->m_Next = nullptr;
  Node* prev = reinterpret_cast<Node*>(
      RF_SysThread::Interlocked::InterlockedExchangePointer(
          reinterpret_cast<void* volatile*>(&m_Head),
          reinterpret_cast<void*>(node)));
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

  if(next != nullptr)
  {
    m_Tail = next;
    void* result = tail->m_Data;
    RF_Mem::MemoryBlock block = {reinterpret_cast<RF_Type::UInt8*>(tail),
                                 sizeof(Node)};
    NodeAllocator->Deallocate(block);
    return result;
  }

  Node* head = m_Head;
  if(tail != head)
  {
    return nullptr;
  }

  m_Stub->m_Next = nullptr;
  Node* prev = reinterpret_cast<Node*>(
      RF_SysThread::Interlocked::InterlockedExchangePointer(
          reinterpret_cast<void* volatile*>(&m_Head),
          reinterpret_cast<void*>(m_Stub)));
  prev->m_Next = m_Stub;

  next = tail->m_Next;
  if(next != nullptr)
  {
    m_Tail = next;
    void* result = tail->m_Data;
    RF_Mem::MemoryBlock block = {reinterpret_cast<RF_Type::UInt8*>(tail),
                                 sizeof(Node)};
    NodeAllocator->Deallocate(block);
    return result;
  }
  return nullptr;
}

RF_Type::Bool TypelessDynamicQueueMPSC::IsEmpty() const
{
  return m_Head == m_Tail;
}

}  // namespace RadonFramework::Collections::Concurrency