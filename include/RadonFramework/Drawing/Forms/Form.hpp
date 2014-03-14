#ifndef RF_FORM_HPP
#define RF_FORM_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Drawing/Forms/IWindow.hpp>
#include <RadonFramework/Core/Pattern/Event.hpp>
#include <RadonFramework/Drawing/Forms/Control.hpp>

namespace RadonFramework { namespace Forms
{
    class Form:public Control,public IObserver
    {
    public:
        Form();
        RadonFramework::Core::Types::Bool Visible();
        virtual void Visible(const RadonFramework::Core::Types::Bool Value);
        virtual RadonFramework::Core::Types::String Title();
        virtual void Title(const RadonFramework::Core::Types::String &Value);
        virtual void InitializeComponent();
        virtual void Idle(const IObserver* Sender);
        virtual void KeyPressed(const IO::VirtualKey::Type VK);
        virtual void KeyReleased(const IO::VirtualKey::Type VK);
        virtual void MouseButtonPressed(const IO::MouseEvent& Value);
        virtual void MouseButtonReleased(const IO::MouseEvent& Value);
        virtual void MouseMove(const IO::MouseEvent& Value);
        virtual IWindow* Backend();
        virtual void Size(const Math::Geometry::Size2D<>& NewSize);
        virtual void Position(const Math::Geometry::Point2D<>& NewPosition);
        virtual void Border(const RFTYPE::Bool Show);
        virtual void CloseButton(const RFTYPE::Bool Show);
        virtual void CursorVisible(const bool Value);

        Event<const IObserver*> OnIdle;
        Event<const IO::VirtualKey::Type> OnKeyPress;
        Event<const IO::VirtualKey::Type> OnKeyRelease;
        Event<const IO::MouseEvent&> OnMouseButtonPressed;
        Event<const IO::MouseEvent&> OnMouseButtonReleased;
        Event<const IO::MouseEvent&> OnMouseMove;
    protected:
        IWindow* m_Backend;
    };
} }

#endif
