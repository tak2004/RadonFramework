#ifndef RF_CORE_TYPES_FLOAT32_HPP
#define RF_CORE_TYPES_FLOAT32_HPP
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER > 1000

namespace RadonFramework::Core::Types
{
/** A Float32 have always the size of 4 byte and represent a signed
 * floating point value.
 **/
using Float32 = float;

/// The minimum value which can be contained by a Float32.
extern const Float32 Float32Min;

/// The maximum value which can be contained by a Float32.
extern const Float32 Float32Max;

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::Float32;
#endif

#endif  // RF_CORE_TYPES_FLOAT32_HPP
