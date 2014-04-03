#ifndef RF_CORE_TYPES_FLOAT32_HPP
#define RF_CORE_TYPES_FLOAT32_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework { namespace Core { namespace Types {

/** A Float32 have always the size of 4 byte and represent a signed
  * floating point value.
  **/
typedef float Float32;

/// The minimum value which can be contained by a Float32.
extern const Float32 Float32Min;

/// The maximum value which can be contained by a Float32.
extern const Float32 Float32Max;

} } }

#endif // RF_CORE_TYPES_FLOAT32_HPP
