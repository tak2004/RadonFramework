#ifndef RF_X11WINDOWSERVICE_HPP
#define RF_X11WINDOWSERVICE_HPP

#include <RadonFramework/Drawing/Forms/WindowService.hpp>

namespace RadonFramework
{
  namespace Forms
  {
    class X11WindowService:public WindowService
    {
      protected:
        IApplication* m_Application;
      public:
        X11WindowService(const RF_Type::String &Name);
        ~X11WindowService();
        IWindow* NewWindow();
        IApplication* Application();

        Collections::AutoVector<DisplayInformation> GetAllDisplays();
        WindowServiceError ScreenResolution(const DisplayInformation& DiplayInfo,
                                                    RF_Type::UInt32& ResolutionListIndex);
        void ScreenResolution(const DisplayInformation& DiplayInfo, const Resolution& NewResolution);
    };
  }
}

#endif
