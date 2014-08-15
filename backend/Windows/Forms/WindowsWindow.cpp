# include "RadonFramework/precompiled.hpp"
#include <RadonFramework/backend/Windows/Forms/WindowsWindow.hpp>
#include <RadonFramework/Drawing/Forms/WindowServiceLocator.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>
#include <RadonFramework/backend/Windows/Forms/WindowsWindowService.hpp>
#include <RadonFramework/backend/Windows/Forms/WindowsApplication.hpp>
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <Windowsx.h>

using namespace RadonFramework::Forms;
using namespace RadonFramework::Math::Geometry;
using namespace RadonFramework::IO;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;

List<WindowsWindow*> WindowsWindow::m_Objects;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    WindowsWindow *wnd=0;
    Size2D<> size;
    Point2D<> pos;
    VirtualKey vk=VirtualKey::NotSet;
    switch (uMsg)
    {
        case WM_PAINT:
        {
            wnd=dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
            break;
        }
        case WM_MOVE:
            wnd = dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
            pos.X = LOWORD(lParam);
            pos.Y = HIWORD(lParam);
            wnd->OnReposition(pos);
            return 0;
        case WM_SIZE:
        {
            wnd=dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
            size.Width=LOWORD(lParam);
            size.Height=HIWORD(lParam);
            wnd->OnResize(size);
            return 0;
        }
        case WM_KEYDOWN:
        {
            wnd=dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
            switch (wParam)
            {
                case VK_ESCAPE:vk=VirtualKey::Escape;break;
                case VK_SPACE:vk=VirtualKey::Space;break;
                case VK_PRIOR:vk=VirtualKey::PageUp;break;
                case VK_NEXT:vk=VirtualKey::PageDown;break;
                case VK_LEFT:vk=VirtualKey::Left;break;
                case VK_UP:vk=VirtualKey::Up;break;
                case VK_RIGHT:vk=VirtualKey::Right;break;
                case VK_DOWN:vk=VirtualKey::Down;break;
                case VK_LSHIFT:vk=VirtualKey::ShiftLeft;break;
                case VK_RSHIFT:vk=VirtualKey::ShiftRight;break;
            }
            if (wParam>='a' && wParam<='z')
                vk=(VirtualKey)((int)(VirtualKey::a)+(wParam-'a'));
            if (wParam>='A' && wParam<='Z')
                vk=(VirtualKey)((int)(VirtualKey::A)+(wParam-'A'));
            if (vk!=VirtualKey::NotSet)
                wnd->OnKeyPress(vk);
            break;
        }
        case WM_KEYUP:
        {
            wnd=dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
            switch (wParam)
            {
                case VK_ESCAPE:vk=VirtualKey::Escape;break;
                case VK_SPACE:vk=VirtualKey::Space;break;
                case VK_PRIOR:vk=VirtualKey::PageUp;break;
                case VK_NEXT:vk=VirtualKey::PageDown;break;
                case VK_LEFT:vk=VirtualKey::Left;break;
                case VK_UP:vk=VirtualKey::Up;break;
                case VK_RIGHT:vk=VirtualKey::Right;break;
                case VK_DOWN:vk=VirtualKey::Down;break;
                case VK_LSHIFT:vk=VirtualKey::ShiftLeft;break;
                case VK_RSHIFT:vk=VirtualKey::ShiftRight;break;
            }
            if (wParam>='a' && wParam<='z')
                vk=(VirtualKey)((int)(VirtualKey::a)+(wParam-'a'));
            if (wParam>='A' && wParam<='Z')
                vk=(VirtualKey)((int)(VirtualKey::A)+(wParam-'A'));
            if (vk!=VirtualKey::NotSet)
                wnd->OnKeyRelease(vk);
            break;
        }
    //case WM_CHAR:
            
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
        {
            wnd=dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
            MouseEvent event;
            event.CurrentPosition=Point2D<>(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
            for (UInt32 i=0;i<VirtualMouseButton::MAX;++i)
                event.MouseButtonState[i]=0;
            if (uMsg == WM_MBUTTONDOWN)
                event.MouseButtonState[VirtualMouseButton::Middle]=true;
            if (uMsg == WM_LBUTTONDOWN)
                event.MouseButtonState[VirtualMouseButton::Left]=true;
            if (uMsg == WM_RBUTTONDOWN)
                event.MouseButtonState[VirtualMouseButton::Right]=true;
            wnd->OnMouseButtonPressed(event);
            break;
        }
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
        {
            wnd=dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
            MouseEvent event;
            event.CurrentPosition=Point2D<>(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
            for (UInt32 i=0;i<VirtualMouseButton::MAX;++i)
                event.MouseButtonState[i]=0;
            if (uMsg == WM_MBUTTONUP)
                event.MouseButtonState[VirtualMouseButton::Middle]=true;
            if (uMsg == WM_LBUTTONUP)
                event.MouseButtonState[VirtualMouseButton::Left]=true;
            if (uMsg == WM_RBUTTONUP)
                event.MouseButtonState[VirtualMouseButton::Right]=true;
            wnd->OnMouseButtonReleased(event);
            break;
        }
    case WM_MOUSEMOVE:
        {
            wnd=dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
            MouseEvent event;
            event.CurrentPosition=Point2D<>(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
            for (UInt32 i=0;i<VirtualMouseButton::MAX;++i)
                event.MouseButtonState[i]=0;
            if (wParam & MK_MBUTTON)
                event.MouseButtonState[VirtualMouseButton::Middle]=true;
            if (wParam & MK_LBUTTON)
                event.MouseButtonState[VirtualMouseButton::Left]=true;
            if (wParam & MK_RBUTTON)
                event.MouseButtonState[VirtualMouseButton::Right]=true;
            wnd->OnMouseMove(event);
            break;
        }
    //case WM_MOUSEWHEEL:
        case WM_DESTROY:
            return 0;
        case WM_CLOSE:
        {
            wnd=dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
            wnd->Visible(false);
            return 0;
        }
    }
    return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

WindowsWindow::WindowsWindow(WindowService *Service)
:m_Service(Service)
,m_Title("unnamed", sizeof("unnamed"))
,m_Border(true)
,m_Visible(false)
,m_CursorVisible(true)
,m_Created(false)
,m_Handle(0)
,m_CloseButton(true)
,m_WindowFlags(WS_OVERLAPPEDWINDOW)
{
    WindowsWindow::m_Objects.AddLast(this);
}

WindowsWindow::~WindowsWindow()
{
    for (RF_Type::Size i=0;i<m_Objects.Size();i++)
    if (m_Objects[i]->m_Handle==m_Handle)
    {
        WindowsWindow::m_Objects.RemoveAt(i);
        break;
    }
    DestroyWindow(m_Handle);
}

void* WindowsWindow::Handle()
{
    return (void*)0;
}

Bool WindowsWindow::Visible()
{
    return m_Visible;
}

void WindowsWindow::Visible(const Bool Value)
{
    if (Value!=m_Visible)
    {
        if (Value)
        {
            if (!m_Created)//Form wasn't created till now
            {
                m_Created=true;
                m_Handle=CreateWindowExA(0,"#32770",m_Title.c_str(),
                                            WS_VISIBLE | m_WindowFlags,
                                            m_Pos.X, m_Pos.Y, m_Size.Width, m_Size.Height,
                                            0, 0, 0, NULL );
                SetWindowLongPtr(m_Handle,GWLP_WNDPROC,(LONG_PTR)WndProc);
            }
            else
                ShowWindow(m_Handle,SW_SHOW);
        }
        else
            ShowWindow(m_Handle,SW_HIDE);
    }
    m_Visible=Value;
}

String WindowsWindow::Title()
{
    return m_Title;
}

void WindowsWindow::Title(const String &Value)
{
    if (SetWindowText(m_Handle,Value.c_str()) || GetLastError()==0)
        m_Title=Value;
}

void WindowsWindow::ClientRectSize(const RF_Geo::Size2D<>& NewSize)
{
    RECT r;
    r.left=0; r.top=0; r.right=NewSize.Width; r.bottom=NewSize.Height;
    AdjustWindowRect(&r,m_WindowFlags,FALSE);
    RF_Geo::Size2D<> wndSize;
    wndSize.Width=r.right-r.left;
    wndSize.Height=r.bottom-r.top;
    Size(wndSize);
}

void WindowsWindow::Size(const RF_Geo::Size2D<>& NewSize)
{        
    m_Size=NewSize;
    if (m_Visible)
        SetWindowPos(m_Handle,HWND_TOP,0,0,m_Size.Width,m_Size.Height,SWP_NOMOVE);
}

void WindowsWindow::Position(const RF_Geo::Point2D<>& NewPosition)
{
    m_Pos=NewPosition;
    if (m_Visible)
        SetWindowPos(m_Handle,HWND_TOP,m_Pos.X,m_Pos.Y,0,0,SWP_NOSIZE);
}

void WindowsWindow::Border(const Bool Value)
{
    if (m_Border!=Value)
    {
        m_Border=Value;
        if (m_Border)
        {
            m_WindowFlags=WS_OVERLAPPEDWINDOW;
            SetWindowLongPtr( m_Handle, GWL_STYLE, m_WindowFlags );
            SetWindowPos( m_Handle, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE );
        }
        else
        {
            m_WindowFlags=WS_POPUP;
            SetWindowLongPtr( m_Handle, GWL_STYLE, m_WindowFlags );
            SetWindowPos( m_Handle, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE );
        }
    }
}

void WindowsWindow::CursorVisible(const Bool Value)
{
    ::ShowCursor(Value);
}

WindowsWindow* WindowsWindow::GetObjectByHandle(const HWND Handle)
{
    for (RF_Type::Size i=0;i<m_Objects.Size();i++)
        if (m_Objects[i]->m_Handle==Handle)
            return m_Objects[i];
    return 0;
}

UInt32 WindowsWindow::GetObjectCount()
{
    return static_cast<UInt32>(m_Objects.Size());
}

WindowsWindow* WindowsWindow::GetObjectByIndex(const UInt32 Index)
{
    return m_Objects[Index];
}

HWND WindowsWindow::GetHandle()
{
    return m_Handle;
}

WindowService* WindowsWindow::GetService()
{
    return m_Service;
}

void WindowsWindow::CloseButton(const RF_Type::Bool Show)
{
    if (Show != m_CloseButton)
    {
        m_CloseButton = Show;
        HMENU hmenu = GetSystemMenu(m_Handle, FALSE);
        EnableMenuItem(hmenu, SC_CLOSE, Show ? (MF_BYCOMMAND | MF_ENABLED) : (MF_BYCOMMAND | MF_DISABLED | MF_GRAYED));
    }
}