#ifndef RF_COLLECTIONS_ARRAYENUMERATOR_HPP
#define RF_COLLECTIONS_ARRAYENUMERATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework { namespace Collections {

template <typename T>
class ArrayEnumerator
{
public:
    ArrayEnumerator(T* Begin, T* End);
    T* Current()const;
    RFTYPE::Bool MoveNext();
    void Reset();
    RFTYPE::Size GetLength()const;
    RFTYPE::Bool MoveTo(RFTYPE::Size Amount);
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
RFTYPE::Bool ArrayEnumerator<T>::MoveNext()
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
RFTYPE::Size ArrayEnumerator<T>::GetLength()const
{
    return static_cast<RFTYPE::Size>(m_End - m_Begin);
}

template <class T>
RFTYPE::Bool ArrayEnumerator<T>::MoveTo(RFTYPE::Size Amount)
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

} }

#endif // RF_COLLECTIONS_ARRAYENUMERATOR_HPP