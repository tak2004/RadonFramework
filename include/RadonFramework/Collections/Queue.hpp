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

namespace RadonFramework
{
    namespace Collections
    {
        /** @brief This class is can grow and shrink.
            *
            * The Queue class supports the first-in-first-out(FIFO)
            * model for adding and removing elements.
            */
            
        template <typename T, 
                  typename SP=Threading::Policies::NoSynchronization, 
                  typename MA=Core::Policies::CPPAllocator,
                  typename MO=Core::Policies::CMemoryOperation>
        class Queue: public IEnumerable<T>
        {
            template <typename,typename,typename,typename>
            friend class Queue;
            public:
            // Constructor and destructor
                Queue();
                Queue(const Queue<T,SP,MA,MO>& Copy);
                Queue(RFTYPE::UInt32 Capacity);
                Queue(IEnumerable<T>* Collection);
                ~Queue();

            // Properties
                /// Gets the number of elements contained in the Queue<T>.
                RFTYPE::UInt32 Count()const;

                RFTYPE::UInt32 Capacity()const;

            // Methods
                /// Removes all objects from the Queue<T>.
                void Clear();

                /// Determines whether an element is in the Queue<T>.
                RFTYPE::Bool Contains(const T& Item);

                /**
                    * \brief Copies the Queue(Of T) elements to an existing 
                    *        one-dimensional Array, starting at the specified 
                    *        array index.
                    */
                RFTYPE::Bool CopyTo(Array<T,SP,MA,MO>& Destination, 
                                         RFTYPE::UInt32 ArrayIndex);

                /// Removes and assign the object at the beginning of the Queue<T> to Item.
                RFTYPE::Bool Dequeue(T& Item);

                /// Removes the object at the beginning of the Queue<T>.
                void Dequeue();

                /// Adds a copy of an object to the end of the Queue<T>.
                void Enqueue(const T& Item);
                    
                /// Returns an enumerator that iterates through the Queue<T>.
                Memory::AutoPointer<IEnumerator<T> > GetEnumerator();
                                        
                /** 
                    * \brief Gets an object that can be used to synchronize access 
                    *        to the Queue.
                    *
                    * Classes that use arrays can also implement their own 
                    * synchronization using the SyncRoot property. The synchronizing
                    * code must perform operations on the SyncRoot of the collection,
                    * not directly on the collection. This ensures proper operation 
                    * of collections that are derived from other objects. 
                    * Specifically, it maintains proper synchronization with other 
                    * threads that might be simultaneously modifying the collection. 
                    * Note that some implementations of SyncRoot might return the 
                    * Queue itself.
                    * 
                    * Enumerating through a collection is intrinsically not a thread 
                    * safe procedure. Even when a collection is synchronized, other 
                    * threads can still modify the collection. To guarantee 
                    * thread safety during enumeration, you can either lock the
                    * collection during the entire enumeration.
                    *
                    * Retrieving the value of this property is an O(1) operation.
                    *
                    * \return An object that can be used to synchronize access to 
                    *         the Queue.
                    */
                Threading::ISynchronize& SyncRoot();    

                /**
                    * \brief Gets a value indicating whether access to the 
                    *        Array is synchronized (thread safe).
                    */           
                RFTYPE::Bool IsSynchronized()const;
                    
                /** Returns the object at the beginning of the Queue<T> 
                    * without removing it.
                    **/
                T* Peek();

                /// Copies the Queue<T> elements to a new array.
                Memory::AutoPointer<Array<T,SP,MA,MO> > ToArray();
                    
                /** Sets the capacity to the actual number of elements in 
                    * the Queue<T>, if that number is less than 90 percent of 
                    * current capacity.
                    **/
                void TrimExcess();

                /// Swap the content of two Queue's.
                RFTYPE::Bool Swap(Queue<T,SP,MA,MO>& Other);
            protected:
                struct Node
                {
                    Node* m_Next;
                    T m_Value;
                };

                RFTYPE::UInt32 m_Size;
                RFTYPE::UInt32 m_Capacity;
                Node* m_Head;
                Node* m_Tail;
                Node* m_Reserved;
                Threading::ISynchronize* m_SyncRoot;
                RFTYPE::Bool m_Synchronized;
        };
            
        template<typename T, typename SP, typename MA, typename MO>
        Queue<T,SP,MA,MO>::Queue()
        :m_Size(0)
        ,m_Capacity(0)
        ,m_Tail(0)
        ,m_Head(0)
        ,m_Reserved(0)
        ,m_SyncRoot(MA::template New<SP>())
        ,m_Synchronized(false)
        {
        }

