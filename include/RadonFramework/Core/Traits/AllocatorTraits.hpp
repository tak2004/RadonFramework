#ifndef RF_CORE_TRAITS_ALLOCATORTRAITS_HPP
#define RF_CORE_TRAITS_ALLOCATORTRAITS_HPP

#include <RadonFramework/Core/Types/MemoryRange.hpp>

namespace RadonFramework { namespace Core { namespace Traits {

template <class T>
struct AllocatorTraits
{
    typedef T ValueType;
    typedef T* Pointer;
    typedef T& Reference;
    typedef const T* ConstPointer;
    typedef const T& ConstReference;
    typedef RF_Type::MemoryRange SizeType;
    typedef RF_Type::MemoryRange DifferenceType;
};

template<>
struct AllocatorTraits<void>
{
    typedef void ValueType;
    typedef void* Pointer;
    typedef const void* ConstPointer;
    typedef RF_Type::MemoryRange SizeType;
    typedef RF_Type::MemoryRange DifferenceType;
};
        
} } }

#ifndef RF_SHORTHAND_NAMESPACE_TRAIT
#define RF_SHORTHAND_NAMESPACE_TRAIT
namespace RF_Trait = RadonFramework::Core::Traits;
#endif

#endif // RF_CORE_TRAITS_ALLOCATORTRAITS_HPP