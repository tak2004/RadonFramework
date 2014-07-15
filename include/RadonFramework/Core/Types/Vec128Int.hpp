#ifndef RF_CORE_TYPES_VEC128INT_HPP
#define RF_CORE_TYPES_VEC128INT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Int8.hpp>
#include <RadonFramework/Core/Types/Int16.hpp>
#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/Vec.hpp>

namespace RadonFramework { namespace Core { namespace Types {

/// A Vec128Int8 have always the size of 16 byte and represent 16 signed numbers.
typedef Vec<Int8,16> Vec128Int8;

/// The minimum value which can be contained by a Vec128Int8.
extern const Int8 Vec128Int8Min;

/// The maximum value which can be contained by a Vec128Int8.
extern const Int8 Vec128Int8Max;

/// A Vec128Int16 have always the size of 16 byte and represent 8 signed numbers.
typedef Vec<Int16,8> Vec128Int16;

/// The minimum value which can be contained by a Vec128Int16.
extern const Int16 Vec128Int16Min;

/// The maximum value which can be contained by a Vec128Int16.
extern const Int16 Vec128Int16Max;

/// A Vec128Int32 have always the size of 16 byte and represent 4 signed numbers.
typedef Vec<Int32,4> Vec128Int32;

/// The minimum value which can be contained by a Vec128Int32.
extern const Int32 Vec128Int32Min;

/// The maximum value which can be contained by a Vec128Int32.
extern const Int32 Vec128Int32Max;

} } }

#endif // RF_CORE_TYPES_VEC128INT_HPP