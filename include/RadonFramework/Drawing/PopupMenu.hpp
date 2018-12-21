#ifndef RF_DRAWING_FORMS_POPUPMENU_HPP
#define RF_DRAWING_FORMS_POPUPMENU_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/IO/Uri.hpp>

namespace RadonFramework::Drawing
{
class MenuItem
{
public:
  MenuItem() = default;

  RF_Type::String Name;
  RF_Type::Bool IsChecked = false;
  RF_Type::UInt32 ActionId = 0;
  RF_Type::Bool CanChecked = false;
  RF_Type::Bool IsSeperator = false;
};

class PopupMenu : public MenuItem
{
public:
  RF_Collect::Array<PopupMenu> Items;
};

}  // namespace RadonFramework::Drawing

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif  // RF_DRAWING_FORMS_POPUPMENU_HPP