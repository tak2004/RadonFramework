#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/MeshGenerator2D.hpp"
#include "RadonFramework/Drawing/NativeShape.hpp"
#include "RadonFramework/Drawing/Path2D.hpp"
#include "RadonFramework/Math/Geometry/Vector.hpp"

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

        result = RF_Mem::AutoPointer<NativeShape>(new NativeShape);

        RF_Mem::AutoPointerArray<RF_Type::UInt8> vertexStream(triangles.Count()*sizeof(RF_Geo::Vec3f));
        RF_Mem::AutoPointerArray<RF_Type::UInt8> indicesStream(triangles.Count()*sizeof(RF_Type::UInt16));

        result->MapVariable(RF_HASH("vertexdatasize"), vertexStream.Count());
        result->MapVariable(RF_HASH("indexdatasize"), indicesStream.Count());
        result->MapVariable(RF_HASH("vertexdata"), vertexStream.Get());
        result->MapVariable(RF_HASH("indexdata"), indicesStream.Get());
        result->AssignDataStream(vertexStream);
        result->AssignDataStream(indicesStream);
    }
    return result;
}

}
}