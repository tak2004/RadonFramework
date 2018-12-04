#ifndef RF_CORE_TYPES_SIZE_HPP
#define RF_CORE_TYPES_SIZE_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <cstddef>

namespace RadonFramework::Core::Types {

/// The size of Size can vary by compiler and system but it's always unsigned.
using Size = size_t;

/// The maximum value which can be contained by a Size.
extern const Size SizeMax;

/// The minimum value which can be contained by a Size.
extern const Size SizeMin;

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::Size;
#endif

#endif // RF_CORE_TYPES_SIZE_HPP
