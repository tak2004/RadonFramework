#ifndef RF_WINDOWSAPPLICATION_HPP
#define RF_WINDOWSAPPLICATION_HPP

#include <RadonFramework/Drawing/Forms/IApplication.hpp>

namespace RadonFramework
{
  namespace Forms
  {
    class WindowsApplication:public IApplication
    {
      protected:
        bool m_Active;
      public:
        WindowsApplication();
        ~WindowsApplication();
        void Run(Form *MainForm);
        void End();
        bool IsRunningOnDesktop();
        void ShowConsole(bool isVisible);
    };
  }
}

#endif
