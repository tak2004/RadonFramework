#ifndef RF_DRAWING_CANVAS3D_HPP
#define RF_DRAWING_CANVAS3D_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <RadonFramework/Drawing/Forms/Control.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>

namespace RadonFramework { namespace System { namespace Threading {
class Mutex;
} } }

namespace RadonFramework { namespace Drawing {

class ICanvas3D;
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
    ICanvas3D const* Backend()const;

    Draw2D& Draw2D();
protected:
    ICanvas3D* m_Backend;
    Draw2D m_Draw2D;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_DRAWING_CANVAS3D_HPP
