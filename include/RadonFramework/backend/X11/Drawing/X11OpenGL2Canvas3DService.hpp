#ifndef RF_X11OPENGL2CANVAS3DSERVICE_HPP
#define RF_X11OPENGL2CANVAS3DSERVICE_HPP

#include <string>
#include <RadonFramework/Drawing/Canvas3DService.hpp>

namespace RadonFramework
{
  namespace Drawing
  {
    class X11OpenGL2Canvas3DService:public Canvas3DService
    {
      public:
        X11OpenGL2Canvas3DService(const RF_Type::String &Name);
        ~X11OpenGL2Canvas3DService();
        ICanvas3D* CreateCanvas3D();
    };

    //PLUGIN(X11OpenGL2Canvas3DService,"OpenGL2.x")
  }
}
#endif
