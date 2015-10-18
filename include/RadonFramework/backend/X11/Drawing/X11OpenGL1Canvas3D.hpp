#ifndef RF_X11OPENGL1CANVAS3D_HPP
#define RF_X11OPENGL1CANVAS3D_HPP

#include <X11/Xlib.h>
#include <GL/glx.h>
#undef Bool
#undef True
#undef False
#include <RadonFramework/backend/OpenGL/OpenGLCanvas.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>

namespace RadonFramework {

namespace Forms{
    class IWindow;
}

namespace Drawing {
class IDrawableMesh;

class X11OpenGL1Canvas3D:public OpenGLCanvas
{
public:
    X11OpenGL1Canvas3D();
    ~X11OpenGL1Canvas3D();

    //ICanvas3D
    virtual void Generate();
    virtual void SetWindowInfos(Forms::IWindow* Window);
    virtual void Clear();
    virtual void SwapBuffer();
    virtual void UpdateRectangle(RF_Geo::Rectangle<RF_Type::Int32> &Rec);

    virtual void MakeCurrent();

    virtual RF_Geo::Matrix4f& TexturecoordMatrix();
protected:
    Forms::IWindow* m_Window;
    GLXContext m_Context;
    RF_Type::Int32 m_Attr[11];
    RF_Geo::Matrix4f m_TexturecoordMatrix;
};

} }

#endif