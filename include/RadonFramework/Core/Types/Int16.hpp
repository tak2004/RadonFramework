#ifndef RF_CORE_TYPES_INT16_HPP
#define RF_CORE_TYPES_INT16_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <cstdint>

namespace RadonFramework::Core::Types {

/// A Int16 have always the size of 2 byte and represent a signed number.
using Int16 = int16_t;

/// The maximum value which can be contained by a Int16.
extern const Int16 Int16Max;

/// The minimum value which can be contained by a Int16.
extern const Int16 Int16Min;

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::Int16;
#endif

#endif // RF_CORE_TYPES_INT16_HPP
