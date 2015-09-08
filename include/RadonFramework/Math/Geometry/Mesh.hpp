#ifndef RF_MATH_GEOMETRY_MESH_HPP
#define RF_MATH_GEOMETRY_MESH_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <vector>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/Float32.hpp>

namespace RadonFramework { namespace Math { namespace Geometry {

namespace FaceGeometry
{
    enum Type
    {
        Triangle = 0,
        Line,
        Point,

        MAX
    };
}

class VertexData
{
public:
    VertexData();
    VertexData(const RF_Type::String& BufferName,
                const RF_Type::Float32* BufferData,
                const RF_Type::UInt32 ElementCount,
                const RF_Type::UInt32 ElementSize);
    VertexData(const VertexData& Copy);
    ~VertexData();
    VertexData& operator =(const VertexData& Other);

    RF_Type::String Name;
    const RF_Type::Float32* Data;
    RF_Type::UInt32 Count;
    RF_Type::UInt32 Size;
};

struct FaceData
{
    FaceGeometry::Type Type;
    RF_Type::UInt32 Start;
    RF_Type::UInt32 Count;
};

struct ElementData
{
    const RF_Type::UInt32* Data;
    RF_Type::UInt32 Count;
};

class Mesh
{
protected:
    //dataptr,elementcount
    std::vector<VertexData> m_VertexAttributes;
    ElementData m_ElementList;
    std::vector<FaceData> m_Faces;
public:
    void AddVertexAttribute(const RF_Type::String& Name,
                            const RF_Type::Float32* Data,
                            const RF_Type::UInt32 ElementCount,
                            const RF_Type::UInt32 ElementSize);
    void AddFace(const FaceGeometry::Type GeometryType, 
                    const RF_Type::UInt32 Start,
                    const RF_Type::UInt32 Count);
    void SetElementList(const RF_Type::UInt32* Data,
                        const RF_Type::UInt32 Count);

    RF_Type::UInt32 AttributeCount()const;
    const std::vector<VertexData>& Attributes()const;

    RF_Type::UInt32 FaceCount()const;
    const std::vector<FaceData>& Faces()const;

    const ElementData& ElementList()const;
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif // RF_MATH_GEOMETRY_MESH_HPP
