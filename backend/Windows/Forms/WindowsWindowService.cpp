#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/backend/Windows/Forms/WindowsWindowService.hpp>
#include <RadonFramework/backend/Windows/Forms/WindowsWindow.hpp>
#include <RadonFramework/backend/Windows/Forms/WindowsApplication.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>
#include <RadonFramework/IO/Log.hpp>

using namespace RadonFramework::Forms;
using namespace RadonFramework::Math::Geometry;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::IO;

static String CurrResNotSupportedError="Can't find current resolution in the supported resolution list of this display.";

WindowsWindowService::WindowsWindowService(const RadonFramework::Core::Types::String &Name)
:WindowService(Name),m_Application(0)
{
}

WindowsWindowService::~WindowsWindowService()
{
}

IWindow* WindowsWindowService::NewWindow()
{
  return new WindowsWindow(this);
}

IApplication* WindowsWindowService::Application()
{
  if (!m_Application)
    m_Application=new WindowsApplication;
  return m_Application;
}

AutoVector<DisplayInformation> WindowsWindowService::GetAllDisplays()
{
    AutoVector<DisplayInformation> list;
    DISPLAY_DEVICE dd;
    dd.cb = sizeof(dd); 
    DWORD dev = 0; 
    //go through all desktops
    while (EnumDisplayDevices(0, dev++, &dd,0))
    {
        //DISPLAY_DEVICE ddMon;
        //ZeroMemory(&ddMon, sizeof(ddMon));
        //ddMon.cb = sizeof(ddMon);
        //DWORD devMon = 0;
        //all monitors of this desktop
        //while (EnumDisplayDevices(dd.DeviceName, devMon++, &ddMon, 0))
        {
            if (dd.StateFlags & DISPLAY_DEVICE_ACTIVE)
            {
                AutoPointer<DisplayInformation> display(new DisplayInformation);
                display->DisplayName=String(dd.DeviceName,32);
                display->Description=String(dd.DeviceString,128);
                display->IsAttachedToDesktop=dd.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP;
                display->IsPrimary=(dd.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)!=0;
                display->IsMirroring=(dd.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER)!=0;
                
                int index = 0;
                DEVMODE dm;
                // initialize the DEVMODE structure
                ZeroMemory(&dm, sizeof(dm));
                dm.dmSize = sizeof(dm);
                AutoVector<Resolution> reslist;
                while (0 != EnumDisplaySettings(dd.DeviceName,index++, &dm))
                {
                    AutoPointer<Resolution> res(new Resolution);
                    res->Width=dm.dmPelsWidth;
                    res->Height=dm.dmPelsHeight;
                    res->BitsPerPixel=dm.dmBitsPerPel;
                    res->Frequency=dm.dmDisplayFrequency;
                    reslist.PushBack(res);
                    // initialize the DEVMODE structure
                    ZeroMemory(&dm, sizeof(dm));
                    dm.dmSize = sizeof(dm);
                }
                display->AvaiableResolution=Array<Resolution>(reslist.Size());
                for (UInt32 i=0;i<reslist.Size();++i)
                    RFMEM::Copy(&display->AvaiableResolution(i), reslist[i], sizeof(Resolution));
                list.PushBack(display);
            }
//            ZeroMemory(&ddMon, sizeof(ddMon));
//            ddMon.cb = sizeof(ddMon);
        }
        ZeroMemory(&dd, sizeof(dd));
        dd.cb = sizeof(dd);
    }
    return list;
}

WindowServiceError WindowsWindowService::ScreenResolution( const DisplayInformation& DisplayInfo, UInt32& ResolutionListIndex )
{
    DEVMODE dm;
    // initialize the DEVMODE structure
    ZeroMemory(&dm, sizeof(dm));
    dm.dmSize = sizeof(dm);
    EnumDisplaySettings(DisplayInfo.DisplayName.c_str(), ENUM_CURRENT_SETTINGS, &dm);
    for(UInt32 i=0;i<DisplayInfo.AvaiableResolution.Count();++i)
        if (DisplayInfo.AvaiableResolution(i).Width==dm.dmPelsWidth &&
            DisplayInfo.AvaiableResolution(i).Height==dm.dmPelsHeight &&
            DisplayInfo.AvaiableResolution(i).BitsPerPixel==dm.dmBitsPerPel &&
            DisplayInfo.AvaiableResolution(i).Frequency==dm.dmDisplayFrequency)
        {
            ResolutionListIndex=i;
            return WindowServiceError::Generate(WindowServiceErrors::NoError);
        }
    return WindowServiceError::Generate(WindowServiceErrors::InternalError,CurrResNotSupportedError);
}

void WindowsWindowService::ScreenResolution(const DisplayInformation& DiplayInfo, const Resolution& NewResolution)
{
    DEVMODE dm;
    ZeroMemory(&dm, sizeof(dm));
    dm.dmSize=sizeof(dm);
    if (0!=EnumDisplaySettings(DiplayInfo.DisplayName.c_str(), ENUM_CURRENT_SETTINGS, &dm))
    {
        dm.dmBitsPerPel=NewResolution.BitsPerPixel;
        dm.dmPelsHeight=NewResolution.Height;
        dm.dmPelsWidth=NewResolution.Width;
        dm.dmDisplayFrequency=NewResolution.Frequency;
        dm.dmFields=(DM_PELSWIDTH|DM_PELSHEIGHT|DM_BITSPERPEL|DM_DISPLAYFREQUENCY);
        LONG ret=ChangeDisplaySettings(&dm,CDS_TEST);
        if (ret==DISP_CHANGE_SUCCESSFUL)
            ret=ChangeDisplaySettings(&dm,0);
        else
            LogError("EnumDisplaySettings failed:%d", GetLastError());
    }
    else
        LogError("EnumDisplaySettings failed:%d", GetLastError());
}
