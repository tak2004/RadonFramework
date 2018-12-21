#ifndef RF_SYSTEM_DRAWING_SYSTEMTRAYSERVICELOCATOR_HPP
#define RF_SYSTEM_DRAWING_SYSTEMTRAYSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/System/Drawing/SystemTrayService.hpp>

namespace RadonFramework::System::Drawing
{
class NullSystemTrayService : public SystemTrayService
{
public:
  NullSystemTrayService(const RF_Type::String& Name) : SystemTrayService(Name)
  {
  }

  ~NullSystemTrayService() final = default;

  Handle AddIcon(const RF_Draw::TrayIcon& Settings) final { return 0; }
  void Remove(Handle IconInstance) final {}
  RF_Type::Bool IsSupported() final { return false; }
};

using SystemTrayServiceLocator =
    RF_Pattern::Locator<SystemTrayService, NullSystemTrayService>;

}  // namespace RadonFramework::System::Drawing

#ifndef RF_SHORTHAND_NAMESPACE_SYSDRAW
#define RF_SHORTHAND_NAMESPACE_SYSDRAW
namespace RF_SysDraw = RadonFramework::System::Drawing;
#endif

#endif  // RF_SYSTEM_DRAWING_SYSTEMTRAYSERVICELOCATOR_HPP
