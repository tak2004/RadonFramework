#ifndef RF_X11OPENGL3CANVAS3DSERVICE_HPP
#define RF_X11OPENGL3CANVAS3DSERVICE_HPP

#include <string>
#include <RadonFramework/Drawing/Canvas3DService.hpp>

namespace RadonFramework
{
  namespace Drawing
  {
    class X11OpenGL3Canvas3DService:public Canvas3DService
    {
      public:
        X11OpenGL3Canvas3DService(const Core::Types::String &Name);
        ~X11OpenGL3Canvas3DService();
        ICanvas3D* CreateCanvas3D();
    };

    //PLUGIN(X11OpenGL3Canvas3DService,"OpenGL3.x")
  }
}
#endif
