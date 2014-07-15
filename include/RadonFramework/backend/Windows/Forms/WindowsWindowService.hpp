#ifndef RF_WINDOWSWINDOWSERVICE_HPP
#define RF_WINDOWSWINDOWSERVICE_HPP

#include <RadonFramework/Drawing/Forms/WindowService.hpp>

namespace RadonFramework
{
    namespace Forms
	{
		class WindowsWindowService:public WindowService
		{
			protected:
				IApplication* m_Application;
			public:
				WindowsWindowService(const RF_Type::String &Name);
				~WindowsWindowService();
				IWindow* NewWindow();
				IApplication* Application();

                Collections::AutoVector<DisplayInformation> GetAllDisplays();
                WindowServiceError ScreenResolution(const DisplayInformation& DisplayInfo,
                                                    RF_Type::UInt32& ResolutionListIndex);
				void ScreenResolution(const DisplayInformation& DiplayInfo, const Resolution& NewResolution);
		};
    }
}

#endif //namespace