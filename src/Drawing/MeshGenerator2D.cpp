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

        result = RF_Mem::AutoPointer<NativeShape>(new NativeShape);

        RF_Mem::AutoPointerArray<RF_Type::UInt8> vertexStream(triangles.Count()*sizeof(RF_Geo::Vec3f));
        RF_Mem::AutoPointerArray<RF_Type::UInt8> indicesStream(triangles.Count()*sizeof(RF_Type::UInt16));


        CommandBuffer cmdBuffer;
        auto buffers = cmdBuffer.AddVariable<RF_Type::UInt32>(2);
        auto vao = cmdBuffer.AddVariable<RF_Type::UInt32>(1);
        auto shader = cmdBuffer.AddVariable<RF_Type::UInt32>(1, true, "shader");
        auto vertexDataSize = cmdBuffer.AddVariable<RF_Type::Size>(1, true, "vertexdatasize");
        auto indexDataSize = cmdBuffer.AddVariable<RF_Type::Size>(1, true, "indexdatasize");
        auto vertexStream = cmdBuffer.AddVariable<void*>(1, true, "vertexdata");
        auto indexStream = cmdBuffer.AddVariable<void*>(1, true, "indexdata");

        // startup
        cmdBuffer.State("startup");
        cmdBuffer.Call<GLFunctions::CreateBuffers>(2, buffers.Ptr());
        cmdBuffer.Call<GLFunctions::NamedBufferData>(buffers, vertexDataSize,
            vertexStream, static_cast<RF_Type::UInt32>(RF_GL::GL_STATIC_DRAW));
        cmdBuffer.Call<GLFunctions::NamedBufferData>(buffers[1], indexDataSize,
            indexStream, static_cast<RF_Type::UInt32>(RF_GL::GL_STATIC_DRAW));
        cmdBuffer.Call<GLFunctions::CreateVertexArrays>(1, vao.Ptr());
        cmdBuffer.Call<GLFunctions::VertexArrayElementBuffer>(vao, buffers[1]);
        cmdBuffer.Call<GLFunctions::EnableVertexArrayAttrib>(vao, 0);
        cmdBuffer.Call<GLFunctions::VertexArrayAttribFormat>(vao, 0, 3, static_cast<RF_Type::UInt32>(RF_GL::GL_FLOAT), static_cast<RF_Type::UInt32>(RF_GL::GL_FALSE), 0);
        cmdBuffer.Call<GLFunctions::VertexArrayVertexBuffer>(vao, 0, buffers,0 ,0);
        cmdBuffer.Call<GLFunctions::VertexArrayAttribBinding>(vao, 0, 0);
        
        // shutdown
        cmdBuffer.State("shutdown");
        cmdBuffer.Call<GLFunctions::DeleteVertexArrays>(vao.Ptr());
        cmdBuffer.Call<GLFunctions::DeleteBuffers>(buffers.Ptr());
        
        // z-pass
        cmdBuffer.State("zpass");
        cmdBuffer.Call<RF_Draw::GLFunctions::UseProgram>(shader);
        cmdBuffer.Call<RF_Draw::GLFunctions::BindVertexArray>(vao);
        cmdBuffer.Call<RF_Draw::GLFunctions::DrawArrays>(static_cast<RF_Type::UInt32>(RF_GL::GL_TRIANGLES), 0, 3);
        
        cmdBuffer.Finalize();
        result->AssignByteCode(cmdBuffer.ReleaseData());
        result->MapVariable("vertexdatasize", vertexStream.Count());
        result->MapVariable("indexdatasize", indexStream.Count());
        result->MapVariable("vertexdata", vertexStream.Get());
        result->MapVariable("indexdata", indexStream.Get());
        result->AssignDataStream(vertexStream);
        result->AssignDataStream(indexStream);
    }
    return result;
}

}
}