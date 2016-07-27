#ifndef RF_OPENGLCANVAS_HPP
#define RF_OPENGLCANVAS_HPP

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Drawing/AbstractCanvas.hpp>

namespace RadonFramework { namespace Drawing {

class GraphicDriverInformation;
class GraphicDriverInformationOpenGL;
/** This class implement common OpenGL stuff.
    * A specialized version, like OpenGL1,2..., should inherit from this class.
    */
class OpenGLCanvas:public AbstractCanvas
{
public:
    OpenGLCanvas();
    virtual const GraphicDriverInformation& GetGraphicDriverInformation() final;
    /// This method return information about OpenGL capabilities.
    const GraphicDriverInformationOpenGL& GetContextRelatedGraphicDriverInformation();
    System::Threading::Mutex& RenderLock();
protected:
    GraphicDriverInformation* m_GraphicDriverInformation;
    GraphicDriverInformationOpenGL* m_GraphicDriverInformationOpenGL;
    Memory::AutoPointer<System::Threading::Mutex> m_Lock;
    virtual void GetExtensions(RF_Collect::Array<RF_Type::String>& Extensions);
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_OPENGLCANVAS_HPP
