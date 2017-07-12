#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Drawing/SystemTrayServiceWindows.hpp"
#include "RadonFramework/Collections/HashMap.hpp"
#include "RadonFramework/Collections/Array.hpp"
#include "RadonFramework/IO/File.hpp"
#include "RadonFramework/System/IO/FileSystem.hpp"
#include <windows.h>
#include <Windowsx.h>
#include <Strsafe.h>

namespace RadonFramework::Core::Idioms {

template<>
struct RF_Idiom::PImpl<RF_SysDraw::SystemTrayServiceWindows>::Data
{
    class TrayIconItem
    {
    public:
        ~TrayIconItem()
        {
            if(m_MenuHandle)
            {
                DestroyMenu(m_MenuHandle);
                m_MenuHandle = 0;
            }
        }
        HMENU m_MenuHandle;
        RF_Mem::AutoPointer<NOTIFYICONDATA> m_NotificationData;
    };

    Data()
    {

    }

    ~Data()
    {

    }

    void OnPopup(UINT uMsg, long x, long y)
    {
        if(m_MessageLookup.ContainsKey(uMsg))
        {
            if(m_MessageLookup[uMsg]->m_MenuHandle)
            {
                SetForegroundWindow(m_HWND);
                TrackPopupMenuEx(m_MessageLookup[uMsg]->m_MenuHandle,
                    TPM_RIGHTBUTTON | TPM_VERNEGANIMATION, x, y, m_HWND, 0);
            }
        }
    }

    HMENU AddSubMenu(const RF_Draw::PopupMenu& Menu)
    {
        HMENU result = 0;
        if(Menu.Items.Count() > 0)
        {
            result = CreatePopupMenu();

            for(RF_Type::Size i = 0; i < Menu.Items.Count(); ++i)
            {
                auto& menuItem = Menu.Items(i);
                if(menuItem.Items.Count() > 0)
                {
                    HMENU submenu = AddSubMenu(menuItem);
                    AppendMenu(result, MF_POPUP | MF_STRING, (UINT_PTR)submenu, menuItem.Name.c_str());
                }
                else
                {
                    UINT flags = MF_STRING;
                    if(menuItem.CanChecked)
                    {
                        if(menuItem.IsChecked)
                        {
                            flags |= MF_CHECKED;
                        }
                        else
                        {
                            flags |= MF_UNCHECKED;
                        }
                        m_CheckMenuItemLookup[menuItem.ActionId] = result;
                    }
                    if(menuItem.IsSeperator)
                    {
                        flags |= MF_SEPARATOR;
                    }

                    AppendMenu(result, flags, menuItem.ActionId, menuItem.Name.c_str());
                }
            }
        }
        return result;
    }

    HMENU AddPopupMenu(const RF_Draw::TrayIcon& Settings)
    {
        HMENU result = 0;
        if(Settings.Menu.Items.Count() > 0)
        {
            result = AddSubMenu(Settings.Menu);
        }
        return result;
    }

    void HandleToggleCheckBoxCommand(WORD wParam)
    {
        if(m_CheckMenuItemLookup.ContainsKey(wParam))
        {
            UINT state = GetMenuState(m_CheckMenuItemLookup[wParam], wParam, MF_BYCOMMAND);
            if (state != -1)
            {
                if(state & MFS_CHECKED)
                {
                    state &= ~MFS_CHECKED;
                }
                else
                {
                    state |= MFS_CHECKED;
                }

                CheckMenuItem(m_CheckMenuItemLookup[wParam], wParam, state);
            }
        }
    }

    RF_Collect::HashMap<RF_Type::UInt32, TrayIconItem* > m_HandleLookup;
    RF_Collect::HashMap<RF_Type::UInt32, TrayIconItem* > m_MessageLookup;
    RF_Collect::HashMap<RF_Type::UInt32, HMENU > m_CheckMenuItemLookup;
    RF_Collect::Array<TrayIconItem> m_IconData;
    HWND m_HWND;
};
}

RF_SysDraw::SystemTrayServiceWindows* SYSTEMTRAYSERVICE = 0;
RF_Idiom::PImpl<RF_SysDraw::SystemTrayServiceWindows>::Data* SYSTEMTRAYSERVICEDATA = 0;
const RF_Type::UInt32 MAX_WM_APP = 0xBFFF;

