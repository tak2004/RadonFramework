#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Path2D.hpp"

namespace RadonFramework { namespace Drawing {

enum class Path2D::Command:RF_Type::UInt8
{
    MoveTo,
    LineTo,
    BezierTo,
    QuadraticBezierTo,
    ArcTo,
    Close
};

Path2D::Path2D()
{

}

Path2D::~Path2D()
{

}

void Path2D::Clear()
{
    m_CommandBuffer.Clear();
    m_ValueBuffer.Clear();
}

void Path2D::MoveTo(const RF_Geo::Point2Df& Position)
{
    m_CommandBuffer.AddLast(Command::MoveTo);
}

void Path2D::LineTo(const RF_Geo::Point2Df& Position)
{
    m_CommandBuffer.AddLast(Command::LineTo);
}

void Path2D::BezierTo(const RF_Geo::Point2Df& ControlPoint1, const RF_Geo::Point2Df& ControlPoint2, const RF_Geo::Point2Df& Position)
{
    m_CommandBuffer.AddLast(Command::BezierTo);
}

void Path2D::QuadraticBezierTo(const RF_Geo::Point2Df& ControlPoint, const RF_Geo::Point2Df& Position)
{
    m_CommandBuffer.AddLast(Command::QuadraticBezierTo);
}

void Path2D::ArcTo(const RF_Geo::Point2Df& Position1, const RF_Geo::Point2Df& Position2, RF_Type::Float32 Radius)
{
    m_CommandBuffer.AddLast(Command::ArcTo);
}

void Path2D::Close()
{
    m_CommandBuffer.AddLast(Command::Close);
}

void Path2D::AddArc(const RF_Geo::Point2Df& Position, RF_Type::Float32 Radius, RF_Type::Float32 AngleStart, RF_Type::Float32 AngleStop)
{
    m_CommandBuffer.AddLast(Command::MoveTo);
    m_CommandBuffer.AddLast(Command::ArcTo);
    m_CommandBuffer.AddLast(Command::Close);
}

void Path2D::AddRectangle(const RF_Geo::Point2Df& Position, const RF_Geo::Size2Df& Dimension)
{
    m_CommandBuffer.AddLast(Command::MoveTo);
    m_CommandBuffer.AddLast(Command::LineTo);
    m_CommandBuffer.AddLast(Command::LineTo);
    m_CommandBuffer.AddLast(Command::LineTo);
    m_CommandBuffer.AddLast(Command::Close);
}

void Path2D::AddRoundRectangle(const RF_Geo::Point2Df& Position, const RF_Geo::Size2Df& Dimension, RF_Type::Float32 Radius)
{
    m_CommandBuffer.AddLast(Command::MoveTo);
    m_CommandBuffer.AddLast(Command::QuadraticBezierTo);

}

void Path2D::AddEllipse(const RF_Geo::Point2Df& Position, const RF_Geo::Size2Df& Dimension, RF_Type::Float32 Angle)
{

}

void Path2D::AddCircle(const RF_Geo::Point2Df& Position, RF_Type::Float32 Radius)
{

}

Stroke& Path2D::StrokeProperties()
{
    return m_StrokeProperties;
}

Fill& Path2D::FillProperties()
{
    return m_FillProperties;
}

Fill::Fill()
:Color(1,1,1,1)
{

}

Stroke::Stroke()
:Color(1,1,1,1)
{

}

} }