#ifndef RF_CORE_TYPES_UINT32_HPP
#define RF_CORE_TYPES_UINT32_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <cstdint>

namespace RadonFramework::Core::Types {

/// A UInt32 have always the size of 4 byte and represent a unsigned number.
using UInt32 = uint32_t;

/// The minimum value which can be contained by a UInt32.
extern const UInt32 UInt32Min;

/// The maximum value which can be contained by a UInt32.
extern const UInt32 UInt32Max;

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::UInt32;
#endif

#endif // RF_CORE_TYPES_UINT32_HPP