LRESULT CALLBACK WindowMessageProcessor(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    WORD message;
    if(uMsg >= WM_APP && uMsg <= MAX_WM_APP)
    {
        message = LOWORD(lParam);
        if(message == WM_RBUTTONUP)
        {
            if(SYSTEMTRAYSERVICEDATA)
            {
                POINT position;
                GetCursorPos(&position);
                SYSTEMTRAYSERVICEDATA->OnPopup(uMsg, position.x, position.y);
            }
        }
    }
    else
    {
        switch(uMsg)
        {
            case WM_COMMAND:
                if(SYSTEMTRAYSERVICE)
                {
                    SYSTEMTRAYSERVICE->OnAction(LOWORD(wParam));
                    SYSTEMTRAYSERVICEDATA->HandleToggleCheckBoxCommand(LOWORD(wParam));
                }
                break;
            default:
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
        
    }
    return 0;
}

namespace RadonFramework::System::Drawing {

// http://blogs.msdn.com/b/oldnewthing/archive/2004/10/25/247180.aspx
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
const char* CLASS_NAME = "SYSTEMTRAYSERVICE";

SystemTrayServiceWindows::SystemTrayServiceWindows(const RF_Type::String &Name)
:SystemTrayService(Name)
{
    SYSTEMTRAYSERVICE = this;
    SYSTEMTRAYSERVICEDATA = &*m_PImpl;
    // Create a message only window to process events from windows message system
    // This kind of window don't create a visual window and will not be listed as such.
    WNDCLASSEX wx = {};
    wx.cbSize = sizeof(WNDCLASSEX);
    wx.lpfnWndProc = WindowMessageProcessor;
    wx.hInstance = (HINSTANCE)&__ImageBase;
    wx.lpszClassName = CLASS_NAME;
    m_PImpl->m_HWND = 0;
    if(RegisterClassEx(&wx)) 
    {
        m_PImpl->m_HWND = CreateWindowEx(0, CLASS_NAME, "dummy_name", 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, NULL);
    }
}

SystemTrayServiceWindows::~SystemTrayServiceWindows()
{
    m_PImpl->m_HandleLookup.Clear();
    m_PImpl->m_MessageLookup.Clear();
    m_PImpl->m_CheckMenuItemLookup.Clear();
    m_PImpl->m_IconData.Resize(0);

    if (DestroyWindow(m_PImpl->m_HWND))
        m_PImpl->m_HWND = 0;
    UnregisterClass(CLASS_NAME, (HINSTANCE)&__ImageBase);
}

SystemTrayService::Handle SystemTrayServiceWindows::AddIcon(const RF_Draw::TrayIcon& Settings)
{
    // early exit if there are too many icons registered
    if(m_PImpl->m_IconData.Count() > MAX_WM_APP - WM_APP)
        return 0;

    RF_Mem::AutoPointer<NOTIFYICONDATA> notifyData(new NOTIFYICONDATA);

    RF_SysMem::Set(notifyData.Get(), 0, sizeof(NOTIFYICONDATA));
    notifyData->cbSize = sizeof(NOTIFYICONDATA);
    notifyData->hWnd = m_PImpl->m_HWND;
    notifyData->uVersion = NOTIFYICON_VERSION_4;
    notifyData->uFlags = NIF_GUID | NIF_MESSAGE;
    notifyData->uCallbackMessage = WM_APP + m_PImpl->m_IconData.Count();
    CoCreateGuid(&notifyData->guidItem);

    if(!Settings.Notification.IsEmpty())
    {
        notifyData->uFlags |= NIF_INFO | NIF_SHOWTIP;
        StringCchCopyA(notifyData->szInfo, ARRAYSIZE(notifyData->szInfo), Settings.Notification.c_str());
    }

    if(!Settings.Tooltip.IsEmpty())
    {
        notifyData->uFlags |= NIF_TIP;
        StringCchCopyA(notifyData->szTip, ARRAYSIZE(notifyData->szTip), Settings.Tooltip.c_str());
    }

    // search in the resource file
    HINSTANCE hinstance = GetModuleHandle(NULL);
    notifyData->hIcon = LoadIcon(hinstance, Settings.Icon.c_str());

    if(notifyData->hIcon == 0)
    {// search for the file on disc
        RF_IO::File icon;
        RF_Type::String systemPath;

        RF_IO::Uri uri(Settings.Icon);
        RF_SysFile::UriToSystemPath(uri,systemPath);
        RF_SysFile::RealPath(systemPath, systemPath);
        icon.SetLocation(uri);
        if(icon.Exists())
        {
            int min = GetSystemMetrics(SM_CXSMICON);
            notifyData->hIcon = (HICON)LoadImage(NULL, systemPath.c_str(), IMAGE_ICON,
                                                 min, min, LR_LOADFROMFILE);
        }
    }

    if(notifyData->hIcon != 0)
    {// set icon visible
        notifyData->uFlags |= NIF_ICON;
    }

    Handle handle = 0;
    SystemTrayService::Handle result = Shell_NotifyIcon(NIM_ADD, notifyData.Get());
    if(result)
    {
        handle = static_cast<Handle>(reinterpret_cast<intptr_t>(notifyData.Get()));
        
        m_PImpl->m_IconData.Resize(m_PImpl->m_IconData.Count() + 1);
        auto& item = m_PImpl->m_IconData(m_PImpl->m_IconData.Count() - 1);
        m_PImpl->m_MessageLookup[notifyData->uCallbackMessage] = &item;
        m_PImpl->m_HandleLookup[handle] = &item;
        
        item.m_MenuHandle = m_PImpl->AddPopupMenu(Settings);
        item.m_NotificationData = notifyData;
    }

    return handle;
}

void SystemTrayServiceWindows::Remove(Handle IconInstance)
{
    if(m_PImpl->m_HandleLookup.ContainsKey(IconInstance))
    {
        NOTIFYICONDATA* data = m_PImpl->m_HandleLookup[IconInstance]->m_NotificationData.Get();
        Shell_NotifyIcon(NIM_DELETE, data);
        m_PImpl->m_HandleLookup.Erase(IconInstance);
        m_PImpl->m_MessageLookup.Erase(data->uCallbackMessage);
        
        for (RF_Type::Size i = 0; i < m_PImpl->m_IconData.Count(); ++i)
        {
            if(m_PImpl->m_IconData(i).m_NotificationData.Get() == data)
            {
                if(m_PImpl->m_IconData.Count() > 1 ||
                   i < m_PImpl->m_IconData.Count())
                {
                    m_PImpl->m_IconData.Exchange(i, m_PImpl->m_IconData.Count()-1);
                }
                m_PImpl->m_IconData.Resize(m_PImpl->m_IconData.Count()-1);
                break;
            }
        }
    }
}

RF_Type::Bool SystemTrayServiceWindows::IsSupported()
{
    return true;
}

}