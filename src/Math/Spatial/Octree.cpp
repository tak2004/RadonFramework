#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Spatial/Octree.hpp"
#include "RadonFramework/Collections/Pair.hpp"
#include "RadonFramework/Collections/HashList.hpp"
#include "morton.h"

namespace RadonFramework::Math::Spatial {

// Perfect hash
class OctreeDataV1
{
public:
    typedef RF_Collect::Pair<RF_Type::UInt8, RF_Type::UInt8> OffsetEntry;
    RF_Collect::Array<RF_Type::UInt64> m_Hashtable;
    RF_Collect::Array<OffsetEntry> m_Offsets;

    void Add(const Octree::SpatialType X, const Octree::SpatialType Y, 
        const Octree::SpatialType Z, const Octree::IDType ID)
    {

    }

    RF_Collect::Array<Octree::IDType> GetIntersectingIDs(const RF_Geo::Ray32& Ray)
    {
        RF_Collect::Array<Octree::IDType> result;
        return result;
    }
};

// Morton key
class OctreeDataV2
{
public:
    RF_Collect::HashList m_Entries;

    OctreeDataV2()
    :m_Entries(500)
    {
    }

    void Add(const Octree::SpatialType X, const Octree::SpatialType Y, 
        const Octree::SpatialType Z, const Octree::IDType ID)
    {
        auto key = morton3D_32_encode(X,Y,Z);
        m_Entries.Add(key, ID);
    }

    RF_Collect::Array<Octree::IDType> GetIntersectingIDs(const RF_Geo::Ray32& Ray)
    {
        RF_Collect::Array<Octree::IDType> result;
        uint_fast16_t x,y,z;
        morton3D_32_decode(8,x,y,z);
        TopDownIntersection(0, Ray);
        return result;
    }

private:
    void TopDownIntersection(const uint_fast32_t Node, const RF_Geo::Ray32& Ray)
    {
        for(auto i = 0; i < 8; ++i)
        {
            // get bounding box of child
            // aabb <-> ray intersection
            //if()
//             {
//                 TopDownIntersection(child,Ray);
//             }
        }
    }
};

}

template<>
class ::RadonFramework::Core::Idioms::PImpl<RF_Spatial::Octree>::Data
{
public:
    RF_Spatial::OctreeDataV2 m_NodeData;
};

namespace RadonFramework::Math::Spatial {

Octree::Octree()
{
}

void Octree::Add(const SpatialType X, const SpatialType Y, const SpatialType Z, const IDType ID)
{
    m_PImpl->m_NodeData.Add(X,Y,Z,ID);
}

RF_Collect::Array<Octree::IDType> Octree::GetIntersectingIDs(const RF_Geo::Ray32& Ray)
{
    return m_PImpl->m_NodeData.GetIntersectingIDs(Ray);
}

}