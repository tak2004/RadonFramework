#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/MeshGenerator2D.hpp"
#include "RadonFramework/Drawing/NativeShape.hpp"
#include "RadonFramework/Drawing/Path2D.hpp"
#include "RadonFramework/Drawing/CommandBuffer.hpp"
#include "RadonFramework/Math/Geometry/Vector.hpp"
#include "RadonFramework/backend/GL/OpenGLConstants.hpp"

namespace RadonFramework { namespace Drawing {

void MeshGenerator2D::Tesselate()
{

}

void AddEdge(RF_Collect::List<RF_Geo::Vec3f> &Triangles, 
             RF_Geo::Point2Df& Point0, RF_Geo::Point2Df& Point1/*,
             RF_Geo::Point2Df& Tangent0, RF_Geo::Point2Df& Tangent1*/)
{
    RF_Geo::Vec3f vertex;
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

void EndPath(RF_Collect::List<RF_Geo::Vec3f> &Triangles, RF_Geo::Point2Df& SegmentStart,
             RF_Geo::Point2Df& CurrentPosition)
{
    AddEdge(Triangles, SegmentStart, CurrentPosition);
}

void LineTo(RF_Collect::List<RF_Geo::Vec3f> &Triangles, 
            RF_Geo::Point2Df& SegmentStart, RF_Geo::Point2Df& CurrentPosition)
{
    AddEdge(Triangles, SegmentStart, CurrentPosition);
}

RF_Mem::AutoPointer<NativeShape> MeshGenerator2D::Generate(const Path2D& Path) const
{
    RF_Mem::AutoPointer<NativeShape> result;

    if(Path.Data().Count())
    {
        RF_Type::UInt8* cursor = Path.Data().Get();
        RF_Type::UInt8* lastByte = Path.Data().Get() + Path.Data().Count();
        RF_Collect::List<RF_Geo::Vec3f> triangles;
        Path2D::Command::Type previousSegment = Path2D::Command::MoveTo;
        RF_Geo::Point2Df currentPosition, lastPositionOfPreviousSegment,
            firstPositionOfSegment;
        RF_Type::Bool subpathHasGeometry = false;
        do
        {
            switch(*cursor)
            {
            case Path2D::Command::LineTo:
            {
                ++cursor;

                currentPosition = *reinterpret_cast<RF_Geo::Point2Df*>(cursor);
                cursor += sizeof(RF_Geo::Point2Df);

                LineTo(triangles, lastPositionOfPreviousSegment, currentPosition);
                lastPositionOfPreviousSegment = currentPosition;
                break;
            }
            case Path2D::Command::MoveTo:
            {
                ++cursor;

                if(previousSegment != Path2D::Command::MoveTo &&
                   previousSegment != Path2D::Command::Close)
                {
                    EndPath(triangles, lastPositionOfPreviousSegment, currentPosition);
                }

                currentPosition = *reinterpret_cast<RF_Geo::Point2Df*>(cursor);
                firstPositionOfSegment = currentPosition;
                lastPositionOfPreviousSegment = currentPosition;
                cursor += sizeof(RF_Geo::Point2Df);
                break;
            }
            case Path2D::Command::Close:
            {
                EndPath(triangles, lastPositionOfPreviousSegment, firstPositionOfSegment);
                lastPositionOfPreviousSegment = firstPositionOfSegment;
                ++cursor;
                break;
            }
            default:
                return result;
            }
        } while(cursor != lastByte);

        CommandBuffer cmdBuffer;
        CommandBuffer::HandleList buffer = cmdBuffer.ReserveHandleList();
        CommandBuffer::DataStream dataStream = cmdBuffer.ReserveDataStream();
        cmdBuffer.Call<GLFunctions::CreateBuffers>(1, buffer);
        cmdBuffer.Call<GLFunctions::BufferData>(static_cast<RF_Type::UInt32>(RF_GL::GL_ARRAY_BUFFER),
            triangles.Count() * sizeof(RF_Geo::Vec3f), dataStream,
            static_cast<RF_Type::UInt32>(RF_GL::GL_STATIC_DRAW));

        cmdBuffer.Finalize();

        result = RF_Mem::AutoPointer<NativeShape>(new NativeShape);
        result->AddState(cmdBuffer.ReleaseData());
    }
    return result;
}

}
}