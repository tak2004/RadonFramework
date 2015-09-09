#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Path2D.hpp"

namespace RadonFramework { namespace Drawing {

enum
{
    CHUNKSIZE = 4096
};

Path2D::Path2D()
{

}

Path2D::~Path2D()
{

}

void Path2D::Clear()
{
    m_Final.Reset();
    m_ScratchPad.Clear();
}

void Path2D::MoveTo(const RF_Geo::Point2Df& Position)
{
    RF_Type::Size neededByteCount = sizeof(RF_Geo::Point2Df) + sizeof(Command::Type);
    if(m_ScratchPad.Length() - m_ScratchPad.Position() < neededByteCount)
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> newMemoryBlock(CHUNKSIZE);
        m_ScratchPad.AddLast(newMemoryBlock);
    }

    m_ScratchPad.WriteType(Command::MoveTo);
    m_ScratchPad.WriteType(Position);
}

void Path2D::LineTo(const RF_Geo::Point2Df& Position)
{
    RF_Type::Size neededByteCount = sizeof(RF_Geo::Point2Df) + sizeof(Command::Type);
    if(m_ScratchPad.Length() - m_ScratchPad.Position() < neededByteCount)
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> newMemoryBlock(CHUNKSIZE);
        m_ScratchPad.AddLast(newMemoryBlock);
    }
    m_ScratchPad.WriteType(Command::LineTo);
    m_ScratchPad.WriteType(Position);
}

void Path2D::BezierTo(const RF_Geo::Point2Df& ControlPoint1, const RF_Geo::Point2Df& ControlPoint2, const RF_Geo::Point2Df& Position)
{
/*    m_CommandBuffer.AddLast(Command::BezierTo);*/
}

void Path2D::QuadraticBezierTo(const RF_Geo::Point2Df& ControlPoint, const RF_Geo::Point2Df& Position)
{
/*    m_CommandBuffer.AddLast(Command::QuadraticBezierTo);*/
}

void Path2D::ArcTo(const RF_Geo::Point2Df& Position1, const RF_Geo::Point2Df& Position2, RF_Type::Float32 Radius)
{
//     m_CommandBuffer.AddLast(Command::LineTo);
//     m_CommandBuffer.AddLast(Command::QuadraticBezierTo);
}

void Path2D::Close()
{
    if(m_ScratchPad.Length() - m_ScratchPad.Position() < sizeof(Command))
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> newMemoryBlock(CHUNKSIZE);
        m_ScratchPad.AddLast(newMemoryBlock);
    }
    m_ScratchPad.WriteType(Command::Close);
}

void Path2D::AddArc(const RF_Geo::Point2Df& Position, RF_Type::Float32 Radius, RF_Type::Float32 AngleStart, RF_Type::Float32 AngleStop)
{
//     m_CommandBuffer.AddLast(Command::MoveTo);
//     m_CommandBuffer.AddLast(Command::QuadraticBezierTo);
//     if(Radius> 90.0f)
//         m_CommandBuffer.AddLast(Command::QuadraticBezierTo);
//     if(Radius> 180.0f)
//         m_CommandBuffer.AddLast(Command::QuadraticBezierTo);
//     if(Radius> 270.0f)
//         m_CommandBuffer.AddLast(Command::QuadraticBezierTo);
//     m_CommandBuffer.AddLast(Command::Close);
}

void Path2D::AddRectangle(const RF_Geo::Point2Df& Position, const RF_Geo::Size2Df& Dimension)
{
    RF_Geo::Point2Df position;
    MoveTo(Position);
    position = Position;
    position.X += Dimension.Width;
    LineTo(position);
    position.Y += Dimension.Height;
    LineTo(position);
    position.X = Position.X;
    LineTo(position);
    Close();
}

void Path2D::AddRoundRectangle(const RF_Geo::Point2Df& Position, const RF_Geo::Size2Df& Dimension, RF_Type::Float32 Radius)
{
//     m_CommandBuffer.AddLast(Command::MoveTo);
//     m_CommandBuffer.AddLast(Command::QuadraticBezierTo);
//     m_CommandBuffer.AddLast(Command::LineTo);
//     m_CommandBuffer.AddLast(Command::QuadraticBezierTo);
//     m_CommandBuffer.AddLast(Command::LineTo);
//     m_CommandBuffer.AddLast(Command::QuadraticBezierTo);
//     m_CommandBuffer.AddLast(Command::LineTo);
//     m_CommandBuffer.AddLast(Command::QuadraticBezierTo);
//     m_CommandBuffer.AddLast(Command::Close);
}

void Path2D::AddEllipse(const RF_Geo::Point2Df& Position, const RF_Geo::Size2Df& Dimension, RF_Type::Float32 Angle)
{
//     m_CommandBuffer.AddLast(Command::MoveTo);
//     m_CommandBuffer.AddLast(Command::QuadraticBezierTo);
//     m_CommandBuffer.AddLast(Command::QuadraticBezierTo);
//     m_CommandBuffer.AddLast(Command::Close);
}

void Path2D::AddCircle(const RF_Geo::Point2Df& Position, RF_Type::Float32 Radius)
{
//     m_CommandBuffer.AddLast(Command::MoveTo);
//     m_CommandBuffer.AddLast(Command::QuadraticBezierTo);
//     m_CommandBuffer.AddLast(Command::QuadraticBezierTo);
//     m_CommandBuffer.AddLast(Command::Close);
}

Stroke& Path2D::StrokeProperties()
{
    return m_StrokeProperties;
}

Fill& Path2D::FillProperties()
{
    return m_FillProperties;
}

void Path2D::Finalize()
{
    m_Final = RF_Mem::AutoPointerArray<RF_Type::UInt8>(m_ScratchPad.Position());
    m_ScratchPad.Seek(0, RF_IO::SeekOrigin::Begin);
    m_ScratchPad.Read(m_Final.Get(), 0, m_Final.Size());
    m_ScratchPad.Clear();
}

const RF_Mem::AutoPointerArray<RF_Type::UInt8>& Path2D::Data() const
{
    return m_Final;
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