#ifndef RF_CORE_TYPES_UINT32_HPP
#define RF_CORE_TYPES_UINT32_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework { namespace Core { namespace Types {

/// A UInt32 have always the size of 4 byte and represent a unsigned number.
typedef uint32_t UInt32;

/// The minimum value which can be contained by a UInt32.
extern const UInt32 UInt32Min;

/// The maximum value which can be contained by a UInt32.
extern const UInt32 UInt32Max;

} } }

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#endif // RF_CORE_TYPES_UINT32_HPP
