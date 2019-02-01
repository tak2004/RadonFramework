#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Geometry/PackRectangle.hpp"
#include "RadonFramework/Collections/Algorithm/QuickSort.hpp"

namespace RadonFramework::Math::Geometry {

struct Node
{
    struct LeafNode
    {
        Node* Instance;
        RF_Type::Bool Fill;
        LeafNode();
        void Set(const RF_Geo::Rectangle<>& Rectangle);
    };
    LeafNode Childs[2];
    void* UserData;
    RF_Geo::Rectangle<> Rectangle;
    RF_Type::Bool Flipped;

    Node();
    Node* Insert(RF_Collect::Pair<RF_Geo::Size2D<>, void*>& RectangleData);
    RF_Type::Size TotalElements()const;
};

Node::LeafNode::LeafNode()
:Instance(nullptr)
,Fill(false)
{
}

void Node::LeafNode::Set(const RF_Geo::Rectangle<>& Rectangle)
{
    if (!Instance)
    {
        Instance = new Node();
        Instance->Rectangle = Rectangle;
    }
    else
    {
        Instance->Rectangle = Rectangle;
        Instance->UserData = nullptr;
    }
    Fill = true;
}

Node* Node::Insert(RF_Collect::Pair<RF_Geo::Size2D<>, void*>& RectangleData)
{
    if(Childs[0].Instance && Childs[0].Fill)
    {
      Node* newNode = Childs[0].Instance->Insert(RectangleData);
      if (newNode)
        return newNode;
      return Childs[1].Instance->Insert(RectangleData);
    }

    if (UserData)
        return nullptr;

    auto fitting = RectangleData.First.CanFitInto(Rectangle.GetSize());
    switch(fitting)
    {
        case RF_Geo::Fitting::No: 
            return nullptr;
        case RF_Geo::Fitting::Fit: 
            break;
        case RF_Geo::Fitting::FitIfFlip: 
            RectangleData.First.Flip(); 
            Flipped = true;
            break;
        case RF_Geo::Fitting::PerfectFit: 
            UserData = RectangleData.Second; 
            return this;
        case RF_Geo::Fitting::PerfectFitIfFlip: 
            UserData = RectangleData.Second; 
            RectangleData.First.Flip(); 
            Flipped = true;
            return this;
    }

    if(Rectangle.Width() - RectangleData.First.Width > Rectangle.Height() - RectangleData.First.Height)
    {
        Childs[0].Set(Rectangle);
        Childs[0].Instance->Rectangle.Width(RectangleData.First.Width);
        Childs[1].Set(Rectangle);
        Childs[1].Instance->Rectangle.Left(Childs[1].Instance->Rectangle.Left() + RectangleData.First.Width);
        Childs[1].Instance->Rectangle.Width(Rectangle.Width() - RectangleData.First.Width);
    }
    else
    {
        Childs[0].Set(Rectangle);
        Childs[0].Instance->Rectangle.Height(RectangleData.First.Height);
        Childs[1].Set(Rectangle);
        Childs[1].Instance->Rectangle.Top(Childs[1].Instance->Rectangle.Top() + RectangleData.First.Height);
        Childs[1].Instance->Rectangle.Height(Rectangle.Height() - RectangleData.First.Height);
    }

    return Childs[0].Instance->Insert(RectangleData);
}

RF_Type::Size Node::TotalElements() const
{
    RF_Type::Size result = 0;
    if (Childs[0].Fill)
        result += Childs[0].Instance->TotalElements();

    if (Childs[1].Fill)
        result += Childs[1].Instance->TotalElements();

    if (UserData)
        ++result;
    return result;
}

Node::Node()
:UserData(nullptr)
,Flipped(false)
{

}

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

void AddLeafs(const Node& CurrentNode, PackRectangle::Bin& Bin, int& Index)
{
    if (CurrentNode.UserData)
    {
        Bin(Index).UserData = CurrentNode.UserData;
        Bin(Index).Rectangle = CurrentNode.Rectangle;
        Bin(Index).Flipped = CurrentNode.Flipped;
        ++Index;
    }
    else
    {
        if (CurrentNode.Childs[0].Fill)
            AddLeafs(*CurrentNode.Childs[0].Instance, Bin, Index);
        if(CurrentNode.Childs[1].Fill)
            AddLeafs(*CurrentNode.Childs[1].Instance, Bin, Index);
    }
}

RF_Type::Bool PackRectangle::Pack()
{
    RF_Type::Bool fits = true;

    if(m_NotProcessedRectangles.IsEmpty() == false)
    {
        SortLargestToSmallest();
        fits = IsDimensionRequirementFullfilled();

        if(fits)
        {
            RF_Collect::List<Node> bins;
            auto& root = bins.CreateElementAtEnd();
            root.Rectangle.SetSize(m_Dimension);
            for(auto& rectangle: m_NotProcessedRectangles)
                if(root.Insert(rectangle) == nullptr)
                {
                    root = bins.CreateElementAtEnd();
                    root.Rectangle.SetSize(m_Dimension);
                    root.Insert(rectangle);
                }                    
            m_NotProcessedRectangles.Clear();
            m_Bins.Resize(bins.Count());
            for(auto i = 0; i < bins.Count(); ++i)
            {
                auto elements = bins[i].TotalElements();
                m_Bins(i).Resize(elements);
                auto index = 0;
                AddLeafs(bins[i], m_Bins(i), index);
            }
        }            
    }
    return fits;
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

            if(m_Bins(i)(j).Flipped)
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

const RF_Collect::Array<PackRectangle::Bin>& PackRectangle::GetBins() const
{
    return m_Bins;
}

RF_Type::Bool PackRectangle::NeedProcessing() const
{
    return m_NotProcessedRectangles.IsEmpty() == false;
}

void PackRectangle::SortLargestToSmallest()
{
    RF_Algo::QuickSort(m_NotProcessedRectangles,
                       [](RF_Collect::Pair<RF_Geo::Size2D<>, void*>& A,
                          RF_Collect::Pair<RF_Geo::Size2D<>, void*>& B) 
    {
        if(A.First.GetArea() == B.First.GetArea()) {
            return 0;
        }
        else {
            if(A.First.GetArea() > B.First.GetArea())
                return 1;
            else
                return -1;
        }
    });
}

RF_Type::Bool PackRectangle::IsDimensionRequirementFullfilled()const
{
    RF_Type::Bool result = true;
    for(auto& rectangle : m_NotProcessedRectangles)
    {
        if(rectangle.First.CanFitInto(m_Dimension) == RF_Geo::Fitting::No)
        {
            result = false;
            break;
        }
    }
    return result;
}

}