#ifndef RF_WINDOWSWINDOW_HPP
#define RF_WINDOWSWINDOW_HPP

#include <RadonFramework/Defines.hpp>

#include <RadonFramework/Drawing/Forms/AbstractWindow.hpp>
#include <windows.h>

namespace RadonFramework::Forms {

class WindowsWindow:public AbstractWindow
{
public:
    WindowsWindow(WindowService *Service);
    virtual ~WindowsWindow();

    //IWindow
    virtual void* Handle()const override;
    virtual RF_Type::Bool Visible() override;
    virtual void Visible(const RF_Type::Bool Value) override;
    virtual RF_Type::String Title() override;
    virtual void Title(const RF_Type::String &Value) override;
    virtual void Size(const Math::Geometry::Size2D<>& NewSize) override;
    virtual void Position(const Math::Geometry::Point2D<>& NewPosition) override;
    virtual void ClientRectSize(const Math::Geometry::Size2D<>& NewSize) override;
    virtual void Border(const RF_Type::Bool Value) override;
    virtual void CursorVisible(const RF_Type::Bool Value) override;
    virtual void CloseButton(const RF_Type::Bool Show) override;
    virtual WindowService* GetService() override;
    virtual RF_Type::Bool HasFocus()const;
    virtual RF_Geo::Point2D<> GetCursorPosition()const;
    virtual RF_Mem::AutoPointerArray<RF_Type::UInt8> CaptureClientRect() override;
    virtual void ChangeCursor(const Cursor& NewCursor) override;

    HWND GetHandle()const;

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

#endif
