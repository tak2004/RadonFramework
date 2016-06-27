#ifndef RF_MATH_MATHOFTYPE_HPP
#define RF_MATH_MATHOFTYPE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Float32.hpp>
#include <RadonFramework/Math/Float64.hpp>

namespace RadonFramework { namespace Math {

template<class T>
struct MathOfType
{};

template<>
struct MathOfType<RF_Type::Float32>: public Float32
{
};

template<>
struct MathOfType<RF_Type::Float64>: public Float64
{};

} }

#ifndef RF_SHORTHAND_NAMESPACE_MATH
#define RF_SHORTHAND_NAMESPACE_MATH
namespace RF_Math = RadonFramework::Math;
#endif

#endif // RF_MATH_MATHOFTYPE_HPP
