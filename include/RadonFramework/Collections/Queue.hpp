#ifndef RF_COLLECTIONS_QUEUE_HPP
#define RF_COLLECTIONS_QUEUE_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <RadonFramework/Core/Types/AtomicInt32.hpp>
#include <RadonFramework/Core/Types/AtomicPointer.hpp>
#include <RadonFramework/System/Hardware/Hardware.hpp>
#include <RadonFramework/Core/Policies/CPPAllocator.hpp>
#include <RadonFramework/Core/Policies/CMemoryOperation.hpp>

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
        RF_Type::AtomicInt32 Head;
        RF_Type::AtomicInt32 Tail;
    };
    RF_Type::AtomicInt32 m_Head;
    RF_Type::AtomicInt32 m_Tail;
    RF_Type::AtomicInt32 m_LastHead;
    RF_Type::AtomicInt32 m_LastTail;
    // Used as ring buffer.
    RF_Mem::AutoPointerArray<T> m_Array;
    // An information set per logical processor.
    RF_Mem::AutoPointerArray<LPInfo> m_LPInfos;
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
    auto lpcount = RF_SysHardware::GetAvailableLogicalProcessorCount();
    m_LPInfos = RF_Mem::AutoPointerArray<LPInfo>(lpcount);
    RF_SysMem::Fill(m_LPInfos.Get(), &RF_Type::Int32Max, sizeof(RF_Type::Int32),
        m_LPInfos.Size());
    m_Array = RF_Mem::AutoPointerArray<T>(ReserveElements);
}


template<typename T, typename MA, typename MO>
Queue<T,MA,MO>::Queue()
:Queue(RF_SysHardware::GetAvailableLogicalProcessorCount()*8)
{
}

template<typename T, typename MA, typename MO>
void Queue<T,MA,MO>::Enqueue(const T& Item)
{
    auto lpId = RF_SysHardware::GetCurrentUniqueProcessorNumber();
    m_LPInfos[lpId].Head = m_Head;
    m_LPInfos[lpId].Head = m_Head.FetchAndAdd(1);

    while(m_LPInfos[lpId].Head >= m_LastTail + m_Array.Count())
    {
        RF_Type::Int32 min = m_Tail;
        for (RF_Type::Size i = 0; i < m_LPInfos.Count(); ++i)
        {
            volatile RF_Type::Int32 tmp = m_LPInfos[i].Tail;
            if(tmp < min)
            {
                min = tmp;
            }
        }
        m_LastTail = min;

        if(m_LPInfos[lpId].Head < m_LastTail + m_Array.Count())
        {
            break;
        }
    }
    m_Array[m_LPInfos[lpId].Head & (m_Array.Count() - 1)] = Item;
    m_LPInfos[lpId].Head = RF_Type::Int32Max;
}

template<typename T, typename MA, typename MO>
void Queue<T, MA, MO>::Enqueue(T& Item)
{
    auto lpId = RF_SysHardware::GetCurrentUniqueProcessorNumber();
    m_LPInfos[lpId].Head = m_Head;
    m_LPInfos[lpId].Head = m_Head.FetchAndAdd(1);

    while(m_LPInfos[lpId].Head >= m_LastTail + m_Array.Count())
    {
        RF_Type::Int32 min = m_Tail;
        for(RF_Type::Size i = 0; i < m_LPInfos.Count(); ++i)
        {
            volatile RF_Type::Int32 tmp = m_LPInfos[i].Tail;
            if(tmp < min)
            {
                min = tmp;
            }
        }
        m_LastTail = min;

        if(m_LPInfos[lpId].Head < m_LastTail + m_Array.Count())
        {
            break;
        }
    }
    m_Array[m_LPInfos[lpId].Head & (m_Array.Count() - 1)] = Item;
    m_LPInfos[lpId].Head = RF_Type::Int32Max;
}

template<typename T, typename MA, typename MO>
RF_Type::Bool Queue<T,MA,MO>::Dequeue(T& Item)
{
    RF_Type::Bool result=false;
    auto lpId = RF_SysHardware::GetCurrentUniqueProcessorNumber();

    m_LPInfos[lpId].Tail = m_Tail;
    m_LPInfos[lpId].Tail = m_Tail.FetchAndAdd(1);

    if (m_LPInfos[lpId].Tail < m_Head)
    {
        while(m_LPInfos[lpId].Tail >= m_LastHead)
        {
            RF_Type::Int32 min = m_Head;
            for(RF_Type::Size i = 0; i < m_LPInfos.Count(); ++i)
            {
                volatile RF_Type::Int32 tmp = m_LPInfos[lpId].Head;
                if(tmp < min)
                {
                    min = tmp;
                }
            }
            m_LastHead = min;

            if(m_LPInfos[lpId].Tail < m_LastHead)
            {
                break;
            }
        }
        Item = m_Array[m_LPInfos[lpId].Tail & (m_Array.Count() - 1)];
        result = true;
    }
    else
    {
        m_Tail.Decrement();
    }
    m_LPInfos[lpId].Tail = RF_Type::Int32Max;
    return result;
}

template<typename T, typename MA, typename MO>
RF_Type::Bool Queue<T, MA, MO>::Dequeue()
{
    RF_Type::Bool result = false;
    auto lpId = RF_SysHardware::GetCurrentUniqueProcessorNumber();
    m_LPInfos[lpId].Tail = m_Tail;
    m_LPInfos[lpId].Tail = m_Tail.FetchAndAdd(1);

    if(m_LPInfos[lpId].Tail < m_Head)
    {
        while(m_LPInfos[lpId].Tail >= m_LastHead)
        {
            RF_Type::Int32 min = m_Head;
            for(RF_Type::Size i = 0; i < m_LPInfos.Count(); ++i)
            {
                volatile RF_Type::Int32 tmp = m_LPInfos[lpId].Head;
                if(tmp < min)
                {
                    min = tmp;
                }
            }
            m_LastHead = min;

            if(m_LPInfos[lpId].Tail < m_LastHead)
            {
                break;
            }
        }
        result = true;
    }
    m_LPInfos[lpId].Tail = RF_Type::Int32Max;
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
