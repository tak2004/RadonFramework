#ifndef RF_CORE_TYPES_UINT16_HPP
#define RF_CORE_TYPES_UINT16_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <cstdint>

namespace RadonFramework::Core::Types {

/// A UInt16 have always the size of 2 byte and represent a unsigned number.
using UInt16 = uint16_t;

/// The minimum value which can be contained by a UInt16.
extern const UInt16 UInt16Min;

/// The maximum value which can be contained by a UInt16.
extern const UInt16 UInt16Max;

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::UInt16;
#endif

#endif // RF_CORE_TYPES_UINT16_HPP
