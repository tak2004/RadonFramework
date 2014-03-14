#include "RadonFramework/precompiled.hpp"
#include <GL/glew.h>
#include <RadonFramework/backend/Windows/Drawing/GDIOpenGL1Canvas3D.hpp>
#include <RadonFramework/Drawing/Forms/IWindow.hpp>
#include <RadonFramework/Drawing/Forms/WindowServiceLocator.hpp>
#include <RadonFramework/backend/Windows/Forms/WindowsApplication.hpp>
#include <RadonFramework/backend/Windows/Forms/WindowsWindow.hpp>
#include <RadonFramework/IO/Log.hpp>

using namespace RadonFramework::Drawing;
using namespace RadonFramework::Forms;
using namespace RadonFramework::Math::Geometry;
using namespace RadonFramework::IO;

GDIOpenGL1Canvas3D::GDIOpenGL1Canvas3D()
{
  m_TexturecoordMatrix.Scale(1.0,-1.0,1.0);
  m_TexturecoordMatrix.Translate(0.0,1.0,0.0);
}

GDIOpenGL1Canvas3D::~GDIOpenGL1Canvas3D()
{
}

void GDIOpenGL1Canvas3D::Generate()
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
        LogError("Couldn't create an OpenGL rendering context.");

    wglMakeCurrent(m_DeviceContext,m_Context);

    GLenum err=glewInit();
    if (GLEW_OK!=err)
        LogFatalError("Can't initialize Glew. The OpenGL services wouldn't work without.");
}

void GDIOpenGL1Canvas3D::SetWindowInfos(IWindow* Window)
{
    WindowsWindow* wnd=static_cast<WindowsWindow*>(Window);
    m_DeviceContext=GetDC(wnd->GetHandle());
}

void GDIOpenGL1Canvas3D::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}

void GDIOpenGL1Canvas3D::SwapBuffer()
{
    SwapBuffers(m_DeviceContext);
}

void GDIOpenGL1Canvas3D::UpdateRectangle(RadonFramework::Math::Geometry::Rectangle<> &Rec)
{
  glViewport(Rec.Left(),Rec.Top(),Rec.Width(),Rec.Height());
}

Matrix4f& GDIOpenGL1Canvas3D::TexturecoordMatrix()
{
  return m_TexturecoordMatrix;
}

void GDIOpenGL1Canvas3D::MakeCurrent()
{
    wglMakeCurrent(m_DeviceContext, m_Context);
}