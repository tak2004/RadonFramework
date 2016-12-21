#include "RadonFramework/precompiled.hpp"
#include "WindowsWindowService.hpp"

extern "C" void RF_RegisterService()
{
    RF_Form::WindowsWindowService::Register();
}