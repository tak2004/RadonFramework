#ifndef RF_WINDOWSERVICELOCATOR_HPP
#define RF_WINDOWSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/Drawing/Forms/WindowService.hpp>

namespace RadonFramework::Forms
{
class NullWindowService : public WindowService
{
public:
  NullWindowService(const RF_Type::String& Name) : WindowService(Name) {}
  AbstractWindow* NewWindow() final { return nullptr; }
  AbstractApplication* Application() final { return nullptr; }

  RF_Collect::AutoVector<DisplayInformation> GetAllDisplays() final
  {
    return RF_Collect::AutoVector<DisplayInformation>();
  }

  WindowServiceError
  ScreenResolution(const DisplayInformation& DiplayInfo,
                   RF_Type::UInt32& ResolutionListIndex) final
  {
    ResolutionListIndex = 0;
    return WindowServiceError::Generate(WindowServiceErrors::InvalidArgument);
  }

  void ScreenResolution(const DisplayInformation& DiplayInfo,
                        const Resolution& NewResolution) final
  {
  }

  RF_Type::Bool
  IsMouseButtonPressed(RF_IO::VirtualMouseButton::Type Which) final
  {
    return false;
  }
};

using WindowServiceLocator =
    RF_Pattern::Locator<WindowService, NullWindowService>;

}  // namespace RadonFramework::Forms

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif

#endif
