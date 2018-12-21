#ifndef RF_DRAWING_CANVAS3D_HPP
#define RF_DRAWING_CANVAS3D_HPP
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER > 1000

#include <RadonFramework/Core/Pattern/Signal.hpp>
#include <RadonFramework/Drawing/Forms/Control.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>

namespace RadonFramework::Forms
{
class Form;
}

namespace RadonFramework::Drawing
{
class AbstractCanvas;
class AbstractRenderer;
class GraphicDriverInformation;

class Canvas3D : public Forms::Control, public RF_Pattern::SignalReceiver
{
public:
  Canvas3D(Forms::Form& Window, Control* Parent = nullptr);
  void ChangeContentRectangle(const RF_Geo::Rectanglef& NewContent,
                              const RF_Geo::Rectanglef& OldContent) override;

  void Clear();
  void SwapBuffer();
  const GraphicDriverInformation& GetGraphicDriverInformation();
  void MakeCurrent();
  void SetVSync(const RF_Type::Bool Synchronize = true,
                const RF_Type::Bool ShouldContinue = true);
  AbstractCanvas const* Backend() const;
  void Draw();
  AbstractRenderer* GetRenderer() const;

protected:
  AbstractCanvas* m_Backend;
  AbstractRenderer* m_Renderer;
};

}  // namespace RadonFramework::Drawing

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif  // RF_DRAWING_CANVAS3D_HPP
