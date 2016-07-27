#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/System/Drawing/OpenGL.hpp>
#include <RadonFramework/System/Drawing/OpenGLSystem.hpp>
#include <RadonFramework/backend/Windows/Drawing/GDIOpenGL3Canvas3D.hpp>
#include <RadonFramework/Drawing/Forms/AbstractWindow.hpp>
#include <RadonFramework/Drawing/Forms/WindowServiceLocator.hpp>
#include <RadonFramework/backend/Windows/Forms/WindowsApplication.hpp>
#include <RadonFramework/backend/Windows/Forms/WindowsWindow.hpp>
#include <RadonFramework/IO/Log.hpp>

using namespace RadonFramework;
using namespace RadonFramework::Math::Geometry;
using namespace RadonFramework::Drawing;
using namespace RadonFramework::Forms;
using namespace RadonFramework::IO;

void GDIOpenGL3Canvas3D::Generate()
{
    int iFormat=0;

    static PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
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

    HGLRC TempContext=wglCreateContext(m_DeviceContext);//erstellt ein alten OpenGL Context
    if (TempContext==NULL)
    {
        LogError("Could not create an OpenGL rendering context");
        return;//beenden
    }
    wglMakeCurrent(m_DeviceContext,TempContext);//setzt den erstellten GC als aktuellen GC

    OpenGLInit();
//     GLenum err=glewInit();
//     if (GLEW_OK!=err)
//     {
//         LogError("Couldn't init OpenGL extension wrangler.");
//         return;
//     }

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
        0, 0       //End
    };

    if (OpenGLGetProcAddress("wglChoosePixelFormatARB") != NULL)
    {
        if (wglChoosePixelFormatARB(m_DeviceContext, attribList, 0, 1, &iFormat, &numFormats) != 0 && numFormats > 0)
            SetPixelFormat(m_DeviceContext, iFormat, &m_PixelFormat);
    }

    if(OpenGLGetProcAddress("wglCreateContextAttribsARB") == NULL)//wenn es diese Funktion nicht gibt, dann hat der -->Treiber<-- keinen OpenGL3 support
    {
        wglDeleteContext(TempContext);
        LogError("There is no OpenGL3 context support.");
        return;
    }

    const int attribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 2,
        WGL_CONTEXT_FLAGS_ARB,
        WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        0
    };

    if ((m_Context=wglCreateContextAttribsARB(m_DeviceContext,0, attribs))==0)//versuche ein OpenGL3.2 f�higen Context zu erstellen
    {
        //Entweder hat der Treiber noch keinen OpenGL3.2 support oder die Grafikkarte beherrscht kein OpenGL3.2.
        LogError("Couldn't create OpenGL3.2 context. Try now OpenGL3.0 context");

        const int olderVersionAttribs [] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
            WGL_CONTEXT_MINOR_VERSION_ARB, 0,
            WGL_CONTEXT_FLAGS_ARB,
            WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            0
        };

        if ((m_Context = wglCreateContextAttribsARB(m_DeviceContext, 0, olderVersionAttribs)) == 0)
        {
          //Die -->Grafikkarte<-- beherrscht kein OpenGL3.
          wglDeleteContext(TempContext);//aufr�umen und beenden
          LogError("Couldn't create OpenGL3 context.");
          return;
        }
    }
    wglMakeCurrent(m_DeviceContext,m_Context);//wechsel auf den OpenGL3.x context
    wglDeleteContext(TempContext);//Zerst�re den tempor�ren Context, denn er wird nicht l�nger ben�tigt.
}