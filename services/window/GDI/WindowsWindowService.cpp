#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Forms/WindowServiceLocator.hpp"
#include "WindowsWindowService.hpp"
#include "WindowsWindow.hpp"
#include "WindowsApplication.hpp"
#include <RadonFramework/Math/Geometry/Size2D.hpp>
#include <RadonFramework/IO/Log.hpp>
#include <SetupApi.h>
#pragma comment(lib, "setupapi.lib")

using namespace RadonFramework::Forms;
using namespace RadonFramework::Math::Geometry;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::IO;

static String CurrResNotSupportedError(
    "Can't find current resolution in the supported resolution list of this display.",
    sizeof("Can't find current resolution in the supported resolution list of this display."));

WindowsWindowService::WindowsWindowService(const RF_Type::String &Name)
:WindowService(Name),m_Application(0)
{
}

WindowsWindowService::~WindowsWindowService()
{
}

AbstractWindow* WindowsWindowService::NewWindow()
{
  return new WindowsWindow(this);
}

AbstractApplication* WindowsWindowService::Application()
{
  if (!m_Application)
    m_Application=new WindowsApplication;
  return m_Application;
}

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, 
    LPRECT lprcMonitor, LPARAM dwData)
{
    AutoVector<DisplayInformation>* list = reinterpret_cast<AutoVector<DisplayInformation>*>(dwData);
    MONITORINFOEX mi;
    mi.cbSize = sizeof(mi);
    GetMonitorInfo(hMonitor, &mi);
    String displayName(mi.szDevice, 32);
    for (RF_Type::Size i = 0; i < list->Count(); ++i)
    {
        if((*list)[i]->DisplayName == displayName)
        {
            (*list)[i]->Left = mi.rcWork.left;
            (*list)[i]->Top = mi.rcWork.top;
            break;
        }
    }
    return true;
}

const GUID GUID_CLASS_MONITOR = {0x4d36e96e, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18};

// Credits for following routine goes to KindDragon and Earlz from http://stackoverflow.com/a/579448 .
void GetMonitorSizeFromEDID(const RF_Type::String& AdapterName, DisplayInformation& Display)
{
    RF_Type::String adapterName(AdapterName);
    auto adapterChain = adapterName.Split(String("\\"));
    RF_Type::String model = adapterChain[1];

    Display.HorizontalLengthInMilimeter = 0;
    Display.VerticalLengthInMilimeter = 0;

    HDEVINFO devInfo = SetupDiGetClassDevsEx(
        &GUID_CLASS_MONITOR, //class GUID
        NULL, //enumerator
        NULL, //HWND
        DIGCF_PRESENT, // Flags //DIGCF_ALLCLASSES|
        NULL, // device info, create a new one.
        NULL, // machine name, local machine
        NULL);// reserved

    if(NULL != devInfo)
    {
        for(ULONG i = 0; ERROR_NO_MORE_ITEMS != GetLastError(); ++i)
        {
            SP_DEVINFO_DATA devInfoData;
            memset(&devInfoData, 0, sizeof(devInfoData));
            devInfoData.cbSize = sizeof(devInfoData);

            if(SetupDiEnumDeviceInfo(devInfo, i, &devInfoData))
            {
                char Instance[128];
                SetupDiGetDeviceInstanceId(devInfo, &devInfoData, Instance, MAX_PATH, NULL);

                if(-1 == RF_Type::String(Instance, 128).Contains(model))
                    continue;

                HKEY hDevRegKey = SetupDiOpenDevRegKey(devInfo, &devInfoData,
                                                       DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);

                if(!hDevRegKey || (hDevRegKey == INVALID_HANDLE_VALUE))
                    continue;

                DWORD dwType, AcutalValueNameLength = 128;
                char valueName[128];

                BYTE EDIDdata[1024];
                DWORD edidsize = sizeof(EDIDdata);

                RF_Type::String edid("EDID");
                for(LONG i = 0, retValue = ERROR_SUCCESS; retValue != ERROR_NO_MORE_ITEMS; ++i)
                {
                    retValue = RegEnumValue(hDevRegKey, i, &valueName[0],
                                            &AcutalValueNameLength, NULL, &dwType,
                                            EDIDdata, // buffer
                                            &edidsize); // buffer size

                    if(retValue != ERROR_SUCCESS || RF_Type::String(valueName, 128) != edid)
                        continue;

                    Display.HorizontalLengthInMilimeter = ((EDIDdata[68] & 0xF0) << 4) + EDIDdata[66];
                    Display.VerticalLengthInMilimeter = ((EDIDdata[68] & 0x0F) << 8) + EDIDdata[67];
                }
                RegCloseKey(hDevRegKey);
            }
        }
        SetupDiDestroyDeviceInfoList(devInfo);
    }
}

AutoVector<DisplayInformation> WindowsWindowService::GetAllDisplays()
{
    AutoVector<DisplayInformation> list;
    DISPLAY_DEVICE dd;
    dd.cb = sizeof(dd); 
    DWORD dev = 0; 

    //go through all graphics adapter
    while (EnumDisplayDevices(0, dev++, &dd,0))
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

            DWORD mon = 0;
            DISPLAY_DEVICE mondd;
            mondd.cb = sizeof(mondd);
            // find the display device
            if(EnumDisplayDevices(dd.DeviceName, 0, &mondd,0))
            {
                RF_Type::String adapterName(mondd.DeviceID, 128);
                GetMonitorSizeFromEDID(RF_Type::String(mondd.DeviceID), *display);
            }

            display->AvaiableResolution = Array<Resolution>(reslist.Count());
            for(UInt32 i = 0; i<reslist.Count(); ++i)
                RF_SysMem::Copy(&display->AvaiableResolution(i), reslist[i], sizeof(Resolution));
            list.PushBack(display);
        }

        ZeroMemory(&dd, sizeof(dd));
        dd.cb = sizeof(dd);
    }

    // Go through all monitors attached to the active virtual desktop(subset of devices).
    EnumDisplayMonitors(0, 0, &MonitorEnumProc, (LPARAM)&list);
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

RF_Type::Bool WindowsWindowService::IsMouseButtonPressed(RF_IO::VirtualMouseButton::Type Which)
{
    int mapping[RF_IO::VirtualMouseButton::MAX] = {VK_LBUTTON, VK_RBUTTON, VK_MBUTTON};
    return GetAsyncKeyState(mapping[Which]) & 0x8000;
}

void WindowsWindowService::Register()
{
    RF_Mem::AutoPointer<WindowService> gdi(new WindowsWindowService("Windows_GDI"_rfs));
    WindowServiceLocator::Register(gdi);
}
