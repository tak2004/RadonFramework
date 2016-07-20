#ifndef RF_CORE_TYPES_VEC64INT_HPP
#define RF_CORE_TYPES_VEC64INT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Core { namespace Types {

/// A Vec64Int8 have always the size of 8 byte and represent 8 signed numbers.
typedef Vec<Int8,8> Vec64Int8;

/// The minimum value which can be contained by a Vec64Int8.
extern const Int8 Vec64Int8Min;

/// The maximum value which can be contained by a Vec64Int8.
extern const Int8 Vec64Int8Max;

/// A Vec64Int16 have always the size of 8 byte and represent 4 signed numbers.
typedef Vec<Int16,4> Vec64Int16;

/// The minimum value which can be contained by a Vec64Int16.
extern const Int16 Vec64Int16Min;

/// The maximum value which can be contained by a Vec64Int16.
extern const Int16 Vec64Int16Max;

/// A Vec64Int32 have always the size of 8 byte and represent 2 signed numbers.
typedef Vec<Int32,2> Vec64Int32;

/// The minimum value which can be contained by a Vec64Int32.
extern const Int32 Vec64Int32Min;

/// The maximum value which can be contained by a Vec64Int32.
extern const Int32 Vec64Int32Max;

} } }

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#endif // RF_CORE_TYPES_VEC64INT_HPP