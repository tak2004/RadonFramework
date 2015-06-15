#ifndef RF_COLLECTIONS_AUTOVECTOR_HPP
#define RF_COLLECTIONS_AUTOVECTOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>

namespace RadonFramework { namespace Collections {

/** @brief The AutoVector class is designed to work more safety with pointer.
*
* The class base on a link list and every node hold a pointer.
* The primary gloal is to avoid memory leaks and the secondary is speed.
* Moving Pointer instead of whole objects is much faster and the class
* support auto_ptr(c++ std),AutoPointer and AutoPointerArray.
*
* Some compiler can't recognize that a AutoVector is returned by a function
* and have to be converted to non const, to swap the ressource.
* This problem will generate an error if you try to assign the result of a
* function to a variable. Instead of assign operator you can use the Swap
* method of the result and set the variable as parameter.
* AutoVector vec;
* vec=MyFunctionReturnAutoVector();//generate an error on some compiler
* MyFunctionReturnAutoVector().Swap(vec);//works fine
*/
template<class T>
class AutoVector
{
public:
    struct PtrInfo
    {
        T* m_Ptr;
        RF_Type::Bool m_IsArray;
        RF_Type::Size m_ElementCount;
    };

    struct AutoVectorReference
    {
        List<PtrInfo> m_PointerList;
        explicit AutoVectorReference(List<PtrInfo>& PointerList){m_PointerList.Swap(PointerList);}
    };

    class Iterator:public List<PtrInfo>::Iterator
    {
    public:
        Iterator(const typename List<PtrInfo>::Iterator& Copy)
        :List<PtrInfo>::Iterator(Copy)
        {
        }
        T** operator->()const
        {
            Assert(this->m_Node,"Invalid use of null pointer.");
            return &this->m_Node->Value().m_Ptr;
        }
        T*& operator*()const
        {
            Assert(this->m_Node,"Invalid use of null pointer.");
            return this->m_Node->Value().m_Ptr;
        }
    };

    class ConstIterator:public List<PtrInfo>::ConstIterator
    {
    public:
        ConstIterator(const typename List<PtrInfo>::ConstIterator& Copy)
        :List<PtrInfo>::ConstIterator(Copy)
        {
        }
        T const* const* operator->()const
        {
            Assert(this->m_Node,"Invalid use of null pointer.");
            return &(const T*)(this->m_Node->Value().m_Ptr);
        }
        T const* const& operator*()const
        {
            Assert(this->m_Node,"Invalid use of null pointer.");
            return (const T*)this->m_Node->Value().m_Ptr;
        }
    };
    AutoVector();
    ~AutoVector();
    AutoVector(AutoVector<T> &Copy);
    AutoVector(AutoVectorReference Copy);
    AutoVector<T>& operator=(AutoVector<T>& From);
    AutoVector<T>& operator=(AutoVectorReference From);
    void Swap(AutoVector<T> &Other);

    RF_Type::UInt32 Size()const;
    void Erase(RF_Type::UInt32 Index);
    void Erase(Iterator It);
    void Erase(ConstIterator It);
    void Release(RF_Type::UInt32 Index, Memory::AutoPointer<T>& Ptr);
    void Release(RF_Type::UInt32 Index, Memory::AutoPointerArray<T>& Ptr);
    void Clear();

    void PushBack(Memory::AutoPointer<T> Pointer);
    void PushBack(Memory::AutoPointerArray<T> Pointer);

    RF_Type::Bool PopBack(Memory::AutoPointer<T> *SaveToPointer=0);
    RF_Type::Bool PopBack(Memory::AutoPointerArray<T> *SaveToPointer=0);

    void Insert(RF_Type::UInt32 AtIndex, Memory::AutoPointer<T> Pointer);
    void Insert(RF_Type::UInt32 AtIndex, Memory::AutoPointerArray<T> Pointer);

    T const* operator[](RF_Type::UInt32 Index)const;
    T* operator[](RF_Type::UInt32 Index);

