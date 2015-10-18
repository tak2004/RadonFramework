#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/backend/OpenGL/OpenGLCanvas.hpp>
#include <RadonFramework/Drawing/GraphicDriverInformation.hpp>
#include <RadonFramework/backend/GL/glew.h>
#include <RadonFramework/backend/OpenGL/GraphicDriverInformationOpenGL.hpp>
#include "RadonFramework/Diagnostics/Debugging/Assert.hpp"
#include "RadonFramework/System/Threading/Mutex.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Drawing;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Memory;
using namespace RadonFramework;
using namespace RadonFramework::IO;

struct GLConstantData
{
    UInt32 GLConstant;
    const char* GLConstantName;
    OpenGLCapabilitiesType::Type Type;
    UInt32 ElementCount;//0 mean dynamic, get the number on runtime
};

#define GLCONSTANDNAME(GLCONSTNAME)\
    GLCONSTNAME,#GLCONSTNAME

GLConstantData GLConstantWrapper[OpenGLCapabilities::MAX]={
    {GLCONSTANDNAME(GL_ALIASED_POINT_SIZE_RANGE),OpenGLCapabilitiesType::GLFLOAT,2},
    {GLCONSTANDNAME(GL_ALIASED_LINE_WIDTH_RANGE),OpenGLCapabilitiesType::GLFLOAT,2},
    {GLCONSTANDNAME(GL_COLOR_MATRIX_STACK_DEPTH),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_COMPRESSED_TEXTURE_FORMATS),OpenGLCapabilitiesType::GLINT,0},
    {GLCONSTANDNAME(GL_DOUBLEBUFFER),OpenGLCapabilitiesType::GLBOOLEAN,1},
    {GLCONSTANDNAME(GL_LINE_WIDTH_GRANULARITY),OpenGLCapabilitiesType::GLFLOAT,1},
    {GLCONSTANDNAME(GL_LINE_WIDTH_RANGE),OpenGLCapabilitiesType::GLFLOAT,2},
    {GLCONSTANDNAME(GL_MAX_3D_TEXTURE_SIZE),OpenGLCapabilitiesType::GLINT,2},
    {GLCONSTANDNAME(GL_MAX_CLIENT_ATTRIB_STACK_DEPTH),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_ATTRIB_STACK_DEPTH),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_CLIP_PLANES),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_COLOR_MATRIX_STACK_DEPTH),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_CUBE_MAP_TEXTURE_SIZE),OpenGLCapabilitiesType::GLINT,2},
    {GLCONSTANDNAME(GL_MAX_DRAW_BUFFERS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_ELEMENTS_INDICES),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_ELEMENTS_VERTICES),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_EVAL_ORDER),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_LIGHTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_LIST_NESTING),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_MODELVIEW_STACK_DEPTH),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_NAME_STACK_DEPTH),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_PIXEL_MAP_TABLE),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_PROJECTION_STACK_DEPTH),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TEXTURE_COORDS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TEXTURE_IMAGE_UNITS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TEXTURE_LOD_BIAS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TEXTURE_SIZE),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TEXTURE_UNITS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_VARYING_FLOATS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_VERTEX_ATTRIBS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_VERTEX_UNIFORM_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_VIEWPORT_DIMS),OpenGLCapabilitiesType::GLINT,2},
    {GLCONSTANDNAME(GL_NUM_COMPRESSED_TEXTURE_FORMATS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_POINT_SIZE_GRANULARITY),OpenGLCapabilitiesType::GLFLOAT,1},
    {GLCONSTANDNAME(GL_POINT_SIZE_RANGE),OpenGLCapabilitiesType::GLFLOAT,2},
    {GLCONSTANDNAME(GL_SMOOTH_LINE_WIDTH_RANGE),OpenGLCapabilitiesType::GLFLOAT,2},
    {GLCONSTANDNAME(GL_SMOOTH_LINE_WIDTH_GRANULARITY),OpenGLCapabilitiesType::GLFLOAT,1},
    {GLCONSTANDNAME(GL_SMOOTH_POINT_SIZE_RANGE),OpenGLCapabilitiesType::GLFLOAT,2},
    {GLCONSTANDNAME(GL_SMOOTH_POINT_SIZE_GRANULARITY),OpenGLCapabilitiesType::GLFLOAT,1},
    {GLCONSTANDNAME(GL_STEREO),OpenGLCapabilitiesType::GLBOOLEAN,1},
    {GLCONSTANDNAME(GL_SUBPIXEL_BITS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_ARRAY_TEXTURE_LAYERS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_RENDERBUFFER_SIZE),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_VIEWPORTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_VIEWPORT_SUBPIXEL_BITS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_VIEWPORT_BOUNDS_RANGE),OpenGLCapabilitiesType::GLINT,2},
    {GLCONSTANDNAME(GL_LAYER_PROVOKING_VERTEX),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TEXTURE_BUFFER_SIZE),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_RECTANGLE_TEXTURE_SIZE),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_PROGRAM_BINARY_FORMATS),OpenGLCapabilitiesType::GLINT,0},
    {GLCONSTANDNAME(GL_NUM_PROGRAM_BINARY_FORMATS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_SHADER_BINARY_FORMATS),OpenGLCapabilitiesType::GLINT,0},
    {GLCONSTANDNAME(GL_NUM_SHADER_BINARY_FORMATS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_SHADER_COMPILER),OpenGLCapabilitiesType::GLBOOLEAN,1},
    {GLCONSTANDNAME(GL_NUM_EXTENSIONS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAJOR_VERSION),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MINOR_VERSION),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_CONTEXT_FLAGS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_RENDERER),OpenGLCapabilitiesType::GLSTRING,1},
    {GLCONSTANDNAME(GL_SHADING_LANGUAGE_VERSION),OpenGLCapabilitiesType::GLSTRING,1},
    {GLCONSTANDNAME(GL_VENDOR),OpenGLCapabilitiesType::GLSTRING,1},
    {GLCONSTANDNAME(GL_VERSION),OpenGLCapabilitiesType::GLSTRING,1},
    {GLCONSTANDNAME(GL_MAX_VERTEX_UNIFORM_VECTORS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_VERTEX_UNIFORM_BLOCKS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_VERTEX_OUTPUT_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TESS_GEN_LEVEL),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_PATCH_VERTICES),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TESS_PATCH_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TESS_CONTROL_INPUT_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_GEOMETRY_UNIFORM_BLOCKS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_GEOMETRY_INPUT_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_GEOMETRY_OUTPUT_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_GEOMETRY_OUTPUT_VERTICES),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_GEOMETRY_SHADER_INVOCATIONS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_VERTEX_STREAMS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_FRAGMENT_UNIFORM_VECTORS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_FRAGMENT_UNIFORM_BLOCKS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_FRAGMENT_INPUT_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MIN_PROGRAM_TEXEL_OFFSET),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_PROGRAM_TEXEL_OFFSET),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_UNIFORM_BUFFER_BINDINGS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_UNIFORM_BLOCK_SIZE),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_COMBINED_UNIFORM_BLOCKS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_VARYING_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_VARYING_VECTORS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_SUBROUTINES),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_SAMPLE_MASK_WORDS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_COLOR_TEXTURE_SAMPLES),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_DEPTH_TEXTURE_SAMPLES),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_INTEGER_SAMPLES),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_SERVER_WAIT_TIMEOUT),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MIN_FRAGMENT_INTERPOLATION_OFFSET),OpenGLCapabilitiesType::GLFLOAT,1},
    {GLCONSTANDNAME(GL_MAX_FRAGMENT_INTERPOLATION_OFFSET),OpenGLCapabilitiesType::GLFLOAT,1},
    {GLCONSTANDNAME(GL_FRAGMENT_INTERPOLATION_OFFSET_BITS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_TRANSFORM_FEEDBACK_BUFFERS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_DUAL_SOURCE_DRAW_BUFFERS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_SAMPLE_BUFFERS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_SAMPLES),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_COLOR_ATTACHMENTS),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_MAX_SAMPLES),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_IMPLEMENTATION_COLOR_READ_TYPE),OpenGLCapabilitiesType::GLINT,1},
    {GLCONSTANDNAME(GL_IMPLEMENTATION_COLOR_READ_FORMAT),OpenGLCapabilitiesType::GLINT,1}
};

