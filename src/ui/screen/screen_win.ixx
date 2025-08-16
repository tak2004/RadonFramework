module;
#include <Windows.h>
#include <SetupAPI.h>
export module rf.ui.screen:system;
import rf.core.memory;
import rf.core.types;
import rf.core.cpu;
import :data;

const GUID GUID_CLASS_MONITOR = { 0x4d36e96e, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08,
                                 0x00,       0x2b,   0xe1,   0x03, 0x18 };

// http://stackoverflow.com/a/579448
void GetMonitorSizeFromEDID(const rf::strview AdapterName, rf::ScreenData& Display) {
    rf::strview model;
    auto modelStart = rf::findFirstOf(AdapterName,'\\', 0) + 1;
    auto modelEnd = rf::findFirstOf(AdapterName,'\\', modelStart);
    model = rf::slice(AdapterName,modelStart, modelEnd - modelStart);

    Display.horizontalLengthInMilimeter = 0;
    Display.verticalLengthInMilimeter = 0;

    HDEVINFO devInfo = SetupDiGetClassDevsEx(&GUID_CLASS_MONITOR, // class GUID
        NULL,                // enumerator
        NULL,                // HWND
        DIGCF_PRESENT,       // Flags //DIGCF_ALLCLASSES|
        NULL,                // device info, create a new one.
        NULL,                // machine name, local machine
        NULL);               // reserved

    if (NULL != devInfo) {
        for (ULONG i = 0; ERROR_NO_MORE_ITEMS != GetLastError(); ++i) {
            SP_DEVINFO_DATA devInfoData;
            memset(&devInfoData, 0, sizeof(devInfoData));
            devInfoData.cbSize = sizeof(devInfoData);

            if (SetupDiEnumDeviceInfo(devInfo, i, &devInfoData)) {
                char Instance[MAX_PATH];
                SetupDiGetDeviceInstanceIdA(devInfo, &devInfoData, Instance, MAX_PATH, NULL);
                auto setupModel = rf::strview{ Instance,MAX_PATH };
                modelStart = rf::findFirstOf(setupModel,'\\',0) + 1;
                modelEnd = rf::findFirstOf(setupModel,'\\', modelStart);
                setupModel = rf::slice(setupModel, modelStart, modelEnd - modelStart);
                if (rf::compare(setupModel,rf::constmem{.address=Instance, .bytes=MAX_PATH}) != 0)
                    continue;

                HKEY hDevRegKey =
                    SetupDiOpenDevRegKey(devInfo, &devInfoData, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);

                if (!hDevRegKey || (hDevRegKey == INVALID_HANDLE_VALUE))
                    continue;

                DWORD dwType, AcutalValueNameLength = 128;
                char valueName[128];

                BYTE EDIDdata[1024];
                DWORD edidsize = sizeof(EDIDdata);

                rf::strview edid("EDID");
                for (LONG i = 0, retValue = ERROR_SUCCESS; retValue != ERROR_NO_MORE_ITEMS; ++i) {
                    retValue =
                        RegEnumValueA(hDevRegKey, i, &valueName[0], &AcutalValueNameLength, NULL, &dwType,
                            EDIDdata,   // buffer
                            &edidsize); // buffer size

                    if (retValue != ERROR_SUCCESS || rf::compare(rf::strview(valueName, 128), edid))
                        continue;

                    Display.horizontalLengthInMilimeter = ((EDIDdata[68] & 0xF0) << 4) + EDIDdata[66];
                    Display.verticalLengthInMilimeter = ((EDIDdata[68] & 0x0F) << 8) + EDIDdata[67];
                }
                RegCloseKey(hDevRegKey);
            }
        }
        SetupDiDestroyDeviceInfoList(devInfo);
    }
}

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor,
    LPARAM dwData) {
    auto* list = reinterpret_cast<rf::arr<rf::ScreenData>*>(dwData);
    MONITORINFOEXA mi;
    mi.cbSize = sizeof(mi);
    GetMonitorInfoA(hMonitor, &mi);
    rf::constmem displayName{ .address = mi.szDevice,.bytes = 32 };
    for (auto i = 0; i < list->count; ++i) {
        if (rf::compare(rf::constmem{ .address=(*list).elements[i].name.address,.bytes = 32 }, displayName) == 0) {
            (*list).elements[i].x = mi.rcWork.left;
            (*list).elements[i].y = mi.rcWork.top;
            break;
        }
    }
    return true;
}

