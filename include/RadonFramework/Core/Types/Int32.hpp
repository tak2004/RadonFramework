#ifndef RF_CORE_TYPES_INT32_HPP
#define RF_CORE_TYPES_INT32_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <cstdint>

namespace RadonFramework::Core::Types {

/// A Int32 have always the size of 4 byte and represent a signed number.
using Int32 = int32_t;

/// The maximum value which can be contained by a Int32.
extern const Int32 Int32Max;

/// The minimum value which can be contained by a Int32.
extern const Int32 Int32Min;

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::Int32;
#endif

#endif // RF_CORE_TYPES_INT32_HPP
