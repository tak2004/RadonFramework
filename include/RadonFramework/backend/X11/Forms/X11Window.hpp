#ifndef RF_X11WINDOW_HPP
#define RF_X11WINDOW_HPP

#include <X11/Xlib.h>
#undef Bool
#undef True
#undef False
#include <RadonFramework/Drawing/Forms/IWindow.hpp>
#include <vector>

namespace RadonFramework
{
  namespace Forms
  {
    class X11Window:public IWindow
    {
      protected:
        Window m_Handle;
        Atom m_wmDelete;
        Cursor m_InvisibleCursor;
        XSetWindowAttributes m_WindowFlags;
        WindowService *m_Service;

        RFTYPE::String m_Title;
        RFTYPE::Bool m_Border;
        RFTYPE::Bool m_Visible;
        RFTYPE::Bool m_CursorVisible;
        RFTYPE::Bool m_Created;//true if window is created;
        RFTYPE::Bool m_CloseButton;

        static std::vector<X11Window*>m_Objects;
      public:
        X11Window(WindowService *Service);
        ~X11Window();

        //IWindow
        void* Handle();
        Core::Types::Bool Visible();
        void Visible(const Core::Types::Bool Value);
        Core::Types::String Title();
        void Title(const Core::Types::String &Value);
        void Size(const Math::Geometry::Size2D<>& NewSize);
        void Position(const Math::Geometry::Point2D<>& NewPosition);
        void Border(const Core::Types::Bool Value);
        void CursorVisible(const Core::Types::Bool Value);
        void ClientRectSize(const Math::Geometry::Size2D<>& NewSize);
        void CloseButton(const RFTYPE::Bool Show);

        Window GetHandle();
        Atom GetDeleteAtom();
        static X11Window* GetObjectByHandle(Window Handle);
        static unsigned int GetObjectCount();
        static X11Window* GetObjectByIndex(unsigned int Index);
        WindowService* GetService();
    };
  }
}
#endif
