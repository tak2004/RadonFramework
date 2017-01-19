#ifndef RF_CONCURRENCY_TYPELESSDYNAMICQUEUEMPSC_HPP
#define RF_CONCURRENCY_TYPELESSDYNAMICQUEUEMPSC_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/FreeListAllocator.hpp>

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
    TypelessDynamicQueueMPSC();
    ~TypelessDynamicQueueMPSC();

    // Disable copy and assign for this class.
    TypelessDynamicQueueMPSC(const TypelessDynamicQueueMPSC& Copy) = delete;
    TypelessDynamicQueueMPSC& operator = (const TypelessDynamicQueueMPSC& Other) = delete;

    /// Enqueue a pointer to the end of the queue. Take care that the pointer
    /// is not managed by this class.
    void Enqueue(void* Data);
    /// Enqueue a pointer to the end of the queue. Take care that the pointer
    /// is not managed by this class.
    void Enqueue(const void* Data);
    /// Remove the last pointer of the queue. If empty it return nullptr.
    void* Dequeue();
    /// Removes all objects from the queue.
    void Clear();
    /// Return true if the queue was empty at call else false. 
    RF_Type::Bool IsEmpty()const;

    struct AllocatorTraits;
private:
    struct Node;
    Node* volatile m_Head;
    Node* m_Tail;
    Node* m_Stub;    
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_CON
#define RF_SHORTHAND_NAMESPACE_CON
namespace RF_Con = RadonFramework::Concurrency;
#endif

#endif // RF_CONCURRENCY_TYPELESSDYNAMICQUEUEMPSC_HPP