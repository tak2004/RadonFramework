#include "RadonFramework/precompiled.hpp"
#include "WindowsWindow.hpp"
#include <RadonFramework/Drawing/Forms/WindowServiceLocator.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>
#include "WindowsWindowService.hpp"
#include "WindowsApplication.hpp"
#include "RadonFramework/Drawing/Forms/Cursor.hpp"
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <Windowsx.h>

using namespace RadonFramework::Forms;
using namespace RadonFramework::Math::Geometry;
using namespace RadonFramework::IO;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;

List<WindowsWindow*> WindowsWindow::m_Objects;

void MapWindowsToRadonVirtualKeys(WPARAM wParam, LPARAM lParam, KeyboardEvent& event)
{
    VirtualKey vk = VirtualKey::NotSet;

    // Numpad
    auto hiFlags = HIWORD(lParam);
    static const RF_Type::UInt16 KEYDOWNBIT = 1 << 15;
    static const RF_Type::UInt16 EXTENDEDKEYBIT = 1 << 8;
    static const RF_Type::UInt16 SCANCODEBITS = 255;
    if((hiFlags & EXTENDEDKEYBIT) == 0)
    {
        switch(MapVirtualKey(hiFlags & SCANCODEBITS, MAPVK_VSC_TO_VK))
        {
            case VK_INSERT: vk = VirtualKey::Keypad0; break;
            case VK_END: vk = VirtualKey::Keypad1; break;
            case VK_DOWN: vk = VirtualKey::Keypad2; break;
            case VK_NEXT: vk = VirtualKey::Keypad3; break;
            case VK_LEFT: vk = VirtualKey::Keypad4; break;
            case VK_CLEAR: vk = VirtualKey::Keypad5; break;
            case VK_RIGHT: vk = VirtualKey::Keypad6; break;
            case VK_HOME: vk = VirtualKey::Keypad7; break;
            case VK_UP: vk = VirtualKey::Keypad8; break;
            case VK_PRIOR: vk = VirtualKey::Keypad9; break;
            case VK_DIVIDE: vk = VirtualKey::KeypadDivide; break;
            case VK_MULTIPLY: vk = VirtualKey::KeypadMultiply; break;
            case VK_SUBTRACT: vk = VirtualKey::KeypadSubtract; break;
            case VK_ADD: vk = VirtualKey::KeypadAdd; break;
            case VK_DELETE: vk = VirtualKey::KeypadDecimal; break;
            default:
                break;
        }
    }

    switch(wParam)
    {
        case VK_ESCAPE:vk = VirtualKey::Escape; break;
        case VK_TAB: vk = VirtualKey::Tab; break;
        case VK_BACK: vk = VirtualKey::Backspace; break;
        case VK_HOME: vk = VirtualKey::Home; break;
        case VK_END: vk = VirtualKey::End; break;
        case VK_INSERT: vk = VirtualKey::Insert; break;
        case VK_DELETE: vk = VirtualKey::Delete; break;
        case VK_PRIOR:vk = VirtualKey::PageUp; break;
        case VK_NEXT:vk = VirtualKey::PageDown; break;
        case VK_LEFT:vk = VirtualKey::Left; break;
        case VK_UP:vk = VirtualKey::Up; break;
        case VK_RIGHT:vk = VirtualKey::Right; break;
        case VK_DOWN:vk = VirtualKey::Down; break;
        case VK_SHIFT:
        {
            // both shift keys have the extended bit set but use different virtual keys
            auto virtualKey= MapVirtualKey(VK_RSHIFT, 0);
            if((hiFlags & (EXTENDEDKEYBIT | SCANCODEBITS)) == virtualKey)
            {
                vk = VirtualKey::ShiftRight;
            }
            else
            {
                vk = VirtualKey::ShiftLeft;
            }
            break;
        }
        case VK_CONTROL:
        {
            if(hiFlags & EXTENDEDKEYBIT)
            {
                vk = VirtualKey::ControlRight;
            }
            else
            {
                vk = VirtualKey::ControlLeft;
            }
            break;
        }
        case VK_MENU:
        {
            if(hiFlags & EXTENDEDKEYBIT)
            {
                vk = VirtualKey::AltRight;
            }
            else
            {
                vk = VirtualKey::AltLeft;
            }
            break;
        }
        case VK_RETURN:
        {
            if(hiFlags & EXTENDEDKEYBIT)
            {
                vk = VirtualKey::KeypadEnter;
            }
            else
            {
                vk = VirtualKey::Enter;
            }
        }
    }
    if (wParam >= VK_F1 && wParam <= VK_F12)
        vk = (VirtualKey)((int)(VirtualKey::F1) + (wParam - VK_F1));

    if((wParam >= '0' && wParam <= '9'))
    {
        event.PrintableCharacter = String(2);
        event.PrintableCharacter[0] = static_cast<RF_Type::UInt8>(wParam);
    }
    if((wParam >= 'A' && wParam <= 'Z'))
    {
        event.PrintableCharacter = String(2);
        event.PrintableCharacter[0] = 'a'+(static_cast<RF_Type::UInt8>(wParam)-'A');
    }
    
    event.Key = vk;
    BYTE states[256];
    GetKeyboardState(states);
    event.Alt = states[VK_MENU];
    event.Ctrl = states[VK_CONTROL];
    event.Shift = states[VK_SHIFT];
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static const RF_Type::UInt16 EXTENDEDKEYBIT = 1 << 8;

    WindowsWindow *wnd=0;
    Size2D<> size;
    Point2D<> pos;
    VirtualKey vk=VirtualKey::NotSet;
    switch (uMsg)
    {
    case WM_ERASEBKGND:
        return 1;// avoid GDI to clean the background
    case WM_PAINT:
    {
        wnd=dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
        break;
    }
    case WM_MOVE:
        wnd = dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
        pos.X = (int)(short)LOWORD(lParam);
        pos.Y = (int)(short)HIWORD(lParam);
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
    case WM_CHAR:
    case WM_SYSCHAR:
    {
        BYTE states[256];
        GetKeyboardState(states);
        if(states[VK_CONTROL] == 0)
        {
            RF_Type::UInt32 glyph = static_cast<RF_Type::UInt32>(wParam);
            if((glyph >= 0xD800) && (glyph <= 0xDBFF))
            {
                MSG nextMessage;
                if(PeekMessageW(&nextMessage, NULL, 0, 0, PM_NOREMOVE))
                {// check if there is an other message without removing it from the queue
                    if(nextMessage.message == WM_CHAR ||
                       nextMessage.message == WM_SYSCHAR)
                    {
                        RF_Type::UInt32 glyphPart = static_cast<RF_Type::UInt32>(nextMessage.wParam);
                        if((glyphPart >= 0xDC00) && (glyphPart <= 0xDFFF))
                        {
                            WCHAR multybyteText[3] = {static_cast<WCHAR>(glyph), static_cast<WCHAR>(glyphPart),0};
                            char languageUtf8[LOCALE_NAME_MAX_LENGTH];
                            size_t writtenBytes = wcstombs(languageUtf8, multybyteText, LOCALE_NAME_MAX_LENGTH);
                            if(writtenBytes > 0)
                            {
                                wnd = dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
                                KeyboardEvent event;
                                event.PrintableCharacter = RF_Type::String(languageUtf8, writtenBytes + 1);
                                wnd->OnPrintableKeyPressed(event);
                            }
                        }
                    }
                }
            }
            else
            {
                WCHAR multybyteText[2] = {static_cast<WCHAR>(glyph),0};
                char languageUtf8[LOCALE_NAME_MAX_LENGTH];
                size_t writtenBytes = wcstombs(languageUtf8, multybyteText, LOCALE_NAME_MAX_LENGTH);
                if(writtenBytes > 0)
                {
                    wnd = dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
                    KeyboardEvent event;
                    event.Key = VirtualKey::NotSet;
                    event.PrintableCharacter = RF_Type::String(languageUtf8, writtenBytes + 1);
                    wnd->OnPrintableKeyPressed(event);
                }
            }
        }
        break;
    }
    case WM_SYSKEYDOWN:
    case WM_KEYDOWN:
    {
        wnd=dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
        if(wParam == VK_CONTROL)
        {// right alt key will throw 2 messages, first left control and then right alt key
            auto hiFlags = HIWORD(lParam);
            if(hiFlags & EXTENDEDKEYBIT != 0)
            {// current message is a left control key
                auto messageTime = GetMessageTime();
                MSG nextMessage;
                if(PeekMessageW(&nextMessage, NULL, 0, 0, PM_NOREMOVE))
                {// check if there is an other message without removing it from the queue
                    if(nextMessage.message == WM_KEYDOWN ||
                       nextMessage.message == WM_SYSKEYDOWN)
                    {
                        if(nextMessage.wParam == VK_MENU &&
                            (HIWORD(nextMessage.lParam) & EXTENDEDKEYBIT) &&
                           nextMessage.time == messageTime)
                        {// remove the left control key message
                            return -1;
                        }
                    }
                }
            }
        }

        KeyboardEvent event;
        MapWindowsToRadonVirtualKeys(wParam, lParam, event);
        wnd->OnKeyPress(event);
        break;
    }
    case WM_SYSKEYUP:
    case WM_KEYUP:
    {
        wnd=dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
        if(wParam == VK_CONTROL)
        {// right alt key will throw 2 messages, first left control and then right alt key
            auto hiFlags = HIWORD(lParam);
            if(hiFlags & EXTENDEDKEYBIT != 0)
            {// current message is a left control key
                auto messageTime = GetMessageTime();
                MSG nextMessage;
                if(PeekMessageW(&nextMessage, NULL, 0, 0, PM_NOREMOVE))
                {// check if there is an other message without removing it from the queue
                    if(nextMessage.message == WM_KEYUP ||
                       nextMessage.message == WM_SYSKEYUP)
                    {
                        if(nextMessage.wParam == VK_MENU &&
                            (HIWORD(nextMessage.lParam) & EXTENDEDKEYBIT) &&
                           nextMessage.time == messageTime)
                        {// remove the left control key message
                            return -1;
                        }
                    }
                }
            }
        }

        KeyboardEvent event;
        MapWindowsToRadonVirtualKeys(wParam, lParam, event);
        wnd->OnKeyRelease(event);
        break;
    }
    case WM_SYSCOMMAND:
    {
        // disallow screen saver and window menu activation 
        switch(wParam)
        {
            case SC_SCREENSAVE:
                return 0;
            case SC_KEYMENU:
                return 0;
        }
        break;
    }
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_XBUTTONDOWN:
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
        if(uMsg == WM_XBUTTONUP)
        {
            if(HIWORD(wParam) == XBUTTON1)
            {
                event.MouseButtonState[VirtualMouseButton::Button4] = true;
            }
            if(HIWORD(wParam) == XBUTTON2)
            {
                event.MouseButtonState[VirtualMouseButton::Button5] = true;
            }
        }
        wnd->OnMouseButtonPressed(event);
        break;
    }
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    case WM_XBUTTONUP:
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
        if(uMsg == WM_XBUTTONUP)
        {
            if(HIWORD(wParam) == XBUTTON1)
            {
                event.MouseButtonState[VirtualMouseButton::Button4] = true;
            }
            if(HIWORD(wParam) == XBUTTON2)
            {
                event.MouseButtonState[VirtualMouseButton::Button5] = true;
            }
        }
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
    case WM_MOUSEWHEEL:
    {
        wnd = dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
        auto zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
        wnd->OnVerticalMouseWheelMoved(zDelta);
        break;
    }
    case WM_MOUSEHWHEEL:
    {
        wnd = dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
        auto zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
        wnd->OnHorizontalMouseWheelMoved(zDelta);
        break;
    }
    case WM_SETFOCUS:
    {
        wnd = dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
        wnd->OnGotFocus();
        break;
    }
    case WM_KILLFOCUS:
    {
        wnd = dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
        wnd->OnLostFocus();
        break;
    }
    case WM_DPICHANGED:
    {
        wnd = dynamic_cast<WindowsWindow*>(WindowsWindow::GetObjectByHandle(hWnd));
        RF_Geo::Point2D<> dpi;
        dpi.Y = HIWORD(wParam);
        dpi.X = LOWORD(wParam);

        RECT* const prcNewWindow = (RECT*)lParam;
        SetWindowPos(hWnd,
                     NULL,
                     prcNewWindow->left,
                     prcNewWindow->top,
                     prcNewWindow->right - prcNewWindow->left,
                     prcNewWindow->bottom - prcNewWindow->top,
                     SWP_NOZORDER | SWP_NOACTIVATE);

        wnd->OnDPIChanged(dpi);
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
    return DefWindowProcW(hWnd,uMsg,wParam,lParam);
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
,m_WindowFlags(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN)
{
    WindowsWindow::m_Objects.AddLast(this);
}

WindowsWindow::~WindowsWindow()
{
    for(RF_Type::Size i = 0; i<m_Objects.Count(); i++)
    if (m_Objects[i]->m_Handle==m_Handle)
    {
        WindowsWindow::m_Objects.RemoveAt(i);
        break;
    }
    DestroyWindow(m_Handle);
}

void* WindowsWindow::Handle()const
{
    return (void*)&m_Handle;
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
                WCHAR languageUtf16[LOCALE_NAME_MAX_LENGTH];
                mbstowcs(languageUtf16, m_Title.c_str(), LOCALE_NAME_MAX_LENGTH);
                m_Handle=CreateWindowExW(0,L"#32770", languageUtf16,
                                            WS_VISIBLE | m_WindowFlags,
                                            m_Pos.X, m_Pos.Y, m_Size.Width, m_Size.Height,
                                            0, 0, 0, NULL );
                SetWindowLongPtrW(m_Handle,GWLP_WNDPROC,(LONG_PTR)WndProc);
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
    WCHAR languageUtf16[LOCALE_NAME_MAX_LENGTH];
    mbstowcs(languageUtf16, Value.c_str(), LOCALE_NAME_MAX_LENGTH);
    if (SetWindowTextW(m_Handle, languageUtf16) || GetLastError()==0)
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
            m_WindowFlags &= ~WS_POPUP;
            m_WindowFlags |= WS_OVERLAPPEDWINDOW;
            SetWindowLongPtr( m_Handle, GWL_STYLE, m_WindowFlags );
            SetWindowPos( m_Handle, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE );
        }
        else
        {
            m_WindowFlags &= ~WS_OVERLAPPEDWINDOW;
            m_WindowFlags |= WS_POPUP;
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
    for(RF_Type::Size i = 0; i<m_Objects.Count(); i++)
        if (m_Objects[i]->m_Handle==Handle)
            return m_Objects[i];
    return 0;
}

UInt32 WindowsWindow::GetObjectCount()
{
    return static_cast<UInt32>(m_Objects.Count());
}

WindowsWindow* WindowsWindow::GetObjectByIndex(const UInt32 Index)
{
    return m_Objects[Index];
}

HWND WindowsWindow::GetHandle()const
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

RF_Type::Bool WindowsWindow::HasFocus()const
{
    return GetForegroundWindow() == m_Handle;
}

RF_Geo::Point2D<> WindowsWindow::GetCursorPosition() const
{
    RF_Geo::Point2D<> result;
    POINT p;

    GetCursorPos(&p);
    ScreenToClient(m_Handle, &p);
    result.X = p.x;
    result.Y = p.y;
    
    return result;
}

RF_Mem::AutoPointerArray<RF_Type::UInt8> WindowsWindow::CaptureClientRect()
{
    RF_Mem::AutoPointerArray<RF_Type::UInt8> result;
    HDC hdc = GetDC(NULL); // get the desktop device context
    HDC hDest = CreateCompatibleDC(hdc); // create a device context to use yourself
    // get the height and width of the screen
    int height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    int width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    // create a bitmap
    HBITMAP hbDesktop = CreateCompatibleBitmap(hdc, width, height);
    // use the previously created device context with the bitmap
    SelectObject(hDest, hbDesktop);
    // copy from the desktop device context to the bitmap device context
    // call this once per 'frame'
    BitBlt(hDest, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
    // release the desktop context you got..
    ReleaseDC(NULL, hdc);
    // ..and delete the context you created
    DeleteDC(hDest);
    // Retrieve the bitmap color format, width, and height.  
    BITMAP bmp;
    if(GetObject(hbDesktop, sizeof(BITMAP), (LPSTR)&bmp))
    {
        // Convert the color format to a count of bits.  
        WORD cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
        if(cClrBits == 1)
            cClrBits = 1;
        else if(cClrBits <= 4)
            cClrBits = 4;
        else if(cClrBits <= 8)
            cClrBits = 8;
        else if(cClrBits <= 16)
            cClrBits = 16;
        else if(cClrBits <= 24)
            cClrBits = 24;
        else cClrBits = 32;

        result.New(bmp.bmWidthBytes*bmp.bmHeight).Copy(bmp.bmBits, bmp.bmWidthBytes*bmp.bmHeight);
    }
    return result;
}

void WindowsWindow::ChangeCursor(const Cursor& NewCursor)
{
    HCURSOR cursorHandle = LoadCursor(NULL, IDC_ARROW);
    RF_Type::Int32 which = NewCursor.GetType();
    switch(which)
    {
        case Cursor::NorthWestResize:
        case Cursor::SouthEastResize:
            cursorHandle = LoadCursor(NULL, IDC_SIZENWSE);
            break;
        case Cursor::NorthEastResize:
        case Cursor::SouthWestResize:
            cursorHandle = LoadCursor(NULL, IDC_SIZENESW);
            break;
        case Cursor::NorthResize:
        case Cursor::SouthResize:
            cursorHandle = LoadCursor(NULL, IDC_SIZENS);
            break;
        case Cursor::EastResize:
        case Cursor::WestResize:
            cursorHandle = LoadCursor(NULL, IDC_SIZEWE);
            break;
        case Cursor::Move:
            cursorHandle = LoadCursor(NULL, IDC_SIZEALL);
            break;
    }
    SetCursor(cursorHandle);
}
