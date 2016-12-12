#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Geometry/PackRectangle.hpp"
#include "RadonFramework/Collections/Algorithm/QuickSort.hpp"

namespace RadonFramework { namespace Math { namespace Geometry {

struct PackRectangle::Node
{
    Node* Childs[2];
    void* UserData;
    RF_Geo::Rectangle<> Rectangle;
};

PackRectangle::PackRectangle(const RF_Type::Size EdgeSize)
:m_Dimension(EdgeSize, EdgeSize)
{

}

PackRectangle::PackRectangle(const RF_Type::Size MaxWidth, const RF_Type::Size MaxHeight)
:m_Dimension(MaxWidth,MaxHeight)
{

}

PackRectangle::PackRectangle(const RF_Geo::Size2D<>& MaxSize)
:m_Dimension(MaxSize)
{

}

PackRectangle::~PackRectangle()
{
    Clear();
}

void PackRectangle::Clear()
{
    m_NotProcessedRectangles.Clear();
    m_Bins.Clear();
    m_Root.Clear();
}

void PackRectangle::AddRectangle(const RF_Geo::Size2D<>& Size, void* UserData)
{
    RF_Collect::Pair<RF_Geo::Size2D<>, void*> info(Size, UserData);
    m_NotProcessedRectangles.AddLast(info);
}

void PackRectangle::Insert(RF_Collect::Pair<RF_Geo::Size2D<>, void*>& RectangleData)
{
    RF_Type::Size i = 0;
    for (; i < m_Bins.Count(); ++i)
    {
        for (RF_Type::Size j = 0; j < m_Root[i].Count(); ++j)
        {
            if(m_Root[i][j].Childs[1] == nullptr && m_Root[i][j].UserData == nullptr)
            {
                if(RectangleData.First.FitsInto(m_Root[i][j].Rectangle.GetSize()))
                {
/*                    RF_Geo::Rectangle<> rect(m_Root[i][j].Rectangle.GetPosition(), RectangleData.First);
                    if(m_Root[i][j].Childs[0]->Rectangle.Width == m_Root[i][j].Rectangle.Width)
                    {// is vertical split
                        rect.SetPosition({m_Root[i][j].Childs[0]->Rectangle.Left, m_Root[i][j].Childs[0]->Rectangle.Bottom});
                    }
                    else
                    {// is horizontal split
                        rect.SetPosition({m_Root[i][j].Childs[0]->Rectangle.Right, m_Root[i][j].Childs[0]->Rectangle.Top});
                    }
                    // add node
                    m_Root.Last()->AddLast({nullptr, nullptr, RectangleData.Second, rect});
                    // add horizontal split
                    rect.SetSize({rect.Width(), m_Root[i][j].Rectangle.Height});
                    m_Root.Last()->AddLast({m_Root.Last()->Last(), nullptr, nullptr, rect});
                    // add vertical split

                    // erst hier muss noch das richtige maß hin

                    rect.SetSize(m_Root[i][j].Rectangle.Height);
                    m_Root.Last()->AddLast({m_Root.Last()->Last(), nullptr, nullptr, rect});
                    m_Root[i][j].Childs[1] = m_Root.Last()->Last();
*/                }
            }
        }
    }

    if(i == m_Bins.Count())
    {
        m_Root.AddLast(RF_Collect::List<Node>());
        // add node
        m_Root.Last()->AddLast({nullptr, nullptr,RectangleData.Second, {{0,0},RectangleData.First}});
        // add horizontal split
        RF_Geo::Rectangle<> split(0,0,m_Dimension.Width,RectangleData.First.Height);
        m_Root.Last()->AddLast({m_Root.Last()->Last(), nullptr, nullptr, split});
        // add vertical split
        m_Root.Last()->AddLast({m_Root.Last()->Last(), nullptr, nullptr, {{0,0},m_Dimension}});
    }
}

RF_Type::Bool PackRectangle::Pack()
{
    RF_Type::Bool result = true;

    // New rectangles were added.
    if(m_NotProcessedRectangles.Count() > 0)
    {
        RF_Type::Size alreadyProcessedRectangles = 0;
        for(RF_Type::Size i = 0; i < m_Bins.Count(); ++i)
        {
            alreadyProcessedRectangles += m_Bins[i].Count();
        }

        RF_Algo::QuickSort(m_NotProcessedRectangles, 
            [](RF_Collect::Pair<RF_Geo::Size2D<>, void*>& A, 
                RF_Collect::Pair<RF_Geo::Size2D<>, void*>& B) {
            if(A.First.GetArea() == B.First.GetArea())
                return 0;
            else
                if(A.First.GetArea() > B.First.GetArea())
                    return 1;
                else
                    return -1;
        });

        
        for (RF_Type::Size i = 0; i < m_NotProcessedRectangles.Count(); ++i)
        {
            Insert(m_NotProcessedRectangles[i]);
        }
        m_NotProcessedRectangles.Clear();
    }
    return result;
}

RF_Type::Bool PackRectangle::Rebuild()
{
    return false;
}

void PackRectangle::SetDimension(const RF_Type::Size EdgeSize)
{
    SetDimension(Size2D<>(EdgeSize, EdgeSize));
}

void PackRectangle::SetDimension(const RF_Type::Size MaxWidth, 
    const RF_Type::Size MaxHeight)
{
    SetDimension(Size2D<>(MaxWidth, MaxHeight));
}

void PackRectangle::SetDimension(const RF_Geo::Size2D<>& MaxSize)
{
    m_Dimension = MaxSize;
    for(RF_Type::Size i = 0; i < m_Bins.Count(); ++i)
    {
        for (RF_Type::Size j = 0; j < m_Bins[i].Count(); ++j)
        {
            RF_Collect::Pair<RF_Geo::Size2D<>, void*> entry(m_Bins[i](j).Rectangle.GetSize(),
                m_Bins[i](j).UserData);

            if(m_Bins[i](j).Fliped)
            {
                entry.First.Flip();
            }
            m_NotProcessedRectangles.AddLast(entry);
        }
    }
    m_Bins.Clear();
    m_Root.Clear();
}

const RF_Geo::Size2D<>& PackRectangle::GetDimension() const
{
    return m_Dimension;
}

const RF_Collect::List<PackRectangle::Bin>& PackRectangle::GetBins() const
{
    return m_Bins;
}

RF_Type::Bool PackRectangle::NeedProcessing() const
{
    return m_NotProcessedRectangles.IsEmpty() == false;
}

} } }