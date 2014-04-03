#ifndef RF_AUTOPOINTERARRAY_HPP
#define RF_AUTOPOINTERARRAY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Memory {

template <typename T>
struct AutoPointerArrayData{T* Ptr; RFTYPE::Size Count;};

template <typename T>
struct AutoPointerArrayReference
{
    AutoPointerArrayData<T> m_Data;
            
    explicit AutoPointerArrayReference(AutoPointerArrayData<T> Ptr);
};

template <typename T>
class AutoPointerArray
{
    public:
        typedef T ElementType;

        explicit AutoPointerArray();
                
        AutoPointerArray(ElementType* Ptr, RFTYPE::Size Count,
            RFTYPE::Bool Copy = false);

        AutoPointerArray(AutoPointerArray& Copy);

        template <typename T1>
        AutoPointerArray(AutoPointerArray<T1>& Ref);

        AutoPointerArray(AutoPointerArrayReference<ElementType> Ref);

        ~AutoPointerArray();

        ElementType* Get()const;

        RFTYPE::Size Count()const;

        RFTYPE::Size Size()const;

        AutoPointerArray& operator=(const AutoPointerArray& Copy);

        template <typename T1>
        AutoPointerArray& operator=(AutoPointerArray<T1>& Copy);

        AutoPointerArray& operator=(const AutoPointerArrayReference<ElementType>& Ref);

        AutoPointerArrayData<T> Release();

        void Reset();

        void Reset(AutoPointerArrayData<T> Data);

        AutoPointerArray Clone()const;

        template <typename T1>
        operator AutoPointerArrayReference<T1>();

        template <typename T1>
        operator AutoPointerArray<T1>();

        T& operator [](const RFTYPE::Size Index);

        const T& operator [](const RFTYPE::Size Index)const;

        /// Return true if the pointer is 0 else false.
        RFTYPE::Bool operator!();
        /// Convert to Bool to allow boolean operation.
        operator RFTYPE::Bool();

        void Swap(AutoPointerArray<T>& Other);
    private:
        mutable T* m_Data;
        mutable RFTYPE::Size m_Size;
};

template<typename T>
AutoPointerArrayReference<T>::AutoPointerArrayReference(AutoPointerArrayData<T> Ptr)
:m_Data(Ptr)
{
}

template<typename T>
AutoPointerArray<T>::AutoPointerArray()
:m_Data(0)
,m_Size(0)
{

}

template<typename T>
AutoPointerArray<T>::AutoPointerArray(ElementType* Ptr, RFTYPE::Size Count,
    RFTYPE::Bool Copy)
{
    m_Size=Count;
    if (Copy)
    {
        m_Data=new ElementType[Count];
        for (RFTYPE::Size i=0; i<Count; ++i)
            m_Data[i]=ElementType(Ptr[i]);
    }
    else
        m_Data=Ptr;
}

template<typename T>
AutoPointerArray<T>::AutoPointerArray(AutoPointerArray& Copy)
{
    AutoPointerArrayData<T> data=Copy.Release();
    m_Size=data.Count;
    m_Data=data.Ptr;
}

template<typename T>
template <typename T1>
AutoPointerArray<T>::AutoPointerArray(AutoPointerArray<T1>& Ref)
{
    AutoPointerArrayData<T1> data=Ref.Release();
    m_Size=data.Count;
    m_Data=data.Ptr;
}

template<typename T>
AutoPointerArray<T>::AutoPointerArray(AutoPointerArrayReference<ElementType> Ref)
:m_Data(Ref.m_Data.Ptr)
,m_Size(Ref.m_Data.Count)
{
}

template<typename T>
AutoPointerArray<T>::~AutoPointerArray()
{
    if (m_Data)
        delete[] m_Data;
    m_Data=0;
    m_Size=0;
}

template<typename T>
T* AutoPointerArray<T>::Get()const
{
    return m_Data;
}

template<typename T>
RFTYPE::Size AutoPointerArray<T>::Count()const
{
    return m_Size;
}

template<typename T>
RFTYPE::Size AutoPointerArray<T>::Size()const
{
    return m_Size*sizeof(T);
}

template<typename T>
AutoPointerArray<T>& AutoPointerArray<T>::operator=(const AutoPointerArray<T>& Copy)
{
    Reset();
    m_Data=Copy.m_Data;
    Copy.m_Data=0;
    m_Size=Copy.m_Size;
    Copy.m_Size=0;
    return *this;
}

template<typename T>
template <typename T1>
AutoPointerArray<T>& AutoPointerArray<T>::operator=(AutoPointerArray<T1>& Copy)
{
    AutoPointerArrayData<T1> data=Copy.Release();
    Reset(*reinterpret_cast<AutoPointerArrayData<T>*>(&data));
    return *this;
}

template<typename T>
AutoPointerArray<T>& AutoPointerArray<T>::operator=(const AutoPointerArrayReference<ElementType>& Ref)
{
    if (Ref.m_Data.Ptr!=this->Get())
    {
        delete[] m_Data;
        m_Data=Ref.m_Data.Ptr;
        m_Size=Ref.m_Data.Count;
    }
    return *this;
}

template<typename T>
AutoPointerArrayData<T> AutoPointerArray<T>::Release()
{
    AutoPointerArrayData<T> arr;
    arr.Ptr=m_Data;
    arr.Count=m_Size;
    m_Data=0;
    m_Size=0;
    return arr;
}

template<typename T>
void AutoPointerArray<T>::Reset()
{
    delete[] m_Data;
    m_Data=0;
    m_Size=0;
}

template<typename T>
void AutoPointerArray<T>::Reset(AutoPointerArrayData<T> Data)
{
    if (m_Data!=Data.Ptr)
    {
        delete[] m_Data;
        m_Data=Data.Ptr;
        m_Size=Data.Count;
    }
}

template<typename T>
AutoPointerArray<T> AutoPointerArray<T>::Clone()const
{
    AutoPointerArray arr;
    arr.m_Data=new ElementType[m_Size];
    arr.m_Size=m_Size;
    RFMEM::Copy(arr.m_Data, m_Data, m_Size*sizeof(T));
    return arr;
}

template<typename T>
template <typename T1>
AutoPointerArray<T>::operator AutoPointerArrayReference<T1>()
{
    AutoPointerArrayData<T1> tmp(this->Release());
    AutoPointerArrayReference<T1> result(tmp);
    return result;
}

template<typename T>
template<typename T1>
AutoPointerArray<T>::operator AutoPointerArray<T1>()
{
    return AutoPointerArray<T1>(this->Release());
}

template<typename T>
T& AutoPointerArray<T>::operator [](const RFTYPE::Size Index)
{
    Assert(Index<m_Size, "Out of bound.");
    return m_Data[Index];
}

template<typename T>
const T& AutoPointerArray<T>::operator [](const RFTYPE::Size Index)const
{
    Assert(Index<m_Size, "Out of bound.");
    return m_Data[Index];
}

template<typename T>
void AutoPointerArray<T>::Swap(AutoPointerArray<T>& Other)
{
    T* p=m_Data;
    m_Data=Other.m_Data;
    Other.m_Data=p;
    RFTYPE::Size s = m_Size;
    m_Size=Other.m_Size;
    Other.m_Size=s;
}

template<typename T>
RFTYPE::Bool AutoPointerArray<T>::operator!()
{
    return 0==m_Data;
}

template<typename T>
AutoPointerArray<T>::operator RFTYPE::Bool()
{
    return 0!=m_Data;
}

} }

#endif // RF_AUTOPOINTERARRAY_HPP
