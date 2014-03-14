#ifndef RF_X11OPENGL2CANVAS3D_HPP
#define RF_X11OPENGL2CANVAS3D_HPP

#include <X11/Xlib.h>
#include <GL/glx.h>
#undef Bool
#undef True
#undef False
#include <RadonFramework/backend/OpenGL/OpenGLCanvas.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>
#include <string>

namespace RadonFramework
{
  namespace Forms{
    class IWindow;
  }

  namespace Drawing
  {
    class IDrawableMesh;

    class X11OpenGL2Canvas3D:public OpenGLCanvas
    {
      protected:
        Forms::IWindow* m_Window;
        GLXContext m_Context;
        int m_Attr[11];
        Math::Geometry::Matrix4f m_TexturecoordMatrix;
      public:
        X11OpenGL2Canvas3D();
        ~X11OpenGL2Canvas3D();

        //ICanvas3D
        void Generate();
        void SetWindowInfos(Forms::IWindow* Window);
        void Clear();
        void SwapBuffer();
        void UpdateRectangle(Math::Geometry::Rectangle<> &Rec);

        Math::Geometry::Matrix4f& TexturecoordMatrix();
    };
  }
}
#endif
