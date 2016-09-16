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

    virtual void SetWindowInfos(const Forms::AbstractWindow& Window) final;
    virtual void Clear() final;
    virtual void SwapBuffer() final;
    virtual void UpdateRectangle(RF_Geo::Rectangle<> &Rec) final;
    virtual void MakeCurrent() final;

    virtual void SetVSync(const RF_Type::Bool Synchronize = true,
        const RF_Type::Bool ShouldContinue = true) final;
protected:
    HWND m_WndHandle;
    HDC m_DeviceContext;
    PIXELFORMATDESCRIPTOR m_PixelFormat;
    HGLRC m_Context;
};

} }

#endif // RF_WINDOWSOPENGLCANVAS3D_HPP
