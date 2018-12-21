#ifndef RF_DRAWING_FORMS_HORIZONTALLAYOUTER_HPP
#define RF_DRAWING_FORMS_HORIZONTALLAYOUTER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Drawing/Forms/Control.hpp>
#include <RadonFramework/Drawing/Forms/Layouter.hpp>

namespace RadonFramework::Forms
{
class HorizontalLayouter : public Control, public Layouter
{
public:
  HorizontalLayouter(Control* Parent = nullptr);
  void SetGap(const RF_Geo::Size2Df& Gap);
  void AddChild(Control& Obj) override;
  RF_Geo::Rectanglef GetContentRect(const Control& Child) const override;

protected:
  RF_Geo::Size2Df m_CellGap;
};

}  // namespace RadonFramework::Forms

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif  // RF_SHORTHAND_NAMESPACE_FORM

#endif  // RF_DRAWING_FORMS_HORIZONTALLAYOUTER_HPP
