#ifndef RF_ICANVAS3D_HPP
#define RF_ICANVAS3D_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Geometry/Rectangle.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>

namespace RadonFramework
{

    namespace System
    {
        namespace Threading
        {
            class Mutex;
        }
    }
    
    namespace Forms{
        class IWindow;
    }

    namespace Drawing
    {
        class GraphicDriverInformation;

        /// This is a abstract class which should be used as interface for the backend implementation.
        class ICanvas3D
        {
        public:
            virtual void Generate()=0;
            virtual void SetWindowInfos(Forms::IWindow* Window)=0;
            virtual void Clear()=0;
            virtual void SwapBuffer()=0;
            virtual void UpdateRectangle(Math::Geometry::Rectangle<Core::Types::Int32> &Rec)=0;
            /** All upcomming rendering commands will piped to this canvas.
              * This is necessary if you use two or more canvas in one process.
              **/
            virtual void MakeCurrent()=0;
            virtual System::Threading::Mutex& RenderLock() = 0;

            virtual Math::Geometry::Matrix4f& TexturecoordMatrix()=0;
            virtual const GraphicDriverInformation& GetGraphicDriverInformation()=0;
        };
    }
}

#endif
