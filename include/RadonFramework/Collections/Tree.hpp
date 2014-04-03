#ifndef RF_COLLECTIONS_TREE_HPP
#define RF_COLLECTIONS_TREE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Diagnostics/Debugging/Assert.hpp>

namespace RadonFramework
{
    namespace Collections
    {
        template<class T,class NodeInfo> class Node;

        template<class T>
        class ArrayNode
        {
            public:
                ArrayNode(ArrayNode<T>* Parent=0);

                ArrayNode(const ArrayNode<T>& Copy);

                ArrayNode<T>* AddChild(const T& Value);

                void RemoveChild(ArrayNode<T>* Node);

                ArrayNode<T>* FirstChild();

                ArrayNode<T>* LastChild();

                ArrayNode<T>* Parent();

                ArrayNode<T>* Next();

                ArrayNode<T>* Prev();

                T& Data();

                ArrayNode<T>& operator =(const ArrayNode<T>& Other);
            protected:
                ArrayNode<T>* m_Parent;
                Array<ArrayNode<T> > m_Children;
                T m_Data;
        };

        template <class T, class Node=ArrayNode<T> >
        class Tree
        {
            public:
                typedef Node NodeType;
                typedef T ValueType;

                NodeType& GetRootElement();
                void SetRootElement(NodeType& RootElement);
            protected:
                NodeType m_Root;
        };

        template <class T>
        ArrayNode<T>::ArrayNode(ArrayNode<T>* Parent /* = 0 */)
        :m_Parent(Parent)
        {
        }

        template <class T>
        ArrayNode<T>::ArrayNode(const ArrayNode<T>& Copy)
        {
            *this=Copy;
        }

        template <class T>
        ArrayNode<T>* ArrayNode<T>::AddChild(const T& Value)
        {
            if (m_Children.Count()==0)
                m_Children=Array<ArrayNode<T> >(1);
            else
                m_Children.Resize(m_Children.Count()+1);
            m_Children(m_Children.Count()-1).m_Data=Value;
            m_Children(m_Children.Count()-1).m_Parent=this;
            return &m_Children(m_Children.Count()-1);
        }

        template <class T>
        void ArrayNode<T>::RemoveChild(ArrayNode<T>* Node)
        {
            Assert(m_Children.Count()>0,"Invalid parameter.");
            if (m_Children.Count()>1)// most expected case
            {
                RFTYPE::UInt32 index=(RFTYPE::UInt32)((&m_Children[0]-Node)/sizeof(T));
                Array<ArrayNode<T> > tmp(m_Children.Count()-1);
                if (index>0)
                {
                    RFTYPE::UInt32 leftPart=index-1;
                    RFTYPE::UInt32 rightPart=index+1;
                    m_Children.Copy(0,tmp,0,leftPart);
                    if (index<tmp.Count())// if not the last one
                        m_Children.Copy(rightPart,tmp,index,tmp.Count()-index);
                }
                else// index==0
                    m_Children.Copy(1,tmp,0,tmp.Count());
                m_Children.Swap(tmp);
            }
            else// count==1
            {
                Assert(Node==&m_Children[0],"Invalid parameter.");
                m_Children.Resize(0);
            }
        }

        template <class T>
        ArrayNode<T>* ArrayNode<T>::FirstChild()
        {
            Assert(m_Children.Count()>0,"Invalid operation on empty container.");
            if (m_Children.Count()>0)
                return &m_Children(0);
            else
                return 0;
        }

        template <class T>
        ArrayNode<T>* ArrayNode<T>::LastChild()
        {
            Assert(m_Children.Count()>0,"Invalid operation on empty container.");
            if (m_Children.Count()>0)
                return &m_Children(m_Children.Count()-1);
            else
                return 0;
        }

        template <class T>
        ArrayNode<T>* ArrayNode<T>::Parent()
        {
            return m_Parent;
        }

        template <class T>
        ArrayNode<T>* ArrayNode<T>::Next()
        {
            Assert(m_Parent,"Invalid Operation on null pointer.");
            if (m_Parent->m_Children.Count()==0)
                return 0;
            RFTYPE::MemoryRange index=this-&m_Parent->m_Children(0);
            if (static_cast<RFTYPE::MemoryRange>(m_Parent->m_Children.Count()) <= index+1)
                return 0;
            else    
                return &m_Parent->m_Children(static_cast<RFTYPE::UInt32>(index)+1);
        }

        template <class T>
        ArrayNode<T>* ArrayNode<T>::Prev()
        {
            Assert(m_Parent,"Invalid operation.");
            if (m_Parent->m_Children.Count()==0)
                return 0;
            RFTYPE::MemoryRange index=this-&m_Parent->m_Children(0);
            if (m_Parent->m_Children.Count()<=index-1)
                return 0;
            else
                return &m_Parent->m_Children(index-1);
        }

        template <class T>
        T& ArrayNode<T>::Data()
        {
            return m_Data;
        }

        template <class T>
        ArrayNode<T>& ArrayNode<T>::operator =(const ArrayNode<T>& Other)
        {
            m_Parent=Other.m_Parent;
            Other.m_Children.Clone()->Swap(m_Children);
            for (RFTYPE::UInt32 i=0;i<m_Children.Count();++i)
                m_Children(i).m_Parent=this;
            m_Data=Other.m_Data;
            return *this;
        }

        template <class T, class NodeInfo>
        typename Tree<T,NodeInfo>::NodeType& Tree<T,NodeInfo>::GetRootElement()
        {
            return m_Root;
        }

        template <class T, class NodeInfo>
        void Tree<T,NodeInfo>::SetRootElement(typename Tree<T,NodeInfo>::NodeType& RootElement)
        {
            m_Root=RootElement;
        }
    }
}

#endif // RF_COLLECTIONS_TREE_HPP