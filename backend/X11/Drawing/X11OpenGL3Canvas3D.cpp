#include "RadonFramework/precompiled.hpp"
#include <GL/glew.h>
#include <GL/glxew.h>
#include <RadonFramework/backend/X11/Drawing/X11OpenGL3Canvas3D.hpp>
#include <RadonFramework/Drawing/Forms/AbstractWindow.hpp>
#include <RadonFramework/Drawing/Forms/WindowServiceLocator.hpp>
#include <RadonFramework/IO/Log.hpp>
#include <RadonFramework/backend/X11/Forms/X11Application.hpp>
#include <RadonFramework/backend/X11/Forms/X11Window.hpp>

using namespace RadonFramework::Drawing;
using namespace RadonFramework::Forms;
using namespace RadonFramework::Math::Geometry;
using namespace RadonFramework::IO;
using namespace RadonFramework::Core::Types;

X11OpenGL3Canvas3D::X11OpenGL3Canvas3D()
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

X11OpenGL3Canvas3D::~X11OpenGL3Canvas3D()
{
}

void X11OpenGL3Canvas3D::Generate()
{
    Display* display=static_cast<X11Application*>(static_cast<X11Window*>(m_Window)->GetService()->Application())->GetDisplay();
    m_FBConfig=glXChooseFBConfig(display,DefaultScreen(display),m_Attr,&m_FBConfigCount);
    if (!m_FBConfig)
    {
        RF_IO::LogError("Failed to retrieve a framebuffer config");
      return;
    }

    XVisualInfo* visinfo=glXChooseVisual(display,DefaultScreen(display),&m_Attr[0]);
    GLXContext TempContext=glXCreateContext(display,visinfo,NULL,true);
    if(TempContext==NULL)
    {
        RF_IO::LogError("Could not vreate an OpenGL rendering context.");
        return;
    }

    glXMakeCurrent(display,static_cast<X11Window*>(m_Window)->GetHandle(),TempContext);

    //Typedefinition of wglCreateContextAttribsARB
    using GLXCREATECONTEXTATTRIBSARBPROC = GLXContext(*)(Display *dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int *attrib_list);
    //does the function exists
    GLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB=(GLXCREATECONTEXTATTRIBSARBPROC)glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");

    if (glXCreateContextAttribsARB==NULL)//if the function don't exists then there is no OpenGL3 support
    {
        RF_IO::LogError("There is no OpenGL3 context support.");
        return;
    }

    int major=0;
    int minor=0;
    glGetIntegerv(GL_MAJOR_VERSION,&major);
    glGetIntegerv(GL_MINOR_VERSION,&minor);
    int attribs[]={GLX_CONTEXT_MAJOR_VERSION_ARB,major,GLX_CONTEXT_MINOR_VERSION_ARB,minor,GLX_CONTEXT_FLAGS_ARB,GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,0};
    for (UInt32 i=minor; i>=0; i--)
    {
        attribs[3]=i;
        m_Context=glXCreateContextAttribsARB(display,m_FBConfig[0],NULL,true,attribs);
        if(!m_Context)
        {
            if(i>0)
            {
                RF_IO::LogError("Couldn't create OpenGL3.%u context. Try now OpenGL3.%u context.", i, i - 1);
                continue;
            }
            else
            {
                glXDestroyContext(display,TempContext);
                RF_IO::LogError("Couldn't create OpenGL3 context.");
                return;
            }
        }
        break;
    }
    glXMakeCurrent(display,static_cast<X11Window*>(m_Window)->GetHandle(),m_Context);
    glXDestroyContext(display,TempContext);
    GLenum err=glewInit();
    if (GLEW_OK!=err)
    {
        RF_IO::LogFatalError("Couldn't init OpenGL extension wrangler.");
        return;
    }
}

void X11OpenGL3Canvas3D::SetWindowInfos(AbstractWindow* Window)
{
    m_Window=Window;
}

void X11OpenGL3Canvas3D::Clear()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void X11OpenGL3Canvas3D::SwapBuffer()
{
    glXSwapBuffers(static_cast<X11Application*>(static_cast<X11Window*>(m_Window)->GetService()->Application())->GetDisplay(),static_cast<X11Window*>(m_Window)->GetHandle());
}

void X11OpenGL3Canvas3D::UpdateRectangle(Rectangle<> &Rec)
{
    glViewport(Rec.Left(),Rec.Top(),Rec.Width(),Rec.Height());
}

Matrix4f& X11OpenGL3Canvas3D::TexturecoordMatrix()
{
    return m_TexturecoordMatrix;
}

void X11OpenGL3Canvas3D::MakeCurrent()
{
    glXMakeCurrent(static_cast<X11Application*>(static_cast<X11Window*>(m_Window)->GetService()->Application())->GetDisplay(),
                   static_cast<X11Window*>(m_Window)->GetHandle(), m_Context);
}