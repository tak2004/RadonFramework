#ifndef RF_CORE_TYPES_SIZE_HPP
#define RF_CORE_TYPES_SIZE_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdlib.h>

namespace RadonFramework::Core::Types {

/// The size of Size can vary by compiler and system but it's always unsigned.
typedef size_t Size;

/// The maximum value which can be contained by a Size.
extern const Size SizeMax;

/// The minimum value which can be contained by a Size.
extern const Size SizeMin;

}

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#endif // RF_CORE_TYPES_SIZE_HPP
