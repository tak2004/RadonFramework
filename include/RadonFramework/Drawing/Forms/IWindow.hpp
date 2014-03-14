#ifndef RF_IWINDOW_HPP
#define RF_IWINDOW_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Event.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>
#include <RadonFramework/Math/Geometry/Point2D.hpp>
#include <RadonFramework/IO/VirtualKey.hpp>
#include <RadonFramework/IO/MouseEvent.hpp>

namespace RadonFramework
{
    namespace Forms
    {
        class WindowService;

        class IWindow
        {
            public:
                virtual ~IWindow(){};
                virtual void* Handle()=0;
                virtual RFTYPE::Bool Visible()=0;
                virtual void Visible(const RFTYPE::Bool Value)=0;
                virtual RFTYPE::String Title()=0;
                virtual void Title(const RFTYPE::String &Value)=0;
                virtual void Size(const Math::Geometry::Size2D<>& NewSize)=0;
                virtual void Position(const Math::Geometry::Point2D<>& NewPosition)=0;
                virtual void ClientRectSize(const Math::Geometry::Size2D<>& NewSize)=0;
                virtual void Border(const RFTYPE::Bool Value)=0;
                virtual void CursorVisible(const RFTYPE::Bool Value)=0;
                virtual WindowService* GetService()=0;
                virtual void CloseButton(const RFTYPE::Bool Show) = 0;

                Event<const Math::Geometry::Size2D<>&> OnResize;
                Event<const Math::Geometry::Point2D<>&> OnReposition;
                Event<const IObserver*> OnIdle;
                Event<const IO::VirtualKey::Type> OnKeyPress;
                Event<const IO::VirtualKey::Type> OnKeyRelease;
                Event<const IO::MouseEvent&> OnMouseButtonPressed;
                Event<const IO::MouseEvent&> OnMouseButtonReleased;
                Event<const IO::MouseEvent&> OnMouseMove;
        };
    }
}

#endif
