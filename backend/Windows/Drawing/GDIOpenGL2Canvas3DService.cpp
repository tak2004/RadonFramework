#include "RadonFramework/precompiled.hpp"
#ifdef RF_USE_GDI
    #ifdef RF_USE_OPENGL
        #include <RadonFramework/backend/Windows/Drawing/GDIOpenGL2Canvas3DService.hpp>
        #include <RadonFramework/backend/Windows/Drawing/GDIOpenGL2Canvas3D.hpp>

        using namespace RadonFramework::Drawing;

        GDIOpenGL2Canvas3DService::GDIOpenGL2Canvas3DService(const RadonFramework::Core::Types::String &Name)
        :Canvas3DService(Name)
        {
        }

        GDIOpenGL2Canvas3DService::~GDIOpenGL2Canvas3DService()
        {
        }

        ICanvas3D* GDIOpenGL2Canvas3DService::CreateCanvas3D()
        {
          return new GDIOpenGL2Canvas3D;
        }
    #endif
#endif
