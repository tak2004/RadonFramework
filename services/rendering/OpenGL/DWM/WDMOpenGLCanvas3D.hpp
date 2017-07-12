#ifndef RF_WDMOPENGLCANVAS3D_HPP
#define RF_WDMOPENGLCANVAS3D_HPP

#include <OpenGLRenderer.hpp>
#include <RadonFramework/Drawing/AbstractCanvas.hpp>
#include <windows.h>

namespace RadonFramework::Drawing {

class GraphicDriverInformation;
class GraphicDriverInformationOpenGL;

class WDMOpenGLCanvas3D : public AbstractCanvas
{
public:
    WDMOpenGLCanvas3D();
    ~WDMOpenGLCanvas3D();
    virtual void Generate(const RF_Geo::Size2Df& FrameSize) final;
    virtual void SetWindowInfos(const Forms::AbstractWindow& Window) final;
    virtual void Clear() final;
    virtual void SwapBuffer() final;
    virtual void UpdateRectangle(RF_Geo::Rectangle<> &Rec) final;
    virtual void MakeCurrent() final;
    virtual const GraphicDriverInformation& GetGraphicDriverInformation() final;
    /// This method return information about OpenGL capabilities.
    const GraphicDriverInformationOpenGL& GetContextRelatedGraphicDriverInformation();
    virtual void SetVSync(const RF_Type::Bool Synchronize = true,
        const RF_Type::Bool ShouldContinue = true) final;
    virtual AbstractRenderer* GetRenderer()const final;
protected:
    void GetExtensions(RF_Collect::Array<RF_Type::String>& Extensions);
    void GetExtensionsLegacy(RF_Collect::Array<RF_Type::String>& Extensions);
    RF_Type::UInt32 m_MajorVersion;
    GraphicDriverInformation* m_GraphicDriverInformation;
    GraphicDriverInformationOpenGL* m_GraphicDriverInformationOpenGL;
    HWND m_WndHandle;
    HDC m_DeviceContext;
    PIXELFORMATDESCRIPTOR m_PixelFormat;
    HGLRC m_Context; 
    OpenGLRenderer m_OpenGLRenderer;
};

}

#endif // RF_WDMOPENGLCANVAS3D_HPP
