#ifndef RF_DRAWING_DRAWING_SYSTEMTRAY_HPP
#define RF_DRAWING_DRAWING_SYSTEMTRAY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Core/Idioms/PImpl.hpp>
#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>
#include <RadonFramework/System/Drawing/SystemTrayService.hpp>

namespace RadonFramework::Drawing
{
class TrayIcon;

class SystemTray : public RF_Pattern::Singleton<SystemTray>
{
public:
  using Handle = RF_SysDraw::SystemTrayService::Handle;
  /// Adds a TrayIcon to the SystemTray.
  Handle Add(RF_Mem::AutoPointer<TrayIcon>& NewTrayIcon);

  /// Remove the specified TrayIcon from the SystemTray if known.
  void Remove(Handle RegisteredTrayIcon);

  /// Return the list of all known TrayIcon instances.
  const RF_Collect::AutoVector<TrayIcon>& GetRegisteredTrayIcons() const;

  /// Request the dimension at which a TrayIcon will be represented in the
  /// SystemTray.
  void RequestTrayIconSize(RF_Geo::Size2D<>& WriteTo) const;

  /// Return true if the SystemTray is supported on the running system else
  /// false.
  static RF_Type::Bool IsSupported();

protected:
  friend class RF_Pattern::Singleton<SystemTray>;
  SystemTray();
  ~SystemTray() override;
  static void OnAction(RF_Type::UInt32 ActionId);

private:
  RF_Idiom::PImpl<SystemTray> m_PImpl;
};

}  // namespace RadonFramework::Drawing

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif  // RF_DRAWING_DRAWING_SYSTEMTRAY_HPP