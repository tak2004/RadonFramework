#ifndef RF_MATH_GEOMETRY_SPHERE32_HPP
#define RF_MATH_GEOMETRY_SPHERE32_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Geometry/Vector.hpp>

namespace RadonFramework::Math::Geometry
{
class Sphere32
{
public:
  Sphere32();
  Sphere32(const Vec3f& Position, const RF_Type::Float32 Radius);

  const Vec3f& GetPosition() const;
  RF_Type::Float32 GetRadius() const;

  Sphere32& operator=(const Sphere32& AssignThis);
  RF_Type::Bool operator==(const Sphere32& CompareWith);

protected:
  Vec3f m_Position;
  RF_Type::Float32 m_Radius;
};

}  // namespace RadonFramework::Math::Geometry

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif  // RF_MATH_GEOMETRY_SPHERE32_HPP
