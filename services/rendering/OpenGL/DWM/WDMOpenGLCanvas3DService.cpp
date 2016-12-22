#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Canvas3DServiceLocator.hpp"
#include "WDMOpenGLCanvas3DService.hpp"
#include "WDMOpenGLCanvas3D.hpp"

using namespace RadonFramework::Drawing;

WDMOpenGLCanvas3DService::WDMOpenGLCanvas3DService(const RF_Type::String &Name)
:Canvas3DService(Name)
{
}

WDMOpenGLCanvas3DService::~WDMOpenGLCanvas3DService()
{
}

AbstractCanvas* WDMOpenGLCanvas3DService::CreateCanvas3D()
{
    return new WDMOpenGLCanvas3D;
}

void WDMOpenGLCanvas3DService::Register()
{
    RF_Mem::AutoPointer<Canvas3DService> service((Canvas3DService*)new WDMOpenGLCanvas3DService("OpenGL_DWM"_rfs));
    Canvas3DServiceLocator::Register(service);
}
