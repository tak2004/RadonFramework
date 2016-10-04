#ifndef RF_DRAWING_PATH2DTRIANGULATION_HPP
#define RF_DRAWING_PATH2DTRIANGULATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Drawing/Path2D.hpp>
#include <RadonFramework/Math/Geometry/Vector.hpp>

namespace RadonFramework { namespace Drawing {

class Path2DTriangulation: public Path2D::Visitor
{
public:
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
    virtual void Error() override;
    const RF_Collect::Array<RF_Geo::Vec2f>& GetVertices()const;
private:
    RF_Collect::List<RF_Geo::Vec2f> m_Triangles;
    RF_Collect::Array<RF_Geo::Vec2f> m_Vertices;
    RF_Geo::Point2Df m_CurrentPosition, m_LastPositionOfPreviousSegment, 
        m_FirstPositionOfSegment;
    RF_Type::Bool m_IsLastSegmentMoveTo;
    RF_Type::Bool m_IsLastSegmentClose;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif // RF_SHORTHAND_NAMESPACE_DRAW

#endif // !RF_DRAWING_PATH2DTRIANGULATION_HPP