#ifndef RF_CORE_TYPES_UINT8_HPP
#define RF_CORE_TYPES_UINT8_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework::Core::Types {

/// A UInt8 have always the size of 1 byte and represent a unsigned number.
typedef uint8_t UInt8;

/// The minimum value which can be contained by a UInt8.
extern const UInt8 UInt8Min;

/// The maximum value which can be contained by a UInt8.
extern const UInt8 UInt8Max;

}

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#endif // RF_CORE_TYPES_UINT8_HPP
