#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Forms/GridLayouter.hpp"
#include "RadonFramework/Drawing/Forms/Cursor.hpp"

namespace RadonFramework::Forms {

GridLayouter::GridLayouter(Control* Parent /*= nullptr*/, 
    const RF_Type::Size RowCount /*= 1*/, const RF_Type::Size ColumnCount /*= 1*/)
:Control(Parent)
,m_RowCount(RowCount)
,m_ColumnCount(ColumnCount)
{
    m_Cells.Resize(RowCount*ColumnCount);
    for(RF_Type::Size i = 0; i < m_Cells.Count(); ++i)
    {
        m_Cells(i) = nullptr;
    }
}

void GridLayouter::SetGap(const RF_Geo::Size2Df& Gap)
{
    m_CellGap = Gap;
}

void GridLayouter::AddChild(Control& Obj)
{
    Obj.SetLayouter(*this);
    Control::AddChild(Obj);
}

void GridLayouter::AddChild(Control& Obj, const RF_Type::Size RowIndex,
    const RF_Type::Size ColumnIndex)
{
    if(RowIndex < m_RowCount && ColumnIndex < m_ColumnCount)
    {
        if(m_Cells(RowIndex * m_ColumnCount + ColumnIndex) != nullptr)
        {
            RemoveChild(*m_Cells(RowIndex * m_ColumnCount + ColumnIndex));
        }
        m_Cells(RowIndex * m_ColumnCount + ColumnIndex) = &Obj;
        AddChild(Obj);
    }
}

RF_Geo::Rectanglef GridLayouter::GetContentRect(const Control& Child) const
{
    RF_Geo::Rectanglef result;
    RF_Type::Size row = m_RowCount;
    RF_Type::Size column = m_ColumnCount;
    for (RF_Type::Size i = 0; i < m_Cells.Count(); ++i)
    {
        if(m_Cells(i) == &Child)
        {
            row = i / m_ColumnCount;
            column = i-(row * m_ColumnCount);
            break;
        }
    }

    if(row < m_RowCount)
    {
        result.Width(Width() / m_RowCount);
        result.Height(Height() / m_ColumnCount);
        result.Left(Left()+column * result.Width());
        result.Top(Top()+row* result.Height());
    }
    return result;
}

}