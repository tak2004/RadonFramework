#ifndef X11OPENGL1CANVAS3D_HPP
#define X11OPENGL1CANVAS3D_HPP

#include <X11/Xlib.h>
#include <GL/glx.h>
#undef Bool
#undef True
#undef False
#include "RadonFramework/backend/OpenGL/OpenGLCanvas.hpp"
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

    class X11OpenGL1Canvas3D:public OpenGLCanvas
    {
      protected:
        Forms::IWindow* m_Window;
        GLXContext m_Context;
        int m_Attr[11];
        Math::Geometry::Matrix4f m_TexturecoordMatrix;
        GraphicDriverInformation* m_GraphicDriverInformation;
      public:
        X11OpenGL1Canvas3D();
        ~X11OpenGL1Canvas3D();

        //ICanvas3D
        void Generate();
        void SetWindowInfos(Forms::IWindow* Window);
        void Clear();
        void SwapBuffer();
        void UpdateRectangle(Math::Geometry::Rectangle<RF_Type::Int32> &Rec);

        Math::Geometry::Matrix4f& TexturecoordMatrix();
    };
  }
}
#endif
