#include "RadonFramework/precompiled.hpp"
#include "WDMOpenGLCanvas3DService.hpp"

#if defined (__cplusplus)
extern "C" {
#endif

__declspec(dllexport) void RF_CreateCanvasService(RF_Mem::AutoPointer<RF_Draw::Canvas3DService>& Service)
{
    RF_Mem::AutoPointer<RF_Draw::Canvas3DService> service((RF_Draw::Canvas3DService*)new RF_Draw::WDMOpenGLCanvas3DService("OpenGL_DWM"_rfs));
    Service = service;
}

#if defined (__cplusplus)
}
#endif