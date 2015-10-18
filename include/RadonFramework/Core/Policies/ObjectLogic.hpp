#ifndef RF_CORE_POLICIES_OBJECTLOGIC_HPP
#define RF_CORE_POLICIES_OBJECTLOGIC_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Core
    {
        namespace Policies
        {
            template <class T>
            class ObjectLogic
            {
                public:
                    virtual ~ObjectLogic();
                protected:
                    typename T::Traits::Pointer Allocate(typename T::Traits::SizeType ElementCount, 
                                                void* Hint=0);

                    void Deallocate(typename T::Traits::Pointer Ptr, 
                                    typename T::Traits::SizeType ElementCount);

                    void Construct(typename T::Traits::Pointer Ptr, 
                                   typename T::Traits::ConstReference Value);

                    void Destroy(typename T::Traits::Pointer Ptr);
            };

            template<class T>
            ObjectLogic<T>::~ObjectLogic()
            {
            }

            template<class T>
            typename T::Traits::Pointer ObjectLogic<T>::Allocate(
                typename T::Traits::SizeType ElementCount, 
                void* Hint)
            {
                return ElementCount != 0 ? static_cast<typename T::Traits::Pointer>(T::MemoryAllocator::Allocate(ElementCount * sizeof(T::Traits::ValueType))) 
                        : 0;
            }

            template<class T>
            void ObjectLogic<T>::Deallocate(typename T::Traits::Pointer Ptr, 
                                            typename T::Traits::SizeType ElementCount)
            {
                 T::MemoryAllocator::Deallocate(Ptr, ElementCount * sizeof(typename T::Traits::ValueType));
            }

            template<class T>
            void ObjectLogic<T>::Construct(typename T::Traits::Pointer Ptr, 
                                           typename T::Traits::ConstReference Value)
            {
                new(Ptr)T(Value);
            }

            template<class T>
            void ObjectLogic<T>::Destroy(typename T::Traits::Pointer Ptr)
            {
                Ptr->~Ptr();
            }
        }
    }
}

#endif // RF_CORE_POLICIES_OBJECTLOGIC_HPP
