#ifndef RF_DRAWING_FORMS_FORM_HPP
#define RF_DRAWING_FORMS_FORM_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Event.hpp>
#include <RadonFramework/Core/Pattern/Signal.hpp>
#include <RadonFramework/Drawing/Forms/AbstractWindow.hpp>
#include <RadonFramework/Drawing/Forms/Control.hpp>

namespace RadonFramework::Forms
{
class Form : public Control,
             public RF_Pattern::IObserver,
             public RF_Pattern::SignalReceiver
{
public:
  Form();
  RF_Type::Bool Visible() const override;
  void Visible(const RF_Type::Bool& Value) override;
  virtual RF_Type::String Title();
  virtual void Title(const RF_Type::String& Value);
  virtual void InitializeComponent();
  virtual void Idle();
  virtual void KeyPressed(const IO::KeyboardEvent& Value);
  virtual void KeyReleased(const IO::KeyboardEvent& Value);
  virtual void PrintableKeyPressed(const IO::KeyboardEvent& Value);
  virtual const AbstractWindow* Backend() const;
  ///
  virtual void SetWindowSize(const RF_Geo::Size2D<>& NewSize);
  ///
  virtual void SetWindowPosition(const RF_Geo::Point2D<>& NewPosition);
  virtual void Border(const RF_Type::Bool Show);
  virtual void CloseButton(const RF_Type::Bool Show);
  virtual void CursorVisible(const bool Value);
  virtual void ChangeCursor(const Cursor& NewCursor);
  virtual void LostFocus();
  virtual void GotFocus();
  virtual void VerticalMouseWheelMoved(RF_Type::Int32 Value);
  virtual void HorizontalMouseWheelMoved(RF_Type::Int32 Value);
  virtual void DPIChanged(const RF_Geo::Point2D<>& DPI);

  /// Window was resized from outside.
  void Resize(const RF_Geo::Size2D<>& Value);
  /// Window was moved from outside.
  void Move(const RF_Geo::Point2D<>& Value);

  RF_Type::Bool HasFocus() const;
  RF_Geo::Point2D<> GetCursorPosition() const;
  RF_Type::Float32 GetHorizontalScale() const;
  RF_Type::Float32 GetVerticalScale() const;
  const RF_Geo::Point2D<>& GetWindowPosition() const;
  const RF_Geo::Size2D<>& GetWindowSize() const;

  RF_Pattern::Signal OnIdle;
  RF_Pattern::Event<const IO::KeyboardEvent&> OnKeyPress;
  RF_Pattern::Event<const IO::KeyboardEvent&> OnKeyRelease;
  RF_Pattern::Event<const IO::KeyboardEvent&> OnPrintableKeyPressed;
  RF_Pattern::Signal OnLostFocus;
  RF_Pattern::Signal OnGotFocus;
  RF_Pattern::Event<RF_Type::Int32> OnVerticalMouseWheelMoved;
  RF_Pattern::Event<RF_Type::Int32> OnHorizontalMouseWheelMoved;

protected:
  AbstractWindow* m_Backend;
  RF_Type::Bool m_HasFocus;
  RF_Type::UInt64 m_NextAnimation;
  RF_Type::UInt64 m_Now;
  RF_Type::UInt64 m_AnimationStep;
  RF_Type::Float32 m_HorizontalScale;
  RF_Type::Float32 m_VerticalScale;
  RF_Geo::Point2D<> m_WindowPosition;
  RF_Geo::Size2D<> m_WindowSize;
};

}  // namespace RadonFramework::Forms

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif

#endif  // RF_DRAWING_FORMS_FORM_HPP
