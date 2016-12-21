#include "RadonFramework/precompiled.hpp"
#include "WDMOpenGLCanvas3DService.hpp"

__declspec(dllexport) void RF_RegisterService()
{
    RF_Draw::WDMOpenGLCanvas3DService::Register();
}