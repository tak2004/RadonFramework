#ifndef RF_COLLECTIONS_QUEUE_HPP
#define RF_COLLECTIONS_QUEUE_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <RadonFramework/Core/Types/AtomicUInt32.hpp>
#include <RadonFramework/Core/Types/AtomicPointer.hpp>
#include <RadonFramework/System/Hardware/Hardware.hpp>
#include <RadonFramework/System/Threading/Thread.hpp>
#include <RadonFramework/Core/Policies/CPPAllocator.hpp>
#include <RadonFramework/Core/Policies/CMemoryOperation.hpp>
#include <atomic>

namespace RadonFramework { namespace Collections {
/** @brief This class is can grow and shrink.
*
* The Queue class supports the first-in-first-out(FIFO)
* model for adding and removing elements.
* It's implemented as multiple producer(MP) and multiple consumer(MC) container.
* If you have single producer(SP)-MC, MP-single consumer(SC) or 
* SP-CS then look for the specialized implementation.
*/
            
template <typename T, 
            typename MA=Core::Policies::CPPAllocator,
            typename MO=Core::Policies::CMemoryOperation>
class Queue
{
public:
    Queue();
    Queue(const RF_Type::Size ReserveElements);
    Queue(const Queue& Copy) = delete;
    Queue& operator = (const Queue& Other) = delete;
    ~Queue();

    /// Removes all objects from the Queue<T>.
    void Clear();

    /// Removes and assign the object at the beginning of the Queue<T> to Item.
    RF_Type::Bool Dequeue(T& Item);

    /// Removes the object at the beginning of the Queue<T>.
    RF_Type::Bool Dequeue();

    /// Adds a copy of an object to the end of the Queue<T>.
    void Enqueue(const T& Item);
    /// Adds a copy of an object to the end of the Queue<T>.
    void Enqueue(T& Item);

    RF_Type::Bool IsEmpty()const;
private:
    struct LPInfo
    {
        RF_Type::AtomicUInt32 Head;
        RF_Type::AtomicUInt32 Tail;
    };
    // Used as ring buffer.
    T* m_Array;
    RF_Type::Size m_ArrayCount;
    // An information set per logical processor.
    LPInfo* m_LPInfos;
    RF_Type::Size m_LPInfoCount;

