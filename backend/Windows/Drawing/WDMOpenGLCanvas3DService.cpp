#include "RadonFramework/precompiled.hpp"
#ifdef RF_USE_WDM
#ifdef RF_USE_OPENGL
#include <RadonFramework/backend/Windows/Drawing/WDMOpenGLCanvas3DService.hpp>
#include <RadonFramework/backend/Windows/Drawing/WDMOpenGLCanvas3D.hpp>

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
#endif
#endif
