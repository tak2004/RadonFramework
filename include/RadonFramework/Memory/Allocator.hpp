#ifndef RF_MEMORY_ALLOCATOR_HPP
#define RF_MEMORY_ALLOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Policies/MallocAllocator.hpp>
#include <RadonFramework/Core/Policies/ObjectLogic.hpp>

namespace RadonFramework
{
    namespace Memory
    {
        template<class T=RFTYPE::UInt8,
                 class ALLOCATOR=RadonFramework::Core::Policies::MallocAllocator,
                 template<class> class COLLECTORLOGIC=RadonFramework::Core::Policies::ObjectLogic>
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
                template<class U,class V>
                Allocator(const Allocator<U,V,COLLECTORLOGIC>& Copy);
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

        template<class T,class ALLOCATOR, template<class> class COLLECTORLOGIC>
        Allocator<T,ALLOCATOR,COLLECTORLOGIC>::Allocator()
        {
        }

        template<class T,class ALLOCATOR, template<class> class COLLECTORLOGIC>
        Allocator<T,ALLOCATOR,COLLECTORLOGIC>::Allocator(const Allocator<T,ALLOCATOR,COLLECTORLOGIC>& Copy)
        {
        }

        template<class T,class ALLOCATOR, template<class> class COLLECTORLOGIC>
        template<class U,class V>
        Allocator<T,ALLOCATOR,COLLECTORLOGIC>::Allocator(const Allocator<U,V,COLLECTORLOGIC>& Copy)
        {
            //m_Collector=Copy.m_Collector;
        }

        template<class T,class ALLOCATOR, template<class> class COLLECTORLOGIC>
        Allocator<T,ALLOCATOR,COLLECTORLOGIC>::~Allocator()
        {
        }

        template<class T,class ALLOCATOR, template<class> class COLLECTORLOGIC>
        typename Allocator<T,ALLOCATOR,COLLECTORLOGIC>::Pointer 
            Allocator<T,ALLOCATOR,COLLECTORLOGIC>::Address(Reference Ref)const
        {
            return &Ref;
        }

        template<class T,class ALLOCATOR, template<class> class COLLECTORLOGIC>
        typename Allocator<T,ALLOCATOR,COLLECTORLOGIC>::ConstPointer 
            Allocator<T,ALLOCATOR,COLLECTORLOGIC>::Address(ConstReference Ref)const
        {
            return &Ref;
        }

        template<class T,class ALLOCATOR, template<class> class COLLECTORLOGIC>
        typename Allocator<T,ALLOCATOR,COLLECTORLOGIC>::SizeType 
            Allocator<T,ALLOCATOR,COLLECTORLOGIC>::MaxSize()const
        {
            return RFTYPE::MemoryRangeMax / 
                sizeof(ValueType);
        }

        template<class T,class ALLOCATOR, template<class> class COLLECTORLOGIC>
        typename Allocator<T,ALLOCATOR,COLLECTORLOGIC>::Pointer 
            Allocator<T,ALLOCATOR,COLLECTORLOGIC>::Allocate(SizeType ElementCount, 
                                                            void* Hint)
        {
            return ElementCount!=0?
                        static_cast<Pointer>(
                            m_Collector.Allocate(
                                ElementCount * sizeof(ValueType)
                            )
                        ) 
                       :0;
        }

        template<class T,class ALLOCATOR, template<class> class COLLECTORLOGIC>
        void Allocator<T,ALLOCATOR,COLLECTORLOGIC>::Deallocate(Pointer Ptr, 
                                                               SizeType ElementCount)
        {
             m_Collector.Deallocate(Ptr, ElementCount * sizeof(ValueType));
        }

        template<class T,class ALLOCATOR, template<class> class COLLECTORLOGIC>
        void Allocator<T,ALLOCATOR,COLLECTORLOGIC>::Construct(Pointer Ptr, 
                                                              ConstReference Value)
        {
            new(Ptr)T(Value);
        }

        template<class T,class ALLOCATOR, template<class> class COLLECTORLOGIC>
        void Allocator<T,ALLOCATOR,COLLECTORLOGIC>::Destroy(Pointer Ptr)
        {
            Ptr->~Ptr();
        }
    }
}

#endif // RF_MEMORY_ALLOCATOR_HPP