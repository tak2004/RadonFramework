#ifndef RF_DRAWING_FORMS_GRIDLAYOUTER_HPP
#define RF_DRAWING_FORMS_GRIDLAYOUTER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Drawing/Forms/Control.hpp>
#include <RadonFramework/Drawing/Forms/Layouter.hpp>

namespace RadonFramework::Forms
{
class GridContainer;

class GridLayouter : public Control, public Layouter
{
public:
  GridLayouter(Control* Parent = nullptr,
               const RF_Type::Size RowCount = 1,
               const RF_Type::Size ColumnCount = 1);
  void SetGap(const RF_Geo::Size2Df& Gap);
  void AddChild(Control& Obj,
                const RF_Type::Size RowIndex,
                const RF_Type::Size ColumnIndex);

  RF_Geo::Rectanglef GetContentRect(const Control& Child) const override;

protected:
  RF_Geo::Size2Df m_CellGap;
  RF_Collect::Array<Control*> m_Cells;
  RF_Type::Size m_RowCount;
  RF_Type::Size m_ColumnCount;
  void AddChild(Control& Obj) override;
};

}  // namespace RadonFramework::Forms

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif  // RF_SHORTHAND_NAMESPACE_FORM

#endif  // RF_DRAWING_FORMS_GRIDLAYOUTER_HPP
