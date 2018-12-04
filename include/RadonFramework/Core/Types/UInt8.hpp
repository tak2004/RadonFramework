#ifndef RF_CORE_TYPES_UINT8_HPP
#define RF_CORE_TYPES_UINT8_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <cstdint>

namespace RadonFramework::Core::Types {

/// A UInt8 have always the size of 1 byte and represent a unsigned number.
using UInt8 = uint8_t;

/// The minimum value which can be contained by a UInt8.
extern const UInt8 UInt8Min;

/// The maximum value which can be contained by a UInt8.
extern const UInt8 UInt8Max;

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::UInt8;
#endif

#endif // RF_CORE_TYPES_UINT8_HPP
