#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Forms/WindowServiceLocator.hpp"
#include "WindowsWindowService.hpp"

extern "C" void RF_RegisterService()
{
    RF_Mem::AutoPointer<RF_Form::WindowService> gdi(new RF_Form::WindowsWindowService("Windows_GDI"_rfs));
    RF_Form::WindowServiceLocator::Register(gdi);
}