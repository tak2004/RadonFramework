#ifndef RF_COLLECTIONS_TREE_HPP
#define RF_COLLECTIONS_TREE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Algorithm/FindAll.hpp>
#include <RadonFramework/Collections/Algorithm/ForEach.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Core/Common/Assert.hpp>

namespace RadonFramework::Collections
{
template <class T, class NodeInfo>
class Node;

template <class T>
class ArrayNode
{
public:
  ArrayNode(ArrayNode<T>* Parent = nullptr);
  ArrayNode(const ArrayNode<T>& Copy);

  ArrayNode<T>* AddChild(const T& Value);
  void AddChilds(RF_Type::Size Count);
  void RemoveChild(ArrayNode<T>* Node);
  ArrayNode<T>* FirstChild();
  const ArrayNode<T>* FirstChild() const;
  ArrayNode<T>* LastChild();
  void MoveFrom(ArrayNode<T>& Node, RF_Type::Size Start, RF_Type::Size End);

  ArrayNode<T>* Parent();
  const ArrayNode<T>* Parent() const;
  ArrayNode<T>* Next();
  const ArrayNode<T>* Next() const;
  ArrayNode<T>* Prev();
  const ArrayNode<T>* Prev() const;
  ArrayNode<T>* Child(RF_Type::Size Index);

  T& Data();
  const T& Data() const;
  RF_Type::Size Childs() const;
  RF_Type::Bool IndexOf(const ArrayNode<T>& Object, RF_Type::Size& Index) const;

  ArrayNode<T>& operator=(const ArrayNode<T>& Other);

protected:
  ArrayNode<T>* m_Parent;
  Array<ArrayNode<T>> m_Children;
  T m_Data;
};

template <class T>
void ArrayNode<T>::MoveFrom(ArrayNode<T>& Node,
                            RF_Type::Size Start,
                            RF_Type::Size End)
{
  RF_Type::Size index = m_Children.Count();
  RF_Type::Size count = End - Start + 1;
  if(count > 0)
  {
    m_Children.Resize(index + count);
    Node.m_Children.Copy(Start, m_Children, index, count);
    Node.m_Children.ConstrainedCopy(End + 1, Node.m_Children, Start,
                                    Node.m_Children.Count() - End - 1);
    Node.m_Children.Resize(Node.m_Children.Count() - count);
    for(RF_Type::Size i = 0; i < m_Children.Count(); ++i)
    {
      m_Children(i).m_Parent = this;
    }
  }
}

template <class T, class Node = ArrayNode<T>>
class Tree
{
public:
  using NodeType = Node;
  using ValueType = T;

