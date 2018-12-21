#ifndef RF_DRAWING_FORMS_LABEL_HPP
#define RF_DRAWING_FORMS_LABEL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Drawing/Forms/Control.hpp>

namespace RadonFramework::Forms
{
class Label : public Control
{
public:
  Label(Control* Parent = nullptr);
  void SetText(const RF_Type::String& NewText);
  const RF_Type::String& GetText() const;
  void RebuildVisuals() override;

protected:
  RF_Type::String m_Text;
};

}  // namespace RadonFramework::Forms

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif  // RF_SHORTHAND_NAMESPACE_FORM

#endif  // RF_DRAWING_FORMS_LABEL_HPP