OpenGLCanvas::OpenGLCanvas()
:m_GraphicDriverInformation(0)
,m_GraphicDriverInformationOpenGL(0)
{
    m_Lock = AutoPointer<System::Threading::Mutex>(new System::Threading::Mutex());
}

const GraphicDriverInformation& OpenGLCanvas::GetGraphicDriverInformation()
{
    if (!m_GraphicDriverInformation)
    {
        GraphicDriverCapabilities caps;
        memset(&caps,0,sizeof(GraphicDriverCapabilities));

        const GraphicDriverInformationOpenGL& oglcaps=GetContextRelatedGraphicDriverInformation();
        caps.DoubleBuffer=oglcaps.Capabilities().IsAvaiable[OpenGLCapabilities::_GL_DOUBLEBUFFER];
        caps.MajorVersion=oglcaps.Capabilities().IsAvaiable[OpenGLCapabilities::_GL_MAJOR_VERSION]?
            oglcaps.Capabilities().Value[OpenGLCapabilities::_GL_MAJOR_VERSION].GLInt():0;
        caps.MinorVersion=oglcaps.Capabilities().IsAvaiable[OpenGLCapabilities::_GL_MINOR_VERSION]?
            oglcaps.Capabilities().Value[OpenGLCapabilities::_GL_MINOR_VERSION].GLInt():0;
        caps.Renderer=oglcaps.Capabilities().IsAvaiable[OpenGLCapabilities::_GL_RENDERER]?
            oglcaps.Capabilities().Value[OpenGLCapabilities::_GL_RENDERER].GLString():"not available";
        UInt32 sm=0;
        if (oglcaps.Capabilities().IsAvaiable[OpenGLCapabilities::_GL_SHADING_LANGUAGE_VERSION])
        {//all unsupported glslang version return sm with the value 0
            //look at http://www.opengl.org/wiki/Detecting_the_Shader_Model for details
            String slv=oglcaps.Capabilities().Value[OpenGLCapabilities::_GL_SHADING_LANGUAGE_VERSION].GLString();
            String majorstr=slv.SubString(0,1);
            String minorstr=slv.SubString(2,2);
            UInt32 major=0;
            UInt32 minor=0;
            if (majorstr.IsNumber())
                major<<majorstr;
            if (minorstr.IsNumber())
                minor<<minorstr;
            if (major>=1 && major<=3)
            {
                if (major==1 && minor<30)
                    sm=1;
                else
                    sm=3;
                if (major==3 && minor>=30)
                    sm=4;
            }
            if (major==4 && minor>0)
                sm=5;
        }
        caps.ShaderModel=sm;
        caps.Stereo=oglcaps.Capabilities().IsAvaiable[OpenGLCapabilities::_GL_STEREO];
        caps.Vendor=oglcaps.Capabilities().IsAvaiable[OpenGLCapabilities::_GL_VENDOR]?
            oglcaps.Capabilities().Value[OpenGLCapabilities::_GL_VENDOR].GLString():"not available";
        caps.Version=oglcaps.Capabilities().IsAvaiable[OpenGLCapabilities::_GL_VERSION]?
            oglcaps.Capabilities().Value[OpenGLCapabilities::_GL_VERSION].GLString():"not available";

        m_GraphicDriverInformation=new GraphicDriverInformation(caps);
    }
    return *m_GraphicDriverInformation;
}

