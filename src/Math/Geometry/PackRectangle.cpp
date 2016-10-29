#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Geometry/PackRectangle.hpp"
#include "RadonFramework/Collections/Algorithm/QuickSort.hpp"

namespace RadonFramework { namespace Math { namespace Geometry {

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
    m_Bins.Resize(0);
}

void PackRectangle::AddRectangle(const RF_Geo::Size2D<>& Size, void* UserData)
{
    RF_Collect::Pair<RF_Geo::Size2D<>, void*> info(Size, UserData);
    m_NotProcessedRectangles.AddLast(info);
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
            alreadyProcessedRectangles += m_Bins(i).Count();
        }

        RF_Type::Float32 necessaryArea = 0;
        for(RF_Type::Size i = 0; i < m_NotProcessedRectangles.Count(); ++i)
        {
            if(!m_NotProcessedRectangles[i].First.FitsInto(m_Dimension))
            {
                result = false;
                break;
            }
            necessaryArea += m_NotProcessedRectangles[i].First.GetArea();
        }

        if(result)
        {
            RF_Type::Size minimalBinAmount = ((necessaryArea-1.0) / m_Dimension.GetArea())+1;
            if(m_Bins.Count() < minimalBinAmount)
            {
                m_Bins.Resize(minimalBinAmount);
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

            }
            m_NotProcessedRectangles.Clear();
        }
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
        for (RF_Type::Size j = 0; j < m_Bins(i).Count(); ++j)
        {
            RF_Collect::Pair<RF_Geo::Size2D<>, void*> entry(m_Bins(i)(j).Rectangle.GetSize(),
                m_Bins(i)(j).UserData);

            if(m_Bins(i)(j).Fliped)
            {
                entry.First.Flip();
            }
            m_NotProcessedRectangles.AddLast(entry);
        }
    }
    m_Bins.Resize(0);
}

const RF_Geo::Size2D<>& PackRectangle::GetDimension() const
{
    return m_Dimension;
}

const RF_Collect::Array<RF_Collect::Array<PackRectangle::RectangleInfo>>& 
PackRectangle::GetBins() const
{
    return m_Bins;
}

RF_Type::Bool PackRectangle::NeedProcessing() const
{
    return m_NotProcessedRectangles.IsEmpty() == false;
}

} } }