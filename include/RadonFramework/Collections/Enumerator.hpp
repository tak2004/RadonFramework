#ifndef RF_COLLECTIONS_ENUMERATOR_HPP
#define RF_COLLECTIONS_ENUMERATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Collections {

struct GenericEnumeratorType{};

template<typename T, class ENUMERATORTYPE = GenericEnumeratorType>
struct Enumerator
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
};

template<typename T, class ENUMERATORTYPE>
Enumerator<T, ENUMERATORTYPE> Enumerator<T, ENUMERATORTYPE>::operator++(int)
{
    static_assert(false, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE>
Enumerator<T, ENUMERATORTYPE>& Enumerator<T, ENUMERATORTYPE>::operator++()
{
    static_assert(false, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE>
Enumerator<T, ENUMERATORTYPE> Enumerator<T, ENUMERATORTYPE>::operator--(int)
{
    static_assert(false, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE>
Enumerator<T, ENUMERATORTYPE>& Enumerator<T, ENUMERATORTYPE>::operator--()
{
    static_assert(false, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE>
T& Enumerator<T, ENUMERATORTYPE>::operator*()
{
    static_assert(false, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE>
const T& Enumerator<T, ENUMERATORTYPE>::operator*() const
{
    static_assert(false, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE>
T* Enumerator<T, ENUMERATORTYPE>::operator->()
{
    static_assert(false, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE>
const T* Enumerator<T, ENUMERATORTYPE>::operator->() const
{
    static_assert(false, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE>
Enumerator<T, ENUMERATORTYPE>& Enumerator<T, ENUMERATORTYPE>::MoveBy(const RFTYPE::Size Steps)
{
    static_assert(false, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE>
RFTYPE::Size Enumerator<T, ENUMERATORTYPE>::Size() const
{
    static_assert(false, "Container isn't supported yet.");
}

} }

#endif // RF_COLLECTIONS_ENUMERATOR_HPP