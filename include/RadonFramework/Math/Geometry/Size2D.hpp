#ifndef RF_MATH_GEOMETRY_SIZE2D_HPP
#define RF_MATH_GEOMETRY_SIZE2D_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/Float32.hpp>
#include <RadonFramework/Core/Types/Float64.hpp>
#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>

namespace RadonFramework::Math::Geometry
{
enum class Fitting
{
  No,
  PerfectFit,
  PerfectFitIfFlip,
  Fit,
  FitIfFlip
};

template <class T = RF_Type::UInt32, class FLOAT = RF_Type::Float32>
class Size2D
{
public:
  Size2D();
  Size2D(T Width, T Height);
  template <class NT, class NFLOAT>
  Size2D(const Size2D<NT, NFLOAT>& Convert);
  T Width;
  T Height;

  RF_Type::Bool Equals(const Size2D<T, FLOAT>& Other) const;
  RF_Type::Bool FitsInto(const Size2D<T, FLOAT>& Other) const;
  Fitting CanFitInto(const Size2D<T, FLOAT>& Other) const;
  FLOAT Ratio() const;
  FLOAT GetArea() const;
  void Flip();

  static Size2D<T, FLOAT>
  Min(const Size2D<T, FLOAT>& A, const Size2D<T, FLOAT>& B);
  static Size2D<T, FLOAT>
  Max(const Size2D<T, FLOAT>& A, const Size2D<T, FLOAT>& B);

  RF_Type::Bool operator==(const Size2D<T, FLOAT>& Other) const;
};

template <class T = RF_Type::UInt32, class FLOAT = RF_Type::Float32>
Size2D<T, FLOAT> operator+(const Size2D<T, FLOAT>& A, const Size2D<T, FLOAT>& B)
{
  Size2D<> result(A);
  result.Width += B.Width;
  result.Height += B.Height;
  return result;
}

template <class T, class FLOAT>
template <class NT, class NFLOAT>
Size2D<T, FLOAT>::Size2D(const Size2D<NT, NFLOAT>& Convert)
: Width((T)Convert.Width), Height((T)Convert.Height)
{
}

using Size2Di = Size2D<RF_Type::Int32>;
using Size2Du = Size2D<RF_Type::UInt32>;
using Size2Df = Size2D<RF_Type::Float32>;
using Size2Dd = Size2D<RF_Type::Float64, RF_Type::Float64>;

}  // namespace RadonFramework::Math::Geometry

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif  // RF_MATH_GEOMETRY_SIZE2D_HPP