    RF_ALIGN(32) RF_Type::AtomicUInt32 m_Head;
    RF_ALIGN(32) RF_Type::AtomicUInt32 m_Tail;
    RF_ALIGN(32) RF_Type::AtomicUInt32 m_LastHead;
    RF_ALIGN(32) RF_Type::AtomicUInt32 m_LastTail;
};

template <typename T,
    typename MA/*=Core::Policies::CPPAllocator*/,
    typename MO/*=Core::Policies::CMemoryOperation*/>
    Queue<T, MA, MO>::Queue(const RF_Type::Size ReserveElements)
:m_Tail(0)
,m_Head(0)
,m_LastHead(0)
,m_LastTail(0)
{
    m_LPInfoCount = RF_SysHardware::GetAvailableLogicalProcessorCount();
    m_LPInfos = reinterpret_cast<LPInfo*>(RF_SysMem::Allocate(sizeof(LPInfo)*m_LPInfoCount, 4096));
    RF_SysMem::Fill(m_LPInfos, &RF_Type::UInt32Max, sizeof(RF_Type::UInt32),
                    sizeof(LPInfo)*m_LPInfoCount);

    m_Array = reinterpret_cast<T*>(RF_SysMem::Allocate(sizeof(T)*ReserveElements, 4096));
    m_ArrayCount = ReserveElements;
    RF_SysMem::Fill(m_Array, &RF_Type::UInt32Min, sizeof(RF_Type::UInt32),
                    sizeof(T)*ReserveElements);
}


template<typename T, typename MA, typename MO>
Queue<T,MA,MO>::Queue()
:Queue(RF_SysHardware::GetAvailableLogicalProcessorCount()*8)
{
}

template<typename T, typename MA, typename MO>
Queue<T, MA, MO>::~Queue()
{
    RF_SysMem::Free(m_LPInfos);
    RF_SysMem::Free(m_Array);
}

template<typename T, typename MA, typename MO>
void Queue<T,MA,MO>::Enqueue(const T& Item)
{
    auto lpId = RF_SysHardware::GetCurrentUniqueProcessorNumber();
    m_LPInfos[lpId].Head = m_Head;
    m_LPInfos[lpId].Head = m_Head.FetchAndAdd(1);

    while(m_LPInfos[lpId].Head >= m_LastTail + m_ArrayCount)
    {
        RF_Type::UInt32 min = m_Tail;        
        for (RF_Type::Size i = 0; i < m_LPInfoCount; ++i)
        {
            RF_Type::UInt32 tmp = m_LPInfos[i].Tail;
            std::atomic_thread_fence(std::memory_order_acq_rel);
            if(tmp < min)
            {
                min = tmp;
            }
        }
        m_LastTail = min;

        if(m_LPInfos[lpId].Head < m_LastTail + m_ArrayCount)
        {
            break;
        }
        RF_SysThread::ShortestPause();
    }
    m_Array[m_LPInfos[lpId].Head & (m_ArrayCount - 1)] = Item;
    m_LPInfos[lpId].Head = RF_Type::UInt32Max;
}

template<typename T, typename MA, typename MO>
void Queue<T, MA, MO>::Enqueue(T& Item)
{
    auto lpId = RF_SysHardware::GetCurrentUniqueProcessorNumber();
    m_LPInfos[lpId].Head = m_Head;
    m_LPInfos[lpId].Head = m_Head.FetchAndAdd(1);

    while(m_LPInfos[lpId].Head >= m_LastTail + m_ArrayCount)
    {
        RF_Type::UInt32 min = m_Tail;
        
        for(RF_Type::Size i = 0; i < m_LPInfoCount; ++i)
        {
            RF_Type::UInt32 tmp = m_LPInfos[i].Tail;
            std::atomic_thread_fence(std::memory_order_acq_rel);
            if(tmp < min)
            {
                min = tmp;
            }
        }
        m_LastTail = min;

        if(m_LPInfos[lpId].Head < m_LastTail + m_ArrayCount)
        {
            break;
        }
        RF_SysThread::ShortestPause();
    }
    m_Array[m_LPInfos[lpId].Head & (m_ArrayCount - 1)] = Item;
    m_LPInfos[lpId].Head = RF_Type::UInt32Max;
}

template<typename T, typename MA, typename MO>
RF_Type::Bool Queue<T,MA,MO>::Dequeue(T& Item)
{
    RF_Type::Bool result=false;
    auto lpId = RF_SysHardware::GetCurrentUniqueProcessorNumber();

    if (m_LPInfos[lpId].Tail == RF_Type::UInt32Max)
    {
        m_LPInfos[lpId].Tail = m_Tail;
        m_LPInfos[lpId].Tail = m_Tail.FetchAndAdd(1);
    }

    if(m_LPInfos[lpId].Tail >= m_LastHead)
    {
        RF_Type::UInt32 min = m_Head;
        for(RF_Type::Size i = 0; i < m_LPInfoCount; ++i)
        {
            RF_Type::UInt32 tmp = m_LPInfos[i].Head;
            std::atomic_thread_fence(std::memory_order_acq_rel);
            if(tmp < min)
            {
                min = tmp;
            }
        }
        m_LastHead = min;
    }

    if(m_LPInfos[lpId].Tail < m_LastHead)
    {
        Item = m_Array[m_LPInfos[lpId].Tail & (m_ArrayCount - 1)];
        result = true;
        m_LPInfos[lpId].Tail = RF_Type::UInt32Max;
    }
    return result;
}

template<typename T, typename MA, typename MO>
RF_Type::Bool Queue<T, MA, MO>::Dequeue()
{
    RF_Type::Bool result = false;
    auto lpId = RF_SysHardware::GetCurrentUniqueProcessorNumber();

    if (m_LPInfos[lpId].Tail == RF_Type::UInt32Max)
    {
        m_LPInfos[lpId].Tail = m_Tail;
        m_LPInfos[lpId].Tail = m_Tail.FetchAndAdd(1);
    }

    if(m_LPInfos[lpId].Tail >= m_LastHead)
    {
        RF_Type::UInt32 min = m_Head;
        for(RF_Type::Size i = 0; i < m_LPInfoCount; ++i)
        {
            RF_Type::UInt32 tmp = m_LPInfos[i].Head;
            std::atomic_thread_fence(std::memory_order_acq_rel);
            if(tmp < min)
            {
                min = tmp;
            }
        }
        m_LastHead = min;
    }

    if(m_LPInfos[lpId].Tail < m_LastHead)
    {
        result = true;
        m_LPInfos[lpId].Tail = RF_Type::UInt32Max;
    }
    return result;
}

template<typename T, typename MA, typename MO>
void Queue<T,MA,MO>::Clear()
{
    while(Dequeue()){}
}

template<typename T, typename MA, typename MO>
RF_Type::Bool Queue<T, MA, MO>::IsEmpty()const
{
    return m_Head == m_Tail;
}

} }

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif // RF_COLLECTIONS_QUEUE_HPP
