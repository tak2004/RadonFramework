#ifndef RF_CORE_TYPES_MEMORYRANGE_HPP
#define RF_CORE_TYPES_MEMORYRANGE_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stddef.h>

namespace RadonFramework::Core::Types {

/** MemoryRange can have different size, it's depend on the size of a pointer.
  * It should be used instead of pointer to be sure that you use the right
  * pointer arithmetic.
  **/
typedef ptrdiff_t MemoryRange;

/// The maximum value which can be contained by MemoryRange.
extern const MemoryRange MemoryRangeMin;

/// The minimum value which can be contained by MemoryRange.
extern const MemoryRange MemoryRangeMax;

}

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::MemoryRange;
#endif

#endif // RF_CORE_TYPES_MEMORYRANGE_HPP