        template<typename T, typename SP, typename MA, typename MO>
        Queue<T,SP,MA,MO>::Queue(const Queue<T,SP,MA,MO>& Copy)
        :m_Size(Copy.m_Size)
        ,m_Capacity(0)
        ,m_Head(0)
        ,m_Tail(0)
        ,m_Reserved(0)
        ,m_SyncRoot(MA::template New<SP>())
        ,m_Synchronized(false)
        {
            if (m_Size>0)
            {                    
                Node* node,*cpyNode=Copy.m_Head;
                for (RFTYPE::UInt32 i=0;i<m_Size;++i)
                {
                    node = MA::template New<Node>();
                    node->m_Value=cpyNode->m_Value;
                    if (m_Tail!=0)
                        m_Tail->m_Next=node;

                    m_Tail = node;
                        
                    cpyNode=cpyNode->m_Next;                        

                    if (m_Head==0)
                        m_Head=node;
                }
                m_Tail->m_Next=0;
            }      
        }

        template<typename T, typename SP, typename MA, typename MO>
        Queue<T,SP,MA,MO>::Queue(RFTYPE::UInt32 Capacity)
        :m_Size(0)
        ,m_Capacity(Capacity)
        ,m_Tail(0)
        ,m_Head(0)
        ,m_Reserved(0)
        ,m_SyncRoot(MA::template New<SP>())
        ,m_Synchronized(false)
        {
            if (m_Capacity>0)
            {
                Node* node;
                for (RFTYPE::UInt32 i=0;i<m_Capacity;++i)
                {
                    node=MA::template New<Node>();
                    node->m_Next=m_Reserved;
                    m_Reserved=node;                        
                }
            }
        }

        template<typename T, typename SP, typename MA, typename MO>
        Queue<T,SP,MA,MO>::Queue(IEnumerable<T>* Collection)
        :m_Size(0)
        ,m_Capacity(0)
        ,m_Tail(0)
        ,m_Head(0)
        ,m_Reserved(0)
        ,m_SyncRoot(MA::template New<SP>())
        ,m_Synchronized(false)
        {
            Memory::AutoPointer<IEnumerator<T> > it=Collection->GetEnumerator();
            while (it->MoveNext())
                Enqueue(*it->Current());
        }

