#ifndef RF_CORE_TYPES_VEC128FLOAT_HPP
#define RF_CORE_TYPES_VEC128FLOAT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Core { namespace Types {

/// A Vec128Float32 have always the size of 16 byte and represent 4 floating point numbers.
typedef Vec<Float32,4> Vec128Float32;

/// The minimum value which can be contained by a Vec128Float32.
extern const Float32 Vec128Float32Min;

/// The maximum value which can be contained by a Vec128Float32.
extern const Float32 Vec128Float32Max;

} } }

#endif // RF_CORE_TYPES_VEC128FLOAT_HPP