#include "RadonFramework/precompiled.hpp"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#undef Bool
#undef True
#undef False
#include <iostream>

#include <RadonFramework/backend/X11/Forms/X11Window.hpp>
#include <RadonFramework/Drawing/Forms/WindowServiceLocator.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>
#include <RadonFramework/backend/X11/Forms/X11WindowService.hpp>
#include <RadonFramework/backend/X11/Forms/X11Application.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>

using namespace RadonFramework::Forms;
using namespace RadonFramework::Math::Geometry;
using namespace RadonFramework::IO;
using namespace RadonFramework::Core::Types;

std::vector<X11Window*> X11Window::m_Objects;

void ResolveEvent(XEvent& Event)
{
  X11Window* m_Window;
  Size2D<> size;
  Point2D<> pos;
  VirtualKey vk;
  KeySym key;
  MouseEvent me;
  switch(Event.type)
  {
    case Expose:
      break;
    case ConfigureNotify:
      m_Window=X11Window::GetObjectByHandle(Event.xconfigure.window);
      size.Width=Event.xconfigure.width;
      size.Height=Event.xconfigure.height;
      m_Window->OnResize(size);
      break;
    case ClientMessage:
      m_Window=X11Window::GetObjectByHandle(Event.xclient.window);
      if (m_Window->GetDeleteAtom()==Event.xclient.data.l[0])
            m_Window->Visible(false);
      break;
    case ButtonPress:
      m_Window=X11Window::GetObjectByHandle(Event.xbutton.window);
      me.CurrentPosition=Point2D<>(Event.xbutton.x,Event.xbutton.y);
      for (UInt32 i=0;i<VirtualMouseButton::MAX;++i)
                me.MouseButtonState[i]=0;
      switch (Event.xbutton.button)
      {
        case Button1:me.MouseButtonState[VirtualMouseButton::Left]=true;break;
        case Button2:me.MouseButtonState[VirtualMouseButton::Middle]=true;break;
        case Button3:me.MouseButtonState[VirtualMouseButton::Right]=true;break;
        case Button4:me.MouseButtonState[VirtualMouseButton::WheelUp]=true;break;
        case Button5:me.MouseButtonState[VirtualMouseButton::WheelDown]=true;break;
      }
      m_Window->OnMouseButtonPressed(me);
      break;
    case ButtonRelease:
      m_Window=X11Window::GetObjectByHandle(Event.xbutton.window);
      me.CurrentPosition=Point2D<>(Event.xbutton.x,Event.xbutton.y);
      for (UInt32 i=0;i<VirtualMouseButton::MAX;++i)
                me.MouseButtonState[i]=0;
      switch (Event.xbutton.button)
      {
        case Button1:me.MouseButtonState[VirtualMouseButton::Left]=true;break;
        case Button2:me.MouseButtonState[VirtualMouseButton::Middle]=true;break;
        case Button3:me.MouseButtonState[VirtualMouseButton::Right]=true;break;
        case Button4:me.MouseButtonState[VirtualMouseButton::WheelUp]=true;break;
        case Button5:me.MouseButtonState[VirtualMouseButton::WheelDown]=true;break;
      }
      m_Window->OnMouseButtonReleased(me);
      break;
    case KeyRelease:
        m_Window=X11Window::GetObjectByHandle(Event.xkey.window);
        key=XKeycodeToKeysym(Event.xkey.display,Event.xkey.keycode,0);
        switch (key)
        {
            case XK_Escape:vk=VirtualKey::Escape;break;
            case XK_space:vk=VirtualKey::Space;break;
            case XK_Page_Up:vk=VirtualKey::PageUp;break;
            case XK_Page_Down:vk=VirtualKey::PageDown;break;
            case XK_Left:vk=VirtualKey::Left;break;
            case XK_Up:vk=VirtualKey::Up;break;
            case XK_Right:vk=VirtualKey::Right;break;
            case XK_Down:vk=VirtualKey::Down;break;
            case XK_Shift_L:vk=VirtualKey::ShiftLeft;break;
            case XK_Shift_R:vk=VirtualKey::ShiftRight;break;
            case 'a'...'z':vk=(VirtualKey)((int)(VirtualKey::a)+(key-'a'));break;
            case 'A'...'Z':vk=(VirtualKey)((int)(VirtualKey::A)+(key-'A'));break;
        }
        m_Window->OnKeyRelease(vk);
        break;
    case KeyPress:
        m_Window=X11Window::GetObjectByHandle(Event.xkey.window);
        key=XKeycodeToKeysym(Event.xkey.display,Event.xkey.keycode,0);
        switch (key)
        {
            case XK_Escape:vk=VirtualKey::Escape;break;
            case XK_space:vk=VirtualKey::Space;break;
            case XK_Page_Up:vk=VirtualKey::PageUp;break;
            case XK_Page_Down:vk=VirtualKey::PageDown;break;
            case XK_Left:vk=VirtualKey::Left;break;
            case XK_Up:vk=VirtualKey::Up;break;
            case XK_Right:vk=VirtualKey::Right;break;
            case XK_Down:vk=VirtualKey::Down;break;
            case XK_Shift_L:vk=VirtualKey::ShiftLeft;break;
            case XK_Shift_R:vk=VirtualKey::ShiftRight;break;
            case 'a'...'z':vk=(VirtualKey)((int)(VirtualKey::a)+(key-'a'));break;
            case 'A'...'Z':vk=(VirtualKey)((int)(VirtualKey::A)+(key-'A'));break;
        }
        m_Window->OnKeyPress(vk);
        break;
    case MotionNotify:
        m_Window=X11Window::GetObjectByHandle(Event.xmotion.window);
        me.CurrentPosition=Point2D<>(Event.xmotion.x,Event.xmotion.y);
        for (UInt32 i=0;i<VirtualMouseButton::MAX;++i)
            me.MouseButtonState[i]=0;
        switch (Event.xmotion.state)
        {
            case Button1:me.MouseButtonState[VirtualMouseButton::Left]=true;break;
            case Button2:me.MouseButtonState[VirtualMouseButton::Middle]=true;break;
            case Button3:me.MouseButtonState[VirtualMouseButton::Right]=true;break;
            case Button4:me.MouseButtonState[VirtualMouseButton::WheelUp]=true;break;
            case Button5:me.MouseButtonState[VirtualMouseButton::WheelDown]=true;break;
        }
        m_Window->OnMouseMove(me);
        break;
    default:
      break;
  }
}

