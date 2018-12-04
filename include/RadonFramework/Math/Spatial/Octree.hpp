#ifndef RF_MATH_SPATIAL_OCTREE_HPP
#define RF_MATH_SPATIAL_OCTREE_HPP

#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Math/Geometry/Ray32.hpp>
#include <RadonFramework/Core/Idioms/PImpl.hpp>

namespace RadonFramework::Math::Spatial {

class Octree
{
public:
    typedef RF_Type::Float32 SpatialType;
    typedef void* IDType;

    Octree();
    void Add(const SpatialType X, const SpatialType Y,
             const SpatialType Z, const IDType ID);
    RF_Collect::Array<IDType> GetIntersectingIDs(const RF_Geo::Ray32& Ray);
private:
    RF_Idiom::PImpl<Octree> m_PImpl;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_SPATIAL
#define RF_SHORTHAND_NAMESPACE_SPATIAL
namespace RF_Spatial = RadonFramework::Math::Spatial;
#endif

#endif // !RF_MATH_SPATIAL_OCTREE_HPP