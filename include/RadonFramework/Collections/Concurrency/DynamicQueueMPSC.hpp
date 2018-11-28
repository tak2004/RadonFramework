#ifndef RF_COLLECTIONS_CONCURRENCY_DYNAMICQUEUEMPSC_HPP
#define RF_COLLECTIONS_CONCURRENCY_DYNAMICQUEUEMPSC_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Concurrency/TypelessDynamicQueueMPSC.hpp>
#include <RadonFramework/Memory/HeapAllocator.hpp>
#include <RadonFramework/Memory/FreeListAllocator.hpp>
#include <new>

namespace RadonFramework::Collections::Concurrency {

/** @brief This class is a lock free queue which can grow and shrink.
*
* - first-in-first-out(FIFO)
* - multiple producer and single consumer(MPSC)
* - dynamic size(link list)
*
* If you need other producer and/or consumer combination then look for the 
* specialized implementation.
*/
template<typename T, typename ALLOCATOR = RF_Mem::HeapAllocator>
class DynamicQueueMPSC
{
public:
    /// You can pass a custom Allocator instance to exchange the standard
    /// memory allocation. The specified instance will not be destroyed on destruction.
    DynamicQueueMPSC(ALLOCATOR* Arena = nullptr);
    ~DynamicQueueMPSC();

    // Disable copy and assign for this class.
    DynamicQueueMPSC(const DynamicQueueMPSC& Copy) = delete;
    DynamicQueueMPSC& operator = (const DynamicQueueMPSC& Other) = delete;

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
    RF_Mem::FreeListAllocator<ALLOCATOR, sizeof(T), alignof(T)> m_PayloadAllocator;
};

template<typename T, typename ALLOCATOR>
DynamicQueueMPSC<T, ALLOCATOR>::DynamicQueueMPSC(ALLOCATOR* Arena /*= nullptr*/)
{
}

template<typename T, typename ALLOCATOR>
DynamicQueueMPSC<T, ALLOCATOR>::~DynamicQueueMPSC()
{
    Clear();
}

template<typename T, typename ALLOCATOR>
inline RF_Type::Bool DynamicQueueMPSC<T, ALLOCATOR>::IsEmpty()const
{
    return m_RealQueue.IsEmpty();
}

template<typename T, typename ALLOCATOR>
inline void DynamicQueueMPSC<T, ALLOCATOR>::Clear()
{
    void* p = nullptr;
    while(p = (m_RealQueue.Dequeue()))
    {
        reinterpret_cast<T*>(p)->~T();
        RF_Mem::MemoryBlock block = {reinterpret_cast<RF_Type::UInt8*>(p),sizeof(T)};
        m_PayloadAllocator.Deallocate(block);
    }
}

template<typename T, typename ALLOCATOR>
inline RF_Type::Bool DynamicQueueMPSC<T, ALLOCATOR>::Dequeue(T& Data)
{    
    RF_Type::Bool result = false;
    T* p = reinterpret_cast<T*>(m_RealQueue.Dequeue());
    if(p)
    {
        Data = *p;
        p->~T();
        RF_Mem::MemoryBlock block = {reinterpret_cast<RF_Type::UInt8*>(p),sizeof(T)};
        m_PayloadAllocator.Deallocate(block);
        result = true;
    }
    return result;
}

template<typename T, typename ALLOCATOR>
inline RF_Type::Bool DynamicQueueMPSC<T, ALLOCATOR>::Dequeue()
{
    RF_Type::Bool result = false;
    T* p = m_RealQueue.Dequeue();
    if(p)
    {
        result = true;
        p->~T();
        RF_Mem::MemoryBlock block = {reinterpret_cast<RF_Type::UInt8*>(p),sizeof(T)};
        m_PayloadAllocator.Deallocate(block);
    }
    return result;
}

template<typename T, typename ALLOCATOR>
inline void DynamicQueueMPSC<T, ALLOCATOR>::Enqueue(T& Data)
{    
    T* p = ::new(m_PayloadAllocator.Allocate(sizeof(T)).Data)T(Data);
    m_RealQueue.Enqueue(p);
}

template<typename T, typename ALLOCATOR>
inline void DynamicQueueMPSC<T, ALLOCATOR>::Enqueue(const T& Data)
{
    T* p = ::new(m_PayloadAllocator.Allocate(sizeof(T)).Data)T(Data);
    m_RealQueue.Enqueue(p);
}

}

#ifndef RF_SHORTHAND_NAMESPACE_CON
#define RF_SHORTHAND_NAMESPACE_CON
namespace RF_Con = RadonFramework::Collections::Concurrency;
#endif

#endif  // RF_COLLECTIONS_CONCURRENCY_DYNAMICQUEUEMPSC_HPP