const GraphicDriverInformationOpenGL& OpenGLCanvas::GetContextRelatedGraphicDriverInformation()
{
    if (!m_GraphicDriverInformationOpenGL)
    {
        GraphicDriverCapabilitiesOpenGL caps;
        memset(&caps,0,sizeof(GraphicDriverCapabilitiesOpenGL));
        for (Core::Types::UInt32 i=0;i<OpenGLCapabilities::MAX;++i)
        {
            Core::Types::UInt32 elementcount=GLConstantWrapper[i].ElementCount;
            if (0==elementcount)
            {
                GLint count=0;
                switch (GLConstantWrapper[i].GLConstant)
                {
                    case GL_COMPRESSED_TEXTURE_FORMATS:
                        glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS,&count);
                        break;
                    case GL_PROGRAM_BINARY_FORMATS:
                        glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS,&count);
                        break;
                    case GL_SHADER_BINARY_FORMATS:
                        glGetIntegerv(GL_NUM_SHADER_BINARY_FORMATS,&count);
                        break;
                    default:
                        LogError("fixme: Unhandled constant(%s)",GLConstantWrapper[i].GLConstantName);
                }
                elementcount=count;
            }

            OpenGLCapability cap(GLConstantWrapper[i].Type, String::UnsafeStringCreation(GLConstantWrapper[i].GLConstantName), elementcount);
            const GLubyte* str=0;
            if (elementcount)
            {
                switch (GLConstantWrapper[i].Type)
                {
                    case OpenGLCapabilitiesType::GLBOOLEAN:
                        glGetBooleanv(GLConstantWrapper[i].GLConstant,(GLboolean*)cap.Ptr());
                        break;
                    case OpenGLCapabilitiesType::GLDOUBLE:
                        glGetDoublev(GLConstantWrapper[i].GLConstant,(GLdouble*)cap.Ptr());
                        break;
                    case OpenGLCapabilitiesType::GLFLOAT:
                        glGetFloatv(GLConstantWrapper[i].GLConstant,(GLfloat*)cap.Ptr());
                        break;
                    case OpenGLCapabilitiesType::GLINT:
                        glGetIntegerv(GLConstantWrapper[i].GLConstant,(GLint*)cap.Ptr());
                        break;
                    case OpenGLCapabilitiesType::GLINT64:
                        glGetInteger64v(GLConstantWrapper[i].GLConstant,(GLint64*)cap.Ptr());
                        break;
                    case OpenGLCapabilitiesType::GLSTRING:
                        str=glGetString(GLConstantWrapper[i].GLConstant);
                        *reinterpret_cast<Core::Types::String*>(cap.Ptr())=String::UnsafeStringCreation(reinterpret_cast<const char*>(str));
                        break;
                    default:
                        Assert(false,"Global GLConstantWrapper array is corrupted.");
                }
            }
            caps.Value[i]=cap;
            caps.IsAvaiable[i]=glGetError()==GL_NO_ERROR;
        }

        AutoVector<String> ext;
        const char* pext=(const char*)glGetString(GL_EXTENSIONS);
        if (glGetError()==GL_NO_ERROR)
        {
            String extstr = String::UnsafeStringCreation(pext);
            AutoPointerArray<String> vec(extstr.Split(" "));
            for (UInt32 i=0;i<vec.Count();++i)
                ext.PushBack(AutoPointer<String>(new String(vec[i])));
        }

        m_GraphicDriverInformationOpenGL=new GraphicDriverInformationOpenGL(ext,caps);
    }
    return *m_GraphicDriverInformationOpenGL;
}

System::Threading::Mutex& OpenGLCanvas::RenderLock()
{
    return *m_Lock;
}

MeshGenerator2D& RadonFramework::Drawing::OpenGLCanvas::GetMeshGenerator2D()
{
    return m_MeshGenerator;
}
