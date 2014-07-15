#ifndef RF_X11OPENGL1CANVAS3DSERVICE_HPP
#define RF_X11OPENGL1CANVAS3DSERVICE_HPP

#include <string>
#include <RadonFramework/Drawing/Canvas3DService.hpp>

namespace RadonFramework
{
  namespace Drawing
  {
    class X11OpenGL1Canvas3DService:public Canvas3DService
    {
      public:
        X11OpenGL1Canvas3DService(const RF_Type::String &Name);
        ~X11OpenGL1Canvas3DService();
        ICanvas3D* CreateCanvas3D();
    };

    //PLUGIN(X11OpenGL1Canvas3DService,"OpenGL1.x")
  }
}
#endif
