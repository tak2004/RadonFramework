#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Draw2D.hpp"
#include "RadonFramework/Math/Geometry/Point2D.hpp"
#include "RadonFramework/Drawing/Path2D.hpp"
#include "RadonFramework/Drawing/Text2D.hpp"
#include "RadonFramework/Drawing/MeshGenerator2D.hpp"
#include "RadonFramework/backend/GL/OpenGLConstants.hpp"
#include "RadonFramework/Drawing/CommandBuffer.hpp"

namespace RadonFramework { namespace Drawing {

Draw2D::Draw2D()
{

}

Draw2D::~Draw2D()
{

}

RF_Mem::AutoPointer<Path2D> Draw2D::BeginPath()const
{
    RF_Mem::AutoPointer<Path2D> result(new Path2D);
    return result;
}

RF_Mem::AutoPointer<NativeShape> Draw2D::EndPath(Path2D& Path)const
{
    RF_Mem::AutoPointer<NativeShape> result;
    Path.Finalize();
    result = m_MeshGenerator->Generate(Path);

    CommandBuffer cmdBuffer;
    auto buffers = cmdBuffer.AddVariable<RF_Type::UInt32>(2);
    auto vao = cmdBuffer.AddVariable<RF_Type::UInt32>(1);
    auto vertexShader = cmdBuffer.AddVariable<RF_Type::UInt32>(1);
    auto vertexShaderSize = cmdBuffer.AddVariable<RF_Type::Size>(1);
    auto vertexShaderStream = cmdBuffer.AddVariable<void*>(1);
    auto fragmentShader = cmdBuffer.AddVariable<RF_Type::UInt32>(1);
    auto fragmentShaderSize = cmdBuffer.AddVariable<RF_Type::Size>(1);
    auto fragmentShaderStream = cmdBuffer.AddVariable<void*>(1);
    auto shader = cmdBuffer.AddVariable<RF_Type::UInt32>(1);
    auto vertexDataSize = cmdBuffer.AddVariable<RF_Type::Size>(1, true, "vertexdatasize");
    auto indexDataSize = cmdBuffer.AddVariable<RF_Type::Size>(1, true, "indexdatasize");
    auto vertexStream = cmdBuffer.AddVariable<void*>(1, true, "vertexdata");
    auto indexStream = cmdBuffer.AddVariable<void*>(1, true, "indexdata");
    auto isCompiled = cmdBuffer.AddVariable<RF_Type::Int32>(2,true, "isCompiled");
    auto isLinked = cmdBuffer.AddVariable<RF_Type::Int32>(1, true, "isLinked");

    cmdBuffer.State("createmesh");
    cmdBuffer.Call<GLFunctions::CreateBuffers>(2, buffers.Ptr());
    cmdBuffer.Call<GLFunctions::NamedBufferData>(buffers, vertexDataSize,
                                                 vertexStream, static_cast<RF_Type::UInt32>(RF_GL::GL_STATIC_DRAW));
    cmdBuffer.Call<GLFunctions::NamedBufferData>(buffers[1], indexDataSize,
                                                 indexStream, static_cast<RF_Type::UInt32>(RF_GL::GL_STATIC_DRAW));
    cmdBuffer.Call<GLFunctions::CreateVertexArrays>(1, vao.Ptr());
    cmdBuffer.Call<GLFunctions::VertexArrayElementBuffer>(vao, buffers[1]);
    cmdBuffer.Call<GLFunctions::EnableVertexArrayAttrib>(vao, 0);
    cmdBuffer.Call<GLFunctions::VertexArrayAttribFormat>(vao, 0, 3, static_cast<RF_Type::UInt32>(RF_GL::GL_FLOAT), static_cast<RF_Type::UInt32>(RF_GL::GL_FALSE), 0);
    cmdBuffer.Call<GLFunctions::VertexArrayVertexBuffer>(vao, 0, buffers, 0, 0);
    cmdBuffer.Call<GLFunctions::VertexArrayAttribBinding>(vao, 0, 0);

    cmdBuffer.State("destroymesh");
    cmdBuffer.Call<GLFunctions::DeleteVertexArrays>(vao.Ptr());
    cmdBuffer.Call<GLFunctions::DeleteBuffers>(buffers.Ptr());

    cmdBuffer.State("compileshaders");
    cmdBuffer.Call<GLFunctions::CreateShader>(RF_GL::GL_VERTEX_SHADER);
    cmdBuffer.CopyResult(vertexShader);
    cmdBuffer.Call<GLFunctions::ShaderSource>(vertexShader, 1, vertexShaderStream.Ptr(), vertexShaderSize.Ptr());
    cmdBuffer.Call<GLFunctions::CompileShader>(vertexShader);
    cmdBuffer.Call<GLFunctions::GetShaderiv>(vertexShader, RF_GL::GL_COMPILE_STATUS, isCompiled.Ptr());
    cmdBuffer.Call<GLFunctions::CreateShader>(RF_GL::GL_FRAGMENT_SHADER);
    cmdBuffer.CopyResult(fragmentShader);
    cmdBuffer.Call<GLFunctions::ShaderSource>(fragmentShader, 1, fragmentShaderStream.Ptr(), fragmentShaderSize.Ptr());
    cmdBuffer.Call<GLFunctions::CompileShader>(fragmentShader);
    cmdBuffer.Call<GLFunctions::GetShaderiv>(fragmentShader, RF_GL::GL_COMPILE_STATUS, isCompiled[1].Ptr());
    
    cmdBuffer.State("linkprogram");
    cmdBuffer.Call<GLFunctions::CreateProgram>(1, shader.Ptr());
    cmdBuffer.CopyResult(shader);
    cmdBuffer.Call<GLFunctions::AttachShader>(shader, vertexShader);
    cmdBuffer.Call<GLFunctions::AttachShader>(shader, fragmentShader);
    cmdBuffer.Call<GLFunctions::LinkProgram>(shader);
    cmdBuffer.Call<GLFunctions::GetProgramiv>(shader, RF_GL::GL_LINK_STATUS, isLinked.Ptr());
    cmdBuffer.Call<GLFunctions::DetachShader>(shader, vertexShader);
    cmdBuffer.Call<GLFunctions::DetachShader>(shader, fragmentShader);
    cmdBuffer.Call<GLFunctions::DeleteShader>(vertexShader);
    cmdBuffer.Call<GLFunctions::DeleteShader>(fragmentShader);

    cmdBuffer.State("deleteshader");
    cmdBuffer.Call<GLFunctions::DeleteShader>(vertexShader);
    cmdBuffer.Call<GLFunctions::DeleteShader>(vertexShader);

    cmdBuffer.State("deleteprogram");
    cmdBuffer.Call<GLFunctions::DeleteProgram>(shader.Ptr());

    // z-pass
    cmdBuffer.State("zpass");
    cmdBuffer.Call<RF_Draw::GLFunctions::UseProgram>(shader);
    cmdBuffer.Call<RF_Draw::GLFunctions::BindVertexArray>(vao);
    cmdBuffer.Call<RF_Draw::GLFunctions::DrawArrays>(static_cast<RF_Type::UInt32>(RF_GL::GL_TRIANGLES), 0, 3);

    cmdBuffer.Finalize();
    result->AssignByteCode(cmdBuffer.ReleaseData());

    result->MapVariable("shader", m_UIShader);
    return result;
}

RF_Mem::AutoPointer<Text2D> Draw2D::BeginText(const FontDescription& WhichFont, 
    const RF_Type::String& Text)const
{
    RF_Mem::AutoPointer<Path2D> result(new Path2D);
    return result;
}

RF_Mem::AutoPointer<NativeShape> Draw2D::EndText(Text2D& Text)const
{
    RF_Mem::AutoPointer<NativeShape> result;// = m_MeshGenerator->Generate(Path);
    return result;
}

void Draw2D::DrawPath(const NativeShape& Instance, const RF_Geo::Point2Df& Position,
    RF_Type::Float32 Angle/*=0.0f*/)
{

}

void Draw2D::DrawText(const NativeShape& Instance, const RF_Geo::Point2Df& Position,
    RF_Type::Float32 Angle /*= 0.0f*/)
{

}

void Draw2D::SetMeshGenerator(const MeshGenerator2D& Instance)
{
    m_MeshGenerator = &Instance;
}

const MeshGenerator2D* Draw2D::GetMeshGenerator() const
{
    return m_MeshGenerator;
}

} }