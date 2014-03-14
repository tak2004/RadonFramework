#ifdef RF_USE_GDI
    #ifdef RF_USE_OPENGL
        #ifndef RF_GDIOPENGL2CANVAS3DSERVICE_HPP
        #define RF_GDIOPENGL2CANVAS3DSERVICE_HPP

        #include <string>
        #include <RadonFramework/Drawing/Canvas3DService.hpp>

        namespace RadonFramework
        {
          namespace Drawing
          {
            class GDIOpenGL2Canvas3DService:public Canvas3DService
            {
              public:
                GDIOpenGL2Canvas3DService(const RadonFramework::Core::Types::String &Name);
                ~GDIOpenGL2Canvas3DService();
                ICanvas3D* CreateCanvas3D();
            };
          }
        }

        #endif
    #endif
#endif
