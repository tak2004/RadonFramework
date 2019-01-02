#ifndef RF_COLLECTIONS_ARRAYENUMERATORTYPE_HPP
#define RF_COLLECTIONS_ARRAYENUMERATORTYPE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Diagnostics/Debugging/Assert.hpp>
#include <RadonFramework/Collections/Enumerator.hpp>
#include <iterator>

namespace RadonFramework::Collections
{
struct ArrayEnumeratorType
{
};

template <typename T>
struct Enumerator<T, ArrayEnumeratorType>
{
  using Type = T;
  using iterator_category = typename std::random_access_iterator_tag;
  using value_type = typename T;
  using difference_type = typename RF_Type::Size;

  using pointer = typename T*;
  using reference = typename T&;

  /// post-increment operator
  Enumerator operator++(int);
  /// pre-increment operator
  Enumerator& operator++();
  /// post-decrement operator
  Enumerator operator--(int);
  /// pre-decrement operator
  Enumerator& operator--();
  ///
  T& operator*();
  ///
  const T& operator*() const;
  ///
  T* operator->();
  ///
  const T* operator->() const;

  // STL iterator support
  bool operator!=(const Enumerator& other) const;

  Enumerator& MoveBy(const RF_Type::Size Steps);

  RF_Type::Size Size() const;

  RF_Type::Size AtIndex() const;

  const T* Pointer() const;
  T* Pointer();

  T* m_Start;
  RF_Type::Size m_Elements;
  T* m_Current;
};

template <typename T>
T* Enumerator<T, ArrayEnumeratorType>::Pointer()
{
  RF_ASSERT(m_Current >= m_Start && m_Current < (m_Start + m_Elements),
         "Out of bound");
  return m_Current;
}

template <typename T>
const T* Enumerator<T, ArrayEnumeratorType>::Pointer() const
{
  RF_ASSERT(m_Current >= m_Start && m_Current < (m_Start + m_Elements),
         "Out of bound");
  return m_Current;
}

template <typename T>
bool Enumerator<T, ArrayEnumeratorType>::
operator!=(const Enumerator<T, ArrayEnumeratorType>& other) const
{
  return m_Current != other.m_Current;
}

template <typename T>
Enumerator<T, ArrayEnumeratorType> Enumerator<T, ArrayEnumeratorType>::
operator++(int)
{
  RF_ASSERT(m_Current < (m_Start + m_Elements), "Out of bound");
  auto result = *this;
  ++m_Current;
  return result;
}

template <typename T>
Enumerator<T, ArrayEnumeratorType>& Enumerator<T, ArrayEnumeratorType>::
operator++()
{
  RF_ASSERT(m_Current < (m_Start + m_Elements), "Out of bound");
  ++m_Current;
  return *this;
}

template <typename T>
Enumerator<T, ArrayEnumeratorType> Enumerator<T, ArrayEnumeratorType>::
operator--(int)
{
  RF_ASSERT(m_Current >= m_Start, "Out of bound");
  auto result = *this;
  --m_Current;
  return result;
}

template <typename T>
Enumerator<T, ArrayEnumeratorType>& Enumerator<T, ArrayEnumeratorType>::
operator--()
{
  RF_ASSERT(m_Current >= m_Start, "Out of bound");
  --m_Current;
  return *this;
}

template <typename T>
T& Enumerator<T, ArrayEnumeratorType>::operator*()
{
  RF_ASSERT(m_Current >= m_Start && m_Current < (m_Start + m_Elements),
         "Out of bound");
  return *m_Current;
}

template <typename T>
const T& Enumerator<T, ArrayEnumeratorType>::operator*() const
{
  RF_ASSERT(m_Current >= m_Start && m_Current < (m_Start + m_Elements),
         "Out of bound");
  return *m_Current;
}

template <typename T>
T* Enumerator<T, ArrayEnumeratorType>::operator->()
{
  RF_ASSERT(m_Current >= m_Start && m_Current < (m_Start + m_Elements),
         "Out of bound");
  return m_Current;
}

template <typename T>
const T* Enumerator<T, ArrayEnumeratorType>::operator->() const
{
  RF_ASSERT(m_Current >= m_Start && m_Current < (m_Start + m_Elements),
         "Out of bound");
  return m_Current;
}

template <typename T>
Enumerator<T, ArrayEnumeratorType>&
Enumerator<T, ArrayEnumeratorType>::MoveBy(const RF_Type::Size Steps)
{
  RF_ASSERT((m_Current + Steps) <= (m_Start + m_Elements), "Out of bound");
  m_Current += Steps;
  return *this;
}

template <typename T>
RF_Type::Size Enumerator<T, ArrayEnumeratorType>::AtIndex() const
{
  return static_cast<RF_Type::Size>(m_Current - m_Start);
}

template <typename T>
RF_Type::Size Enumerator<T, ArrayEnumeratorType>::Size() const
{
  return m_Elements;
}

}  // namespace RadonFramework::Collections

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif  // RF_COLLECTIONS_ARRAYENUMERATORTYPE_HPP