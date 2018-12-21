#ifndef RF_IWINDOW_HPP
#define RF_IWINDOW_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Event.hpp>
#include <RadonFramework/Core/Pattern/Signal.hpp>
#include <RadonFramework/IO/KeyboardEvent.hpp>
#include <RadonFramework/IO/MouseEvent.hpp>
#include <RadonFramework/IO/VirtualKey.hpp>
#include <RadonFramework/Math/Geometry/Point2D.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>

namespace RadonFramework::Forms
{
class WindowService;
class Screen;
class Cursor;

class AbstractWindow
{
public:
  virtual ~AbstractWindow() = default;
  virtual void* Handle() const = 0;
  virtual RF_Type::Bool Visible() = 0;
  virtual void Visible(const RF_Type::Bool Value) = 0;
  virtual RF_Type::String Title() = 0;
  virtual void Title(const RF_Type::String& Value) = 0;
  virtual void Size(const Math::Geometry::Size2D<>& NewSize) = 0;
  virtual void Position(const Math::Geometry::Point2D<>& NewPosition) = 0;
  virtual void ClientRectSize(const Math::Geometry::Size2D<>& NewSize) = 0;
  virtual void Border(const RF_Type::Bool Value) = 0;
  virtual void CursorVisible(const RF_Type::Bool Value) = 0;
  virtual void ChangeCursor(const Cursor& NewCursor) = 0;
  virtual WindowService* GetService() = 0;
  virtual void CloseButton(const RF_Type::Bool Show) = 0;
  virtual RF_Type::Bool HasFocus() const = 0;
  virtual RF_Geo::Point2D<> GetCursorPosition() const = 0;
  virtual RF_Mem::AutoPointerArray<RF_Type::UInt8> CaptureClientRect() = 0;

  RF_Pattern::Event<const RF_Geo::Size2D<>&> OnResize;
  RF_Pattern::Event<const RF_Geo::Point2D<>&> OnReposition;
  RF_Pattern::Signal OnIdle;
  RF_Pattern::Event<const RF_IO::KeyboardEvent&> OnKeyPress;
  RF_Pattern::Event<const RF_IO::KeyboardEvent&> OnKeyRelease;
  RF_Pattern::Event<const RF_IO::KeyboardEvent&> OnPrintableKeyPressed;
  RF_Pattern::Event<const RF_IO::MouseEvent&> OnMouseButtonPressed;
  RF_Pattern::Event<const RF_IO::MouseEvent&> OnMouseButtonReleased;
  RF_Pattern::Event<const RF_IO::MouseEvent&> OnMouseMove;
  RF_Pattern::Signal OnLostFocus;
  RF_Pattern::Signal OnGotFocus;
  RF_Pattern::Event<RF_Type::Int32> OnVerticalMouseWheelMoved;
  RF_Pattern::Event<RF_Type::Int32> OnHorizontalMouseWheelMoved;
  RF_Pattern::Event<const RF_Geo::Point2D<>&> OnDPIChanged;
};

}  // namespace RadonFramework::Forms

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif

#endif
