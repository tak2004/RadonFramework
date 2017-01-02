#include <RadonFramework/precompiled.hpp>
#include "OpenGLRenderer.hpp"
#include "OpenGL.hpp"
#include "RadonFramework/Drawing/AbstractCanvas.hpp"
#include "RadonFramework/Drawing/BasicRenderFunction.hpp"

namespace RadonFramework { namespace Drawing {

OpenGLRenderer::OpenGLRenderer()
:m_NextId(1)
{

}

void OpenGLRenderer::Generate(const RF_Geo::Size2Df& FrameSize)
{
    m_ShaderPool.Resize(1);
    m_ShaderPool(0).Generate();

    glCreateBuffers(1, &m_SharedUBO);
    glNamedBufferData(m_SharedUBO, sizeof(SharedTransformUniforms), &m_SharedTransformUniforms, GL_STREAM_DRAW);

    ResizedViewport(FrameSize);
}

void OpenGLRenderer::StartFrame()
{
    glClearColor(0.2,0.2,0.2,1.0);
    m_Canvas->Clear();
    m_ShaderPool(0).Bind();
}

void OpenGLRenderer::EndFrame()
{
    m_Canvas->SwapBuffer();
}

RF_Type::UInt32 OpenGLRenderer::Process(RF_Type::UInt32 EntityId, const RF_Draw::Path2D& Path)
{
    if(EntityId != 0)
    {
        OpenGLModel* data;
        m_Objects.Get(EntityId, reinterpret_cast<void*&>(data));
        if(data->Hash == Path.GetHash())
        {

        }
        else
        {
            Path.Visit(m_Tesselator);
            auto& vertices = m_Tesselator.GetVertices();
            auto& colors = m_Tesselator.GetColors();
            if(vertices.Count())
            {
                data->Update((RF_Type::Float32*)&vertices(0), (RF_Type::Float32*)&colors(0), vertices.Count(), 2);
            }
            else
            {
                data->Update(0, 0, 0);
            }
            data->Hash = Path.GetHash();
        }
    }
    else
    {
        Path.Visit(m_Tesselator);
        auto& vertices = m_Tesselator.GetVertices();
        auto& colors = m_Tesselator.GetColors();
        if(vertices.Count())
        {
            RF_Mem::AutoPointer<OpenGLModel> obj(new OpenGLModel);
            obj->Generate((RF_Type::Float32*)&vertices(0), (RF_Type::Float32*)&colors(0), vertices.Count(), 2);
            m_ObjectPool.Resize(m_ObjectPool.Count() + 1);
            EntityId = m_NextId;
            m_ObjectPool(m_ObjectPool.Count() - 1) = EntityId;
            obj->Hash = Path.GetHash();
            m_Objects.Add(EntityId, obj.Release());
            ++m_NextId;
        }
    }
    return EntityId;
}

void OpenGLRenderer::Draw()
{
    for(RF_Type::Size i = 0; i < m_Buckets.Count(); ++i)
    {
        m_Buckets(i).Submit();
    }
    for(RF_Type::Size i = 0; i < m_ObjectPool.Count(); ++i)
    {   
        OpenGLModel* obj = 0;
        m_Objects.Get(m_ObjectPool(i), reinterpret_cast<void*&>(obj));
        obj->Bind();
        obj->Draw();
    }
}

void OpenGLRenderer::SetCanvas(RF_Draw::AbstractCanvas& Canvas)
{
    m_Canvas = &Canvas;
}

void OpenGLRenderer::ResizedViewport(const RF_Geo::Size2Df& NewSize)
{
    m_Projection.SetSize(NewSize);
    m_SharedTransformUniforms.ModelView = m_Camera.GetMatrix();
    m_SharedTransformUniforms.ModelViewProjection = m_Projection.GetMatrix(RF_Geo::Viewtype::View3D) * m_SharedTransformUniforms.ModelView;
    m_SharedTransformUniforms.UIProjection = m_Projection.GetMatrix(RF_Geo::Viewtype::View2D);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_SharedUBO);
    glNamedBufferSubData(m_SharedUBO, 0, sizeof(SharedTransformUniforms), &m_SharedTransformUniforms);
}

void GL45GenerateBuffer(void* Command)
{    
    GenerateBuffer* cmd = reinterpret_cast<GenerateBuffer*>(Command);
    glCreateBuffers(1, cmd->Buffer);
    glBufferData(GL_ARRAY_BUFFER, cmd->ByteSize, nullptr, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, cmd->ByteSize, cmd->Data);
}

void GLDestroyBuffer(void* Command)
{
    DestroyBuffer* cmd = reinterpret_cast<DestroyBuffer*>(Command);
    glDeleteBuffers(1, cmd->Buffer);
    *cmd->Buffer = 0;
}

void GLUpdateBuffer(void* Command)
{
    UpdateBuffer* cmd = reinterpret_cast<UpdateBuffer*>(Command);
    glBindBuffer(GL_ARRAY_BUFFER, *cmd->Buffer);
    glBufferData(GL_ARRAY_BUFFER, cmd->ByteSize, nullptr, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, cmd->ByteSize, cmd->Data);
}

void BindMaterial(RF_Type::UInt32 Id)
{
    glUseProgram(Id);
}

void GLRenderObject(void* Command)
{
    RenderObject* cmd = reinterpret_cast<RenderObject*>(Command);

    BindMaterial(*cmd->Material);
    glBindBuffer(GL_ARRAY_BUFFER,*cmd->Buffer);
    glDrawArrays(GL_POINTS, 0, cmd->Elements);
}

void GLGenerateMaterial(void* Command)
{
    GenerateMaterial* cmd = reinterpret_cast<GenerateMaterial*>(Command);
    *cmd->Material = *cmd->Program;
}

void GLDestroyMaterial(void* Command)
{

}

void GLGenerateProgram(void* Command)
{
    GenerateProgram* cmd = reinterpret_cast<GenerateProgram*>(Command);
    *cmd->Program = 0;
    if (cmd->FragmentData != nullptr && cmd->VertexData != nullptr)
    {
        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &cmd->VertexData, nullptr);
        glCompileShader(vs);
        GLint isCompiled = 0;
        glGetShaderiv(vs, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);
            RF_Collect::Array<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(vs, maxLength, &maxLength, &errorLog(0));
            RF_IO::LogError("Vertex-Shader:%s\n", &errorLog(0));
            glDeleteShader(vs);
            return;
        }

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &cmd->FragmentData, NULL);
        glCompileShader(fs);
        glGetShaderiv(fs, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);
            RF_Collect::Array<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(fs, maxLength, &maxLength, &errorLog(0));
            RF_IO::LogError("Fragment-Shader:%s\n", &errorLog(0));
            glDeleteShader(fs);
            glDeleteShader(vs);
            return;
        }

        GLuint program = glCreateProgram();
        glAttachShader(program, fs);
        glAttachShader(program, vs);
        glLinkProgram(program);
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
        if(isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
            RF_Collect::Array<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog(0));
            RF_IO::LogError("Fragment-Shader:%s\n", &infoLog(0));
            glDeleteProgram(program);
            glDeleteShader(vs);
            glDeleteShader(fs);
            return;
        }
        glDetachShader(program, vs);
        glDetachShader(program, fs);
        glDeleteShader(vs);
        glDeleteShader(fs);
        *cmd->Program = program;
    }
}

