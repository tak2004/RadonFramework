#ifndef RF_MATH_GEOMETRY_PROJECTIONMATRIX_HPP
#define RF_MATH_GEOMETRY_PROJECTIONMATRIX_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Geometry/Matrix.hpp>
#include <RadonFramework/Math/Geometry/Point2D.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>

namespace RadonFramework::Math::Geometry
{
namespace Viewtype
{
enum Type
{
  View2D,
  View3D
};
}

class ProjectionMatrix
{
public:
  ProjectionMatrix();
  void SetPosition(const Point2D<RF_Type::Float32>& Position);
  void SetSize(const Size2D<RF_Type::Float32>& size);
  Size2D<> GetSize() const;
  RF_Type::Float32 FieldOfView() const;
  void FieldOfView(const RF_Type::Float32 FOV);
  RF_Type::Float32 Far() const;
  void Far(const RF_Type::Float32 Far);
  RF_Type::Float32 Near() const;
  void Near(const RF_Type::Float32 Near);
  const Mat4f& GetMatrix(const Viewtype::Type Type) const;
  RF_Type::Float32 AspectRatio() const;

protected:
  Mat4f m_ProjectionMatrix;
  Mat4f m_OrthoMatrix;
  RF_Type::Float32 m_FieldOfView;
  RF_Type::Float32 m_Far;
  RF_Type::Float32 m_Near;
  RF_Type::Float32 m_AspectRatio;
  void SetDefaultProjectionMatrix();
  void SetDefaultOrthoMatrix();
  RF_Type::Float32 m_Width, m_Height;
  RF_Type::Float32 m_Left, m_Top;
};

}  // namespace RadonFramework::Math::Geometry

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif  // RF_MATH_GEOMETRY_PROJECTIONMATRIX_HPP
