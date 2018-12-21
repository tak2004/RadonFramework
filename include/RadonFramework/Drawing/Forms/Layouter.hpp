#ifndef RF_DRAWING_FORMS_LAYOUTER_HPP
#define RF_DRAWING_FORMS_LAYOUTER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Geometry/Rectangle.hpp>

namespace RadonFramework::Forms
{
class Control;

class Layouter
{
public:
  virtual RF_Geo::Rectanglef GetContentRect(const Control& Child) const = 0;
};

}  // namespace RadonFramework::Forms

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif

#endif  // RF_DRAWING_FORMS_LAYOUTER_HPP
