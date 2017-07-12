#ifndef RF_WINDOWSWINDOWSERVICE_HPP
#define RF_WINDOWSWINDOWSERVICE_HPP

#include <RadonFramework/Drawing/Forms/WindowService.hpp>

namespace RadonFramework::Forms {

class WindowsWindowService:public WindowService
{
protected:
	AbstractApplication* m_Application;
public:
	WindowsWindowService(const RF_Type::String &Name);
	~WindowsWindowService();
	AbstractWindow* NewWindow();
	AbstractApplication* Application();

    Collections::AutoVector<DisplayInformation> GetAllDisplays();
    WindowServiceError ScreenResolution(const DisplayInformation& DisplayInfo,
                                        RF_Type::UInt32& ResolutionListIndex);
	void ScreenResolution(const DisplayInformation& DiplayInfo, const Resolution& NewResolution);

    RF_Type::Bool IsMouseButtonPressed(RF_IO::VirtualMouseButton::Type Which);
    static void Register();
};

}

#endif //namespace