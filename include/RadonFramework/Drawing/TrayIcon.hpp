#ifndef RF_DRAWING_FORMS_TRAYICON_HPP
#define RF_DRAWING_FORMS_TRAYICON_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Event.hpp>
#include <RadonFramework/Drawing/PopupMenu.hpp>
#include <RadonFramework/IO/Uri.hpp>

namespace RadonFramework::Drawing
{
class TrayIcon
{
public:
  RF_Type::String Tooltip;
  RF_Type::String Notification;
  RF_Type::String Icon;
  PopupMenu Menu;
  RF_Pattern::Event<RF_Type::UInt32> OnAction;
};

}  // namespace RadonFramework::Drawing

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif  // RF_DRAWING_FORMS_TRAYICON_HPP