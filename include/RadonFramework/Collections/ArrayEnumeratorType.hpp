#ifndef RF_COLLECTIONS_ARRAYENUMERATORTYPE_HPP
#define RF_COLLECTIONS_ARRAYENUMERATORTYPE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Collections {

struct ArrayEnumeratorType
{};

template<typename T>
struct Enumerator <T, ArrayEnumeratorType>
{
    typedef T Type;
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

    Enumerator& MoveBy(const RFTYPE::Size Steps);

    RFTYPE::Size Size()const;

    T* m_Start;
    RFTYPE::Size m_Elements;
    T* m_Current;
};

template<typename T>
Enumerator<T, ArrayEnumeratorType> Enumerator<T, ArrayEnumeratorType>::operator++(int)
{
    Assert(m_Current < m_Start + m_Elements, "Out of bound");
    auto result = *this;
    ++m_Current;
    return result;
}

template<typename T>
Enumerator<T, ArrayEnumeratorType>& Enumerator<T, ArrayEnumeratorType>::operator++()
{
    Assert(m_Current < m_Start + m_Elements, "Out of bound");
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
    Assert(m_Current >= m_Start && m_Current < m_Start + m_Elements, "Out of bound");
    return *m_Current;
}

template<typename T>
const T& Enumerator<T, ArrayEnumeratorType>::operator*() const
{
    Assert(m_Current >= m_Start && m_Current < m_Start + m_Elements, "Out of bound");
    return *m_Current;
}

template<typename T>
T* Enumerator<T, ArrayEnumeratorType>::operator->()
{
    Assert(m_Current >= m_Start && m_Current < m_Start + m_Elements, "Out of bound");
    return m_Current;
}

template<typename T>
const T* Enumerator<T, ArrayEnumeratorType>::operator->() const
{
    Assert(m_Current >= m_Start && m_Current < m_Start + m_Elements, "Out of bound");
    return m_Current;
}

template<typename T>
Enumerator<T, ArrayEnumeratorType>& Enumerator<T, ArrayEnumeratorType>::MoveBy(const RFTYPE::Size Steps)
{
    Assert(m_Current + Steps <= m_Start + m_Elements, "Out of bound");
    m_Current += Steps;
    return *this;
}

template<typename T>
RFTYPE::Size Enumerator<T, ArrayEnumeratorType>::Size() const
{
    return m_Elements;
}

} }

#endif // RF_COLLECTIONS_ARRAYENUMERATORTYPE_HPP