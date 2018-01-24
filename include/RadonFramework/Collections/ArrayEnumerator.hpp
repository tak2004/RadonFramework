#ifndef RF_COLLECTIONS_ARRAYENUMERATOR_HPP
#define RF_COLLECTIONS_ARRAYENUMERATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework::Collections {

template <typename T>
class [[deprecated]] ArrayEnumerator
{
public:
    ArrayEnumerator(T* Begin, T* End);
    T* Current()const;
    RF_Type::Bool MoveNext();
    void Reset();
    RF_Type::Size GetLength()const;
    RF_Type::Bool MoveTo(RF_Type::Size Amount);
    Memory::AutoPointer<ArrayEnumerator<T> > Begin()const;
    Memory::AutoPointer<ArrayEnumerator<T> > End()const;
protected:
    T* m_Begin;
    T* m_End;
    T* m_Previous;
    T* m_Current;
};

template <class T>
ArrayEnumerator<T>::ArrayEnumerator(T* Begin, T* End)
:m_Current(0)
,m_Begin(Begin)
,m_End(End)
,m_Previous(0)
{
}

template <class T>
T* ArrayEnumerator<T>::Current()const
{
    return m_Current;
}

template <class T>
RF_Type::Bool ArrayEnumerator<T>::MoveNext()
{
    if (m_Current==0 && m_Previous==0)
    {
        m_Current=m_Begin;
        return true;
    }
    if (m_Current<m_End)
    {
        m_Previous=m_Current++;
        return true;
    }
    if (m_Current==m_End)
    {
        m_Current=0;
        return false;
    }
    return false;
}

template <class T>
void ArrayEnumerator<T>::Reset()
{
    m_Current=0;
    m_Previous=0;
}

template <class T>
RF_Type::Size ArrayEnumerator<T>::GetLength()const
{
    return static_cast<RF_Type::Size>(m_End - m_Begin);
}

template <class T>
RF_Type::Bool ArrayEnumerator<T>::MoveTo(RF_Type::Size Amount)
{
    if (GetLength()>Amount)
    {
        m_Current=m_Begin+Amount;
        m_Previous=m_Begin+Amount-1;
        return true;
    }
    else
    {
        m_Current=0;
        m_Previous=0;
        return false;
    }
}

template <class T>
Memory::AutoPointer<ArrayEnumerator<T> > ArrayEnumerator<T>::Begin()const
{
    Memory::AutoPointer<ArrayEnumerator<T> > result(new ArrayEnumerator(*this));
    result->Reset();
    return result;
}

template <class T>
Memory::AutoPointer<ArrayEnumerator<T> > ArrayEnumerator<T>::End()const
{
    Memory::AutoPointer<ArrayEnumerator<T> > result(new ArrayEnumerator(*this));
    result->MoveTo(result->GetLength());
    return result;
}

}

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif // RF_COLLECTIONS_ARRAYENUMERATOR_HPP