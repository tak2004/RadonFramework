#ifndef RF_CORE_TYPES_INT64_HPP
#define RF_CORE_TYPES_INT64_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdint.h>
#include <RadonFramework/Defines.hpp>

namespace RadonFramework::Core::Types {

#ifdef RF_HAVE_LONG_LONG
    /// A Int64 have always the size of 8 byte and represent a signed number.
    using Int64 = int64_t;
#else
    /// A Int64 have always the size of 8 byte and represent a signed number.
    typedef struct {
        #ifdef IS_LITTLE_ENDIAN
            unsigned int lo,hi;
        #else
            unsigned int hi,lo;
        #endif
    }Int64;
#endif

/// The maximum value which can be contained by a Int64.
extern const Int64 Int64Max;
/// The minimum value which can be contained by a Int64.
extern const Int64 Int64Min;

}

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::Int64;
#endif

#endif // RF_CORE_TYPES_INT64_HPP
