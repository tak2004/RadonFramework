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
                    VertexData(const RFTYPE::String& BufferName,
                               const RFTYPE::Float32* BufferData,
                               const RFTYPE::UInt32 ElementCount,
                               const RFTYPE::UInt32 ElementSize);
                    VertexData(const VertexData& Copy);
                    ~VertexData();

                    RFTYPE::String Name;
                    const RFTYPE::Float32* Data;
                    RFTYPE::UInt32 Count;
                    RFTYPE::UInt32 Size;
            };

            struct FaceData
            {
                FaceGeometry::Type Type;
                RFTYPE::UInt32 Start;
                RFTYPE::UInt32 Count;
            };

            struct ElementData
            {
                const RFTYPE::UInt32* Data;
                RFTYPE::UInt32 Count;
            };

            class Mesh
            {
                protected:
                    //dataptr,elementcount
                    std::vector<VertexData> m_VertexAttributes;
                    ElementData m_ElementList;
                    std::vector<FaceData> m_Faces;
                public:
                    void AddVertexAttribute(const RFTYPE::String& Name,
                                            const RFTYPE::Float32* Data,
                                            const RFTYPE::UInt32 ElementCount,
                                            const RFTYPE::UInt32 ElementSize);
                    void AddFace(const FaceGeometry::Type GeometryType, 
                                 const RFTYPE::UInt32 Start,
                                 const RFTYPE::UInt32 Count);
                    void SetElementList(const RFTYPE::UInt32* Data,
                                        const RFTYPE::UInt32 Count);

                    RFTYPE::UInt32 AttributeCount()const;
                    const std::vector<VertexData>& Attributes()const;

                    RFTYPE::UInt32 FaceCount()const;
                    const std::vector<FaceData>& Faces()const;

                    const ElementData& ElementList()const;
            };
        }
    }
}

#endif // RF_MATH_GEOMETRY_MESH_HPP
