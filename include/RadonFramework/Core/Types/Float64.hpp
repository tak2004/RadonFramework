#ifndef RF_CORE_TYPES_FLOAT64_HPP
#define RF_CORE_TYPES_FLOAT64_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Core { namespace Types {

/** A Float64 have always the size of 8 byte and represent a signed
  * floating point value.
  **/
typedef double Float64;
            
/// The maximum value which can be contained by a Float64.
extern const Float64 Float64Max;

/// The minimum value which can be contained by a Float64.
extern const Float64 Float64Min;

} } }

#endif // RF_CORE_TYPES_FLOAT64_HPP