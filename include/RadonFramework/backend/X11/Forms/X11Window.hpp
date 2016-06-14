#ifndef RF_X11WINDOW_HPP
#define RF_X11WINDOW_HPP

#include <X11/Xlib.h>
#undef Bool
#undef True
#undef False
#include <RadonFramework/Drawing/Forms/AbstractWindow.hpp>
#include <vector>

namespace RadonFramework { namespace Forms {

class X11Window:public AbstractWindow
{
    protected:
    Window m_Handle;
    Atom m_wmDelete;
    Cursor m_InvisibleCursor;
    XSetWindowAttributes m_WindowFlags;
    WindowService *m_Service;

    RF_Type::String m_Title;
    RF_Type::Bool m_Border;
    RF_Type::Bool m_Visible;
    RF_Type::Bool m_CursorVisible;
    RF_Type::Bool m_Created;//true if window is created;
    RF_Type::Bool m_CloseButton;

    static std::vector<X11Window*>m_Objects;
    public:
    X11Window(WindowService *Service);
    ~X11Window();

    //AbstractWindow
    void* Handle();
    RF_Type::Bool Visible();
    void Visible(const RF_Type::Bool Value);
    RF_Type::String Title();
    void Title(const RF_Type::String &Value);
    void Size(const Math::Geometry::Size2D<>& NewSize);
    void Position(const Math::Geometry::Point2D<>& NewPosition);
    void Border(const RF_Type::Bool Value);
    void CursorVisible(const RF_Type::Bool Value);
    void ClientRectSize(const Math::Geometry::Size2D<>& NewSize);
    void CloseButton(const RF_Type::Bool Show);

    Window GetHandle();
    Atom GetDeleteAtom();
    static X11Window* GetObjectByHandle(Window Handle);
    static unsigned int GetObjectCount();
    static X11Window* GetObjectByIndex(unsigned int Index);
    WindowService* GetService();
};

} }
#endif
