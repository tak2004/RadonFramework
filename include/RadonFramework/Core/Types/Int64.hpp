#ifndef RF_CORE_TYPES_INT64_HPP
#define RF_CORE_TYPES_INT64_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdint.h>

namespace RadonFramework::Core::Types {

/// A Int64 have always the size of 8 byte and represent a signed number.
using Int64 = int64_t;

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
