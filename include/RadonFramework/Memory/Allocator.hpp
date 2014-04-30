#ifndef RF_MEMORY_ALLOCATOR_HPP
#define RF_MEMORY_ALLOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Memory {

template<class T>
class Allocator
{
public:
    typedef T ValueType;
    typedef T* Pointer;
    typedef T& Reference;
    typedef const T* ConstPointer;
    typedef const T& ConstReference;
    typedef RFTYPE::MemoryRange SizeType;

    // constructors/destructor
    Allocator();
    Allocator(const Allocator& Copy);
    ~Allocator();

    // helper functions
    Pointer Address(Reference Ref)const;
    ConstPointer Address(ConstReference Ref)const;
    SizeType MaxSize()const;

    // methods to affect memory
    inline Pointer Allocate(SizeType ElementCount, void* Hint=0);
    inline void Deallocate(Pointer Ptr, SizeType ElementCount);
    inline void Construct(Pointer Ptr, ConstReference Value);
    inline void Destroy(Pointer Ptr);
protected:
    COLLECTORLOGIC<ALLOCATOR> m_Collector;
};

template<>
class Allocator<void>
{
    public:
        typedef void ValueType;
        typedef void* Pointer;
        typedef const void* ConstPointer;
        typedef RFTYPE::MemoryRange SizeType;
};

template<class T>
Allocator<T>::Allocator()
{
}

template<class T>
Allocator<T>::Allocator(const Allocator<T>& Copy)
{
}

template<class T>
Allocator<T>::~Allocator()
{
}

template<class T>
typename Allocator<T>::Pointer Allocator<T>::Address(Reference Ref)const
{
    return &Ref;
}

template<class T>
typename Allocator<T>::ConstPointer Allocator<T>::Address(ConstReference Ref)const
{
    return &Ref;
}

template<class T>
typename Allocator<T>::SizeType Allocator<T>::MaxSize()const
{
    return RFTYPE::MemoryRangeMax / sizeof(ValueType);
}

template<class T>
typename Allocator<T>::Pointer Allocator<T>::Allocate(SizeType ElementCount, 
                                                        void* Hint)
{
    return ElementCount !=0 ?
                static_cast<Pointer>(
                    m_Collector.Allocate(
                        ElementCount * sizeof(ValueType)
                    )
                ) : 0;
}

template<class T>
void Allocator<T>::Deallocate(Pointer Ptr, SizeType ElementCount)
{
    m_Collector.Deallocate(Ptr, ElementCount * sizeof(ValueType));
}

template<class T>
void Allocator<T>::Construct(Pointer Ptr, ConstReference Value)
{
    new(Ptr)T(Value);
}

template<class T>
void Allocator<T>::Destroy(Pointer Ptr)
{
    Ptr->~Ptr();
}

} }

#endif // RF_MEMORY_ALLOCATOR_HPP