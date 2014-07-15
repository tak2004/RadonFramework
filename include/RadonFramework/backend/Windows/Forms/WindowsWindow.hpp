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
                RF_Type::Bool Visible();
                void Visible(const RF_Type::Bool Value);
                RF_Type::String Title();
                void Title(const RF_Type::String &Value);
                void Size(const Math::Geometry::Size2D<>& NewSize);
                void Position(const Math::Geometry::Point2D<>& NewPosition);
                void ClientRectSize(const Math::Geometry::Size2D<>& NewSize);
                void Border(const RF_Type::Bool Value);
                void CursorVisible(const RF_Type::Bool Value);
                void CloseButton(const RF_Type::Bool Show);
                WindowService* GetService();

                HWND GetHandle();

                static WindowsWindow* GetObjectByHandle(const HWND Handle);
                static RF_Type::UInt32 GetObjectCount();
                static WindowsWindow* GetObjectByIndex(const RF_Type::UInt32 Index);
            protected:
                WindowService *m_Service;
                RF_Type::String m_Title;
                RF_Type::Bool m_Border;
                RF_Type::Bool m_Visible;
                RF_Type::Bool m_CursorVisible;
                RF_Type::Bool m_Created;//true if window is created;
                RF_Type::Bool m_CloseButton;
                Math::Geometry::Size2D<> m_Size;
                Math::Geometry::Point2D<> m_Pos;

                HWND m_Handle;
                DWORD m_WindowFlags;

                static Collections::List<WindowsWindow*>m_Objects;
        };
    }
}

#endif
