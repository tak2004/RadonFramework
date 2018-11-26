#ifndef RF_COLLECTIONS_ARRAYENUMERATORTYPE_HPP
#define RF_COLLECTIONS_ARRAYENUMERATORTYPE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <iterator>
#include <RadonFramework/Collections/Enumerator.hpp>

namespace RadonFramework::Collections {

struct ArrayEnumeratorType
{};

template<typename T>
struct Enumerator<T, ArrayEnumeratorType>
{
    typedef T Type;
    typedef typename std::random_access_iterator_tag iterator_category;
    typedef typename T value_type;
    typedef typename RF_Type::Size difference_type;

    typedef typename T* pointer;
    typedef typename T& reference;

    /// post-increment operator
    Enumerator operator ++(int);
    /// pre-increment operator
    Enumerator& operator ++();
    /// post-decrement operator
    Enumerator operator --(int);
    /// pre-decrement operator
    Enumerator& operator --();
    /// 
    T& operator*();
    ///
    const T& operator*()const;
    ///
    T* operator->();
    ///
    const T* operator->()const;

	// STL iterator support
	bool operator!= (const Enumerator& other) const;

    Enumerator& MoveBy(const RF_Type::Size Steps);

    RF_Type::Size Size()const;

    RF_Type::Size AtIndex()const;

    const T* Pointer()const;
    T* Pointer();

    T* m_Start;
    RF_Type::Size m_Elements;
    T* m_Current;
};

template<typename T>
T* Enumerator<T, ArrayEnumeratorType>::Pointer()
{
    Assert(m_Current >= m_Start && m_Current < (m_Start + m_Elements), "Out of bound");
    return m_Current;
}

template<typename T>
const T* Enumerator<T, ArrayEnumeratorType>::Pointer()const
{
    Assert(m_Current >= m_Start && m_Current < (m_Start + m_Elements), "Out of bound");
    return m_Current;
}

template<typename T>
bool Enumerator<T, ArrayEnumeratorType>::operator!=(const Enumerator<T, ArrayEnumeratorType>& other) const
{
	return m_Current != other.m_Current;
}

template<typename T>
Enumerator<T, ArrayEnumeratorType> Enumerator<T, ArrayEnumeratorType>::operator++(int)
{
    Assert(m_Current < (m_Start + m_Elements), "Out of bound");
    auto result = *this;
    ++m_Current;
    return result;
}

template<typename T>
Enumerator<T, ArrayEnumeratorType>& Enumerator<T, ArrayEnumeratorType>::operator++()
{
    Assert(m_Current < (m_Start + m_Elements), "Out of bound");
    ++m_Current;
    return *this;
}

template<typename T>
Enumerator<T, ArrayEnumeratorType> Enumerator<T, ArrayEnumeratorType>::operator--(int)
{
    Assert(m_Current >= m_Start, "Out of bound");
    auto result = *this;
    --m_Current;
    return result;
}

template<typename T>
Enumerator<T, ArrayEnumeratorType>& Enumerator<T, ArrayEnumeratorType>::operator--()
{
    Assert(m_Current >= m_Start, "Out of bound");
    --m_Current;
    return *this;
}

template<typename T>
T& Enumerator<T, ArrayEnumeratorType>::operator*()
{
    Assert(m_Current >= m_Start && m_Current < (m_Start + m_Elements), "Out of bound");
    return *m_Current;
}

template<typename T>
const T& Enumerator<T, ArrayEnumeratorType>::operator*() const
{
    Assert(m_Current >= m_Start && m_Current < (m_Start + m_Elements), "Out of bound");
    return *m_Current;
}

template<typename T>
T* Enumerator<T, ArrayEnumeratorType>::operator->()
{
    Assert(m_Current >= m_Start && m_Current < (m_Start + m_Elements), "Out of bound");
    return m_Current;
}

template<typename T>
const T* Enumerator<T, ArrayEnumeratorType>::operator->() const
{
    Assert(m_Current >= m_Start && m_Current < (m_Start + m_Elements), "Out of bound");
    return m_Current;
}

template<typename T>
Enumerator<T, ArrayEnumeratorType>& Enumerator<T, ArrayEnumeratorType>::MoveBy(const RF_Type::Size Steps)
{
    Assert((m_Current + Steps) <= (m_Start + m_Elements), "Out of bound");
    m_Current += Steps;
    return *this;
}

template<typename T>
RF_Type::Size Enumerator<T, ArrayEnumeratorType>::AtIndex() const
{
    return static_cast<RF_Type::Size>(m_Current - m_Start);
}

template<typename T>
RF_Type::Size Enumerator<T, ArrayEnumeratorType>::Size() const
{
    return m_Elements;
}

}

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif // RF_COLLECTIONS_ARRAYENUMERATORTYPE_HPP