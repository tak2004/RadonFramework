#ifndef RF_MATH_GEOMETRY_MESH_HPP
#define RF_MATH_GEOMETRY_MESH_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <vector>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/Float32.hpp>

namespace RadonFramework
{
    namespace Math
    {
        namespace Geometry
        {
            namespace FaceGeometry{
                enum Type{
                    Triangle,
                    Line,
                    Point
                };
            }
            #define FaceGeometrySize 3

            class VertexData
            {
                public:
                    VertexData();
                    VertexData(const RadonFramework::Core::Types::String& BufferName,
                               const RadonFramework::Core::Types::Float32* BufferData,
                               const RadonFramework::Core::Types::UInt32 ElementCount,
                               const RadonFramework::Core::Types::UInt32 ElementSize);
                    VertexData(const VertexData& Copy);
                    ~VertexData();

                    RadonFramework::Core::Types::String Name;
                    const RadonFramework::Core::Types::Float32* Data;
                    RadonFramework::Core::Types::UInt32 Count;
                    RadonFramework::Core::Types::UInt32 Size;
            };

            struct FaceData
            {
                FaceGeometry::Type Type;
                RadonFramework::Core::Types::UInt32 Start;
                RadonFramework::Core::Types::UInt32 Count;
            };

            struct ElementData
            {
                const RadonFramework::Core::Types::UInt32* Data;
                RadonFramework::Core::Types::UInt32 Count;
            };

            class Mesh
            {
                protected:
                    //dataptr,elementcount
                    std::vector<VertexData> m_VertexAttributes;
                    ElementData m_ElementList;
                    std::vector<FaceData> m_Faces;
                public:
                    void AddVertexAttribute(const RadonFramework::Core::Types::String& Name,
                                            const RadonFramework::Core::Types::Float32* Data,
                                            const RadonFramework::Core::Types::UInt32 ElementCount,
                                            const RadonFramework::Core::Types::UInt32 ElementSize);
                    void AddFace(const FaceGeometry::Type GeometryType, 
                                 const RadonFramework::Core::Types::UInt32 Start,
                                 const RadonFramework::Core::Types::UInt32 Count);
                    void SetElementList(const RadonFramework::Core::Types::UInt32* Data,
                                        const RadonFramework::Core::Types::UInt32 Count);

                    RadonFramework::Core::Types::UInt32 AttributeCount()const;
                    const std::vector<VertexData>& Attributes()const;

                    RadonFramework::Core::Types::UInt32 FaceCount()const;
                    const std::vector<FaceData>& Faces()const;

                    const ElementData& ElementList()const;
            };
        }
    }
}

#endif // RF_MATH_GEOMETRY_MESH_HPP