void GLDestroyProgram(void* Command)
{
    DestroyProgram* cmd = reinterpret_cast<DestroyProgram*>(Command);
    glDeleteProgram(*cmd->Program);
    *cmd->Program = 0;
}

AbstractRenderer::Dispatcher OpenGLRenderer::GetGeneralPurposeDispatcher(const BasicRenderFunctionType Identifier) const
{
    AbstractRenderer::Dispatcher result = nullptr;
    switch(Identifier)
    {
        case BasicRenderFunctionType::RenderObject:
            result = GLRenderObject;
            break;
        case BasicRenderFunctionType::GenerateBuffer:
            result = GL45GenerateBuffer;
            break;
        case BasicRenderFunctionType::DestroyBuffer:
            result = GLDestroyBuffer;
            break;
        case BasicRenderFunctionType::UpdateBuffer:
            result = GLUpdateBuffer;
            break;
        case BasicRenderFunctionType::GenerateMaterial:
            result = GLGenerateMaterial;
            break;
        case BasicRenderFunctionType::DestroyMaterial:
            result = GLDestroyMaterial;
            break;
        case BasicRenderFunctionType::GenerateProgram:
            result = GLGenerateProgram;
            break;
        case BasicRenderFunctionType::DestroyProgram:
            result = GLDestroyProgram;
            break;
    }
    return result;
}

AbstractRenderer::Dispatcher OpenGLRenderer::GetCustomDispatcher(const RF_Type::UInt32 Identifier) const
{
    return nullptr;
}

} }