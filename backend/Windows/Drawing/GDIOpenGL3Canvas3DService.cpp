#include "RadonFramework/precompiled.hpp"
#ifdef RF_USE_GDI
    #ifdef RF_USE_OPENGL
        #include <RadonFramework/backend/Windows/Drawing/GDIOpenGL3Canvas3DService.hpp>
        #include <RadonFramework/backend/Windows/Drawing/GDIOpenGL3Canvas3D.hpp>

        using namespace RadonFramework::Drawing;

        GDIOpenGL3Canvas3DService::GDIOpenGL3Canvas3DService(const RadonFramework::Core::Types::String &Name)
        :Canvas3DService(Name)
        {
        }

        GDIOpenGL3Canvas3DService::~GDIOpenGL3Canvas3DService()
        {
        }

        ICanvas3D* GDIOpenGL3Canvas3DService::CreateCanvas3D()
        {
          return new GDIOpenGL3Canvas3D;
        }
    #endif
#endif
