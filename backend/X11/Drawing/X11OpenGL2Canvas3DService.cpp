#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/backend/X11/Drawing/X11OpenGL2Canvas3DService.hpp>
#include <RadonFramework/backend/X11/Drawing/X11OpenGL2Canvas3D.hpp>

using namespace RadonFramework::Drawing;

X11OpenGL2Canvas3DService::X11OpenGL2Canvas3DService(const Core::Types::String &Name)
:Canvas3DService(Name)
{
}

X11OpenGL2Canvas3DService::~X11OpenGL2Canvas3DService()
{
}

AbstractCanvas* X11OpenGL2Canvas3DService::CreateCanvas3D()
{
  return new X11OpenGL2Canvas3D;
}
