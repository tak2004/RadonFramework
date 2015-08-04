#include "RadonFramework/precompiled.hpp"
#ifdef RF_USE_DWM
#ifdef RF_USE_OPENGL
#include <RadonFramework/backend/Windows/Drawing/DWMIOpenGLCanvas3DService.hpp>
#include <RadonFramework/backend/Windows/Drawing/DWMOpenGLCanvas3D.hpp>

using namespace RadonFramework::Drawing;

DWMOpenGLCanvas3DService::DWMOpenGLCanvas3DService(const RF_Type::String &Name)
:Canvas3DService(Name)
{
}

DWMOpenGLCanvas3DService::~DWMOpenGLCanvas3DService()
{
}

ICanvas3D* DWMOpenGLCanvas3DService::CreateCanvas3D()
{
    return new DWMOpenGLCanvas3D;
}
#endif
#endif
