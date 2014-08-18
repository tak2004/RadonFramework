#ifndef RF_GDIOPENGL2CANVAS3D_HPP
#define RF_GDIOPENGL2CANVAS3D_HPP

#include <RadonFramework/backend/OpenGL/OpenGLCanvas.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>
#include <windows.h>

namespace RadonFramework { namespace Forms {
class IWindow;
} }

namespace RadonFramework { namespace Drawing {

class GDIOpenGL2Canvas3D:public OpenGLCanvas
{
public:
    GDIOpenGL2Canvas3D();
    ~GDIOpenGL2Canvas3D();

    //ICanvas3D
    void Generate();
    void SetWindowInfos(Forms::IWindow* Window);
    void Clear();
    void SwapBuffer();
    void UpdateRectangle(RF_Geo::Rectangle<> &Rec);
    void MakeCurrent();

    RF_Geo::Mat4f& TexturecoordMatrix();
protected:
    RF_Geo::Mat4f m_TexturecoordMatrix;
    HWND m_WndHandle;
    HDC m_DeviceContext;
    PIXELFORMATDESCRIPTOR m_PixelFormat;
    HGLRC m_Context;
    GraphicDriverInformation* m_GraphicDriverInformation;
};

} }

#endif // RF_GDIOPENGL2CANVAS3D_HPP
