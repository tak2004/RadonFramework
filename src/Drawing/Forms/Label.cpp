#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Forms/Label.hpp"

namespace RadonFramework { namespace Forms {

void Label::SetText(const RF_Type::String& NewText)
{
    m_Text = NewText;
}

const RF_Type::String& Label::GetText() const
{
    return m_Text;
}

} }