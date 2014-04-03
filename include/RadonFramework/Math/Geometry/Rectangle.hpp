#ifndef RF_MATH_GEOMETRY_RECTANGLE_HPP
#define RF_MATH_GEOMETRY_RECTANGLE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Geometry/Point2D.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>

namespace RadonFramework { namespace Math { namespace Geometry {

template<class T=RFTYPE::Int32>
class Rectangle
{
public:
    Rectangle();
    Rectangle(const T Left,const T Top,const T Right, const T Bottom);
    Rectangle(const Point2D<T> &Point1, const Point2D<T> &Point2);
    Rectangle(const Rectangle<T>& Copy);

    T Width()const;
    void Width(const T Value);
    T Height()const;
    void Height(const T Value);
    Size2D<T> GetSize()const;
    void SetSize(const Size2D<T>& Size);
    Point2D<T> GetPosition()const;
    void SetPosition(const Point2D<T>& Point);
    T Left()const;
    T Top()const;
    T Bottom()const;
    T Right()const;

    RFTYPE::Bool Equals(const Rectangle<T> &Other)const;
    RFTYPE::Bool IsIntersect(const Rectangle<T> &Other)const;
    RFTYPE::Bool IsIntersect(const Point2D<T> &Other)const;
protected:
    T m_Left;
    T m_Top;
    T m_Bottom;
    T m_Right;
};

template<class T>
Rectangle<T>::Rectangle()
:m_Left(0)
,m_Top(0)
,m_Bottom(0)
,m_Right(0)
{
}

template<class T>
Rectangle<T>::Rectangle(const T Left,const T Top,const T Right, const T Bottom)
:m_Left(Left)
,m_Top(Top)
,m_Bottom(Bottom)
,m_Right(Right)
{
}

template<class T>
Rectangle<T>::Rectangle(const Point2D<T>& Point1, const Point2D<T>& Point2)
{
    if (Point1.X<Point2.X)
    {
        m_Left=Point1.X;
        m_Right=Point2.X;
    }
    else
    {
        m_Left=Point2.X;
        m_Right=Point1.X;
    }

    if (Point1.Y<Point2.Y)
    {
        m_Top=Point1.Y;
        m_Bottom=Point2.Y;
    }
    else
    {
        m_Top=Point2.Y;
        m_Bottom=Point1.Y;
    }
}

template<class T>
Rectangle<T>::Rectangle(const Rectangle<T>& Copy)
{
    m_Left=Copy.m_Left;
    m_Top=Copy.m_Top;
    m_Right=Copy.m_Right;
    m_Bottom=Copy.m_Bottom;
}

template<class T>
T Rectangle<T>::Width()const
{
  return m_Right-m_Left;
}

template<class T>
void Rectangle<T>::Width(const T Value)
{
    m_Right=m_Left+Value;
}

template<class T>
T Rectangle<T>::Height()const
{
    return m_Bottom-m_Top;
}

template<class T>
void Rectangle<T>::Height(const T Value)
{
    m_Bottom=m_Top+Value;
}

template<class T>
Size2D<T> Rectangle<T>::GetSize()const
{
    return Size2D<T>(Width(),Height());
}

template<class T>
void Rectangle<T>::SetSize(const Size2D<T>& Size)
{
    m_Bottom=m_Top+Size.Height;
    m_Right=m_Left+Size.Width;
}

template<class T>
Point2D<T> Rectangle<T>::GetPosition()const
{
    return Point2D<T>(m_Left,m_Top);
}

template<class T>
void Rectangle<T>::SetPosition(const Point2D<T>& Point)
{
    m_Bottom=Point.X+Height();
    m_Right=Point.X+Width();
    m_Left=Point.X;
    m_Top=Point.Y;
}

template<class T>
RFTYPE::Bool Rectangle<T>::Equals(const Rectangle<T>& Other)const
{
  return m_Left==Other.m_Left && m_Top==Other.m_Top && m_Right==Other.m_Right && m_Bottom==Other.m_Bottom;
}

template<class T>
RFTYPE::Bool Rectangle<T>::IsIntersect(const Rectangle<T> &Other)const
{
  return !(Other.m_Left>m_Right || Other.m_Right<m_Left || Other.m_Top>m_Bottom || Other.m_Bottom<m_Top);
}

template<class T>
RFTYPE::Bool Rectangle<T>::IsIntersect(const Point2D<T>& Other)const
{
  return Other.X>=m_Left && Other.X<=m_Right && Other.Y>=m_Bottom && Other.Y<=m_Top;
}

template<class T>
T Rectangle<T>::Left()const
{
    return m_Left;
}

template<class T>
T Rectangle<T>::Top()const
{
    return m_Top;
}

template<class T>
T Rectangle<T>::Bottom()const
{
    return m_Bottom;
}

template<class T>
T Rectangle<T>::Right()const
{
    return m_Right;
}

} } }

#endif // RF_MATH_GEOMETRY_RECTANGLE_HPP
