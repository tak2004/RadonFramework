#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Path2D.hpp"
#include "RadonFramework/Math/Hash/Hash32.hpp"
#include "RadonFramework/Drawing/Image.hpp"

struct Command
{
    enum Type:RF_Type::UInt8
    {
        MoveTo,
        LineTo,
        BezierTo,
        QuadraticBezierTo,
        Close,
        ArcTo,
        SetFill,
        SetStroke,
        Text,
        Image
    };
};

namespace RadonFramework::Drawing {

enum
{
    CHUNKSIZE = 4096
};

Path2D::Path2D()
:m_Hash(0)
{

}

Path2D::Path2D(const Path2D& CopyFrom)
{
    m_ScratchPad.Clear();
    m_Final = CopyFrom.m_Final.Clone();
    m_Hash = CopyFrom.m_Hash;
}

Path2D::~Path2D()
{

}

void Path2D::Clear()
{
    m_Final.Reset();
    m_ScratchPad.Clear();
    m_Hash = 0;
}

Path2D& Path2D::MoveTo(const RF_Geo::Point2Df& Position)
{
    RF_Type::Size neededByteCount = sizeof(RF_Geo::Point2Df) + sizeof(Command);
    if(m_ScratchPad.Length() - m_ScratchPad.Position() < neededByteCount)
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> newMemoryBlock(CHUNKSIZE);
        m_ScratchPad.AddLast(newMemoryBlock);
    }

    m_ScratchPad.WriteType(Command::MoveTo);
    m_ScratchPad.WriteType(Position);
    return *this;
}

Path2D& Path2D::LineTo(const RF_Geo::Point2Df& Position)
{
    RF_Type::Size neededByteCount = sizeof(RF_Geo::Point2Df) + sizeof(Command);
    if(m_ScratchPad.Length() - m_ScratchPad.Position() < neededByteCount)
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> newMemoryBlock(CHUNKSIZE);
        m_ScratchPad.AddLast(newMemoryBlock);
    }
    m_ScratchPad.WriteType(Command::LineTo);
    m_ScratchPad.WriteType(Position);
    return *this;
}

Path2D& Path2D::BezierTo(const RF_Geo::Point2Df& ControlPoint1, const RF_Geo::Point2Df& ControlPoint2, const RF_Geo::Point2Df& Position)
{
    RF_Type::Size neededByteCount = (3 * sizeof(RF_Geo::Point2Df)) + sizeof(Command);
    if(m_ScratchPad.Length() - m_ScratchPad.Position() < neededByteCount)
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> newMemoryBlock(CHUNKSIZE);
        m_ScratchPad.AddLast(newMemoryBlock);
    }
    m_ScratchPad.WriteType(Command::BezierTo);
    m_ScratchPad.WriteType(ControlPoint1);
    m_ScratchPad.WriteType(ControlPoint2);
    m_ScratchPad.WriteType(Position);
    return *this;
}

Path2D& Path2D::QuadraticBezierTo(const RF_Geo::Point2Df& ControlPoint, const RF_Geo::Point2Df& Position)
{
    RF_Type::Size neededByteCount = (2 * sizeof(RF_Geo::Point2Df)) + sizeof(Command);
    if(m_ScratchPad.Length() - m_ScratchPad.Position() < neededByteCount)
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> newMemoryBlock(CHUNKSIZE);
        m_ScratchPad.AddLast(newMemoryBlock);
    }
    m_ScratchPad.WriteType(Command::QuadraticBezierTo);
    m_ScratchPad.WriteType(ControlPoint);
    m_ScratchPad.WriteType(Position);
    return *this;
}

Path2D& Path2D::ArcTo(const RF_Geo::Point2Df& Position1, const RF_Geo::Point2Df& Position2, RF_Type::Float32 Radius)
{
    RF_Type::Size neededByteCount = (2 * sizeof(RF_Geo::Point2Df)) + sizeof(RF_Type::Float32) + sizeof(Command);
    if(m_ScratchPad.Length() - m_ScratchPad.Position() < neededByteCount)
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> newMemoryBlock(CHUNKSIZE);
        m_ScratchPad.AddLast(newMemoryBlock);
    }
    m_ScratchPad.WriteType(Command::ArcTo);
    m_ScratchPad.WriteType(Position1);
    m_ScratchPad.WriteType(Position2);
    m_ScratchPad.WriteType(Radius);
    return *this;
}

Path2D& Path2D::Close()
{
    if(m_ScratchPad.Length() - m_ScratchPad.Position() < sizeof(Command))
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> newMemoryBlock(CHUNKSIZE);
        m_ScratchPad.AddLast(newMemoryBlock);
    }
    m_ScratchPad.WriteType(Command::Close);
    return *this;
}

