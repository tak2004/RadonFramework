#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Path2DTriangulation.hpp"

namespace RadonFramework { namespace Drawing {

void AddEdge(RF_Collect::List<RF_Geo::Vec2f> &Triangles,
             RF_Geo::Point2Df& Point0, RF_Geo::Point2Df& Point1)
{
    RF_Geo::Vec2f vertex;
    vertex[0] = Point0.X;
    vertex[1] = Point0.Y;
    if(Triangles.Count() % 3 == 0)
    {
        Triangles.AddLast(vertex);
    }
    vertex[0] = Point1.X;
    vertex[1] = Point1.Y;
    Triangles.AddLast(vertex);
}

void EndPath(RF_Collect::List<RF_Geo::Vec2f> &Triangles, RF_Geo::Point2Df& SegmentStart,
             RF_Geo::Point2Df& CurrentPosition)
{
    RF_Draw::AddEdge(Triangles, SegmentStart, CurrentPosition);
}

void LineTo(RF_Collect::List<RF_Geo::Vec2f> &Triangles,
            RF_Geo::Point2Df& SegmentStart, RF_Geo::Point2Df& CurrentPosition)
{
    RF_Draw::AddEdge(Triangles, SegmentStart, CurrentPosition);
}

void Path2DTriangulation::Initialize()
{
    m_IsLastSegmentMoveTo = true;
    m_IsLastSegmentClose = false;
    m_Triangles.Clear();
}


void Path2DTriangulation::Finalize()
{
    m_Vertices.Resize(m_Triangles.Count());
    for (RF_Type::Size i = 0; i < m_Triangles.Count(); ++i)
    {
        m_Vertices(i) = m_Triangles[i];
    }
    m_Triangles.Clear();
}

void Path2DTriangulation::MoveTo(const RF_Geo::Point2Df& Position)
{
    if(!m_IsLastSegmentMoveTo && !m_IsLastSegmentClose)
    {
        RF_Draw::EndPath(m_Triangles, m_LastPositionOfPreviousSegment, m_CurrentPosition);
    }
    m_CurrentPosition = Position;
    m_FirstPositionOfSegment = m_CurrentPosition;
    m_LastPositionOfPreviousSegment = m_CurrentPosition;
    m_IsLastSegmentMoveTo = true;
    m_IsLastSegmentClose = false;
}

void Path2DTriangulation::LineTo(const RF_Geo::Point2Df& Position)
{
    m_CurrentPosition = Position;
    RF_Draw::LineTo(m_Triangles, m_LastPositionOfPreviousSegment, m_CurrentPosition);
    m_LastPositionOfPreviousSegment = m_CurrentPosition;
    m_IsLastSegmentMoveTo = false;
    m_IsLastSegmentClose = false;
}

void Path2DTriangulation::Close()
{
    RF_Draw::EndPath(m_Triangles, m_LastPositionOfPreviousSegment, m_FirstPositionOfSegment);
    m_LastPositionOfPreviousSegment = m_FirstPositionOfSegment;
    m_IsLastSegmentMoveTo = false;
    m_IsLastSegmentClose = true;
}

void Path2DTriangulation::BezierTo(const RF_Geo::Point2Df& ControlPoint1, 
    const RF_Geo::Point2Df& ControlPoint2, const RF_Geo::Point2Df& Position)
{
    m_IsLastSegmentMoveTo = false;
    m_IsLastSegmentClose = false;
}

void Path2DTriangulation::QuadraticBezierTo(const RF_Geo::Point2Df& ControlPoint, 
    const RF_Geo::Point2Df& Position)
{
    m_IsLastSegmentMoveTo = false;
    m_IsLastSegmentClose = false;
}

void Path2DTriangulation::AddArc(const RF_Geo::Point2Df& Position, RF_Type::Float32 Radius, 
    RF_Type::Float32 AngleStart, RF_Type::Float32 AngleStop)
{
    m_IsLastSegmentMoveTo = false;
    m_IsLastSegmentClose = false;
}

void Path2DTriangulation::AddRectangle(const RF_Geo::Point2Df& Position, const 
    RF_Geo::Size2Df& Dimension)
{
    m_IsLastSegmentMoveTo = false;
    m_IsLastSegmentClose = false;
}

void Path2DTriangulation::AddRoundRectangle(const RF_Geo::Point2Df& Position, 
    const RF_Geo::Size2Df& Dimension, RF_Type::Float32 Radius)
{
    m_IsLastSegmentMoveTo = false;
    m_IsLastSegmentClose = false;
}

void Path2DTriangulation::AddEllipse(const RF_Geo::Point2Df& Position, 
    const RF_Geo::Size2Df& Dimension, RF_Type::Float32 Angle)
{
    m_IsLastSegmentMoveTo = false;
    m_IsLastSegmentClose = false;
}

void Path2DTriangulation::AddCircle(const RF_Geo::Point2Df& Position, RF_Type::Float32 Radius)
{
    m_IsLastSegmentMoveTo = false;
    m_IsLastSegmentClose = false;
}

void Path2DTriangulation::Error()
{
    
}

const RF_Collect::Array<RF_Geo::Vec2f>& Path2DTriangulation::GetVertices() const
{
    return m_Vertices;
}

} }