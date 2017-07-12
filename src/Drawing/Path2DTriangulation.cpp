#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Path2DTriangulation.hpp"
#include "RadonFramework/Math/Geometry/Normal.hpp"
#include "tesselator.h"

namespace RadonFramework::Drawing {

RF_Type::Size tesselatedVertices = 0;

void AddEdge(RF_Collect::List<RF_Geo::Vec2f> &Triangles,
             RF_Geo::Point2Df& Point0, RF_Geo::Point2Df& Point1)
{
    RF_Geo::Vec2f vertex;
    vertex[0] = Point0.X;
    vertex[1] = Point0.Y;
    if (!tesselatedVertices)
    {
        Triangles.AddLast(vertex);
        ++tesselatedVertices;
    }
    vertex[0] = Point1.X;
    vertex[1] = Point1.Y;
    Triangles.AddLast(vertex);
    ++tesselatedVertices;
}

void EndPath(RF_Collect::List<RF_Geo::Vec2f> &Triangles, RF_Geo::Point2Df& SegmentStart,
             RF_Geo::Point2Df& CurrentPosition, RF_Type::Bool SubpathHasGeometry)
{
    tesselatedVertices=0;
    if(!SubpathHasGeometry)
    {
        RF_Draw::AddEdge(Triangles, SegmentStart, CurrentPosition);
        tesselatedVertices = 0;
        RF_Draw::AddEdge(Triangles, SegmentStart, CurrentPosition);
        return;
    }
    RF_Draw::AddEdge(Triangles, SegmentStart, CurrentPosition);
}

void LineTo(RF_Collect::List<RF_Geo::Vec2f> &Triangles,
            RF_Geo::Point2Df& SegmentStart, RF_Geo::Point2Df& CurrentPosition)
{
    if(!SegmentStart.Equals(CurrentPosition))
    {
        RF_Draw::AddEdge(Triangles, SegmentStart, CurrentPosition);
    }
}

void* Alloc(void* userData, unsigned int size)
{
    return RF_SysMem::Allocate(size, 16);
}

void Memfree(void *userData, void *ptr)
{
    RF_SysMem::Free(ptr);
}

Path2DTriangulation::Path2DTriangulation()
:m_Alloc(nullptr)
,m_Tesselator(nullptr)
{
    m_Fill.Color = {0.3f,0.3f,0.3f,1};
}

Path2DTriangulation::~Path2DTriangulation()
{
    if(m_Alloc)
    {
        if(m_Tesselator)
        {
            tessDeleteTess(m_Tesselator);
        }
        delete m_Alloc;
    }
}

void Path2DTriangulation::Initialize()
{
    if (m_Alloc == 0)
    {
        m_Alloc = new TESSalloc;
        m_Alloc->memalloc = Alloc;
        m_Alloc->memrealloc = nullptr;
        m_Alloc->memfree = Memfree;
        m_Alloc->userData = nullptr;
        m_Alloc->meshEdgeBucketSize = 512;
        m_Alloc->meshVertexBucketSize = 512;
        m_Alloc->meshFaceBucketSize = 256;
        m_Alloc->dictNodeBucketSize = 512;
        m_Alloc->regionBucketSize = 256;
        m_Alloc->extraVertices = 512;
        m_Tesselator = tessNewTess(m_Alloc);
    }
    m_IsLastSegmentMoveTo = true;
    m_IsLastSegmentClose = false;
    m_SubPathHashGeometry = false;
    m_ShapeTriangles.Clear();
    m_StrokeTriangles.Clear();
    m_StrokeColors.Clear();
    m_ShapeColors.Clear();
}


void Path2DTriangulation::Finalize()
{
    if(!m_IsLastSegmentMoveTo && !m_IsLastSegmentClose)
    {
        Close();
    }

    // tessellate shape
    if(tessTesselate(m_Tesselator, TessWindingRule::TESS_WINDING_ODD, TESS_POLYGONS, 3, 2, nullptr) == 1)
    {
        auto shapeVertexCount = tessGetElementCount(m_Tesselator) * 3;
        m_Vertices.Resize(shapeVertexCount + m_StrokeTriangles.Count());
        m_Colors.Resize(m_Vertices.Count()+ m_StrokeTriangles.Count());
        
        const auto* verts = tessGetVertices(m_Tesselator);
        const auto* indices = tessGetElements(m_Tesselator);
        for(RF_Type::Size i = 0; i < shapeVertexCount; ++i)
        {
            m_Vertices(i)[0] = verts[indices[i] * 2];
            m_Vertices(i)[1] = verts[indices[i] * 2 + 1];
            m_Colors(i) = m_ShapeColors[indices[i]];
        }
        for(RF_Type::Size i = shapeVertexCount; i < m_Vertices.Count(); ++i)
        {
            m_Vertices(i) = m_StrokeTriangles[i- shapeVertexCount];
            m_Colors(i) = m_StrokeColors[i-shapeVertexCount];
        }
    }
    else
    {
        m_Vertices.Resize(0);
        m_Colors.Resize(0);
    }

    m_ShapeTriangles.Clear();
    m_StrokeTriangles.Clear();
    m_StrokeColors.Clear();
    m_ShapeColors.Clear();
    if(m_Alloc)
    {
        if(m_Tesselator)
        {
            tessDeleteTess(m_Tesselator);
            m_Tesselator = nullptr;
        }
        delete m_Alloc;
        m_Alloc = nullptr;
    }
}

void Path2DTriangulation::MoveTo(const RF_Geo::Point2Df& Position)
{
    if(!m_IsLastSegmentMoveTo && !m_IsLastSegmentClose)
    {
        Close();
    }
    m_CurrentPosition = Position;
    m_FirstPositionOfSegment = m_CurrentPosition;
    m_LastPositionOfPreviousSegment = m_CurrentPosition;
    m_IsLastSegmentMoveTo = true;
    m_IsLastSegmentClose = false;
    m_SubPathHashGeometry = false;
}

void Path2DTriangulation::LineTo(const RF_Geo::Point2Df& Position)
{
    m_CurrentPosition = Position;
    // shape
    tesselatedVertices = 0;
    RF_Draw::LineTo(m_ShapeTriangles, m_LastPositionOfPreviousSegment, m_CurrentPosition);
    // stroke
    if(!m_LastPositionOfPreviousSegment.Equals(m_CurrentPosition))
    {
        RF_Geo::Vec2f start(m_LastPositionOfPreviousSegment.X, m_LastPositionOfPreviousSegment.Y);
        RF_Geo::Vec2f stop(m_CurrentPosition.X, m_CurrentPosition.Y);
        auto line = stop - start;
        RF_Geo::Vec2f normal(-line[1], line[0]);
        normal.Normalize();
        m_StrokeTriangles.AddLast(start + (normal * m_Stroke.Width));
        m_StrokeColors.AddLast(m_Stroke.Color);
        m_StrokeTriangles.AddLast(start + (normal * -m_Stroke.Width));
        m_StrokeColors.AddLast(m_Stroke.Color);
        m_StrokeTriangles.AddLast(stop + (normal * -m_Stroke.Width));
        m_StrokeColors.AddLast(m_Stroke.Color);
        m_StrokeTriangles.AddLast(stop + (normal * -m_Stroke.Width));
        m_StrokeColors.AddLast(m_Stroke.Color);
        m_StrokeTriangles.AddLast(stop + (normal * m_Stroke.Width));
        m_StrokeColors.AddLast(m_Stroke.Color);
        m_StrokeTriangles.AddLast(start + (normal * m_Stroke.Width));
        m_StrokeColors.AddLast(m_Stroke.Color);
    }

    m_LastPositionOfPreviousSegment = m_CurrentPosition;
    m_IsLastSegmentMoveTo = false;
    m_IsLastSegmentClose = false;
    m_SubPathHashGeometry = true;
}

void Path2DTriangulation::Close()
{
    // shape
    RF_Draw::EndPath(m_ShapeTriangles, m_LastPositionOfPreviousSegment, m_FirstPositionOfSegment, m_SubPathHashGeometry);
    m_Vertices.Resize(m_ShapeTriangles.Count() / 2);
    for(auto i = 0; i < m_Vertices.Count(); ++i)
    {
        m_Vertices(i) = m_ShapeTriangles[i * 2];
        m_ShapeColors.AddLast(m_Fill.Color);
    }
    tessAddContour(m_Tesselator, 2, &m_Vertices(0), sizeof(RF_Geo::Vec2f), m_Vertices.Count());
    m_ShapeTriangles.Clear();
    // stroke
    if(!m_LastPositionOfPreviousSegment.Equals(m_FirstPositionOfSegment))
    {
        RF_Geo::Vec2f start(m_LastPositionOfPreviousSegment.X, m_LastPositionOfPreviousSegment.Y);
        RF_Geo::Vec2f stop(m_FirstPositionOfSegment.X, m_FirstPositionOfSegment.Y);
        auto line = stop - start;
        RF_Geo::Vec2f normal(-line[1], line[0]);
        normal.Normalize();
        m_StrokeTriangles.AddLast(start + (normal * m_Stroke.Width));
        m_StrokeColors.AddLast(m_Stroke.Color);
        m_StrokeTriangles.AddLast(start + (normal * -m_Stroke.Width));
        m_StrokeColors.AddLast(m_Stroke.Color);
        m_StrokeTriangles.AddLast(stop + (normal * -m_Stroke.Width));
        m_StrokeColors.AddLast(m_Stroke.Color);
        m_StrokeTriangles.AddLast(stop + (normal * -m_Stroke.Width));
        m_StrokeColors.AddLast(m_Stroke.Color);
        m_StrokeTriangles.AddLast(stop + (normal * m_Stroke.Width));
        m_StrokeColors.AddLast(m_Stroke.Color);
        m_StrokeTriangles.AddLast(start + (normal * m_Stroke.Width));
        m_StrokeColors.AddLast(m_Stroke.Color);
    }

    m_LastPositionOfPreviousSegment = m_FirstPositionOfSegment;
    m_IsLastSegmentMoveTo = false;
    m_IsLastSegmentClose = true;
    m_SubPathHashGeometry = false;
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

const RF_Collect::Array<RF_Draw::Color4f>& Path2DTriangulation::GetColors() const
{
    return m_Colors;
}

const RF_Type::Size Path2DTriangulation::GetFaceCount() const
{
    return m_Faces.Count();
}

void Path2DTriangulation::GetFaceData(const RF_Type::Size Index, RF_Type::Size& Start, 
    RF_Type::Size& Count, RF_Type::Int32& ImageIndex) const
{
    if(Index < m_Faces.Count())
    {
        Start = m_Faces(Index).Start;
        Count = m_Faces(Index).Count;
        ImageIndex = m_Faces(Index).ImageIndex;
    }
}

const RF_Draw::Image* Path2DTriangulation::GetImage(const RF_Type::Int32 Index) const
{
    const RF_Draw::Image* result = 0;
    if(Index < m_Images.Count())
    {
        result = &m_Images[Index];
    }
    return result;
}

void Path2DTriangulation::SetFill(const Fill& NewFill)
{
    m_Fill = NewFill;
}

void Path2DTriangulation::SetStroke(const Stroke& NewStroke)
{
    m_Stroke = NewStroke;
}

void Path2DTriangulation::AddText(const RF_Geo::Point2Df& Position, 
    const RF_Type::String& Text)
{
    m_IsLastSegmentMoveTo = false;
    m_IsLastSegmentClose = false;
}

void Path2DTriangulation::AddImage(const RF_Geo::Point2Df& Position, 
    const RF_Geo::Size2Df& Dimension, const RF_Draw::Image& Source)
{
    RF_Type::Size i;
    for (i = 0; i < m_Images.Count(); ++i)
    {
        if(m_Images[i] == Source)
        {
            break;
        }
    }
    
    if(i < m_Images.Count())
    {
        m_Images.AddLast(Source);
    }

    m_IsLastSegmentMoveTo = false;
    m_IsLastSegmentClose = false;
    AddRectangle(Position, Dimension);
}

}