#ifndef RF_WINDOWSERVICELOCATOR_HPP
#define RF_WINDOWSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/Drawing/Forms/WindowService.hpp>

namespace RadonFramework
{
    namespace Forms
    {
        class NullWindowService:public WindowService
        {
            public:
                NullWindowService(const RadonFramework::Core::Types::String &Name):WindowService(Name){}
                IWindow* NewWindow(){return 0;}
                IApplication* Application(){return 0;}
                
                Collections::AutoVector<DisplayInformation> GetAllDisplays()
                {
                    return Collections::AutoVector<DisplayInformation>();
                }
                
                WindowServiceError ScreenResolution(const DisplayInformation& DiplayInfo,
                                                    Core::Types::UInt32& ResolutionListIndex)
                {
					ResolutionListIndex=0; return WindowServiceError::Generate(WindowServiceErrors::InvalidArgument);
                }

				void ScreenResolution(const DisplayInformation& DiplayInfo, const Resolution& NewResolution){}
        };

        typedef Core::Pattern::Locator<WindowService,NullWindowService> WindowServiceLocator;
    }
}

#endif
