#ifndef RF_CONCURRENCY_DYNAMICQUEUEMPSC_HPP
#define RF_CONCURRENCY_DYNAMICQUEUEMPSC_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Concurrency/TypelessDynamicQueueMPSC.hpp>
#include <RadonFramework/Memory/AllocatorBase.hpp>
#include <RadonFramework/Memory/SystemAllocator.hpp>

namespace RadonFramework { namespace Concurrency {

/** @brief This class is a lock free queue which can grow and shrink.
*
* - first-in-first-out(FIFO)
* - multiple producer and single consumer(MPSC)
* - dynamic size(link list)
*
* If you need other producer and/or consumer combination then look for the 
* specialized implementation.
*/
template<typename T>
class DynamicQueueMPSC
{
public:
    /// You can pass a custom Allocator instance to exchange the standard
    /// memory allocation. The specified instance will not be destroyed on destruction.
    DynamicQueueMPSC(RF_Mem::AllocatorBase* Arena = nullptr);
    ~DynamicQueueMPSC();

    // Disable copy and assign for this class.
    DynamicQueueMPSC(const DynamicQueueMPSC<T>& Copy) = delete;
    DynamicQueueMPSC& operator = (const DynamicQueueMPSC<T>& Other) = delete;

    /// Removes all objects from the queue.
    void Clear();

    /// Remove the object at the beginning of the queue and assign it to Data.
    RF_Type::Bool Dequeue(T& Data);
    /// Remove the object at the beginning of the queue.
    RF_Type::Bool Dequeue();
    /// Adds a copy of an object to the end of the Queue.
    void Enqueue(const T& Data);
    /// Adds a copy of an object to the end of the Queue.
    void Enqueue(T& Data);

    /// Return true if the queue was empty at call else false. 
    RF_Type::Bool IsEmpty()const;
private:
    TypelessDynamicQueueMPSC m_RealQueue;
    RF_Mem::PoolAllocator m_PayloadAllocator;
};

template<typename T>
DynamicQueueMPSC<T>::DynamicQueueMPSC(RF_Mem::AllocatorBase* Arena /*= nullptr*/)
:m_RealQueue(Arena)
,m_PayloadAllocator(sizeof(T), alignof(T), 
	Arena ? Arena : RF_Pattern::Singleton<RF_Mem::SystemAllocator>::Instance())
{
}

template<typename T>
DynamicQueueMPSC<T>::~DynamicQueueMPSC()
{
    Clear();
}

template<typename T>
inline RF_Type::Bool DynamicQueueMPSC<T>::IsEmpty()const
{
    return m_RealQueue.IsEmpty();
}

template<typename T>
inline void DynamicQueueMPSC<T>::Clear()
{
    void* p = nullptr;
    while(p = (m_RealQueue.Dequeue()))
    {
        RF_Delete(p, m_PayloadAllocator);
    }
}

template<typename T>
inline RF_Type::Bool DynamicQueueMPSC<T>::Dequeue(T& Data)
{    
    RF_Type::Bool result = false;
    T* p = reinterpret_cast<T*>(m_RealQueue.Dequeue());
    if(p)
    {
        Data = *p;
        RF_Delete(p, m_PayloadAllocator);
        result = true;
    }
    return result;
}

template<typename T>
inline RF_Type::Bool DynamicQueueMPSC<T>::Dequeue()
{
    RF_Type::Bool result = false;
    T* p = m_RealQueue.Dequeue();
    if(p)
    {
        result = true;
        RF_Delete(p, m_PayloadAllocator);
    }
    return result;
}

template<typename T>
inline void DynamicQueueMPSC<T>::Enqueue(T& Data)
{
    T* p = RF_New(T, m_PayloadAllocator)(Data);
    m_RealQueue.Enqueue(p);
}

template<typename T>
inline void DynamicQueueMPSC<T>::Enqueue(const T& Data)
{
    T* p = RF_New(T, m_PayloadAllocator)(Data);
    m_RealQueue.Enqueue(p);
}

} }

#ifndef RF_SHORTHAND_NAMESPACE_CON
#define RF_SHORTHAND_NAMESPACE_CON
namespace RF_Con = RadonFramework::Concurrency;
#endif

#endif // RF_CONCURRENCY_DYNAMICQUEUEMPSC_HPP