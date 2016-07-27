#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/backend/GL/WindowsOpenGLConstants.hpp>
#include <RadonFramework/backend/GL/OpenGLConstants.hpp>
#include <RadonFramework/System/Drawing/OpenGL.hpp>
#include <RadonFramework/System/Drawing/OpenGLSystem.hpp>
#include <RadonFramework/backend/Windows/Drawing/WindowsOpenGLCanvas3D.hpp>
#include <RadonFramework/Drawing/Forms/AbstractWindow.hpp>
#include <RadonFramework/Drawing/Forms/WindowServiceLocator.hpp>
#include <RadonFramework/backend/Windows/Forms/WindowsApplication.hpp>
#include <RadonFramework/backend/Windows/Forms/WindowsWindow.hpp>
#include <RadonFramework/IO/Log.hpp>
#include "RadonFramework/backend/OpenGL/GraphicDriverInformationOpenGL.hpp"
#include "RadonFramework/Collections/Algorithm/Exists.hpp"

using namespace RadonFramework;
using namespace RadonFramework::Math::Geometry;
using namespace RadonFramework::Drawing;
using namespace RadonFramework::Forms;
using namespace RadonFramework::IO;
using namespace RadonFramework::GL;

WindowsOpenGLCanvas3D::WindowsOpenGLCanvas3D()
{
    m_TexturecoordMatrix.Scale(1.0,-1.0,1.0);
    m_TexturecoordMatrix.Translate(0.0,1.0,0.0);
}

WindowsOpenGLCanvas3D::~WindowsOpenGLCanvas3D()
{
    OpenGLExit();
    ReleaseDC(m_WndHandle, m_DeviceContext);
}

void WindowsOpenGLCanvas3D::SetWindowInfos(AbstractWindow* Window)
{
    WindowsWindow* wnd=static_cast<WindowsWindow*>(Window);
    m_WndHandle = wnd->GetHandle();
    m_DeviceContext=GetDC(wnd->GetHandle());
}

void WindowsOpenGLCanvas3D::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}

void WindowsOpenGLCanvas3D::SwapBuffer()
{
    SwapBuffers(m_DeviceContext);
}

void WindowsOpenGLCanvas3D::UpdateRectangle(Math::Geometry::Rectangle<>& Rec)
{
    glViewport(Rec.Left(),Rec.Top(),Rec.Width(),Rec.Height());
}

Mat4f& WindowsOpenGLCanvas3D::TexturecoordMatrix()
{
    return m_TexturecoordMatrix;
}

void WindowsOpenGLCanvas3D::MakeCurrent()
{
    wglMakeCurrent(m_DeviceContext, m_Context);
}

void WindowsOpenGLCanvas3D::SetVSync(const RF_Type::Bool Synchronize /*= true*/,
    const RF_Type::Bool ShouldContinue /*= true*/)
{
    int interval = Synchronize ? 1 : 0;
    if (ShouldContinue && Synchronize)
    {
        auto& extensions = GetContextRelatedGraphicDriverInformation().Extensions();
        if(RF_Algo::Exists(extensions, [](RF_Collect::Array<RF_Type::String>::ConstEnumeratorType& it) {
            return *it == "WGL_EXT_swap_control_tear"_rfs; }))
        {
            interval = -1;
        }
    }
    wglSwapIntervalEXT(interval);
}
