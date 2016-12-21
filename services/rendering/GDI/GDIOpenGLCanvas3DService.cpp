#include "RadonFramework/precompiled.hpp"
#ifdef RF_USE_GDI
#ifdef RF_USE_OPENGL
#include "GDIOpenGLCanvas3DService.hpp"
#include "GDIOpenGLCanvas3D.hpp"

using namespace RadonFramework::Drawing;

GDIOpenGLCanvas3DService::GDIOpenGLCanvas3DService(const RF_Type::String &Name)
:Canvas3DService(Name)
{
}

GDIOpenGLCanvas3DService::~GDIOpenGLCanvas3DService()
{
}

AbstractCanvas* GDIOpenGLCanvas3DService::CreateCanvas3D()
{
    return new GDIOpenGLCanvas3D;
}
#endif
#endif
