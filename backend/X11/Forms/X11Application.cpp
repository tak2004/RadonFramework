#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/backend/X11/Forms/X11Application.hpp>
#include <RadonFramework/backend/X11/Forms/X11Window.hpp>

extern void ResolveEvent(XEvent& Event);

using namespace RadonFramework::Forms;

X11Application::X11Application()
:m_Active(false)
{
  m_Display=XOpenDisplay(NULL);
}

X11Application::~X11Application()
{
  XCloseDisplay(m_Display);
}

void X11Application::Run(Form *MainForm)
{
    m_Active=true;
    XEvent event;

    while (m_Active==true && MainForm->Visible())
    {
        while (XPending(m_Display)>0)
        {
            XNextEvent(m_Display,&event);
            ResolveEvent(event);
        }
        for (unsigned int i=0;i<X11Window::GetObjectCount();i++)
            X11Window::GetObjectByIndex(i)->OnIdle();
    }
    XSync(m_Display,false);
}

void X11Application::End()
{
  m_Active=false;
}

Display* X11Application::GetDisplay()
{
  return m_Display;
}

bool X11Application::IsRunningOnDesktop()
{
return false;
}

void X11Application::ShowConsole(bool isVisible)
{

}