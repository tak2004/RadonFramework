#ifndef RF_WINDOWSERVICELOCATOR_HPP
#define RF_WINDOWSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/Drawing/Forms/WindowService.hpp>

namespace RadonFramework { namespace Forms {

class NullWindowService:public WindowService
{
public:
    NullWindowService(const RF_Type::String &Name):WindowService(Name){}
    AbstractWindow* NewWindow(){return 0;}
    AbstractApplication* Application(){return 0;}
                
    RF_Collect::AutoVector<DisplayInformation> GetAllDisplays()
    {
        return RF_Collect::AutoVector<DisplayInformation>();
    }
                
    WindowServiceError ScreenResolution(const DisplayInformation& DiplayInfo,
                                        RF_Type::UInt32& ResolutionListIndex)
    {
		ResolutionListIndex=0; return WindowServiceError::Generate(WindowServiceErrors::InvalidArgument);
    }

	void ScreenResolution(const DisplayInformation& DiplayInfo, const Resolution& NewResolution){}

    RF_Type::Bool IsMouseButtonPressed(RF_IO::VirtualMouseButton::Type Which)
    {
        return false;
    }
};

typedef RF_Pattern::Locator<WindowService,NullWindowService> WindowServiceLocator;

} }

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif

#endif
