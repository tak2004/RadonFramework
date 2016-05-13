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
#include <RadonFramework/IO/VirtualMouseButton.hpp>

namespace RadonFramework { namespace Forms {

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

struct WindowServiceError:public RF_Debug::Error<WindowServiceError,WindowServiceErrors::Type,WindowServiceErrors::MAX>{};

class WindowService:public RF_Pattern::Service
{
public:
    WindowService(const RF_Type::String &Name);
    virtual ~WindowService() override;
    virtual IWindow* NewWindow()=0;
    virtual IApplication* Application()=0;
    /// Get Information of all displays.
    virtual RF_Collect::AutoVector<DisplayInformation> GetAllDisplays()=0;
    /// Get current screen resolution.
    virtual WindowServiceError ScreenResolution(
        const DisplayInformation& DiplayInfo,
        RF_Type::UInt32& ResolutionListIndex)=0;
    /// Set a new screen resolution.
    virtual void ScreenResolution(const DisplayInformation& DiplayInfo,
                                    const Resolution& NewResolution)=0;
    virtual RF_Type::Bool IsMouseButtonPressed(RF_IO::VirtualMouseButton::Type Which)=0;
protected:
    IApplication *m_Application;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif

#endif