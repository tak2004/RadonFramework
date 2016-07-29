#ifndef RF_MEMORY_ALLOCATOR_HPP
#define RF_MEMORY_ALLOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

template<typename T, class ARENA>
void Delete(T* Object, ARENA& Arena)
{
    Object->~T();
    Arena.Free(Object);
}

template<typename T, class ARENA>
T* NewArray(ARENA& Arena, size_t N)
{
    union
    {
        void* as_void;
        size_t* as_size_t;
        T* as_T;
    };

    as_void = Arena.Allocate(sizeof(T)*N + sizeof(size_t), __alignof(T));

    *as_size_t++ = N;

    const T* const onePastLast = as_T + N;
    while(as_T < onePastLast)
    {
        new (as_T++) T;
    }

    return (as_T - N);
}

template<typename T, class ARENA>
void DeleteArray(T* Ptr, ARENA& Arena)
{
    union
    {
        size_t* as_size_t;
        T* as_T;
    };

    as_T = Ptr;

    const size_t N = as_size_t[-1];

    for(size_t i = N; i > 0; --i)
    {
        as_T[i - 1].~T();
    }

    Arena.Free(as_size_t-1);
}

#define RF_NewHint(Type, Arena, Hint) ::new ((Arena).Allocate(sizeof(Type), __alignof(Type), Hint))Type

#define RF_NewArrayHint(Type, Arena, Elements, Hint) NewArray<Type>(Arena, Elements, Hint);

#define RF_New(Type, Arena) ::new ((Arena).Allocate(sizeof(Type), __alignof(Type)))Type

#define RF_NewArray(Type, Arena, Elements) NewArray<Type>(Arena, Elements);

#define RF_Delete(Ptr, Arena) Delete(Ptr, Arena);

#define RF_DeleteArray(Ptr, Arena) DeleteArray(Ptr, Arena);

#endif // RF_MEMORY_ALLOCATOR_HPP