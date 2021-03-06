#ifndef RF_CORE_TYPES_VEC128INT_HPP
#define RF_CORE_TYPES_VEC128INT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Int16.hpp>
#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/Int8.hpp>
#include <RadonFramework/Core/Types/Vec.hpp>

namespace RadonFramework::Core::Types
{
/// A Vec128Int8 have always the size of 16 byte and represent 16 signed
/// numbers.
using Vec128Int8 = Vec<Int8, 16>;

/// The minimum value which can be contained by a Vec128Int8.
extern const Int8 Vec128Int8Min;

/// The maximum value which can be contained by a Vec128Int8.
extern const Int8 Vec128Int8Max;

/// A Vec128Int16 have always the size of 16 byte and represent 8 signed
/// numbers.
using Vec128Int16 = Vec<Int16, 8>;

/// The minimum value which can be contained by a Vec128Int16.
extern const Int16 Vec128Int16Min;

/// The maximum value which can be contained by a Vec128Int16.
extern const Int16 Vec128Int16Max;

/// A Vec128Int32 have always the size of 16 byte and represent 4 signed
/// numbers.
using Vec128Int32 = Vec<Int32, 4>;

/// The minimum value which can be contained by a Vec128Int32.
extern const Int32 Vec128Int32Min;

/// The maximum value which can be contained by a Vec128Int32.
extern const Int32 Vec128Int32Max;

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::Vec128Int16;
using RadonFramework::Core::Types::Vec128Int32;
using RadonFramework::Core::Types::Vec128Int8;
#endif

#endif  // RF_CORE_TYPES_VEC128INT_HPP