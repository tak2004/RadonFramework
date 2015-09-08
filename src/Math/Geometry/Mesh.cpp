#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Geometry/Mesh.hpp"

namespace RadonFramework { namespace Math { namespace Geometry {

VertexData::VertexData()
:Data(0)
,Count(0)
,Size(0)
{
}

VertexData::VertexData(const RadonFramework::Core::Types::String& BufferName,
    const RadonFramework::Core::Types::Float32* BufferData,
    const RadonFramework::Core::Types::UInt32 ElementCount,
    const RadonFramework::Core::Types::UInt32 ElementSize)
:Name(BufferName)
,Data(BufferData)
,Count(ElementCount)
,Size(ElementSize)
{
}

VertexData::VertexData(const VertexData& Copy)
{
    *this = Copy;
}

VertexData::~VertexData()
{
}

VertexData& RadonFramework::Math::Geometry::VertexData::operator=(const VertexData& Other)
{
    Name = Other.Name;
    Data = Other.Data;
    Count = Other.Count;
    Size = Other.Size;
    return *this;
}

void Mesh::AddVertexAttribute(const RadonFramework::Core::Types::String& Name,
    const RadonFramework::Core::Types::Float32* Data,
    const RadonFramework::Core::Types::UInt32 ElementCount,
    const RadonFramework::Core::Types::UInt32 ElementSize)
{
    VertexData data(Name, Data, ElementCount, ElementSize);
    m_VertexAttributes.push_back(data);
}

void Mesh::AddFace(const FaceGeometry::Type GeometryType,
    const RadonFramework::Core::Types::UInt32 Start,
    const RadonFramework::Core::Types::UInt32 Count)
{
    FaceData data = {GeometryType, Start, Count};
    m_Faces.push_back(data);
}

void Mesh::SetElementList(const RadonFramework::Core::Types::UInt32* Data,
    const RadonFramework::Core::Types::UInt32 Count)
{
    m_ElementList.Data = Data;
    m_ElementList.Count = Count;
}

RadonFramework::Core::Types::UInt32 Mesh::AttributeCount()const
{
    return static_cast<RadonFramework::Core::Types::UInt32>(m_VertexAttributes.size());
}

const std::vector<VertexData>& Mesh::Attributes()const
{
    return m_VertexAttributes;
}

RadonFramework::Core::Types::UInt32 Mesh::FaceCount()const
{
    return static_cast<RadonFramework::Core::Types::UInt32>(m_Faces.size());
}

const std::vector<FaceData>& Mesh::Faces()const
{
    return m_Faces;
}

const ElementData& Mesh::ElementList()const
{
    return m_ElementList;
}

} } }