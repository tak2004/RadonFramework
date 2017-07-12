#ifndef RF_MATH_GEOMETRY_RAY32_HPP
#define RF_MATH_GEOMETRY_RAY32_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Pair.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Math/Geometry/Vector.hpp>
#include <RadonFramework/Math/Geometry/Normal.hpp>

namespace RadonFramework::Math::Geometry {

template<typename T>
class Sphere;

class Ray32
{
public:
    typedef RF_Collect::Pair<RF_Type::Bool, RF_Type::Float32> IntersectionResult;

    Ray32();
    Ray32(const Vec3f& Origin, const Norm3f& Direction);
    Ray32(const Ray32& CopyFrom);

    RF_Type::Bool Equals(const Ray32 &Other)const;

    Vec3f GetPoint(RF_Type::Float32 Delta)const;
    const Vec3f& GetOrigin()const;
    const Norm3f& GetDirection()const;

    Ray32& operator = (const Ray32& AssignThis);
protected:
    Vec3f m_Origin;
    Norm3f m_Direction;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif // RF_MATH_GEOMETRY_RAY32_HPP
