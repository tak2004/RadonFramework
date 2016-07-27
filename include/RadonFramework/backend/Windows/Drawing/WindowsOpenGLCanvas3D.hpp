#ifndef RF_WINDOWSOPENGLCANVAS3D_HPP
#define RF_WINDOWSOPENGLCANVAS3D_HPP

#include <RadonFramework/backend/OpenGL/OpenGLCanvas.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>
#include <windows.h>

namespace RadonFramework { namespace Drawing {

class WindowsOpenGLCanvas3D : public OpenGLCanvas
{
public:
    WindowsOpenGLCanvas3D();
    ~WindowsOpenGLCanvas3D();

    void SetWindowInfos(Forms::AbstractWindow* Window);
    void Clear();
    void SwapBuffer();
    void UpdateRectangle(RF_Geo::Rectangle<> &Rec);
    void MakeCurrent();

    RF_Geo::Mat4f& TexturecoordMatrix();

    virtual void SetVSync(const RF_Type::Bool Synchronize = true,
        const RF_Type::Bool ShouldContinue = true) final;
protected:
    RF_Geo::Mat4f m_TexturecoordMatrix;
    HWND m_WndHandle;
    HDC m_DeviceContext;
    PIXELFORMATDESCRIPTOR m_PixelFormat;
    HGLRC m_Context;
};

} }

#endif // RF_WINDOWSOPENGLCANVAS3D_HPP
