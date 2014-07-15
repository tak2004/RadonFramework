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
    m_Backend->OnIdle += Connector<Form, const IObserver*>(&Form::Idle);
    m_Backend->OnResize += Connector<Form, const Math::Geometry::Size2D<>&>(&Form::Resize);
    m_Backend->OnReposition += Connector<Form, const Math::Geometry::Point2D<>&>(&Form::Reposition);
    m_Backend->OnKeyPress += Connector<Form, const VirtualKey::Type>(&Form::KeyPressed);
    m_Backend->OnKeyRelease += Connector<Form, const VirtualKey::Type>(&Form::KeyReleased);
    m_Backend->OnMouseButtonPressed += Connector<Form, const IO::MouseEvent&>(&Form::MouseButtonPressed);
    m_Backend->OnMouseButtonReleased += Connector<Form, const IO::MouseEvent&>(&Form::MouseButtonReleased);
    m_Backend->OnMouseMove += Connector<Form, const IO::MouseEvent&>(&Form::MouseMove);
    InitializeComponent();
}

Bool Form::Visible()
{
    return m_Backend->Visible();
}

void Form::Visible(const Bool Value)
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

void Form::Idle(const IObserver* Sender)
{
    OnIdle(Sender);
}

void Form::KeyPressed(const VirtualKey::Type VK)
{
    OnKeyPress(VK);
}

void Form::KeyReleased(const VirtualKey::Type VK)
{
    OnKeyRelease(VK);
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

IWindow* Form::Backend()
{
    return m_Backend;
}
