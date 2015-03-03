#ifndef RF_DRAWING_FORMS_POPUPMENU_HPP
#define RF_DRAWING_FORMS_POPUPMENU_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/Uri.hpp>
#include <RadonFramework/Collections/Array.hpp>

namespace RadonFramework { namespace Drawing {

class MenuItem
{
public:
    MenuItem()
    :IsChecked(false)
    ,ActionId(0)
    ,CanChecked(false)
    ,IsSeperator(false)
    {}

    RF_Type::String Name;
    RF_Type::Bool IsChecked;
    RF_Type::UInt32 ActionId;

    RF_Type::Bool CanChecked;
    RF_Type::Bool IsSeperator;
};

class PopupMenu:public MenuItem
{
public:
    RF_Collect::Array<PopupMenu> Items;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_DRAWING_FORMS_POPUPMENU_HPP