#ifndef RF_DRAWING_FORMS_FORM_HPP
#define RF_DRAWING_FORMS_FORM_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Drawing/Forms/AbstractWindow.hpp>
#include <RadonFramework/Core/Pattern/Event.hpp>
#include <RadonFramework/Core/Pattern/Signal.hpp>
#include <RadonFramework/Drawing/Forms/Control.hpp>

namespace RadonFramework { namespace Forms {

class Form:public Control, public RF_Pattern::IObserver, public RF_Pattern::SignalReceiver
{
public:
    Form();
    RF_Type::Bool Visible();
    virtual void Visible(const RF_Type::Bool Value);
    virtual RF_Type::String Title();
    virtual void Title(const RF_Type::String &Value);
    virtual void InitializeComponent();
    virtual void Idle();
    virtual void KeyPressed(const IO::KeyboardEvent& Value);
    virtual void KeyReleased(const IO::KeyboardEvent& Value);
    virtual void PrintableKeyPressed(const IO::KeyboardEvent& Value);
    virtual void MouseButtonPressed(const IO::MouseEvent& Value);
    virtual void MouseButtonReleased(const IO::MouseEvent& Value);
    virtual void MouseMove(const IO::MouseEvent& Value);
    virtual AbstractWindow* Backend();
    virtual void Size(const Math::Geometry::Size2D<>& NewSize);
    virtual void Position(const Math::Geometry::Point2D<>& NewPosition);
    virtual void Border(const RF_Type::Bool Show);
    virtual void CloseButton(const RF_Type::Bool Show);
    virtual void CursorVisible(const bool Value);
    virtual void LostFocus();
    virtual void GotFocus();
    virtual void VerticalMouseWheelMoved(RF_Type::Int32 Value);
    virtual void HorizontalMouseWheelMoved(RF_Type::Int32 Value);
    RF_Type::Bool HasFocus()const;
    RF_Geo::Point2D<> GetCursorPosition()const;

    RF_Pattern::Signal OnIdle;
    RF_Pattern::Event<const IO::KeyboardEvent&> OnKeyPress;
    RF_Pattern::Event<const IO::KeyboardEvent&> OnKeyRelease;
    RF_Pattern::Event<const IO::KeyboardEvent&> OnPrintableKeyPressed;
    RF_Pattern::Event<const IO::MouseEvent&> OnMouseButtonPressed;
    RF_Pattern::Event<const IO::MouseEvent&> OnMouseButtonReleased;
    RF_Pattern::Event<const IO::MouseEvent&> OnMouseMove;
    RF_Pattern::Signal OnLostFocus;
    RF_Pattern::Signal OnGotFocus;
    RF_Pattern::Event<RF_Type::Int32> OnVerticalMouseWheelMoved;
    RF_Pattern::Event<RF_Type::Int32> OnHorizontalMouseWheelMoved;
protected:
    AbstractWindow* m_Backend;
    RF_Type::Bool m_HasFocus;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif

#endif // RF_DRAWING_FORMS_FORM_HPP
