#ifndef RF_CONCURRENCY_TYPELESSDYNAMICQUEUEMPSC_HPP
#define RF_CONCURRENCY_TYPELESSDYNAMICQUEUEMPSC_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/PoolAllocator.hpp>

// Forward declaration of the
namespace RadonFramework { namespace Memory { class AllocatorBase; } }

namespace RadonFramework { namespace Concurrency {

/** @brief This class is a lock free queue which can grow and shrink.
*
* - first-in-first-out(FIFO)
* - multiple producer and single consumer(MPSC)
* - dynamic size(link list)
*
* If you need other producer and/or consumer combinations then look for the 
* specialized implementation.
*/
class TypelessDynamicQueueMPSC
{
public:
    /// You can pass a custom Allocator instance to exchange the standard
    /// memory allocation. The specified instance will not be destroyed on destruction.
    TypelessDynamicQueueMPSC(RadonFramework::Memory::AllocatorBase* Arena = nullptr);
    ~TypelessDynamicQueueMPSC();

    // Disable copy and assign for this class.
    TypelessDynamicQueueMPSC(const TypelessDynamicQueueMPSC& Copy) = delete;
    TypelessDynamicQueueMPSC& operator = (const TypelessDynamicQueueMPSC& Other) = delete;

    /// Removes all objects from the queue.
    void Clear();

    /// Enqueue a pointer to the end of the queue. Take care that the pointer
    /// is not managed by this class.
    void Enqueue(void* Data);
    /// Enqueue a pointer to the end of the queue. Take care that the pointer
    /// is not managed by this class.
    void Enqueue(const void* Data);
    /// Remove the last pointer of the queue. If empty it return nullptr.
    void* Dequeue();

    /// Return true if the queue was empty at call else false. 
    RF_Type::Bool IsEmpty()const;

    RadonFramework::Memory::AllocatorBase& GetArena()const;
private:
    RF_Mem::PoolAllocator m_NodeAllocator;
    struct Node;
    Node* volatile m_Head;
    Node* m_Tail;
    Node* m_Stub;
    RadonFramework::Memory::AllocatorBase* m_Arena;    
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_CON
#define RF_SHORTHAND_NAMESPACE_CON
namespace RF_Con = RadonFramework::Concurrency;
#endif

#endif // RF_CONCURRENCY_TYPELESSDYNAMICQUEUEMPSC_HPP