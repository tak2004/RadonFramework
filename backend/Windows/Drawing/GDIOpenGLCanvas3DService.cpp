#include "RadonFramework/precompiled.hpp"
#ifdef RF_USE_GDI
#ifdef RF_USE_OPENGL
#include <RadonFramework/backend/Windows/Drawing/GDIOpenGLCanvas3DService.hpp>
#include <RadonFramework/backend/Windows/Drawing/GDIOpenGLCanvas3D.hpp>

using namespace RadonFramework::Drawing;

GDIOpenGLCanvas3DService::GDIOpenGLCanvas3DService(const RF_Type::String &Name)
:Canvas3DService(Name)
{
}

GDIOpenGLCanvas3DService::~GDIOpenGLCanvas3DService()
{
}

ICanvas3D* GDIOpenGLCanvas3DService::CreateCanvas3D()
{
    return new GDIOpenGLCanvas3D;
}
#endif
#endif
