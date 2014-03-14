#ifndef RF_CORE_TYPES_MEMORYRANGE_HPP
#define RF_CORE_TYPES_MEMORYRANGE_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stddef.h>

namespace RadonFramework
{
    namespace Core
    {
        namespace Types
        {
            /** MemoryRange can have different size, it's depend on the size of a pointer.
              * It should be used instead of pointer to be sure that you use the right
              * pointer arithmetic.
              */
            typedef ptrdiff_t MemoryRange;

            /// The maximum value which can be contained by MemoryRange.
            extern const MemoryRange MemoryRangeMin;

            /// The minimum value which can be contained by MemoryRange.
            extern const MemoryRange MemoryRangeMax;
        }
    }
}

#endif // RF_CORE_TYPES_MEMORYRANGE_HPP
