#ifndef RF_COLLECTIONS_ENUMERATOR_HPP
#define RF_COLLECTIONS_ENUMERATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Collections {

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

    Enumerator& MoveBy(const RF_Type::Size Steps);

    RF_Type::Size Distance(const Enumerator& To);

    RF_Type::Size Size()const;

    T* Pointer();

    const T* Pointer()const;
};

template<typename T, class ENUMERATORTYPE /*= GenericEnumeratorType*/>
T* Enumerator<T, ENUMERATORTYPE>::Pointer()
{
    static_assert(sizeof(T) == 0, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE /*= GenericEnumeratorType*/>
const T* Enumerator<T, ENUMERATORTYPE>::Pointer()const
{
    static_assert(sizeof(T) == 0, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE /*= GenericEnumeratorType*/>
RF_Type::Size Enumerator<T, ENUMERATORTYPE>::Distance(const Enumerator& To)
{
    static_assert(sizeof(T) == 0, "Container isn't supported yet.");
}


template<typename T, class ENUMERATORTYPE>
Enumerator<T, ENUMERATORTYPE> Enumerator<T, ENUMERATORTYPE>::operator++(int)
{
    static_assert(sizeof(T) == 0, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE>
Enumerator<T, ENUMERATORTYPE>& Enumerator<T, ENUMERATORTYPE>::operator++()
{
    static_assert(sizeof(T) == 0, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE>
Enumerator<T, ENUMERATORTYPE> Enumerator<T, ENUMERATORTYPE>::operator--(int)
{
    static_assert(sizeof(T) == 0, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE>
Enumerator<T, ENUMERATORTYPE>& Enumerator<T, ENUMERATORTYPE>::operator--()
{
    static_assert(sizeof(T) == 0, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE>
T& Enumerator<T, ENUMERATORTYPE>::operator*()
{
    static_assert(sizeof(T) == 0, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE>
const T& Enumerator<T, ENUMERATORTYPE>::operator*() const
{
    static_assert(sizeof(T) == 0, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE>
T* Enumerator<T, ENUMERATORTYPE>::operator->()
{
    static_assert(sizeof(T) == 0, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE>
const T* Enumerator<T, ENUMERATORTYPE>::operator->() const
{
    static_assert(sizeof(T) == 0, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE>
Enumerator<T, ENUMERATORTYPE>& Enumerator<T, ENUMERATORTYPE>::MoveBy(const RF_Type::Size Steps)
{
    static_assert(sizeof(T) == 0, "Container isn't supported yet.");
}

template<typename T, class ENUMERATORTYPE>
RF_Type::Size Enumerator<T, ENUMERATORTYPE>::Size() const
{
    static_assert(sizeof(T) == 0, "Container isn't supported yet.");
}

}

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif // RF_COLLECTIONS_ENUMERATOR_HPP