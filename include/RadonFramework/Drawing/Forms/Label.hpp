#ifndef RF_DRAWING_FORMS_LABEL_HPP
#define RF_DRAWING_FORMS_LABEL_HPP

#include <RadonFramework/Drawing/Forms/Control.hpp> 

namespace RadonFramework { namespace Forms { 

class Label: public Control
{
public:
    void SetText(const RF_Type::String& NewText);
    const RF_Type::String& GetText()const;
protected:
    RF_Type::String m_Text;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif // RF_SHORTHAND_NAMESPACE_FORM

#endif // RF_DRAWING_FORMS_LABEL_HPP