X11Window::X11Window(WindowService *Service)
:m_Handle(0),
 m_wmDelete(0),
 m_InvisibleCursor(),
 m_WindowFlags(),
 m_Service(Service),
 m_Title("unnamed"),
 m_Border(true),
 m_Visible(false),
 m_CursorVisible(true),
 m_Created(false),
 m_CloseButton(true)
{
  X11Window::m_Objects.push_back(this);
}

X11Window::~X11Window()
{
  for (unsigned int i=0;i<m_Objects.size();i++)
    if (m_Objects[i]->GetHandle()==m_Handle)
    {
      X11Window::m_Objects.erase(m_Objects.begin()+i);
      break;
    }
  XDestroyWindow(static_cast<X11Application*>(m_Service->Application())->GetDisplay(),m_Handle);
  XFreeCursor(static_cast<X11Application*>(m_Service->Application())->GetDisplay(),m_InvisibleCursor);
}

void* X11Window::Handle()
{
  return (void*)0;
}

Bool X11Window::Visible()
{
  return m_Visible;
}

void X11Window::Visible(const Core::Types::Bool Value)
{
  if (Value!=m_Visible)
  {
    Display* dsp=static_cast<X11Application*>(m_Service->Application())->GetDisplay();
    if (Value)
    {
      if (!m_Created)//Form wasn't created till now
      {
        m_Created=true;
        m_WindowFlags.border_pixel=0;
        m_WindowFlags.background_pixel=0;
        //m_WindowFlags.override_redirect=not m_Border;
        m_WindowFlags.event_mask=ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask | PointerMotionMask | StructureNotifyMask;
        m_Handle=XCreateWindow(dsp,DefaultRootWindow(dsp),0,0,640,480,0,0,InputOutput,CopyFromParent,CWBorderPixel|CWEventMask|CWBackPixel,&m_WindowFlags);

        //XChangeWindowAttributes(dsp,m_Handle,CWBorderPixel | CWEventMask | CWOverrideRedirect,&m_WindowFlags);

        if (m_Border)
        {
          m_wmDelete=XInternAtom(dsp,"WM_DELETE_WINDOW",true);
          XSetWMProtocols(dsp,m_Handle,&m_wmDelete,1);
          Title(m_Title);
        }

        char data=0;
        XColor dummy;
        Pixmap blank=XCreateBitmapFromData(dsp, m_Handle, &data, 1, 1);
        m_InvisibleCursor=XCreatePixmapCursor(dsp, blank, blank, &dummy, &dummy, 0, 0);
        XFreePixmap(dsp, blank);
      }
      XGrabKeyboard(dsp, m_Handle, true, GrabModeAsync, GrabModeAsync, CurrentTime);
      XMapRaised(dsp,m_Handle);
    }
    else
      XUnmapWindow(dsp,m_Handle);
    XFlush(dsp);
  }
  m_Visible=Value;
}

String X11Window::Title()
{
  return m_Title;
}

