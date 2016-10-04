#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Forms/Label.hpp"

namespace RadonFramework { namespace Forms {

Label::Label(Control* Parent /*= nullptr*/)
:Control(Parent)
{
    m_ClientRectangle.Width(100);
    m_ClientRectangle.Height(100);
}

void Label::SetText(const RF_Type::String& NewText)
{
    m_Text = NewText;
    
    RF_Geo::Point2Df position(m_ClientRectangle.Left(), m_ClientRectangle.Top());
    RF_Geo::Size2Df dimension(m_ClientRectangle.Width(), m_ClientRectangle.Height());
    m_Path.Clear();
    m_Path.AddRectangle(position, dimension);
    m_Path.Finalize();
}

const RF_Type::String& Label::GetText() const
{
    return m_Text;
}

} }