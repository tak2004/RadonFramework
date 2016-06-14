#include "RadonFramework/precompiled.hpp"
#include <GL/glew.h>
#include <RadonFramework/backend/X11/Drawing/X11OpenGL1Canvas3D.hpp>
#include <RadonFramework/Drawing/Forms/AbstractWindow.hpp>
#include <RadonFramework/Drawing/Forms/WindowServiceLocator.hpp>
#include <RadonFramework/backend/X11/Forms/X11Application.hpp>
#include <RadonFramework/backend/X11/Forms/X11Window.hpp>

using namespace RadonFramework::Drawing;
using namespace RadonFramework::Forms;
using namespace RadonFramework::Math::Geometry;

X11OpenGL1Canvas3D::X11OpenGL1Canvas3D()
{
  m_Attr[0]=GLX_DEPTH_SIZE;
  m_Attr[1]=1;
  m_Attr[2]=GLX_RGBA;
  m_Attr[3]=GLX_RED_SIZE;
  m_Attr[4]=1;
  m_Attr[5]=GLX_GREEN_SIZE;
  m_Attr[6]=1;
  m_Attr[7]=GLX_BLUE_SIZE;
  m_Attr[8]=1;
  m_Attr[9]=GLX_DOUBLEBUFFER;
  m_Attr[10]=0;
  m_Context=0;
  m_TexturecoordMatrix.Scale(1.0,-1.0,1.0);
  m_TexturecoordMatrix.Translate(0.0,1.0,0.0);
}

X11OpenGL1Canvas3D::~X11OpenGL1Canvas3D()
{
}

void X11OpenGL1Canvas3D::Generate()
{
    Display* display=static_cast<X11Application*>(static_cast<X11Window*>(m_Window)->GetService()->Application())->GetDisplay();
    XVisualInfo* visinfo=glXChooseVisual(display,DefaultScreen(display),&m_Attr[0]);
    m_Context=glXCreateContext(display,visinfo,NULL,true);
    if(m_Context==NULL)
    {
        RF_IO::LogError("Can't create X11 graphic context.");
        return;
    }

    glXMakeCurrent(display,static_cast<X11Window*>(m_Window)->GetHandle(),m_Context);
    GLenum err=glewInit();
    if (GLEW_OK!=err)
        RF_IO::LogFatalError("Can't initialize Glew. The OpenGL services wouldn't work without.");
}

void X11OpenGL1Canvas3D::SetWindowInfos(AbstractWindow* Window)
{
    m_Window=Window;
}

void X11OpenGL1Canvas3D::Clear()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void X11OpenGL1Canvas3D::SwapBuffer()
{
  glXSwapBuffers(static_cast<X11Application*>(static_cast<X11Window*>(m_Window)->GetService()->Application())->GetDisplay(),static_cast<X11Window*>(m_Window)->GetHandle());
}

void X11OpenGL1Canvas3D::UpdateRectangle(Rectangle<Core::Types::Int32> &Rec)
{
  glViewport(Rec.Left(),Rec.Top(),Rec.Width(),Rec.Height());
}

Matrix4f& X11OpenGL1Canvas3D::TexturecoordMatrix()
{
  return m_TexturecoordMatrix;
}

void RadonFramework::Drawing::X11OpenGL1Canvas3D::MakeCurrent()
{
    glXMakeCurrent(static_cast<X11Application*>(static_cast<X11Window*>(m_Window)->GetService()->Application())->GetDisplay(),
        static_cast<X11Window*>(m_Window)->GetHandle(), m_Context);
}
