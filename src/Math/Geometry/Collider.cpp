#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Geometry/Collider.hpp"

namespace RadonFramework::Math::Geometry {

Collider::IntersectionResult Collider::RaySphereIntersection(const Ray32& ARay, 
    const Sphere32& ASphere)
{
    IntersectionResult result;
    result.First = true;

    Vec3f l = ASphere.GetPosition() - ARay.GetOrigin();
    Vec3f d(ARay.GetDirection().GetArray());
    auto tca = l.DotProduct(d);
    auto d2 = l.DotProduct(l) - tca * tca;
    if(d2 <= ASphere.GetRadius())
    {
        auto thc = RF_Math::Float32::Sqrt(ASphere.GetRadius()-d2);
        auto t0 = tca - thc;
        auto t1 = tca + thc;
        if(t0 > t1)
        {
            auto t = t0;
            t0 = t1;
            t1 = t;
        }
        if(t0 < 0)
        {
            t0 = t1;
            if(t0 < 0)
            {
                result.First = false;
            }
        }
        if(result.First)
        {
            result.Second = ARay.GetPoint(t0);
        }
    }
    else
    {
        result.First = false;
    }

    return result;
}

RF_Type::Bool Collider::RaySphereIntersectionBulk(const RF_Collect::Array<Ray32>& Rays, 
    const RF_Collect::Array<Sphere32> &Spheres, RF_Collect::Array<IntersectionResult>& Out)
{
    RF_Type::Bool result = false;
    if(Rays.Count() * Spheres.Count() > 0)
    {
        Out.Resize(Rays.Count() * Spheres.Count());
        for (auto i = 0; i < Rays.Count(); ++i)
        {
            for (auto j = 0; j < Spheres.Count(); ++j)
            {
                Out(i * Spheres.Count() + j) = RaySphereIntersection(Rays(i), Spheres(j));
            }
        }
    }
    return result;
}

}