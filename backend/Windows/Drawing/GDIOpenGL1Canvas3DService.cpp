#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/backend/Windows/Drawing/GDIOpenGL1Canvas3DService.hpp>
#include <RadonFramework/backend/Windows/Drawing/GDIOpenGL1Canvas3D.hpp>

using namespace RadonFramework::Drawing;

GDIOpenGL1Canvas3DService::GDIOpenGL1Canvas3DService(const RadonFramework::Core::Types::String &Name)
:Canvas3DService(Name)
{
}

GDIOpenGL1Canvas3DService::~GDIOpenGL1Canvas3DService()
{
}

ICanvas3D* GDIOpenGL1Canvas3DService::CreateCanvas3D()
{
    return new GDIOpenGL1Canvas3D;
}
