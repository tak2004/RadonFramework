#include <RadonFramework/precompiled.hpp>
#include "OpenGLRenderer.hpp"
#include "OpenGL.hpp"
#include "RadonFramework/Drawing/AbstractCanvas.hpp"
#include "RadonFramework/Drawing/BasicRenderFunction.hpp"

namespace RadonFramework::Drawing {

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
    // ui
    m_ShaderPool(0).Bind();
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
    m_SharedTransformUniforms.ModelViewProjection = m_Projection.GetMatrix(RF_Geo::Viewtype::View3D) *m_SharedTransformUniforms.ModelView;
    m_SharedTransformUniforms.UIProjection = m_Projection.GetMatrix(RF_Geo::Viewtype::View2D);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_SharedUBO);
    glNamedBufferSubData(m_SharedUBO, 0, sizeof(SharedTransformUniforms), &m_SharedTransformUniforms);
}

void GL45GenerateBuffer(void* Command)
{    
    GenerateBuffer* cmd = reinterpret_cast<GenerateBuffer*>(Command);
    glCreateBuffers(1, cmd->Buffer);
    glBindBuffer(GL_ARRAY_BUFFER, *cmd->Buffer);
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

template<class T>
class Factory
{
public:
    union Slot
    {
        T UsedObject;
        Slot* FreeObject;
    };

    static T* Get(RF_Type::UInt32 ID)
    {
        T* result = nullptr;
        if(ID < ObjectCount)
        {
            result = reinterpret_cast<T*>(Objects + ID);
        }
        return result;
    }
    static RF_Type::UInt32 Create()
    {
        RF_Type::UInt32 obj;
        if(Free == nullptr)
        {
            // resize pool
            RF_Type::UInt32 newSize = ObjectCount == 0 ? 512 : ObjectCount * 2;
            Slot* newPool = new Slot[newSize];
            RF_SysMem::Copy(newPool, Objects, sizeof(Slot)*ObjectCount);
            delete[] Objects;
            Objects = newPool;
            for(RF_Type::UInt32 i = ObjectCount; i < newSize; ++i)
            {
                Objects[i].FreeObject = Free;
                Free = Objects + i;
            }
            ObjectCount = newSize;
        }
        obj = Free - Objects;
        Free = Free->FreeObject;
        return obj;
    }
    static void Destroy(RF_Type::UInt32 ID)
    {
        if(ID < ObjectCount)
        {
            Objects[ID].FreeObject = Free;
            Free = Objects + ID;
        }
    }
private:
    static Slot* Objects;
    static RF_Type::UInt32 ObjectCount;
    static Slot* Free;
};

struct GLMaterial
{
    RF_Type::UInt32 ProgramID;
    RF_Type::Bool Blending;
};

typedef Factory<GLMaterial> MaterialFactory;
MaterialFactory::Slot* MaterialFactory::Objects = nullptr;
MaterialFactory::Slot* MaterialFactory::Free = nullptr;
RF_Type::UInt32 MaterialFactory::ObjectCount = 0;

struct GLObject
{
    RF_Type::UInt32 MaterialId;
    RF_Type::UInt32 VAO;
    RF_Type::UInt32 Buffers;
};

typedef Factory<GLObject> GLObjectFactory;
GLObjectFactory::Slot* GLObjectFactory::Objects = nullptr;
GLObjectFactory::Slot* GLObjectFactory::Free = nullptr;
RF_Type::UInt32 GLObjectFactory::ObjectCount = 0;

void GLAssignBufferToObject(void* Command)
{
    AssignBufferToObject* cmd = reinterpret_cast<AssignBufferToObject*>(Command);
    GLObject* obj = GLObjectFactory::Get(*cmd->Object);

    glBindVertexArray(obj->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, *cmd->Buffer);
    glVertexAttribPointer(obj->Buffers, cmd->Stride, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(obj->Buffers);
    ++obj->Buffers;
}

void GLGenerateObject(void* Command)
{
    GenerateObject* cmd = reinterpret_cast<GenerateObject*>(Command);
    *cmd->Object = GLObjectFactory::Create();
    GLObject* obj = GLObjectFactory::Get(*cmd->Object);
    obj->MaterialId = *cmd->Material;
    obj->Buffers = 0;
    obj->VAO = 0;
    glGenVertexArrays(1, &obj->VAO);
}

void GLDestroyObject(void* Command)
{
}

void GLRenderObject(void* Command)
{
    RenderObject* cmd = reinterpret_cast<RenderObject*>(Command);
    GLObject* obj = GLObjectFactory::Get(*cmd->Object);
    GLMaterial* mat = MaterialFactory::Get(obj->MaterialId);
    if(mat->Blending)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    else
    {
        glDisable(GL_BLEND);
    }
    glUseProgram(mat->ProgramID);
    glBindVertexArray(obj->VAO);
    if (cmd->ElementType == RF_Draw::RenderObject::PointSprites)
        glDrawArrays(GL_POINTS, 0, cmd->Elements);
    else
        glDrawArrays(GL_TRIANGLES, 0, cmd->Elements);
}

void GLGenerateMaterial(void* Command)
{
    GenerateMaterial* cmd = reinterpret_cast<GenerateMaterial*>(Command);
    *cmd->Material = MaterialFactory::Create();
    GLMaterial* mat = MaterialFactory::Get(*cmd->Material);
    mat->ProgramID = *cmd->Program;
    mat->Blending = cmd->Blending;
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

GLenum Channel2GLInternalFormat(const GenerateTexture& Command)
{
    GLenum result;
    switch(Command.Channels)
    {
        case 1:
            result = GL_R8;
            break;
        case 3:
            result = GL_RGB8;
            break;
        default:
            result = GL_RGBA8;
            break;
    }
    return result;
}

GLenum Channel2GLFormat(const GenerateTexture& Command)
{
    GLenum result;
    switch(Command.Channels)
    {
        case 1:
            result = GL_RED;
            break;
        case 2:
            result = GL_RG;
            break;
        case 3:
            result = GL_RGB;
            break;
        case 4:
            result = GL_RGBA;
            break;
        default:
            result = GL_RGBA;
            break;
    }
    return result;
}

void GLGenerateTexture(void* Command)
{
    GenerateTexture* cmd = reinterpret_cast<GenerateTexture*>(Command);
    glCreateTextures(GL_TEXTURE_2D,1, cmd->Texture);
    auto internalFormat = Channel2GLInternalFormat(*cmd);
    auto format = Channel2GLFormat(*cmd);
    glTextureStorage2D(*cmd->Texture, 1, internalFormat, cmd->Width, cmd->Height);
    glTextureSubImage2D(*cmd->Texture, 0, 0, 0, cmd->Width, cmd->Height, format, GL_UNSIGNED_BYTE, cmd->Data);
    glBindTextureUnit(0, *cmd->Texture);
}

void GLUpdateTexture(void* Command)
{
    UpdateTexture* cmd = reinterpret_cast<UpdateTexture*>(Command);
    glTextureSubImage2D(*cmd->Texture, 0, 0, 0, cmd->Width, cmd->Height, GL_RGBA, GL_UNSIGNED_BYTE, cmd->Data);
}

void GLDestroyTexture(void* Command)
{
    DestroyTexture* cmd = reinterpret_cast<DestroyTexture*>(Command);
    glDeleteTextures(1,cmd->Texture);
    *cmd->Texture = 0;
}

void GLAssignTextureToMaterial(void* Command)
{
    AssignTextureToMaterial* cmd = reinterpret_cast<AssignTextureToMaterial*>(Command);
    
}

AbstractRenderer::Dispatcher OpenGLRenderer::GetGeneralPurposeDispatcher(const BasicRenderFunctionType Identifier) const
{
    AbstractRenderer::Dispatcher result = nullptr;
    switch(Identifier)
    {
        case BasicRenderFunctionType::DestroyObject:
            result = GLDestroyObject;
            break;
        case BasicRenderFunctionType::GenerateObject:
            result = GLGenerateObject;
            break;
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
        case BasicRenderFunctionType::AssignBufferToObject:
            result = GLAssignBufferToObject;
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
        case BasicRenderFunctionType::GenerateTexture:
            result = GLGenerateTexture;
            break;
        case BasicRenderFunctionType::UpdateTexture:
            result = GLUpdateTexture;
            break;
        case BasicRenderFunctionType::DestroyTexture:
            result = GLDestroyTexture;
            break;
        case BasicRenderFunctionType::AssignTextureToMaterial:
            result = GLAssignTextureToMaterial;
            break;
    }
    return result;
}

AbstractRenderer::Dispatcher OpenGLRenderer::GetCustomDispatcher(const RF_Type::UInt32 Identifier) const
{
    return nullptr;
}

void OpenGLRenderer::OpenGLPath2DTriangulation::AddText(
    const RF_Geo::Point2Df& Position, const RF_Type::String& Text)
{
    
}

}