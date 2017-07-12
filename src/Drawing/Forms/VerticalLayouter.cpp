#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Forms/VerticalLayouter.hpp"
#include "RadonFramework/Drawing/Forms/Cursor.hpp"

namespace RadonFramework::Forms {

VerticalLayouter::VerticalLayouter(Control* Parent /*= nullptr*/)
:Control(Parent)
{

}

void VerticalLayouter::SetGap(const RF_Geo::Size2Df& Gap)
{
    m_CellGap = Gap;
}

void VerticalLayouter::AddChild(Control& Obj)
{
    Obj.SetLayouter(*this);
    Control::AddChild(Obj);
}

RF_Geo::Rectanglef VerticalLayouter::GetContentRect(const Control& Child) const
{
    RF_Geo::Rectanglef result = GetClientRectangle();
    auto index = IndexOfChild(Child);

    if(index >= 0)
    {
        result.Width(Width());
        result.Height(Height() / GetChildCount());
        result.Left(Left());
        result.Top(Top() + index * result.Height());
    }
    return result;
}

}