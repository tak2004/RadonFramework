#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Forms/HorizontalLayouter.hpp"
#include "RadonFramework/Drawing/Forms/Cursor.hpp"

namespace RadonFramework::Forms {

HorizontalLayouter::HorizontalLayouter(Control* Parent /*= nullptr*/)
:Control(Parent)
{

}

void HorizontalLayouter::SetGap(const RF_Geo::Size2Df& Gap)
{
    m_CellGap = Gap;
}

void HorizontalLayouter::AddChild(Control& Obj)
{
    Obj.SetLayouter(*this);
    Control::AddChild(Obj);
}

RF_Geo::Rectanglef HorizontalLayouter::GetContentRect(const Control& Child) const
{
    RF_Geo::Rectanglef result = GetClientRectangle();
    auto index = IndexOfChild(Child);

    if(index >= 0)
    {
        result.Width(Width() / GetChildCount());
        result.Height(Height());
        result.Left(Left() + index * result.Width());
        result.Top(Top());
    }
    return result;
}

}