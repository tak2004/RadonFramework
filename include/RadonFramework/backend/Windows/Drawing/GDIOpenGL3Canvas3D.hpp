#ifndef RF_GDIOPENGL3CANVAS3D_HPP
#define RF_GDIOPENGL3CANVAS3D_HPP

#include <RadonFramework/backend/OpenGL/OpenGLCanvas.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>
#include <RadonFramework/Drawing/MeshGenerator2D.hpp>
#include <windows.h>

namespace RadonFramework { namespace Forms {
class AbstractWindow;
} }

namespace RadonFramework { namespace Drawing {

class GDIOpenGL3Canvas3D:public OpenGLCanvas
{
public:
    GDIOpenGL3Canvas3D();
    ~GDIOpenGL3Canvas3D();

    //ICanvas3D
    void Generate();
    void SetWindowInfos(Forms::AbstractWindow* Window);
    void Clear();
    void SwapBuffer();
    void UpdateRectangle(Math::Geometry::Rectangle<> &Rec);
    void MakeCurrent();

    RF_Geo::Mat4f& TexturecoordMatrix();
protected:
    RF_Geo::Mat4f m_TexturecoordMatrix;
    HWND m_WndHandle;
    HDC m_DeviceContext;
    PIXELFORMATDESCRIPTOR m_PixelFormat;
    HGLRC m_Context;
};

} }

#endif // RF_GDIOPENGL3CANVAS3D_HPP
