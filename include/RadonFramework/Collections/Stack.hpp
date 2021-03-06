#ifndef RF_COLLECTIONS_STACK_HPP
#define RF_COLLECTIONS_STACK_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Size.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Common/Assert.hpp>

namespace RadonFramework::Collections
{
/** @brief This class is can grow and shrink on one end.
 *
 * The Stack class supports the last-in-first-out(LIFO)
 * model for adding and removing elements, also known as
 * push and pop.
 */
template <typename T>
class Stack
{
public:
  class Iterator;

  Stack() = default;
  ~Stack();

  void Push(const T& Element);
  void Pop();
  void Clear();

  T& Peek();
  const T& Peek() const;
  RF_Type::UInt32 Size() const;
  T operator[](const RF_Type::Size Index) const;

protected:
  class Node
  {
  public:
    Node() = default;
    Node(const T& V);

    void SetNext(Node* N);
    Node* GetNext() const;
    void SetPrev(Node* P);
    Node* GetPrev() const;
    T& Value();

  protected:
    Node* m_Next = nullptr;
    Node* m_Prev = nullptr;
    T m_Value;
  };
  RF_Type::UInt32 m_Size = 0;
  Node* m_Data = nullptr;
  Node* m_Top = nullptr;
};

template <typename T>
T Stack<T>::operator[](const RF_Type::Size Index) const
{
  RF_ASSERT(m_Size > Index, "Out of bound.");
  Node* p = m_Data;
  RF_Type::Size count = Index;
  for(; count > 0; p = p->GetNext(), --count)
  {
  }
  return p->Value();
}

template <typename T>
Stack<T>::Node::Node(const T& V)
:m_Value(V)
{}

template <typename T>
void Stack<T>::Node::SetNext(Node* N)
{
  m_Next = N;
}

template <typename T>
typename Stack<T>::Node* Stack<T>::Node::GetNext() const
{
  return m_Next;
}

template <typename T>
void Stack<T>::Node::SetPrev(Node* P)
{
  m_Prev = P;
}

template <typename T>
typename Stack<T>::Node* Stack<T>::Node::GetPrev() const
{
  return m_Prev;
}

template <typename T>
T& Stack<T>::Node::Value()
{
  return m_Value;
}

//
//
//
template <typename T>
Stack<T>::~Stack()
{
  Clear();
}

template <typename T>
void Stack<T>::Clear()
{
  while(m_Top)
  {
    Pop();
  }
}

template <typename T>
void Stack<T>::Pop()
{
  RF_ASSERT(m_Top != nullptr, "Invalid operation.");
  if(m_Top)
  {
    Node* n = m_Top;
    if(n->GetPrev())
    {
      n->GetPrev()->SetNext(nullptr);
    }
    m_Top = n->GetPrev();
    delete n;
    m_Size -= 1;
  }
}

template <typename T>
void Stack<T>::Push(const T& Element)
{
  if(m_Top == nullptr)
  {
    Node* n = new Node(Element);
    m_Data = n;
    m_Top = n;
    m_Size += 1;
  }
  else
  {
    Node* n = new Node(Element);
    n->SetPrev(m_Top);
    m_Top->SetNext(n);
    m_Top = n;
    m_Size += 1;
  }
}

template <typename T>
T& Stack<T>::Peek()
{
  RF_ASSERT(m_Size > 0, "Invalid operation.");
  return m_Top->Value();
}

template <typename T>
const T& Stack<T>::Peek() const
{
  RF_ASSERT(m_Size > 0, "Invalid operation.");
  return m_Top->Value();
}

template <typename T>
RF_Type::UInt32 Stack<T>::Size() const
{
  return m_Size;
}

}  // namespace RadonFramework::Collections

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif  // RF_COLLECTIONS_STACK_HPP
