#ifndef RF_CORE_TYPES_VEC64UINT_HPP
#define RF_CORE_TYPES_VEC64UINT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Core::Types {

/// A Vec128UInt8 have always the size of 8 byte and represent 8 unsigned numbers.
typedef Vec<UInt8,8> Vec64UInt8;

/// The minimum value which can be contained by a Vec64UInt8.
extern const UInt8 Vec64UInt8Min;

/// The maximum value which can be contained by a Vec128UInt16.
extern const UInt8 Vec64UInt8Max;

/// A Vec64UInt16 have always the size of 8 byte and represent 4 unsigned numbers.
typedef Vec<UInt16,4> Vec64UInt16;

/// The minimum value which can be contained by a Vec64UInt16.
extern const UInt16 Vec64UInt16Min;

/// The maximum value which can be contained by a Vec64UInt16.
extern const UInt16 Vec64UInt16Max;

/// A Vec64UInt32 have always the size of 8 byte and represent 2 unsigned numbers.
typedef Vec<UInt32,2> Vec64UInt32;

/// The minimum value which can be contained by a Vec64UInt32.
extern const UInt32 Vec64UInt32Min;

/// The maximum value which can be contained by a Vec64UInt32.
extern const UInt32 Vec64UInt32Max;

}

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#endif // RF_CORE_TYPES_VEC64UINT_HPP