    ConstIterator ConstBegin()const;
    ConstIterator ConstEnd()const;
    Iterator Begin()const;
    Iterator End()const;
    operator AutoVectorReference();
protected:
    List<PtrInfo> m_Pointer;
    typedef typename List<PtrInfo>::Iterator ListIterator;
    typedef typename List<PtrInfo>::ConstIterator ConstListIterator;
};

template <class T>
AutoVector<T>::AutoVector()
{
}

template <class T>
AutoVector<T>::~AutoVector()
{
    Clear();
}

template <class T>
AutoVector<T>::AutoVector(AutoVector &Copy)
{
    Swap(Copy);
}

template <class T>
AutoVector<T>::AutoVector(AutoVectorReference Copy)
{
    m_Pointer=Copy.m_PointerList;
}

template <class T>
AutoVector<T>& AutoVector<T>::operator=(AutoVector<T> &From)
{
    Swap(From);
    return *this;
}

template <class T>
AutoVector<T>& AutoVector<T>::operator=(AutoVectorReference From)
{
    m_Pointer=From.m_PointerList;
    return *this;
}

template <class T>
void AutoVector<T>::Swap(AutoVector<T> &Other)
{
    m_Pointer.Swap(Other.m_Pointer);
}

template<class T>
RF_Type::UInt32  AutoVector<T>::Size()const
{
    return m_Pointer.Count();
}

template<class T>
void  AutoVector<T>::Erase(RF_Type::UInt32 Index)
{
    Assert(Index < m_Pointer.Count(), "Out of bound.");
    if (m_Pointer[Index].m_IsArray)
        delete[] m_Pointer[Index].m_Ptr;
    else
        delete m_Pointer[Index].m_Ptr;
    m_Pointer.RemoveAt(Index);
}

template<class T>
void AutoVector<T>::Erase(Iterator It)
{
    m_Pointer.Remove(It);
}

template<class T>
void AutoVector<T>::Erase(ConstIterator It)
{
    m_Pointer.Remove(It);
}

template<class T>
void AutoVector<T>::Release(RF_Type::UInt32 Index, Memory::AutoPointer<T>& Ptr)
{
    Assert(Index < m_Pointer.Size(),"Out of bound.");
    if (!m_Pointer[Index].m_IsArray)
    {
        Ptr=Memory::AutoPointer<T>(m_Pointer[Index].m_Ptr);
        m_Pointer[Index].m_Ptr=0;
        m_Pointer.RemoveAt(Index);
    }
}

template<class T>
void AutoVector<T>::Release(RF_Type::UInt32 Index, Memory::AutoPointerArray<T>& Ptr)
{
    Assert(Index < m_Pointer.Size(),"Out of bound.");
    if (m_Pointer[Index].m_IsArray)
    {
        Ptr=Memory::AutoPointerArray<T>(m_Pointer[Index].m_Ptr,m_Pointer[Index].m_ElementCount);
        m_Pointer[Index].m_Ptr=0;
        m_Pointer.RemoveAt(Index);
    }
}

template <class T>
void AutoVector<T>::Clear()
{
    for (ListIterator it=m_Pointer.Begin();it!=m_Pointer.End();++it)
    {
        if ((*it).m_IsArray)
            delete[] (*it).m_Ptr;
        else
            delete (*it).m_Ptr;
    }
    m_Pointer.Clear();
}

template <class T>
void AutoVector<T>::PushBack (Memory::AutoPointer<T> Pointer)
{
    PtrInfo ptr;
    ptr.m_IsArray=false;
    ptr.m_Ptr=Pointer.Release();
    ptr.m_ElementCount=0;
    m_Pointer.AddLast(ptr);
}

template <class T>
void AutoVector<T>::PushBack (Memory::AutoPointerArray<T> Pointer)
{
    PtrInfo ptr;
    ptr.m_IsArray=true;
    Memory::AutoPointerArrayData<T> data=Pointer.Release();
    ptr.m_Ptr=data.Ptr;
    ptr.m_ElementCount=data.Count;
    m_Pointer.AddLast(ptr);
}

template <class T>
inline RF_Type::Bool AutoVector<T>::PopBack (Memory::AutoPointer<T> *SaveToPointer)
{
    if(m_Pointer.Count() == 0)
        return false;

    T* p=m_Pointer.Last()->m_Ptr;
    m_Pointer.RemoveLast();
    if (SaveToPointer)
        *SaveToPointer=Memory::AutoPointer<T>(p);

    return true;
}

template <class T>
inline RF_Type::Bool AutoVector<T>::PopBack (Memory::AutoPointerArray<T> *SaveToPointer)
{
    if(m_Pointer.Count() == 0)
        return false;

    PtrInfo p=m_Pointer.Last()->m_Ptr;
    m_Pointer.RemoveLast();
    if (SaveToPointer)
        *SaveToPointer=Memory::AutoPointerArray<T>(p.m_Ptr,p.m_ElementCount);

    return true;
}

template <class T>
void AutoVector<T>::Insert(RF_Type::UInt32 AtIndex, Memory::AutoPointer<T> Pointer)
{
    PtrInfo ptr;
    ptr.m_IsArray=false;
    ptr.m_Ptr=Pointer.Release();
    ptr.m_ElementCount=0;
    m_Pointer.Insert(AtIndex, ptr);
}

template <class T>
void AutoVector<T>::Insert(RF_Type::UInt32 AtIndex, Memory::AutoPointerArray<T> Pointer)
{
    Memory::AutoPointerArrayData<T> data=Pointer.Release();
    PtrInfo ptr;
    ptr.m_IsArray=true;
    ptr.m_Ptr=data.Ptr;
    ptr.m_ElementCount=data.Count;
    m_Pointer.Insert(AtIndex, ptr);
}

template<class T>
T const* AutoVector<T>::operator[](RF_Type::UInt32 Index)const
{
    //there is allready a out of bound check in List class
    return m_Pointer[Index].m_Ptr;
}

template<class T>
T* AutoVector<T>::operator[](RF_Type::UInt32 Index)
{
    //there is allready a out of bound check in List class
    return m_Pointer[Index].m_Ptr;
}

template<class T>
typename AutoVector<T>::ConstIterator AutoVector<T>::ConstBegin()const
{
    return m_Pointer.ConstBegin();
}

template<class T>
typename AutoVector<T>::ConstIterator AutoVector<T>::ConstEnd()const
{
    return m_Pointer.ConstEnd();
}

template<class T>
typename AutoVector<T>::Iterator AutoVector<T>::Begin()const
{
    return m_Pointer.Begin();
}

template<class T>
typename AutoVector<T>::Iterator AutoVector<T>::End()const
{
    return m_Pointer.End();
}

template<class T>
AutoVector<T>::operator AutoVectorReference()
{
    return AutoVectorReference(m_Pointer);
}

} }

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif // RF_COLLECTIONS_AUTOVECTOR_HPP
