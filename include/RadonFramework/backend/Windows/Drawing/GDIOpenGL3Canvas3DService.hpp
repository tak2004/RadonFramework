#ifdef RF_USE_GDI
    #ifdef RF_USE_OPENGL
        #ifndef RF_GDIOPENGL3CANVAS3DSERVICE_HPP
        #define RF_GDIOPENGL3CANVAS3DSERVICE_HPP

        #include <string>
        #include <RadonFramework/Drawing/Canvas3DService.hpp>

        namespace RadonFramework
        {
          namespace Drawing
          {
            class GDIOpenGL3Canvas3DService:public Canvas3DService
            {
              public:
                GDIOpenGL3Canvas3DService(const RadonFramework::Core::Types::String &Name);
                ~GDIOpenGL3Canvas3DService();
                AbstractCanvas* CreateCanvas3D();
            };
          }
        }

        #endif
    #endif
#endif
