#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/backend/Windows/Forms/WindowsApplication.hpp>
#include <RadonFramework/backend/Windows/Forms/WindowsWindow.hpp>
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <tlhelp32.h>

using namespace RadonFramework::Forms;

WindowsApplication::WindowsApplication()
:m_Active(false)
{
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
        SleepEx(0, true);// necessary for completion port api
        while (PeekMessage(&msg,0,0,0,PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
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

bool WindowsApplication::IsRunningOnDesktop()
{
    bool result = false;
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

void WindowsApplication::ShowConsole(bool isVisible)
{
    ShowWindow(GetConsoleWindow(), isVisible? SW_SHOW : SW_HIDE);
}

