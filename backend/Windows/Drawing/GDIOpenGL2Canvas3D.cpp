#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/System/Drawing/OpenGL.hpp>
#include <RadonFramework/System/Drawing/OpenGLSystem.hpp>
#include <RadonFramework/backend/Windows/Drawing/GDIOpenGL2Canvas3D.hpp>
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

void GDIOpenGL2Canvas3D::Generate()
{
    int iFormat=0;
    static	PIXELFORMATDESCRIPTOR pfd=
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW |
        PFD_SUPPORT_OPENGL |
        PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,
        8,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    iFormat=ChoosePixelFormat(m_DeviceContext,&pfd);
    if (iFormat==0)
        LogError("No valid pixelformat.");

    if (!SetPixelFormat(m_DeviceContext,iFormat,&m_PixelFormat))
        LogError("Can't set pixelformat.");

    m_Context=wglCreateContext(m_DeviceContext);
    if (m_Context==NULL)
        LogError("Could not create an OpenGL rendering context");
    wglMakeCurrent(m_DeviceContext,m_Context);

    OpenGLInit();
}