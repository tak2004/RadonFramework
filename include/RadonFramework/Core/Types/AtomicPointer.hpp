#ifndef RF_CORE_TYPES_ATOMICPOINTER_HPP
#define RF_CORE_TYPES_ATOMICPOINTER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/System/Threading/Interlocked.hpp>

namespace RadonFramework::Core::Types {

template<typename T>
struct AtomicPointer
{
public:
    AtomicPointer(T* Value=0);
    AtomicPointer(const AtomicPointer<T>& Other);

    T* FetchAndExchange(T* Ptr);
    T* CompareAndExchange(T* Compare, T* Value);

    operator T*()const;
    Bool operator !()const;
    Bool operator !=(T* Value)const;
    T* operator ->()const;
    AtomicPointer<T>& operator=(T* Value);
    AtomicPointer<T>& operator=(const AtomicPointer<T>& Other);
    Bool operator==(T* Value)const;
protected:
    T* m_Data;
};

template<typename T>
AtomicPointer<T>::AtomicPointer(T* Value)
:m_Data(Value)
{                
}

template<typename T>
AtomicPointer<T>::AtomicPointer(const AtomicPointer<T>& Other)
:m_Data(Other.m_Data)
{
}

template<typename T>
T* AtomicPointer<T>::FetchAndExchange(T* Ptr)
{
    return reinterpret_cast<T*>(System::Threading::Interlocked::InterlockedExchangePointer(
        reinterpret_cast<void* volatile*>(&this->m_Data), Ptr));
}

template<typename T>
T* AtomicPointer<T>::CompareAndExchange(T* Compare, T* Value)
{
    return reinterpret_cast<T*>(System::Threading::Interlocked::InterlockedCompareExchangePointer(
        reinterpret_cast<void* volatile*>(&this->m_Data),Value,Compare));
}

template<typename T>
AtomicPointer<T>::operator T*()const
{
    return m_Data;
}

template<typename T>
Bool AtomicPointer<T>::operator !()const
{
    return m_Data==0?true:false;
}

template<typename T>
Bool AtomicPointer<T>::operator !=(T* Value)const
{
    return m_Data!=Value?true:false;
}

template<typename T>
T* AtomicPointer<T>::operator ->()const
{
    return m_Data;
}

template<typename T>
AtomicPointer<T>& AtomicPointer<T>::operator =(T* Value)
{
    m_Data=Value;
    return *this;
}

template<typename T>
AtomicPointer<T>& AtomicPointer<T>::operator =(const AtomicPointer<T>& Other)
{
    m_Data=Other.m_Data;
    return *this;
}

template<typename T>
Bool AtomicPointer<T>::operator ==(T* Value)const
{
    return m_Data==Value;
}

}

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#endif // RF_CORE_TYPES_ATOMICPOINTER_HPP