Path2D& Path2D::AddArc(const RF_Geo::Point2Df& Position, RF_Type::Float32 Radius, RF_Type::Float32 AngleStart, RF_Type::Float32 AngleStop)
{
//     RF_Geo::Point2Df position = Position;
//     position.X += RF_Math::Float32::Sin(AngleStart)*Radius;
//     position.Y += RF_Math::Float32::Cos(AngleStart)*Radius;
//     MoveTo(position);
//     RF_Geo::Point2Df control = position;
//     position = Position;
//     position.X += RF_Math::Float32::Sin(AngleStop)*Radius;
//     position.Y += RF_Math::Float32::Cos(AngleStop)*Radius;
//     control.X = control.X 
//     ArcTo(position, control ,Radius);

    return *this;
}

Path2D& Path2D::AddRectangle(const RF_Geo::Point2Df& Position, const RF_Geo::Size2Df& Dimension)
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
    return *this;
}

Path2D& Path2D::AddRoundRectangle(const RF_Geo::Point2Df& Position, const RF_Geo::Size2Df& Dimension, RF_Type::Float32 Radius)
{
    return *this;
}

Path2D& Path2D::AddEllipse(const RF_Geo::Point2Df& Position, const RF_Geo::Size2Df& Dimension, RF_Type::Float32 Angle)
{
    return *this;
}

Path2D& Path2D::AddCircle(const RF_Geo::Point2Df& Position, RF_Type::Float32 Radius)
{
    return *this;
}


Path2D& Path2D::AddText(const RF_Type::String& Text, const RF_Geo::Point2Df& Position)
{
    RF_Type::Size neededByteCount = sizeof(RF_Geo::Point2Df) + 
        sizeof(RF_Type::UInt32) + Text.Size() - 1 + sizeof(Command);

    if(m_ScratchPad.Length() - m_ScratchPad.Position() < neededByteCount)
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> newMemoryBlock(CHUNKSIZE);
        m_ScratchPad.AddLast(newMemoryBlock);
    }
    m_ScratchPad.WriteType(Command::Text);
    m_ScratchPad.WriteType(Position);
    m_ScratchPad.WriteType((RF_Type::UInt32)Text.Size());
    m_ScratchPad.WriteText(Text);
    return *this;
}

Path2D& Path2D::AddImage(const RF_Geo::Point2Df& Position, const RF_Geo::Size2Df& Dimension,
    const RF_Draw::Image& Source)
{
    RF_Type::UInt32 imgSize = (Source.PixelFormat().BitPerPixel * Source.Width() * Source.Height() / 8);
    if (imgSize > 0)
    {
        RF_Type::Size neededByteCount = sizeof(RF_Geo::Point2Df) + sizeof(RF_Geo::Size2Df) +
            (sizeof(RF_Type::UInt32) * 3) +imgSize + sizeof(Command);

        if(m_ScratchPad.Length() - m_ScratchPad.Position() < neededByteCount)
        {
            RF_Mem::AutoPointerArray<RF_Type::UInt8> newMemoryBlock(CHUNKSIZE);
            m_ScratchPad.AddLast(newMemoryBlock);
        }
        m_ScratchPad.WriteType(Command::Image);
        m_ScratchPad.WriteType(Position);
        m_ScratchPad.WriteType(Dimension);
        m_ScratchPad.WriteType(Source.Width());
        m_ScratchPad.WriteType(Source.Height());
        m_ScratchPad.WriteType(imgSize);
        m_ScratchPad.Write(Source.UnsafeAccess(), 0, imgSize);
    }
    return *this;
}

Path2D& Path2D::Finalize()
{
    m_Final = RF_Mem::AutoPointerArray<RF_Type::UInt8>(m_ScratchPad.Position());
    m_ScratchPad.Seek(0, RF_IO::SeekOrigin::Begin);
    m_ScratchPad.Read(m_Final.Get(), 0, m_Final.Size());
    m_ScratchPad.Clear();
    m_CurrentPosition.X = 0;
    m_CurrentPosition.Y = 0;
    RF_Hash::Hash32 hash;
    hash.FromMemory(m_Final);
    m_Hash = hash.GetHash();
    return *this;
}

Path2D& Path2D::SetFill(const Fill& NewFill)
{
    RF_Type::Size neededByteCount = sizeof(RF_Draw::Color4f) + sizeof(Command);
    if(m_ScratchPad.Length() - m_ScratchPad.Position() < neededByteCount)
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> newMemoryBlock(CHUNKSIZE);
        m_ScratchPad.AddLast(newMemoryBlock);
    }
    m_ScratchPad.WriteType(Command::SetFill);
    m_ScratchPad.WriteType(NewFill.Color);    
    return *this;
}

Path2D& Path2D::SetStroke(const Stroke& NewStroke)
{
    RF_Type::Size neededByteCount = sizeof(RF_Draw::Color4f) + sizeof(RF_Type::Float32) + sizeof(Command);
    if(m_ScratchPad.Length() - m_ScratchPad.Position() < neededByteCount)
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> newMemoryBlock(CHUNKSIZE);
        m_ScratchPad.AddLast(newMemoryBlock);
    }
    m_ScratchPad.WriteType(Command::SetStroke);
    m_ScratchPad.WriteType(NewStroke.Color);
    m_ScratchPad.WriteType(NewStroke.Width);
    return *this;
}

