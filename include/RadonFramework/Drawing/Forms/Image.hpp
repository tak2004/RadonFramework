#ifndef RF_DRAWING_FORMS_IMAGE_HPP
#define RF_DRAWING_FORMS_IMAGE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Drawing/Forms/Control.hpp>
#include <RadonFramework/Drawing/Image.hpp>

namespace RadonFramework::Forms
{
class Image : public Control
{
public:
  Image(Control* Parent = nullptr);
  void SetImage(const RF_Draw::Image& NewText);
  const RF_Draw::Image& GetImage() const;
  void RebuildVisuals() override;

protected:
  RF_Draw::Image m_Image;
};

}  // namespace RadonFramework::Forms

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif  // RF_SHORTHAND_NAMESPACE_FORM

#endif  // RF_DRAWING_FORMS_IMAGE_HPP