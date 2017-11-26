#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Drawing/Forms/WindowServiceLocator.hpp>
#include <RadonFramework/Drawing/Forms/Form.hpp>
#include "RadonFramework/Time/DateTime.hpp"

using namespace RadonFramework::Forms;
using namespace RadonFramework::IO;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Math::Geometry;

Form::Form()
:Control()
{
    m_AnimationStep = RF_Time::TimeSpan::TicksPerSecond/24;
    m_Now = RF_Time::DateTime::UtcNow().Ticks();
    m_NextAnimation = m_Now + m_AnimationStep;
    m_Backend = WindowServiceLocator::Default().NewWindow();
    if(m_Backend != nullptr)
    {
        m_Backend->OnIdle += SignalReceiver::Connector<Form>(&Form::Idle);
        m_Backend->OnResize += IObserver::Connector<Form, const Math::Geometry::Size2D<>&>(&Form::Resize);
        m_Backend->OnReposition += IObserver::Connector<Form,const RF_Geo::Point2D<>&>(&Form::Move);
        m_Backend->OnKeyPress += IObserver::Connector<Form, const KeyboardEvent&>(&Form::KeyPressed);
        m_Backend->OnPrintableKeyPressed += IObserver::Connector<Form, const KeyboardEvent&>(&Form::PrintableKeyPressed);
        m_Backend->OnKeyRelease += IObserver::Connector<Form, const KeyboardEvent&>(&Form::KeyReleased);
        m_Backend->OnMouseButtonPressed += IObserver::Connector<Form, const IO::MouseEvent&>(&Form::MouseButtonPressed);
        m_Backend->OnMouseButtonReleased += IObserver::Connector<Form, const IO::MouseEvent&>(&Form::MouseButtonReleased);
        m_Backend->OnMouseMove += IObserver::Connector<Form, const IO::MouseEvent&>(&Form::MouseMoved);
        m_Backend->OnLostFocus += SignalReceiver::Connector<Form>(&Form::LostFocus);
        m_Backend->OnGotFocus += SignalReceiver::Connector<Form>(&Form::GotFocus);
        m_Backend->OnVerticalMouseWheelMoved += IObserver::Connector<Form>(&Form::VerticalMouseWheelMoved);
        m_Backend->OnHorizontalMouseWheelMoved += IObserver::Connector<Form>(&Form::HorizontalMouseWheelMoved);
        m_Backend->OnDPIChanged += IObserver::Connector<Form>(&Form::DPIChanged);
    }
    InitializeComponent();
}

Bool Form::Visible()const 
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
    m_WindowPosition = {0,0};
    m_WindowSize = {640,480};
    SetSize(m_WindowSize);
    RF_Geo::Size2D<> size;
    size.Width = GetSize().Width;
    size.Height = GetSize().Height;
    if (m_Backend != nullptr)
    {
        m_Backend->ClientRectSize(size);
        m_Backend->Visible(true);
    }
}

void Form::Idle()
{
    m_Now = RF_Time::DateTime::UtcNow().Ticks();
    if(m_NextAnimation < m_Now)
    {
        Animate(m_NextAnimation);
        RebuildVisuals();
        m_NextAnimation = m_NextAnimation + m_AnimationStep;
    }
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

void Form::SetWindowSize(const RF_Geo::Size2D<>& NewSize)
{
    RF_Geo::Size2Df size;
    size.Width = NewSize.Width;
    size.Height = NewSize.Height;

    Rectanglef contentRectangle;
    contentRectangle.SetSize(size);
    contentRectangle.SetPosition(GetPosition());
    ChangeContentRectangle(contentRectangle, GetClientRectangle());
    m_Backend->Size(NewSize);
}

void Form::SetWindowPosition(const RF_Geo::Point2D<>& NewPosition)
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

RF_Type::Float32 Form::GetHorizontalScale() const
{
    return m_HorizontalScale;
}

RF_Type::Float32 Form::GetVerticalScale() const
{
    return m_VerticalScale;
}

void Form::DPIChanged(const RF_Geo::Point2D<>& DPI)
{
    m_HorizontalScale = DPI.X / 96.0f;
    m_VerticalScale = DPI.Y / 96.0f;
    Control::RebuildVisuals();
}

void Form::ChangeCursor(const Cursor& NewCursor)
{
    m_Backend->ChangeCursor(NewCursor);
}

void Form::Resize(const RF_Geo::Size2D<>& Value)
{
    m_WindowSize = Value;

    RF_Geo::Size2Df size;
    size.Width = Value.Width;
    size.Height = Value.Height;

    Rectanglef contentRectangle;
    contentRectangle.SetSize(size);
    contentRectangle.SetPosition(GetPosition());
    Control::ChangeContentRectangle(contentRectangle, GetClientRectangle());
}

void Form::Move(const RF_Geo::Point2D<>& Value)
{
    m_WindowPosition = Value;
}

const RF_Geo::Point2D<>& Form::GetWindowPosition() const
{
    return m_WindowPosition;
}

const RF_Geo::Size2D<>& Form::GetWindowSize() const
{
    return m_WindowSize;
}
