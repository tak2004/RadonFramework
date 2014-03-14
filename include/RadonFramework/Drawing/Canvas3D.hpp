#ifndef RF_DRAWING_CANVAS3D_HPP
#define RF_DRAWING_CANVAS3D_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <RadonFramework/Drawing/Forms/Control.hpp>
#include <RadonFramework/Math/Geometry/ProjectionMatrix.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>

namespace RadonFramework
{
    namespace System
    {
        namespace Threading
        {
            class Mutex;
        }
    }
    namespace Geometry
    {
        class Mesh;
    }

    namespace Drawing
    {
        class ICanvas3D;
        class GraphicDriverInformation;

        class Canvas3D:public Forms::Control
        {
            public:
                Canvas3D(Control* Parent);
                virtual void Resize(const Math::Geometry::Size2D<>& Value);

                Math::Geometry::ProjectionMatrix ProjectionMatrix;
                void Clear();
                void SwapBuffer();
                Math::Geometry::Matrix4f& TexturecoordMatrix();
                const GraphicDriverInformation& GetGraphicDriverInformation();
                void MakeCurrent();
                System::Threading::Mutex& GetRenderLock();
                ICanvas3D const* Backend()const;
            protected:
                ICanvas3D* m_Backend;
        };
    }
}

#endif // RF_DRAWING_CANVAS3D_HPP
