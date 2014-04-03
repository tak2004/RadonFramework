#ifndef RF_CORE_TRAITS_ALLOCATORTRAITS_HPP
#define RF_CORE_TRAITS_ALLOCATORTRAITS_HPP

#include <RadonFramework/Core/Types/MemoryRange.hpp>

namespace RadonFramework
{
    namespace Core
    {
        namespace Traits
        {
            template <class T>
            struct AllocatorTraits
            {
                typedef T ValueType;
                typedef T* Pointer;
                typedef T& Reference;
                typedef const T* ConstPointer;
                typedef const T& ConstReference;
                typedef RFTYPE::MemoryRange SizeType;
                typedef RFTYPE::MemoryRange DifferenceType;
            };

            template<>
            struct AllocatorTraits<void>
            {
                typedef void ValueType;
                typedef void* Pointer;
                typedef const void* ConstPointer;
                typedef RFTYPE::MemoryRange SizeType;
                typedef RFTYPE::MemoryRange DifferenceType;
            };
        }
    }
}

#endif // RF_CORE_TRAITS_ALLOCATORTRAITS_HPP