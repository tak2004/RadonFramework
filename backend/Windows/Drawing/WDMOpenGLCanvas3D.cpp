#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/backend/GL/WindowsOpenGLConstants.hpp>
#include <RadonFramework/backend/GL/OpenGLConstants.hpp>
#include <RadonFramework/System/Drawing/OpenGL.hpp>
#include <RadonFramework/System/Drawing/OpenGLSystem.hpp>
#include <RadonFramework/backend/Windows/Drawing/WDMOpenGLCanvas3D.hpp>
#include <RadonFramework/Drawing/Forms/AbstractWindow.hpp>
#include <RadonFramework/Drawing/Forms/WindowServiceLocator.hpp>
#include <RadonFramework/backend/Windows/Forms/WindowsApplication.hpp>
#include <RadonFramework/backend/Windows/Forms/WindowsWindow.hpp>
#include <RadonFramework/IO/Log.hpp>
#include "RadonFramework/Collections/AutoVector.hpp"

using namespace RadonFramework;
using namespace RadonFramework::Math::Geometry;
using namespace RadonFramework::Drawing;
using namespace RadonFramework::Forms;
using namespace RadonFramework::IO;
using namespace RadonFramework::GL;

void WDMOpenGLCanvas3D::Generate()
{
    int iFormat=0;
    m_MajorVersion = 1;

    static PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_SUPPORT_COMPOSITION |
        PFD_DRAW_TO_WINDOW |
        PFD_SUPPORT_OPENGL |
        PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        128,
        32, 0, 32, 0, 32, 0,
        32,
        0,
        0,
        0, 0, 0, 0,
        16,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    iFormat = ChoosePixelFormat(m_DeviceContext, &pfd);

    if (iFormat == 0)
        LogError("No valid pixelformat");

    if (!SetPixelFormat(m_DeviceContext, iFormat, &m_PixelFormat))
        LogError("Can't set pixelformat");

    //get an old context first and try to get a new one later on
    HGLRC TempContext=wglCreateContext(m_DeviceContext);
    if (TempContext==NULL)
    {
        LogError("Could not create an OpenGL rendering context");
        return;
    }
    wglMakeCurrent(m_DeviceContext,TempContext);

    OpenGLInit();

    unsigned int numFormats;
    const int attribList [] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_RED_BITS_ARB, 8,
        WGL_GREEN_BITS_ARB, 8,
        WGL_BLUE_BITS_ARB, 8,
        WGL_ALPHA_BITS_ARB, 8,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 0,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        0, 0
    };

    // ask with the current context for OpenGL 3.0 and higher functions
    if (OpenGLGetProcAddress("wglChoosePixelFormatARB") != nullptr)
    {
        if (wglChoosePixelFormatARB(m_DeviceContext, attribList, 0, 1, &iFormat, &numFormats) != 0 && numFormats > 0)
            SetPixelFormat(m_DeviceContext, iFormat, &m_PixelFormat);
    }

    // context version is something between 1.1 and 2.0 yet
    if(OpenGLGetProcAddress("wglCreateContextAttribsARB") == nullptr)
    {
        // wglCreateContextAttribsARB is part of context creation for OpenGL 3.0 and higher 
        m_Context = TempContext;
        // glCreateShader is available since OpenGL 2.0
        if(OpenGLGetProcAddress("glCreateShader") != nullptr)
        {
            m_MajorVersion = 2;
        }
        return;
    }

    // since OpenGL 3.0 it's possible to ask for the version
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    m_MajorVersion = major;

    const int attribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, major,
        WGL_CONTEXT_MINOR_VERSION_ARB, minor,
        WGL_CONTEXT_FLAGS_ARB,
        WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        0
    };

    // request for a OpenGL 3.0 or higher context
    if ((m_Context=wglCreateContextAttribsARB(m_DeviceContext,0, attribs))==0)
    {
        m_Context = TempContext;
        return;
    }

    // switch to the newest context and destroy the old one
    wglMakeCurrent(m_DeviceContext, m_Context);
    wglDeleteContext(TempContext);
}

void WDMOpenGLCanvas3D::GetExtensions(RF_Collect::Array<RF_Type::String>& Extensions)
{
    // since OpenGL 3.0 you have to iterate through each extension
    if (m_MajorVersion >= 3)
    {
        GLint n, i;
        glGetIntegerv(GL_NUM_EXTENSIONS, &n);
        Extensions.Resize(n);
        for(i = 0; i < n; i++)
        {
            Extensions(i)=RF_Type::String::UnsafeStringCreation(
                reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i)));
        }
    }
    else
    {
        OpenGLCanvas::GetExtensions(Extensions);
    }

    // windows and X11 have their own extension function
    const char* ext = wglGetExtensionsStringARB(m_DeviceContext);
    if(glGetError() == GL_NO_ERROR)
    {
        RF_Type::String extstr = RF_Type::String::UnsafeStringCreation(ext);
        RF_Mem::AutoPointerArray<RF_Type::String> vec(extstr.Split(RF_Type::String(" ")));
        RF_Type::Size firstWGLEntry = Extensions.Count();
        Extensions.Resize(firstWGLEntry +vec.Count());
        for(RF_Type::Size i = 0; i < vec.Count(); ++i)
            Extensions(i + firstWGLEntry) = vec[i];
    }
}
