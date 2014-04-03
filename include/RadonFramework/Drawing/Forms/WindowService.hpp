#ifndef RF_WINDOWSERVICE_HPP
#define RF_WINDOWSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFramework/Drawing/Forms/Resolution.hpp>
#include <RadonFramework/Drawing/Forms/DisplayInformation.hpp>
#include <RadonFramework/Diagnostics/Debugging/Error.hpp>
#include <RadonFramework/Collections/AutoVector.hpp>

namespace RadonFramework
{
    namespace Forms
    {
        class IWindow;
        class IApplication;

        namespace WindowServiceErrors
        {
            enum Type
            {
                NoError,
                InternalError,
                InvalidArgument,
                NotImplemented,
                MAX
            };
        }
        struct WindowServiceError:public Diagnostics::Debugging::Error<WindowServiceError,WindowServiceErrors::Type,WindowServiceErrors::MAX>{};

        class WindowService:public Core::Pattern::Service
        {
            public:
                WindowService(const RFTYPE::String &Name);
                ~WindowService();
                virtual IWindow* NewWindow()=0;
                virtual IApplication* Application()=0;
                /// Get Information of all displays.
                virtual Collections::AutoVector<DisplayInformation> GetAllDisplays()=0;
                /// Get current screen resolution.
                virtual WindowServiceError ScreenResolution(
                    const DisplayInformation& DiplayInfo,
                    RFTYPE::UInt32& ResolutionListIndex)=0;
                /// Set a new screen resolution.
                virtual void ScreenResolution(const DisplayInformation& DiplayInfo,
                                              const Resolution& NewResolution)=0;
            protected:
                IApplication *m_Application;
        };
    }
}

#endif