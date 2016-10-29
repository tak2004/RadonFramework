#ifndef RF_MATH_GEOMETRY_COLLIDER_HPP
#define RF_MATH_GEOMETRY_COLLIDER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Collections/Pair.hpp>
#include <RadonFramework/Math/Geometry/Ray32.hpp>
#include <RadonFramework/Math/Geometry/Sphere32.hpp>

namespace RadonFramework { namespace Math { namespace Geometry {

class Collider
{
public:
    typedef RF_Collect::Pair<RF_Type::Bool, Vec3f> IntersectionResult;
    
    static IntersectionResult RaySphereIntersection(const Ray32& ARay, const Sphere32& ASphere);
    static RF_Type::Bool RaySphereIntersectionBulk(
        const RF_Collect::Array<Ray32>& ARay, const RF_Collect::Array<Sphere32> &ASphere,
        RF_Collect::Array<IntersectionResult>& Out);
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif // RF_MATH_GEOMETRY_COLLIDER_HPP