  NodeType& GetRootElement();
  const NodeType& GetRootElement() const;
  void SetRootElement(NodeType& RootElement);

protected:
  NodeType m_Root;
};

template <class T>
RF_Type::Size ArrayNode<T>::Childs() const
{
  return m_Children.Count();
}

template <class T>
ArrayNode<T>* ArrayNode<T>::Child(RF_Type::Size Index)
{
  ArrayNode<T>* result = nullptr;

  if(m_Children.Count() > Index)
  {
    result = &m_Children(Index);
  }

  return result;
}

template <class T>
RF_Type::Bool
ArrayNode<T>::IndexOf(const ArrayNode<T>& Object, RF_Type::Size& Index) const
{
  RF_Type::Bool result = false;

  auto hits = RF_Algo::FindAll(
      m_Children,
      [&](typename Array<ArrayNode<T>>::ConstEnumeratorType& Element) {
        RF_Type::Bool result = false;
        if(&(*Element) == &Object)
        {
          result = true;
        }
        return result;
      });

  if(hits.Count() > 0)
  {
    Index = hits[0];
    result = true;
  }

  return result;
}

template <class T>
void ArrayNode<T>::AddChilds(RF_Type::Size Count)
{
  if(m_Children.Count() == 0)
  {
    m_Children = Array<ArrayNode<T>>(Count);
  }
  else
  {
    m_Children.Resize(m_Children.Count() + Count);
  }
  RF_Algo::ForEach(m_Children,
                   [=](typename Array<ArrayNode<T>>::EnumeratorType& Element) {
                     Element->m_Parent = this;
                     Element->m_Data = T();
                   });
}

template <class T>
ArrayNode<T>::ArrayNode(ArrayNode<T>* Parent /* = 0 */) : m_Parent(Parent)
{
}

template <class T>
ArrayNode<T>::ArrayNode(const ArrayNode<T>& Copy)
{
  *this = Copy;
}

template <class T>
ArrayNode<T>* ArrayNode<T>::AddChild(const T& Value)
{
  if(m_Children.Count() == 0)
    m_Children = Array<ArrayNode<T>>(1);
  else
    m_Children.Resize(m_Children.Count() + 1);
  m_Children(m_Children.Count() - 1).m_Data = Value;
  m_Children(m_Children.Count() - 1).m_Parent = this;
  return &m_Children(m_Children.Count() - 1);
}

template <class T>
void ArrayNode<T>::RemoveChild(ArrayNode<T>* Node)
{
  RF_ASSERT(m_Children.Count() > 0, "Invalid parameter.");
  if(m_Children.Count() > 1)  // most expected case
  {
    RF_Type::MemoryRange index = Node - &m_Children(0);
    Array<ArrayNode<T>> tmp(m_Children.Count() - 1);
    if(index > 0)
    {
      RF_Type::Size rightPart = index + 1;
      m_Children.Copy(0, tmp, 0, index);
      if(index < tmp.Count())  // if not the last one
      {
        m_Children.Copy(rightPart, tmp, index, tmp.Count() - index);
      }
    }
    else  // index==0
    {
      m_Children.Copy(1, tmp, 0, tmp.Count());
    }
    m_Children.Swap(tmp);
  }
  else  // count==1
  {
    RF_ASSERT(Node == &m_Children(0), "Invalid parameter.");
    m_Children.Resize(0);
  }
}

template <class T>
ArrayNode<T>* ArrayNode<T>::FirstChild()
{
  ArrayNode<T>* result = nullptr;

  if(m_Children.Count() > 0)
  {
    result = &m_Children(0);
  }

  return result;
}

template <class T>
const ArrayNode<T>* ArrayNode<T>::FirstChild() const
{
  const ArrayNode<T>* result = 0;

  if(m_Children.Count() > 0)
  {
    result = &m_Children(0);
  }

  return result;
}

template <class T>
ArrayNode<T>* ArrayNode<T>::LastChild()
{
  ArrayNode<T>* result = 0;

  if(m_Children.Count() > 0)
  {
    result = &m_Children(m_Children.Count() - 1);
  }

  return result;
}

template <class T>
ArrayNode<T>* ArrayNode<T>::Parent()
{
  return m_Parent;
}

template <class T>
const ArrayNode<T>* ArrayNode<T>::Parent() const
{
  return m_Parent;
}

template <class T>
ArrayNode<T>* ArrayNode<T>::Next()
{
  ArrayNode<T>* result = nullptr;
  if(m_Parent)
  {
    if(m_Parent->m_Children.Count() > 0)
    {
      RF_Type::MemoryRange index = this - &m_Parent->m_Children(0) + 1;
      if(index < m_Parent->m_Children.Count())
      {
        result = &m_Parent->m_Children(index);
      }
    }
  }
  return result;
}

template <class T>
const ArrayNode<T>* ArrayNode<T>::Next() const
{
  const ArrayNode<T>* result = nullptr;
  if(m_Parent)
  {
    if(m_Parent->m_Children.Count() > 0)
    {
      RF_Type::MemoryRange index = this - &m_Parent->m_Children(0) + 1;
      if(index < m_Parent->m_Children.Count())
      {
        result = &m_Parent->m_Children(index);
      }
    }
  }
  return result;
}

template <class T>
ArrayNode<T>* ArrayNode<T>::Prev()
{
  ArrayNode<T>* result = nullptr;
  if(m_Parent)
  {
    if(m_Parent->m_Children.Count() > 0)
    {
      RF_Type::MemoryRange index = this - &m_Parent->m_Children(0) - 1;
      if(index >= 0)
      {
        result = &m_Parent->m_Children(index);
      }
    }
  }
  return result;
}

template <class T>
inline const ArrayNode<T>* ArrayNode<T>::Prev() const
{
  const ArrayNode<T>* result = nullptr;
  if(m_Parent)
  {
    if(m_Parent->m_Children.Count() > 0)
    {
      RF_Type::MemoryRange index = this - &m_Parent->m_Children(0) - 1;
      if(index >= 0)
      {
        result = &m_Parent->m_Children(index);
      }
    }
  }
  return result;
}

template <class T>
T& ArrayNode<T>::Data()
{
  return m_Data;
}

template <class T>
const T& ArrayNode<T>::Data() const
{
  return m_Data;
}

template <class T>
ArrayNode<T>& ArrayNode<T>::operator=(const ArrayNode<T>& Other)
{
  m_Parent = Other.m_Parent;
  Other.m_Children.Clone()->Swap(m_Children);
  for(RF_Type::UInt32 i = 0; i < m_Children.Count(); ++i)
  {
    m_Children(i).m_Parent = this;
  }
  m_Data = Other.m_Data;
  return *this;
}

template <class T, class NodeInfo>
typename Tree<T, NodeInfo>::NodeType& Tree<T, NodeInfo>::GetRootElement()
{
  return m_Root;
}

template <class T, class NodeInfo>
const typename Tree<T, NodeInfo>::NodeType&
Tree<T, NodeInfo>::GetRootElement() const
{
  return m_Root;
}

template <class T, class NodeInfo>
void Tree<T, NodeInfo>::SetRootElement(
    typename Tree<T, NodeInfo>::NodeType& RootElement)
{
  m_Root = RootElement;
}

}  // namespace RadonFramework::Collections

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif  // RF_COLLECTIONS_TREE_HPP