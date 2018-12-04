#ifndef RF_CORE_TRAITS_ALLOCATORTRAITS_HPP
#define RF_CORE_TRAITS_ALLOCATORTRAITS_HPP

#include <RadonFramework/Core/Types/MemoryRange.hpp>

namespace RadonFramework::Core::Traits {

template <class T>
struct AllocatorTraits
{
    using ValueType = T;
    using Pointer = T *;
    using Reference = T &;
    using ConstPointer = const T *;
    using ConstReference = const T &;
    using SizeType = RF_Type::MemoryRange;
    using DifferenceType = RF_Type::MemoryRange;
};

template<>
struct AllocatorTraits<void>
{
    using ValueType = void;
    using Pointer = void *;
    using ConstPointer = const void *;
    using SizeType = RF_Type::MemoryRange;
    using DifferenceType = RF_Type::MemoryRange;
};
        
}  // namespace RadonFramework::Core::Traits

#ifndef RF_SHORTHAND_NAMESPACE_TRAIT
#define RF_SHORTHAND_NAMESPACE_TRAIT
namespace RF_Trait = RadonFramework::Core::Traits;
#endif

#endif // RF_CORE_TRAITS_ALLOCATORTRAITS_HPP