void Path2D::Visit(Visitor& PathVisitor)const
{
    PathVisitor.Initialize();
    if(m_Final.Count() > 0)
    {
        RF_Type::UInt8* cursor = m_Final.Get();
        RF_Type::UInt8* lastByte = m_Final.Get() + m_Final.Count();
        RF_Geo::Point2Df currentPosition;
        Fill fill;
        Stroke stroke;

        do 
        {
            switch(*cursor)
            {
            case Command::LineTo:
            {
                ++cursor;
                currentPosition = *reinterpret_cast<RF_Geo::Point2Df*>(cursor);
                cursor += sizeof(RF_Geo::Point2Df);
                PathVisitor.LineTo(currentPosition);
                break;
            }
            case Command::MoveTo:
            {
                ++cursor;
                currentPosition = *reinterpret_cast<RF_Geo::Point2Df*>(cursor);
                cursor += sizeof(RF_Geo::Point2Df);
                PathVisitor.MoveTo(currentPosition);
                break;
            }
            case Command::Close:
            {
                ++cursor;
                PathVisitor.Close();
                break;
            }
            case Command::SetFill:
            {
                ++cursor;
                fill.Color = *reinterpret_cast<RF_Draw::Color4f*>(cursor);
                cursor += sizeof(RF_Draw::Color4f);
                PathVisitor.SetFill(fill);
                break;
            }
            case Command::SetStroke:
            {
                ++cursor;
                stroke.Color = *reinterpret_cast<RF_Draw::Color4f*>(cursor);
                cursor += sizeof(RF_Draw::Color4f);
                stroke.Width = *reinterpret_cast<RF_Type::Float32*>(cursor);
                cursor += sizeof(RF_Type::Float32);
                PathVisitor.SetStroke(stroke);
                break;
            }
            case Command::Text:
            {
                ++cursor;
                currentPosition = *reinterpret_cast<RF_Geo::Point2Df*>(cursor);
                cursor += sizeof(RF_Geo::Point2Df);
                auto strSize = *reinterpret_cast<RF_Type::UInt32*>(cursor);
                cursor += sizeof(RF_Type::UInt32);
                RF_Type::String text((const char*)cursor, strSize);
                cursor += strSize;
                PathVisitor.AddText(currentPosition, text);
                break;
            }
            case Command::Image:
            {
                ++cursor;
                currentPosition = *reinterpret_cast<RF_Geo::Point2Df*>(cursor);
                cursor += sizeof(RF_Geo::Point2Df);
                auto dimension = *reinterpret_cast<RF_Geo::Size2Df*>(cursor);
                cursor += sizeof(RF_Geo::Size2Df);
                auto width = *reinterpret_cast<RF_Type::UInt32*>(cursor);
                cursor += sizeof(RF_Type::UInt32);
                auto height = *reinterpret_cast<RF_Type::UInt32*>(cursor);
                cursor += sizeof(RF_Type::UInt32);
                auto bytes = *reinterpret_cast<RF_Type::UInt32*>(cursor);
                cursor += sizeof(RF_Type::UInt32);
                RF_Mem::AutoPointerArray<RF_Type::UInt8> data(bytes);
                RF_SysMem::Copy(data.Get(), cursor, bytes);
                cursor += bytes;
                RF_Draw::PixelFormat format;
                format.BitPerPixel = (bytes * 8) / (width * height);
                format.Channels.Resize(format.BitPerPixel / 8);
                if (format.BitPerPixel <= 32)
                {
                    RF_Draw::ChannelType typeMapper[] = {RF_Draw::ChannelType::Luminocity,
                                        RF_Draw::ChannelType::Red, RF_Draw::ChannelType::Green,
                                        RF_Draw::ChannelType::Blue, RF_Draw::ChannelType::Alpha};
                    for(auto i = 0; i < format.Channels.Count(); ++i)
                    {
                        format.Channels(i).Bits = 8;
                        format.Channels(i).Type = typeMapper[i + (format.BitPerPixel == 8 ? 0 : 1)];
                    }
                    RF_Draw::Image img;
                    img.Initialize(width, height, 1, format, data);
                    PathVisitor.AddImage(currentPosition, dimension, img);
                }
                break;
            }
            default:
                PathVisitor.Error();
                return;
            }
        } while (cursor != lastByte);
    }
    PathVisitor.Finalize();
}

RF_Type::UInt32 Path2D::GetHash() const
{
    return m_Hash;
}

Fill::Fill()
:Color(1,1,1,1)
{

}

Stroke::Stroke()
:Color(1,1,1,1)
,Width(1)
{

}

}