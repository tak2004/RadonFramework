#ifndef RF_OPENGLCANVAS_HPP
#define RF_OPENGLCANVAS_HPP

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <RadonFramework/Drawing/ICanvas3D.hpp>

namespace RadonFramework
{
    namespace Drawing
    {
        class GraphicDriverInformation;
        class GraphicDriverInformationOpenGL;
        /** This class implement common OpenGL stuff.
          * A specialized version, like OpenGL1,2..., should inherit from this class.
          */
        class OpenGLCanvas:public ICanvas3D
        {
            public:
                OpenGLCanvas();
                const GraphicDriverInformation& GetGraphicDriverInformation();
                /// This method return information about OpenGL capabilities.
                const GraphicDriverInformationOpenGL& GetContextRelatedGraphicDriverInformation();
                System::Threading::Mutex& RenderLock();
            protected:
                GraphicDriverInformation* m_GraphicDriverInformation;
                GraphicDriverInformationOpenGL* m_GraphicDriverInformationOpenGL;
                Memory::AutoPointer<System::Threading::Mutex> m_Lock;
        };
    }
}

#endif // RF_OPENGLCANVAS_HPP
