#include "RadonFramework/precompiled.hpp"
#include "WindowsApplication.hpp"
#include "WindowsWindow.hpp"
#include "RadonFramework/System/DynamicLibrary.hpp"
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <tlhelp32.h>

#include <ShellScalingApi.h>
typedef BOOL(*SetProcessDpiAwarenessFunction)(PROCESS_DPI_AWARENESS value);

using namespace RadonFramework::Forms;

WindowsApplication::WindowsApplication()
:m_Active(false)
{
    auto lib = RF_Sys::DynamicLibrary::LoadSystemLibrary("user32.dll"_rfs);
    if(lib)
    {
        auto SetProcessDpiAwareness = (SetProcessDpiAwarenessFunction)lib->GetFunctionAddress("SetProcessDpiAwarenessInternal"_rfs);
        SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
    }
}

WindowsApplication::~WindowsApplication()
{
}

void WindowsApplication::Run(Form *MainForm)
{
    m_Active=true;
    MSG msg;

    while (m_Active==true && (MainForm == 0 || (MainForm != 0 && MainForm->Visible())))
    {
        // process Asynchronous Procedure Call(APC) messages
        SleepEx(0, true);

        while (PeekMessageW(&msg,0,0,0,PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        for (unsigned int i=0;i<WindowsWindow::GetObjectCount();i++)
            WindowsWindow::GetObjectByIndex(i)->OnIdle();

        if (MainForm == 0)
            break;
    }
}

void WindowsApplication::End()
{
  m_Active=false;
}

RF_Type::Bool WindowsApplication::IsRunningOnDesktop()
{
    RF_Type::Bool result = false;
    DWORD sp = GetCurrentProcessId();
    HANDLE ptree = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 e = {0}; 
    e.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(ptree, &e)) 
        do
        {
            if (e.th32ProcessID == sp) 
            {
                sp = e.th32ParentProcessID;
                Process32First(ptree, &e);

                do
                {
                    if (e.th32ProcessID == sp) 
                    {
                        if (strcmp("explorer.exe", e.szExeFile) == 0)
                            result = true;

                        break;
                    }
                }
                while (Process32Next(ptree, &e));

                break;
            }
        }
        while (Process32Next(ptree, &e));

    CloseHandle(ptree);

    return result;
}

void WindowsApplication::ShowConsole(RF_Type::Bool isVisible)
{
    ShowWindow(GetConsoleWindow(), isVisible? SW_SHOW : SW_HIDE);
}

RF_Type::String RadonFramework::Forms::WindowsApplication::GetClipboardText()
{
    RF_Type::String result;
    if(IsClipboardFormatAvailable(CF_UNICODETEXT))
    {
        // Because the process is interested in the clipboard we don't specify a window handle.
        if(OpenClipboard(NULL))
        {
            auto handle = GetClipboardData(CF_UNICODETEXT);
            if(handle)
            {
                void* multybyteText = GlobalLock(handle);
                if(multybyteText)
                {
                    RF_Type::Size bytes = GlobalSize(handle);
                    RF_Mem::AutoPointerArray<RF_Type::UInt8> buffer(bytes);
                    bytes = wcstombs(reinterpret_cast<char*>(buffer.Get()), reinterpret_cast<WCHAR*>(multybyteText), buffer.Size());
                    if(bytes > 0)
                    {
                        result = RF_Type::String(buffer.Release(), bytes, RF_Core::DataManagment::TransfereOwnership);
                    }
                    GlobalUnlock(handle);
                }
            }
            CloseClipboard();
        }        
    }
    return result;
    
}

void RadonFramework::Forms::WindowsApplication::SetClipboardText(const RF_Type::String& NewText)
{
    if(IsClipboardFormatAvailable(CF_UNICODETEXT))
    {
        size_t elements = mbstowcs(0,NewText.c_str(), NewText.Size()) + 1;
        RF_Mem::AutoPointerArray<RF_Type::UInt16> languageUtf16(elements);
        size_t writtenBytes = mbstowcs(reinterpret_cast<WCHAR*>(languageUtf16.Get()), NewText.c_str(), NewText.Size()) * sizeof(WCHAR) + sizeof(WCHAR);
        if(writtenBytes > 0)
        {
            auto stringHandle = GlobalAlloc(GMEM_MOVEABLE, writtenBytes);
            if (stringHandle)
            {
                memcpy(GlobalLock(stringHandle), languageUtf16.Get(), writtenBytes);
                GlobalUnlock(stringHandle);
                if(OpenClipboard(NULL))
                {
                    EmptyClipboard();
                    SetClipboardData(CF_UNICODETEXT, stringHandle);
                    CloseClipboard();
                }
                else
                {
                    GlobalFree(stringHandle);
                }
            }
        }
    }
}

