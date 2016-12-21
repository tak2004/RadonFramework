#include "RadonFramework/precompiled.hpp"
#include "WindowsWindowService.hpp"

__declspec(dllexport) void RF_RegisterService()
{
    RF_Form::WindowsWindowService::Register();
}