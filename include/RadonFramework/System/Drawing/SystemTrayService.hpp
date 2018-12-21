#ifndef RF_SYSTEM_DRAWING_SYSTEMTRAYSERVICE_HPP
#define RF_SYSTEM_DRAWING_SYSTEMTRAYSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFramework/Drawing/TrayIcon.hpp>

namespace RadonFramework::System::Drawing
{
class SystemTrayService : public RF_Pattern::Service
{
public:
  using Handle = RF_Type::UInt32;

  SystemTrayService(const RF_Type::String& Name);
  ~SystemTrayService() override;

  virtual RF_Type::Bool IsSupported() = 0;

  virtual Handle AddIcon(const RF_Draw::TrayIcon& Settings) = 0;
  virtual void Remove(Handle IconInstance) = 0;
  // virtual void Modify(Handle IconInstance, ) = 0;
  // virtual void PopupMenu(Handle IconInstance) = 0;

  void (*OnAction)(RF_Type::UInt32);
};

}  // namespace RadonFramework::System::Drawing

#ifndef RF_SHORTHAND_NAMESPACE_SYSDRAW
#define RF_SHORTHAND_NAMESPACE_SYSDRAW
namespace RF_SysDraw = RadonFramework::System::Drawing;
#endif

#endif  // RF_SYSTEM_DRAWING_SYSTEMTRAYSERVICE_HPP