#ifndef RF_CORE_TYPES_FLOAT64_HPP
#define RF_CORE_TYPES_FLOAT64_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Core::Types {

/** A Float64 have always the size of 8 byte and represent a signed
  * floating point value.
  **/
using Float64 = double;
            
/// The maximum value which can be contained by a Float64.
extern const Float64 Float64Max;

/// The minimum value which can be contained by a Float64.
extern const Float64 Float64Min;

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::Float64;
#endif

#endif // RF_CORE_TYPES_FLOAT64_HPP
