#ifndef RF_WINDOWSWINDOW_HPP
#define RF_WINDOWSWINDOW_HPP

#include <RadonFramework/Defines.hpp>

#include <RadonFramework/Drawing/Forms/IWindow.hpp>
#include <vector>
#include <windows.h>

namespace RadonFramework
{
    namespace Forms
    {
        class WindowsWindow:public IWindow
        {
            public:
                WindowsWindow(WindowService *Service);
                ~WindowsWindow();

                //IWindow
                void* Handle();
                Core::Types::Bool Visible();
                void Visible(const Core::Types::Bool Value);
                Core::Types::String Title();
                void Title(const Core::Types::String &Value);
                void Size(const Math::Geometry::Size2D<>& NewSize);
                void Position(const Math::Geometry::Point2D<>& NewPosition);
                void ClientRectSize(const Math::Geometry::Size2D<>& NewSize);
                void Border(const Core::Types::Bool Value);
                void CursorVisible(const Core::Types::Bool Value);
                void CloseButton(const RFTYPE::Bool Show);
                WindowService* GetService();

                HWND GetHandle();

                static WindowsWindow* GetObjectByHandle(const HWND Handle);
                static Core::Types::UInt32 GetObjectCount();
                static WindowsWindow* GetObjectByIndex(const Core::Types::UInt32 Index);
            protected:
                WindowService *m_Service;
                RFTYPE::String m_Title;
                RFTYPE::Bool m_Border;
                RFTYPE::Bool m_Visible;
                RFTYPE::Bool m_CursorVisible;
                RFTYPE::Bool m_Created;//true if window is created;
                RFTYPE::Bool m_CloseButton;
                Math::Geometry::Size2D<> m_Size;
                Math::Geometry::Point2D<> m_Pos;

                HWND m_Handle;
                DWORD m_WindowFlags;

                static Collections::List<WindowsWindow*>m_Objects;
        };
    }
}

#endif
