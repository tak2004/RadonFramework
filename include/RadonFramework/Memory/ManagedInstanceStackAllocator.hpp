#ifndef RF_MANAGEDINSTANCEALLOCATOR_HPP
#define RF_MANAGEDINSTANCEALLOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/StackAllocator.hpp>

namespace RadonFramework { namespace Memory {

class ManagedInstanceStackAllocator
{
public:
    ManagedInstanceStackAllocator(RF_Type::Size ReservedMemorySize);
    void Clear();

    template<class T>
    T* PushClass();
                
    void* PushRaw(RF_Type::Size MemorySize);
    void Pop();
    void* Peek();
protected:
    using DestructorCallback = void(*)(void*);

    template<class T>
    static void CallDestructor(void* Object);

    void SetDestructorCallback(void* Buffer, RF_Type::Size MemorySize, DestructorCallback Destructor);
    StackAllocator m_Allocator;
};

template<class T>
T* ManagedInstanceStackAllocator::PushClass()
{
    void* buffer=PushRaw(sizeof(T)+sizeof(DestructorCallback));
    T* object=new (reinterpret_cast<T*>(buffer)) T();
    SetDestructorCallback(buffer, sizeof(T), CallDestructor<T>);
    return object;
}

template<class T>
void ManagedInstanceStackAllocator::CallDestructor(void* Object)
{
    T* p = reinterpret_cast<T*>(Object);
    p->T::~T();
}

} }

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif // RF_MANAGEDINSTANCEALLOCATOR_HPP