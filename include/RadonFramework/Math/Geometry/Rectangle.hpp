#ifndef RF_MATH_GEOMETRY_RECTANGLE_HPP
#define RF_MATH_GEOMETRY_RECTANGLE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Geometry/Point2D.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>

namespace RadonFramework::Math::Geometry {

template<class PT=RF_Type::Int32, class ST = RF_Type::UInt32>
class Rectangle
{
public:
    Rectangle();
    Rectangle(const PT Left,const PT Top,const PT Right, const PT Bottom);
    Rectangle(const Point2D<PT> &Point1, const Point2D<PT> &Point2);
    Rectangle(const Point2D<PT> &Position, const Size2D<ST> &Size);
    Rectangle(const Rectangle<PT,ST>& Copy);

    ST Width()const;
    void Width(const ST Value);
    ST Height()const;
    void Height(const ST Value);
    Size2D<ST> GetSize()const;
    void SetSize(const Size2D<ST>& Size);
    Point2D<PT> GetPosition()const;
    void SetPosition(const Point2D<PT>& Point);
    PT Left()const;
    void Left(const PT Value);
    PT Top()const;
    void Top(const PT Value);
    PT Bottom()const;
    PT Right()const;

    RF_Type::Bool Equals(const Rectangle<PT,ST> &Other)const;
    RF_Type::Bool IsIntersect(const Rectangle<PT,ST> &Other)const;
    RF_Type::Bool IsIntersect(const Point2D<PT> &Other)const;
    void Flip();
protected:
    Point2D<PT> m_Position;
    Size2D<ST> m_Size;
};

template<class PT/*=RF_Type::Int32*/, class ST /*= RF_Type::UInt32*/>
void Rectangle<PT, ST>::Top(const PT Value)
{
    m_Position.Y = Value;
}

template<class PT/*=RF_Type::Int32*/, class ST /*= RF_Type::UInt32*/>
void Rectangle<PT, ST>::Left(const PT Value)
{
    m_Position.X = Value;
}

template<class PT, class ST>
Rectangle<PT,ST>::Rectangle(const Point2D<PT> &Position, const Size2D<ST> &Size)
:m_Position(Position.X, Position.Y)
,m_Size(Size.Width, Size.Height)
{
}

template<class PT, class ST>
Rectangle<PT,ST>::Rectangle()
{
}

template<class PT, class ST>
Rectangle<PT,ST>::Rectangle(const PT Left,const PT Top,const PT Right, const PT Bottom)
:m_Position(Left, Top)
,m_Size(Right-Left, Bottom-Top)
{
}

template<class PT, class ST>
Rectangle<PT,ST>::Rectangle(const Point2D<PT>& Point1, const Point2D<PT>& Point2)
{
    if (Point1.X<Point2.X)
    {
        m_Position.X = Point1.X;
        m_Size.Width = Point2.X - Point1.X;
    }
    else
    {
        m_Position.X = Point2.X;
        m_Size.Width = Point1.X - Point2.X;
    }

    if (Point1.Y<Point2.Y)
    {
        m_Position.Y = Point1.Y;
        m_Size.Height = Point2.Y - Point1.Y;
    }
    else
    {
        m_Position.Y = Point2.Y;
        m_Size.Height = Point1.Y - Point2.Y;
    }
}

template<class PT, class ST>
Rectangle<PT,ST>::Rectangle(const Rectangle<PT,ST>& Copy)
{
    m_Position = Copy.m_Position;
    m_Size = Copy.m_Size;
}

template<class PT, class ST>
ST Rectangle<PT,ST>::Width()const
{
  return m_Size.Width;
}

template<class PT, class ST>
void Rectangle<PT,ST>::Width(const ST Value)
{
    m_Size.Width = Value;
}

template<class PT, class ST>
ST Rectangle<PT,ST>::Height()const
{
    return m_Size.Height;
}

template<class PT, class ST>
void Rectangle<PT,ST>::Height(const ST Value)
{
    m_Size.Height = Value;
}

template<class PT, class ST>
Size2D<ST> Rectangle<PT,ST>::GetSize()const
{
    return m_Size;
}

template<class PT, class ST>
void Rectangle<PT,ST>::SetSize(const Size2D<ST>& Size)
{
    m_Size = Size;
}

template<class PT, class ST>
Point2D<PT> Rectangle<PT,ST>::GetPosition()const
{
    return m_Position;
}

template<class PT, class ST>
void Rectangle<PT,ST>::SetPosition(const Point2D<PT>& Point)
{
    m_Position = Point;
}

template<class PT, class ST>
RF_Type::Bool Rectangle<PT,ST>::Equals(const Rectangle<PT,ST>& Other)const
{
  return m_Position == Other.m_Position && m_Size == Other.m_Size;
}

template<class PT, class ST>
RF_Type::Bool Rectangle<PT,ST>::IsIntersect(const Rectangle<PT,ST> &Other)const
{
    auto tmp(m_Position);
    tmp.X += m_Size.Width;
    tmp.Y += m_Size.Height;
    auto tmp2(Other.m_Position);
    tmp.X += Other.m_Size.Width;
    tmp.Y += Other.m_Size.Height;
    return tmp >= Other.m_Position || tmp2 <= m_Position;
}

template<class PT, class ST>
RF_Type::Bool Rectangle<PT,ST>::IsIntersect(const Point2D<PT>& Other)const
{
    auto tmp(m_Position);
    tmp.X += m_Size.Width;
    tmp.Y += m_Size.Height;
    return m_Position <= Other && Other <= tmp;
}

template<class PT, class ST>
PT Rectangle<PT,ST>::Left()const
{
    return m_Position.X;
}

template<class PT, class ST>
PT Rectangle<PT,ST>::Top()const
{
    return m_Position.Y;
}

template<class PT, class ST>
PT Rectangle<PT,ST>::Bottom()const
{
    return m_Position.Y + m_Size.Height;
}

template<class PT, class ST>
PT Rectangle<PT,ST>::Right()const
{
    return m_Position.X + m_Size.Width;
}

template<class PT/*=RF_Type::Int32*/, class ST /*= RF_Type::UInt32*/>
void Rectangle<PT, ST>::Flip()
{
    m_Size.Flip();
}

typedef Rectangle<RF_Type::Float32, RF_Type::Float32> Rectanglef;

}

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif // RF_MATH_GEOMETRY_RECTANGLE_HPP
