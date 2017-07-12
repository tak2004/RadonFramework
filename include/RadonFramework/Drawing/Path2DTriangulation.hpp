#ifndef RF_DRAWING_PATH2DTRIANGULATION_HPP
#define RF_DRAWING_PATH2DTRIANGULATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Drawing/Path2D.hpp>
#include <RadonFramework/Math/Geometry/Vector.hpp>

struct TESSalloc;
struct TESStesselator;

namespace RadonFramework::Drawing {

class Path2DTriangulation: public Path2D::Visitor
{
public:
    Path2DTriangulation();
    virtual ~Path2DTriangulation();
    virtual void Initialize() override;
    virtual void Finalize() override;
    virtual void MoveTo(const RF_Geo::Point2Df& Position) override;
    virtual void LineTo(const RF_Geo::Point2Df& Position) override;
    virtual void Close() override;
    virtual void BezierTo(const RF_Geo::Point2Df& ControlPoint1, 
        const RF_Geo::Point2Df& ControlPoint2, const RF_Geo::Point2Df& Position) override;
    virtual void QuadraticBezierTo(const RF_Geo::Point2Df& ControlPoint, 
        const RF_Geo::Point2Df& Position) override;
    virtual void AddArc(const RF_Geo::Point2Df& Position, RF_Type::Float32 Radius, 
        RF_Type::Float32 AngleStart, RF_Type::Float32 AngleStop) override;
    virtual void AddRectangle(const RF_Geo::Point2Df& Position, 
        const RF_Geo::Size2Df& Dimension) override;
    virtual void AddRoundRectangle(const RF_Geo::Point2Df& Position, 
        const RF_Geo::Size2Df& Dimension, RF_Type::Float32 Radius) override;
    virtual void AddEllipse(const RF_Geo::Point2Df& Position, 
        const RF_Geo::Size2Df& Dimension, RF_Type::Float32 Angle) override;
    virtual void AddCircle(const RF_Geo::Point2Df& Position, RF_Type::Float32 Radius) override;
    virtual void AddText(const RF_Geo::Point2Df& Position, const RF_Type::String& Text) override;
    virtual void AddImage(const RF_Geo::Point2Df& Position, const RF_Geo::Size2Df& Dimension, 
        const RF_Draw::Image& Source) override;
    virtual void Error() override;

    const RF_Collect::Array<RF_Geo::Vec2f>& GetVertices()const;
    const RF_Collect::Array<RF_Draw::Color4f>& GetColors()const;
    const RF_Type::Size GetFaceCount()const;
    void GetFaceData(const RF_Type::Size Index, RF_Type::Size& Start,
        RF_Type::Size& Count, RF_Type::Int32& ImageIndex)const;
    const RF_Draw::Image* GetImage(const RF_Type::Int32 Index)const;

    virtual void SetFill(const Fill& NewFill) override;
    virtual void SetStroke(const Stroke& NewStroke) override;
private:
    struct FaceData
    {
        RF_Type::Size Start;
        RF_Type::Size Count;
        RF_Type::Int32 ImageIndex;
    };
    RF_Draw::Fill m_Fill;
    RF_Draw::Stroke m_Stroke;
    RF_Collect::List<RF_Geo::Vec2f> m_ShapeTriangles;
    RF_Collect::List<RF_Draw::Color4f> m_ShapeColors;
    RF_Collect::List<RF_Geo::Vec2f> m_StrokeTriangles;
    RF_Collect::List<RF_Draw::Color4f> m_StrokeColors;
    RF_Geo::Point2Df m_CurrentPosition, m_LastPositionOfPreviousSegment, 
        m_FirstPositionOfSegment;
    RF_Type::Bool m_IsLastSegmentMoveTo;
    RF_Type::Bool m_IsLastSegmentClose;
    RF_Type::Bool m_SubPathHashGeometry;    
    TESSalloc* m_Alloc;
    TESStesselator* m_Tesselator;

    RF_Collect::Array<RF_Geo::Vec2f> m_Vertices;
    RF_Collect::Array<RF_Draw::Color4f> m_Colors;
    RF_Collect::List<RF_Draw::Image> m_Images;
    RF_Collect::Array<FaceData> m_Faces;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif // RF_SHORTHAND_NAMESPACE_DRAW

#endif // !RF_DRAWING_PATH2DTRIANGULATION_HPP