export namespace rf {
template <IsStack T> arr<ScreenData> getAllScreens(T &Arena) {
  arr<ScreenData> result;
  DISPLAY_DEVICEA dd;
  dd.cb = sizeof(dd);
  DWORD dev = 0;
  // count amount of active display devices
  while (EnumDisplayDevicesA(0, dev++, &dd, 0)) {
    if (dd.StateFlags & DISPLAY_DEVICE_ACTIVE) {
      ++result.count;
    }
  }
  dev = 0;
  result.elements = reinterpret_cast<ScreenData*>(Arena.push(result.count*sizeof(ScreenData)).address);
  // go through all graphics adapter
  size currentDisplay = 0;
  while (EnumDisplayDevicesA(0, dev++, &dd, 0)) {
    if (dd.StateFlags & DISPLAY_DEVICE_ACTIVE) {
      auto &display = result.elements[currentDisplay];
      auto name = Arena.push(32);
      copy({ dd.DeviceName,32 }, name);
      auto desc = Arena.push(128);
      copy({ dd.DeviceString,128 }, desc);
      display.name = { .address = name.address, .bytes = name.bytes };
      display.description = { .address = desc.address, .bytes = name.bytes };
      display.isAttachedToDesktop = dd.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP;
      display.isPrimary = (dd.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) != 0;
      display.isMirroring = (dd.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER) != 0;

      DEVMODEA dm;
      // initialize the DEVMODE structure
      ZeroMemory(&dm, sizeof(dm));
      dm.dmSize = sizeof(dm);
      // count amount of display settings for the current device
      while (0 != EnumDisplaySettingsA(dd.DeviceName, display.supportedResolutions.count, &dm)) {
          ++display.supportedResolutions.count;
          // initialize the DEVMODE structure
          ZeroMemory(&dm, sizeof(dm));
          dm.dmSize = sizeof(dm);
      }
      auto resolutions = Arena.push(sizeof(Resolution) * display.supportedResolutions.count);
      display.supportedResolutions.elements = reinterpret_cast<Resolution*>(resolutions.address);

      int index = 0;
      // go through all display settings of the device
      while (0 != EnumDisplaySettingsA(dd.DeviceName, index, &dm)) {
        auto& res = display.supportedResolutions.elements[index];
        res.width = dm.dmPelsWidth;
        res.height = dm.dmPelsHeight;
        res.bitsPerPixel = dm.dmBitsPerPel;
        res.refreshRate = dm.dmDisplayFrequency;
        // initialize the DEVMODE structure
        ZeroMemory(&dm, sizeof(dm));
        dm.dmSize = sizeof(dm);
          ++index;
      }

      // find active resolution of the display
      if (0 != EnumDisplaySettingsA(dd.DeviceName, ENUM_CURRENT_SETTINGS, &dm)) {
        for (auto i = 0; i < display.supportedResolutions.count; ++i) {
          if (display.supportedResolutions.elements[i].bitsPerPixel == dm.dmBitsPerPel &&
              display.supportedResolutions.elements[i].refreshRate == dm.dmDisplayFrequency &&
              display.supportedResolutions.elements[i].height == dm.dmPelsHeight && 
              display.supportedResolutions.elements[i].width == dm.dmPelsWidth) {
            display.currentResolution = i;
            break;
          }
        }
      }

      DWORD mon = 0;
      DISPLAY_DEVICEA mondd;
      mondd.cb = sizeof(mondd);
      // find the display device
      if (EnumDisplayDevicesA(dd.DeviceName, 0, &mondd, 0)) {
        strview adapterName{ .address = mondd.DeviceID, .bytes=128 };
        GetMonitorSizeFromEDID(adapterName, display);
      }
    }
    ZeroMemory(&dd, sizeof(dd));
    dd.cb = sizeof(dd);
  }
  // Go through all monitors attached to the active virtual desktop(subset of devices) and update positions.
  EnumDisplayMonitors(0, 0, &MonitorEnumProc, (LPARAM)&result);
  return result;
}

ScreenError changeScreenResolution(const ScreenData& DisplayInfo, const Resolution& NewResolution);

} // namespace rf