void X11Window::Title(const String &Value)
{
  m_Title=Value;
  if (m_Created)
  {
    Display* dsp=static_cast<X11Application*>(m_Service->Application())->GetDisplay();
    //XStoreName(dsp,m_Handle,m_Title.c_str());
    XTextProperty title;
    char* c=(char*)Value.c_str();
    Atom _NET_WM_NAME=XInternAtom(dsp,"_NET_WM_NAME",false);
    Xutf8TextListToTextProperty(dsp,&c,1,XUTF8StringStyle,&title);
    XSetTextProperty(dsp,m_Handle,&title,_NET_WM_NAME);
    XFree((char *) title.value);
    XFlush(dsp);
  }
}

void X11Window::Size(const Math::Geometry::Size2D<>& NewSize)
{
    Display* dsp=static_cast<X11Application*>(m_Service->Application())->GetDisplay();
    Window rootWindow, parentWindow, *childWindows;
    unsigned int numChildWindows;
    XQueryTree(dsp, m_Handle, &rootWindow, &parentWindow, &childWindows, &numChildWindows);
    int x,y;
    unsigned int w,h,cw,ch,bw,d;
    Window root;
    // get decorator window
    XGetGeometry(dsp, parentWindow, &root, &x, &y, &w, &h, &bw, &d);
    // get client window
    XGetGeometry(dsp, m_Handle, &root, &x, &y, &cw, &ch, &bw, &d);
    XResizeWindow(dsp,m_Handle,NewSize.Width+(w-cw),NewSize.Height+(h-ch));
    XFlush(dsp);
}

void X11Window::Position(const Point2D<>& NewPosition)
{
  Display* dsp=static_cast<X11Application*>(m_Service->Application())->GetDisplay();
  XMoveWindow(dsp,m_Handle,NewPosition.X,NewPosition.Y);
  XFlush(dsp);
}

enum
{
  _NET_WM_STATE_REMOVE =0,
  _NET_WM_STATE_ADD = 1,
  _NET_WM_STATE_TOGGLE =2

};

void X11Window::Border(const Core::Types::Bool Value)
{
  m_Border=Value;
  Display* dsp=static_cast<X11Application*>(m_Service->Application())->GetDisplay();

  Atom wmState = XInternAtom(dsp, "_NET_WM_STATE", false);
  Atom fullScreen = XInternAtom(dsp,"_NET_WM_STATE_FULLSCREEN", false);

  XEvent xev;
  xev.xclient.type=ClientMessage;
  xev.xclient.serial = 0;
  xev.xclient.send_event=true;
  xev.xclient.window=m_Handle;
  xev.xclient.message_type=wmState;
  xev.xclient.format=32;
  xev.xclient.data.l[0] = (m_Border ? _NET_WM_STATE_REMOVE : _NET_WM_STATE_ADD);
  xev.xclient.data.l[1] = fullScreen;
  xev.xclient.data.l[2] = 0;

  XSendEvent(dsp, DefaultRootWindow(dsp), false, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
}

void X11Window::CursorVisible(const Core::Types::Bool Value)
{
  if (m_CursorVisible==Value)
    return;
  else
    m_CursorVisible=Value;
  Display* dsp=dynamic_cast<X11Application*>(m_Service->Application())->GetDisplay();
  if (m_CursorVisible)
    XUndefineCursor(dsp,m_Handle);
  else
    XDefineCursor(dsp,m_Handle,m_InvisibleCursor);
  XFlush(dsp);
}

Window X11Window::GetHandle()
{
  return m_Handle;
}

Atom X11Window::GetDeleteAtom()
{
  return m_wmDelete;
}

X11Window* X11Window::GetObjectByHandle(Window Handle)
{
  for (unsigned int i=0;i<m_Objects.size();i++)
    if (m_Objects[i]->GetHandle()==Handle)
      return m_Objects[i];
  return 0;
}

unsigned int X11Window::GetObjectCount()
{
  return m_Objects.size();
}

X11Window* X11Window::GetObjectByIndex(unsigned int Index)
{
  return X11Window::m_Objects[Index];
}

WindowService* X11Window::GetService()
{
    return m_Service;
}

void X11Window::ClientRectSize(const Size2D<>& NewSize)
{
    Display* dsp=static_cast<X11Application*>(m_Service->Application())->GetDisplay();
    XResizeWindow(dsp,m_Handle,NewSize.Width,NewSize.Height);
    XFlush(dsp);
}

void X11Window::CloseButton(const Bool Show)
{
    m_CloseButton = Show;
    Display* dsp=static_cast<X11Application*>(m_Service->Application())->GetDisplay();
    XSetWMProtocols(dsp, m_Handle, &m_wmDelete, Show?1:0);
}

