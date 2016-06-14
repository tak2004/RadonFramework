#ifndef RF_DRAWING_CANVAS3D_HPP
#define RF_DRAWING_CANVAS3D_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <RadonFramework/Drawing/Forms/Control.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>
#include <RadonFramework/Drawing/Draw2D.hpp>

namespace RadonFramework { namespace System { namespace Threading {
class Mutex;
} } }

namespace RadonFramework { namespace Drawing {

class AbstractCanvas;
class GraphicDriverInformation;

class Canvas3D:public Forms::Control
{
public:
    Canvas3D(Control* Parent);
    virtual void Resize(const Math::Geometry::Size2D<>& Value);

    void Clear();
    void SwapBuffer();
    RF_Geo::Mat4f& TexturecoordMatrix();
    const GraphicDriverInformation& GetGraphicDriverInformation();
    void MakeCurrent();
    System::Threading::Mutex& GetRenderLock();
    AbstractCanvas const* Backend()const;

    RF_Draw::Draw2D Draw2D;
protected:
    AbstractCanvas* m_Backend;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_DRAWING_CANVAS3D_HPP
