#ifndef RF_MEMORY_CORELOCAL_HPP
#define RF_MEMORY_CORELOCAL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework {
namespace Memory {

template <typename T>
class CoreLocal
{
public:
    static RF_Type::MemoryRange Generate();

    CoreLocal(RF_Type::MemoryRange Id);

    /// Return the const reference of the instance.
    const T& operator*()const;
    /// Return the reference of the instance.
    T& operator*();
    /// Access a const marked member of the instance.
    const T* operator->()const;
    /// Access a member of the instance.
    T* operator->();
    /// Return true if the Id is invalid else false.
    RF_Type::Bool operator!()const;
private:
    RF_Type::MemoryRange m_Id;
};

template <typename T>
CoreLocal<T>::CoreLocal(RF_Type::MemoryRange Id)
:m_Id(Id)
{

}

template <typename T>
RF_Type::MemoryRange CoreLocal<T>::Generate()
{
    auto count = RF_SysHardware::GetAvailableLogicalProcessorCount();
    T* result = new T[count];
    return reinterpret_cast<RF_Type::MemoryRange>(result);
}

template <typename T>
T& CoreLocal<T>::operator*()
{
    RF_Type::UInt32 core = RF_SysHardware::GetCurrentUniqueProcessorNumber();
    return reinterpret_cast<T*>(m_Id)[core];
}

template <typename T>
const T& CoreLocal<T>::operator*() const
{
    RF_Type::UInt32 core = RF_SysHardware::GetCurrentUniqueProcessorNumber();
    return reinterpret_cast<T*>(m_Id)[core];
}


template <typename T>
T* CoreLocal<T>::operator->()
{
    return &reinterpret_cast<T*>(m_Id)[core];
}

template <typename T>
const T* CoreLocal<T>::operator->() const
{
    return &reinterpret_cast<T*>(m_Id)[core];
}

template <typename T>
RF_Type::Bool CoreLocal<T>::operator!()const
{
    return nullptr == m_Id;
}

} }

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif // RF_MEMORY_CORELOCAL_HPP