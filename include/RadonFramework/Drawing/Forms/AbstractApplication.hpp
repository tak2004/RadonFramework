#ifndef RF_IAPPLICATION_HPP
#define RF_IAPPLICATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Drawing/Forms/Form.hpp>

namespace RadonFramework::Forms
{
class AbstractApplication
{
public:
  virtual ~AbstractApplication() = default;
  virtual void Run(Form* MainForm) = 0;
  virtual void End() = 0;
  virtual RF_Type::Bool IsRunningOnDesktop() = 0;
  virtual void ShowConsole(RF_Type::Bool isVisible) = 0;
  virtual RF_Type::String GetClipboardText() = 0;
  virtual void SetClipboardText(const RF_Type::String& NewText) = 0;
};

}  // namespace RadonFramework::Forms

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif

#endif
