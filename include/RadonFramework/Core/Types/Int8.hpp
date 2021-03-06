#ifndef RF_CORE_TYPES_INT8_HPP
#define RF_CORE_TYPES_INT8_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <cstdint>

namespace RadonFramework::Core::Types {

/// A Int8 have always the size of 1 byte and represent a signed number.
using Int8 = int8_t;

/// The maximum value which can be contained by a Int8.
extern const Int8 Int8Max;

/// The minimum value which can be contained by a Int8.
extern const Int8 Int8Min;

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::Int8;
#endif

#endif // RF_CORE_TYPES_INT8_HPP
