#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Drawing/Forms/WindowServiceLocator.hpp>
#include <RadonFramework/Drawing/Forms/Form.hpp>

using namespace RadonFramework::Forms;
using namespace RadonFramework::IO;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Math::Geometry;

Form::Form()
{
    m_Backend = WindowServiceLocator::Default().NewWindow();
    m_Backend->OnIdle += SignalReceiver::Connector<Form>(&Form::Idle);
    m_Backend->OnResize += IObserver::Connector<Form, const Math::Geometry::Size2D<>&>(&Form::Resize);
    m_Backend->OnReposition += IObserver::Connector<Form, const Math::Geometry::Point2D<>&>(&Form::Reposition);
    m_Backend->OnKeyPress += IObserver::Connector<Form, const KeyboardEvent&>(&Form::KeyPressed);
    m_Backend->OnPrintableKeyPressed += IObserver::Connector<Form, const KeyboardEvent&>(&Form::PrintableKeyPressed);
    m_Backend->OnKeyRelease += IObserver::Connector<Form, const KeyboardEvent&>(&Form::KeyReleased);
    m_Backend->OnMouseButtonPressed += IObserver::Connector<Form, const IO::MouseEvent&>(&Form::MouseButtonPressed);
    m_Backend->OnMouseButtonReleased += IObserver::Connector<Form, const IO::MouseEvent&>(&Form::MouseButtonReleased);
    m_Backend->OnMouseMove += IObserver::Connector<Form, const IO::MouseEvent&>(&Form::MouseMove);
    m_Backend->OnLostFocus += SignalReceiver::Connector<Form>(&Form::LostFocus);
    m_Backend->OnGotFocus += SignalReceiver::Connector<Form>(&Form::GotFocus);
    m_Backend->OnVerticalMouseWheelMoved += IObserver::Connector<Form>(&Form::VerticalMouseWheelMoved);
    m_Backend->OnHorizontalMouseWheelMoved += IObserver::Connector<Form>(&Form::HorizontalMouseWheelMoved);
    InitializeComponent();
}

Bool Form::Visible()
{
    return m_Backend->Visible();
}

void Form::Visible(const Bool &Value)
{
    m_Backend->Visible(Value);
}

String Form::Title()
{
    return m_Backend->Title();
}

void Form::Title(const String &Value)
{
    m_Backend->Title(Value);
}

void Form::InitializeComponent()
{
    this->m_ClientRectangle.SetSize(Size2D<>(640, 480));
    m_Backend->ClientRectSize(m_ClientRectangle.GetSize());
    m_Backend->Visible(true);
}

void Form::Idle()
{
    OnIdle();
}

void Form::KeyPressed(const KeyboardEvent& Value)
{
    OnKeyPress(Value);
}

void Form::KeyReleased(const KeyboardEvent& Value)
{
    OnKeyRelease(Value);
}

void Form::MouseButtonPressed(const MouseEvent& Value)
{
    OnMouseButtonPressed(Value);
}

void Form::MouseButtonReleased(const MouseEvent& Value)
{
    OnMouseButtonReleased(Value);
}

void Form::MouseMove(const MouseEvent& Value)
{
    OnMouseMove(Value);
}

void Form::Size(const RF_Geo::Size2D<>& NewSize)
{
    m_Backend->Size(NewSize);
}

void Form::Position(const RF_Geo::Point2D<>& NewPosition)
{
    m_Backend->Position(NewPosition);
}

void Form::Border(const Bool Show)
{
    m_Backend->Border(Show);
}

void Form::CloseButton(const Bool Show)
{
    m_Backend->CloseButton(Show);
}

void Form::CursorVisible(const bool Value)
{
    m_Backend->CursorVisible(Value);
}

const AbstractWindow* Form::Backend()const
{
    return m_Backend;
}

RF_Type::Bool Form::HasFocus()const
{
    return m_Backend->HasFocus();
}

void Form::LostFocus()
{
    OnLostFocus();
}

void Form::GotFocus()
{
    OnGotFocus();
}

RF_Geo::Point2D<> Form::GetCursorPosition() const
{
    return m_Backend->GetCursorPosition();
}

void Form::VerticalMouseWheelMoved(RF_Type::Int32 Value)
{
    OnVerticalMouseWheelMoved(Value);
}

void Form::HorizontalMouseWheelMoved(RF_Type::Int32 Value)
{
    OnHorizontalMouseWheelMoved(Value);
}

void Form::PrintableKeyPressed(const KeyboardEvent& Value)
{
    OnPrintableKeyPressed(Value);
}