        template<typename T, typename SP, typename MA, typename MO>
        Queue<T,SP,MA,MO>::~Queue()
        {
            Clear();
            TrimExcess();
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::UInt32 Queue<T,SP,MA,MO>::Count()const
        {
            return m_Size;
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::UInt32 Queue<T,SP,MA,MO>::Capacity()const
        {
            return m_Capacity;
        }

        template<typename T, typename SP, typename MA, typename MO>
        void Queue<T,SP,MA,MO>::Enqueue(const T& Item)
        {
            Node* node;
            if (m_Capacity==0)
                node=MA::template New<Node>();
            else
            {
                node=m_Reserved;
                m_Reserved=m_Reserved->m_Next;
                --m_Capacity;
            }

            node->m_Next=0;
            node->m_Value=Item;
            ++m_Size;
            if (m_Head==0)
                m_Head=node;
            if (m_Tail!=0)
                m_Tail->m_Next=node;
            m_Tail=node;
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Bool Queue<T,SP,MA,MO>::Dequeue(T& Item)
        {
            RFTYPE::Bool result=false;
            if (m_Size>1)
            {
                result=true;
                Item=m_Tail->m_Value;
                // find prev of last node
                Node* n=m_Head;
                while(n->m_Next!=m_Tail)
                    n=n->m_Next;
                // move node to reserved nodes
                m_Tail->m_Next=m_Reserved;
                m_Reserved=m_Tail;
                --m_Size;
                ++m_Capacity;
                // setup new m_Tail
                m_Tail=n;
                m_Tail->m_Next=0;
            }
            else
                if (m_Size==1)
                {
                    result=true;
                    Item=m_Tail->m_Value;
                    // move node to reserved nodes
                    m_Tail->m_Next=m_Reserved;
                    m_Reserved=m_Tail;
                    ++m_Capacity;
                    // 
                    m_Head=0;
                    m_Tail=0;
                    m_Size=0;                    
                }
            return result;
        }


        template<typename T, typename SP, typename MA, typename MO>
        void Queue<T,SP,MA,MO>::Dequeue()
        {
            if (m_Size>1)
            {
                // find prev of last node
                Node* n=m_Head;
                while(n->m_Next!=m_Tail)
                    n=n->m_Next;
                // move node to reserved nodes
                m_Tail->m_Next=m_Reserved;
                m_Reserved=m_Tail;
                --m_Size;
                ++m_Capacity;
                // setup new m_Tail
                m_Tail=n;
                m_Tail->m_Next=0;
            }
            else
                if (m_Size==1)
                {
                    // move node to reserved nodes
                    m_Tail->m_Next=m_Reserved;
                    m_Reserved=m_Tail;
                    ++m_Capacity;
                    // 
                    m_Head=0;
                    m_Tail=0;
                    m_Size=0;                    
                }
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Bool Queue<T,SP,MA,MO>::Contains(const T& Item)
        {
            Node* n=m_Head;
            while(n!=0)
            {
                if (n->m_Value==Item)
                    return true;
                n=n->m_Next;
            }
            return false;
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Bool Queue<T,SP,MA,MO>::CopyTo(Array<T,SP,MA,MO>& Destination, 
                                                    RFTYPE::UInt32 ArrayIndex)
        {
            if (Destination.Count()-ArrayIndex<m_Size)
                return false;

            Node* n=m_Head;
            RFTYPE::UInt32 ind=ArrayIndex;
            while(n!=0)
            {
                Destination.SetValue(n->m_Value,ind);
                n=n->m_Next;
                ++ind;
            }
            return true;
        }

        template<typename T, typename SP, typename MA, typename MO>
        void Queue<T,SP,MA,MO>::Clear()
        {
            if (m_Tail!=0)
            {
                m_Head=0;
                m_Tail->m_Next=m_Reserved;
                m_Reserved=m_Tail;
                m_Tail=0;
                m_Capacity+=m_Size;
                m_Size=0;
            }                
        }

        template<typename T, typename SP, typename MA, typename MO>
        Memory::AutoPointer<IEnumerator<T> > Queue<T,SP,MA,MO>::GetEnumerator()
        {
            Memory::AutoPointer<IEnumerator<T> > result(
                new LinkedEnumerator<T,Node>(m_Head,m_Tail));
            return result;
        }

        template<typename T, typename SP, typename MA, typename MO>
        Threading::ISynchronize& Queue<T,SP,MA,MO>::SyncRoot()
        {
            return *m_SyncRoot;
        }

        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Bool Queue<T,SP,MA,MO>::IsSynchronized()const
        {
            return m_Synchronized;
        }

        template<typename T, typename SP, typename MA, typename MO>
        T* Queue<T,SP,MA,MO>::Peek()
        {
            return m_Tail==0?0:&m_Tail->m_Value;
        }          

        template<typename T, typename SP, typename MA, typename MO>
        void Queue<T,SP,MA,MO>::TrimExcess()
        {
            Node *node=m_Reserved,*tmp;
            while (node!=0)
            {
                tmp=node;
                node=node->m_Next;
                MA::Free(tmp);
                m_Capacity=0;
            }                
            m_Reserved=0;
        }

        template<typename T, typename SP, typename MA, typename MO>
        Memory::AutoPointer<Array<T,SP,MA,MO> > Queue<T,SP,MA,MO>::ToArray()
        {
            typename Memory::AutoPointer<Array<T,SP,MA,MO> > arr(MA::template New<Array<T,SP,MA,MO> >());
            *arr=Array<T,SP,MA,MO>(m_Size);
            arr->Resize(m_Size);
            Node* n=m_Head;
            RFTYPE::UInt32 ind=0;
            while(n!=0)
            {
                arr->SetValue(n->m_Value,ind);
                n=n->m_Next;
                ++ind;
            }
            return arr;
        }
            
        template<typename T, typename SP, typename MA, typename MO>
        RFTYPE::Bool Queue<T,SP,MA,MO>::Swap(Queue<T,SP,MA,MO>& Other)
        {
            if (&Other==this)
                return false;

            RFTYPE::UInt32 tmpNum;
            tmpNum=m_Size;
            m_Size=Other.m_Size;
            Other.m_Size=tmpNum;
                
            tmpNum=m_Capacity;
            m_Capacity=Other.m_Capacity;
            Other.m_Capacity=tmpNum;
                
            Node* tmpNode;
            tmpNode=m_Head;
            m_Head=Other.m_Head;
            Other.m_Head=tmpNode;

            tmpNode=m_Tail;
            m_Tail=Other.m_Tail;
            Other.m_Tail=tmpNode;

            tmpNode=m_Reserved;
            m_Reserved=Other.m_Reserved;
            Other.m_Reserved=tmpNode;

            return true;
        }
    }
}

#endif // RF_COLLECTIONS_QUEUE_HPP
