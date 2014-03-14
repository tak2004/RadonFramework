#ifndef RF_X11APPLICATION_HPP
#define RF_X11APPLICATION_HPP

#include <RadonFramework/Drawing/Forms/IApplication.hpp>
#include <X11/Xlib.h>
#undef Bool
#undef True
#undef False

namespace RadonFramework
{
  namespace Forms
  {
    class X11Application:public IApplication
    {
      protected:
        Display* m_Display;
        bool m_Active;
      public:
        X11Application();
        ~X11Application();
        void Run(Form *MainForm);
        void End();
        Display* GetDisplay();
    };
  }
}

#endif
