#ifndef RF_CORE_TYPES_VEC128FLOAT_HPP
#define RF_CORE_TYPES_VEC128FLOAT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Float32.hpp>
#include <RadonFramework/Core/Types/Vec.hpp>

namespace RadonFramework::Core::Types
{
/// A Vec128Float32 have always the size of 16 byte and represent 4 floating
/// point numbers.
using Vec128Float32 = Vec<Float32, 4>;

/// The minimum value which can be contained by a Vec128Float32.
extern const Float32 Vec128Float32Min;

/// The maximum value which can be contained by a Vec128Float32.
extern const Float32 Vec128Float32Max;

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::Vec128Float32;
#endif

#endif  // RF_CORE_TYPES_VEC128FLOAT_HPP