#ifndef RF_IAPPLICATION_HPP
#define RF_IAPPLICATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Drawing/Forms/Form.hpp>

namespace RadonFramework
{
  namespace Forms
  {
    class IApplication
    {
      public:
        virtual ~IApplication(){};
        virtual void Run(Form *MainForm)=0;
        virtual void End()=0;
        virtual bool IsRunningOnDesktop()=0;
        virtual void ShowConsole(bool isVisible)=0;
    };
  }
}

#endif
