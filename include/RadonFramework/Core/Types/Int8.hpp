#ifndef RF_CORE_TYPES_INT8_HPP
#define RF_CORE_TYPES_INT8_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework { namespace Core { namespace Types {

/// A Int8 have always the size of 1 byte and represent a signed number.
typedef signed char Int8;

/// The maximum value which can be contained by a Int8.
extern const Int8 Int8Max;

/// The minimum value which can be contained by a Int8.
extern const Int8 Int8Min;

} } }

#endif // RF_CORE_TYPES_INT8_HPP
