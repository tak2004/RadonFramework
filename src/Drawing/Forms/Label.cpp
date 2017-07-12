#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Forms/Label.hpp"

namespace RadonFramework::Forms {

Label::Label(Control* Parent /*= nullptr*/)
:Control(Parent)
{
    SetSize({100,100});
}

void Label::SetText(const RF_Type::String& NewText)
{
    m_Text = NewText;
    RebuildVisuals();
}

const RF_Type::String& Label::GetText() const
{
    return m_Text;
}

void Label::RebuildVisuals()
{
    Control::RebuildVisuals();
    
    RF_Geo::Point2Df position(Left(), Top());
    RF_Geo::Size2Df dimension(Width(), Height());
    RF_Draw::Fill red;
    red.Color = {1,0,0,1};
    m_Path.Clear();
    m_Path.SetFill(red);
    m_Path.AddRectangle(position, dimension);
    m_Path.Finalize();
}

}