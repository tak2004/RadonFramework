#ifndef RF_SYSTEM_DRAWING_SYSTEMTRAYSERVICEWINDOWS_HPP
#define RF_SYSTEM_DRAWING_SYSTEMTRAYSERVICEWINDOWS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Idioms/PImpl.hpp>
#include <RadonFramework/System/Drawing/SystemTrayService.hpp>

namespace RadonFramework::System::Drawing
{
class SystemTrayServiceWindows : public SystemTrayService
{
public:
  SystemTrayServiceWindows(const RF_Type::String& Name);
  ~SystemTrayServiceWindows() override;

  RF_Type::Bool IsSupported() override;

  Handle AddIcon(const RF_Draw::TrayIcon& Settings) override;
  void Remove(Handle IconInstance) override;
  // virtual void Modify(Handle IconInstance, ) = 0;
protected:
  RF_Idiom::PImpl<SystemTrayServiceWindows> m_PImpl;
};

}  // namespace RadonFramework::System::Drawing

#ifndef RF_SHORTHAND_NAMESPACE_SYSDRAW
#define RF_SHORTHAND_NAMESPACE_SYSDRAW
namespace RF_SysDraw = RadonFramework::System::Drawing;
#endif

#endif  // RF_SYSTEM_DRAWING_SYSTEMTRAYSERVICEWINDOWS_HPP