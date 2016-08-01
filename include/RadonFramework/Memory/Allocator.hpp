#ifndef RF_MEMORY_ALLOCATOR_HPP
#define RF_MEMORY_ALLOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <new>

namespace RadonFramework { namespace Memory {

template<typename T, class ARENA>
void Delete(T* Object, ARENA& Arena)
{
    Object->~T();
    Arena.Free(Object);
}

template<typename T, class ARENA>
T* NewArray(ARENA& Arena, RF_Type::Size N)
{
    union
    {
        void* as_void;
        RF_Type::Size* as_size_t;
        T* as_T;
    };

    as_void = Arena.Allocate(sizeof(T)*N + sizeof(RF_Type::Size));

    *as_size_t++ = N;

    const T* const onePastLast = as_T + N;
    while(as_T < onePastLast)
    {
        new (as_T++) T;
    }

    return (as_T - N);
}

template<typename T, class ARENA>
T* NewArrayBestFit(ARENA& Arena, RF_Type::Size& N)
{
    // Allocate the wanted size.
    void* ptr = Arena.Allocate(sizeof(T)*N);
    // Reposition to the next fitting position of the type.
    RF_Type::MemoryRange alignedPos = ((static_cast<RF_Type::MemoryRange>(ptr) - 1) & ~(alignof(T)-1)) + alignof(T);
    RF_Type::Size alignmentLost = alignedPos - static_cast<RF_Type::MemoryRange>(ptr);
    // Calculate the amount of T fitting in the left allocated space.
    N = (Arena.AllocationSize(ptr) - alignmentLost) / sizeof(T);
    return static_cast<void*>(alignedPos);
}

template<typename T, class ARENA>
void DeleteArray(T* Ptr, ARENA& Arena)
{
    union
    {
        RF_Type::Size* as_size_t;
        T* as_T;
    };

    as_T = Ptr;

    const RF_Type::Size N = as_size_t[-1];

    for(RF_Type::Size i = N; i > 0; --i)
    {
        as_T[i - 1].~T();
    }

    Arena.Free(as_size_t-1);
}

inline void* AlignPointer(void* Pointer, RF_Type::Size Alignment)
{
    return reinterpret_cast<void*>(((reinterpret_cast<RF_Type::MemoryRange>(Pointer) - 1) & ~(Alignment - 1)) + Alignment);
}

} }

#define RF_NewHint(Type, Arena, Hint) ::new ((Arena).Allocate(sizeof(Type), __alignof(Type), Hint))Type
#define RF_New(Type, Arena) ::new ((Arena).Allocate(sizeof(Type), __alignof(Type)))Type
#define RF_Delete(Ptr, Arena) RF_Mem::Delete(Ptr, Arena);

#define RF_NewArrayHint(Type, Arena, Elements, Hint) RF_Mem::NewArray<Type>(Arena, Elements, Hint);
#define RF_NewArray(Type, Arena, Elements) RF_Mem::NewArray<Type>(Arena, Elements);
#define RF_NewArrayBestFit(Type, Arena, Elements) RF_Mem::NewArrayBestFit<Type>(Arena, Elements);
#define RF_DeleteArray(Ptr, Arena) RF_Mem::DeleteArray(Ptr, Arena);

#endif // RF_MEMORY_ALLOCATOR_HPP