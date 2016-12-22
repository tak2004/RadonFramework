#include "RadonFramework/precompiled.hpp"
#include "WindowsWindowService.hpp"

#if defined (__cplusplus)
extern "C" {
#endif

__declspec(dllexport) void RF_CreateWindowService(RF_Mem::AutoPointer<RF_Form::WindowService>& Service)
{
    RF_Mem::AutoPointer<RF_Form::WindowService> gdi(new RF_Form::WindowsWindowService("Windows_GDI"_rfs));
    Service = gdi;
}

#if defined (__cplusplus)
}
#endif