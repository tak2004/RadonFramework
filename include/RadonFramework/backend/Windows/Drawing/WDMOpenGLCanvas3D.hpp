#ifndef RF_GDIOPENGLCANVAS3D_HPP
#define RF_GDIOPENGLCANVAS3D_HPP

#include <RadonFramework/backend/OpenGL/OpenGLCanvas.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>
#include <windows.h>

namespace RadonFramework { namespace Forms {
class IWindow;
} }

namespace RadonFramework { namespace Drawing {

class WDMOpenGLCanvas3D : public OpenGLCanvas
{
public:
    WDMOpenGLCanvas3D();
    ~WDMOpenGLCanvas3D();

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
};

} }

#endif // RF_GDIOPENGLCANVAS3D_HPP
