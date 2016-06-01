#ifndef RF_COLLECTIONS_QUEUE_HPP
#define RF_COLLECTIONS_QUEUE_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Collections/IEnumerator.hpp>
#include <RadonFramework/Collections/IEnumerable.hpp>
#include <RadonFramework/Collections/LinkedEnumerator.hpp>

#include <RadonFramework/Core/Types/AtomicInt32.hpp>
#include <RadonFramework/Core/Types/AtomicPointer.hpp>

namespace RadonFramework { namespace Collections {
/** @brief This class is can grow and shrink.
*
* The Queue class supports the first-in-first-out(FIFO)
* model for adding and removing elements.
*/
            
template <typename T, 
            typename MA=Core::Policies::CPPAllocator,
            typename MO=Core::Policies::CMemoryOperation>
class Queue
{
public:
    Queue();
    ~Queue();
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
protected:
    struct Node
    {
        Node* m_Next;
        T m_Value;
    };

    RF_Type::AtomicPointer<Node> m_Head;
    RF_Type::AtomicPointer<Node> m_Tail;
};
            
template<typename T, typename MA, typename MO>
Queue<T,MA,MO>::Queue()
:m_Tail(0)
,m_Head(0)
{
}

template<typename T, typename MA, typename MO>
Queue<T,MA,MO>::~Queue()
{
    Clear();
}

template<typename T, typename MA, typename MO>
void Queue<T,MA,MO>::Enqueue(const T& Item)
{
    Node* node;
    node=MA::template New<Node>();
    node->m_Next=0;
    node->m_Value=Item;
    
    // replace tail pointer and get previous pointer
    Node* old = m_Tail.FetchAndExchange(node);
    // replace head with current pointer if it is 0 else there was already a value
    // which m_Next pointer have to point to our new node
    if(m_Head.CompareAndExchange(0, node) != 0)
        old->m_Next = node;
}

template<typename T, typename MA, typename MO>
void Queue<T, MA, MO>::Enqueue(T& Item)
{
    Node* node;
    node = MA::template New<Node>();
    node->m_Next = 0;
    node->m_Value = Item;

    // replace tail pointer and get previous pointer
    Node* old = m_Tail.FetchAndExchange(node);
    // replace head with current pointer if it is 0 else there was already a value
    // which m_Next pointer have to point to our new node
    if(m_Head.CompareAndExchange(0, node) != 0)
        old->m_Next = node;
}

template<typename T, typename MA, typename MO>
RF_Type::Bool Queue<T,MA,MO>::Dequeue(T& Item)
{
    RF_Type::Bool result=false;
    Node* parameter = 0;
    // take head pointer and replace it temporary by 0 
    parameter = m_Head.FetchAndExchange(0);
    if(parameter)
    {
        // replace tail with 0 if head and tail are the same
        m_Tail.CompareAndExchange(parameter, 0);
        //if the result is a valid Node then replace the head
        m_Head = parameter->m_Next;
        Item = parameter->m_Value;
        delete parameter;
        result = true;
    }
    return result;
}

template<typename T, typename MA, typename MO>
RF_Type::Bool Queue<T, MA, MO>::Dequeue()
{
    RF_Type::Bool result = false;
    Node* node = 0;
    // take head pointer and replace it temporary by 0 
    node = m_Head.FetchAndExchange(0);
    if(node)
    {
        // replace tail with 0 if head and tail are the same
        m_Tail.CompareAndExchange(node, 0);
        //if the result is a valid Node then replace the head
        m_Head = node->m_Next;
        delete node;        
        result = true;
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
    return m_Head == 0;
}

} }

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif // RF_COLLECTIONS_QUEUE_HPP
