#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Geometry/Line.hpp"
#include "RadonFramework/Math/Float32.hpp"

namespace RadonFramework::Math::Geometry {

Line2D::Line2D(const Point2D<> &First, const Point2D<> &Second)
{
    if(First.X < Second.X)
    {
        m_Point1 = First;
        m_Point2 = Second;
    }
    else
    {
        m_Point1 = Second;
        m_Point2 = First;
    }
}

Line2D::Line2D(const RF_Type::Int32 X1, const RF_Type::Int32 Y1, 
    const RF_Type::Int32 X2, const RF_Type::Int32 Y2)
{
    Point2D<> a(X1, Y1), b(X2, Y2);
    if(X1 < X2)
    {
        m_Point1 = a;
        m_Point2 = b;
    }
    else
    {
        m_Point1 = b;
        m_Point2 = a;
    }
}

RF_Type::Bool Line2D::Equals(const Line2D &Other)const
{
    return m_Point1.Equals(Other.m_Point1) && m_Point2.Equals(Other.m_Point2);
}


// http://alienryderflex.com/intersect/
RF_Type::Bool Line2D::Intersection(const Line2D &Other, Point2D<> &Point)const
{
    RF_Type::Float32 distAB, theCos, theSin, newX, ABpos;
    Point2D<> p1, p2, p3, p4;

    //transform:P1 as orign
    p1 = m_Point1;
    p2 = m_Point2 - m_Point1;
    p3 = Other.m_Point1 - m_Point1;
    p4 = Other.m_Point2 - m_Point1;

    //get length of First line
    distAB = Length();

    //transform:P1 and P2 have to lay on the same horizontal line
    theCos = p2.X / distAB;
    theSin = p2.Y / distAB;
    newX = p3.X*theCos + p3.Y*theSin;
    p3.Y = int(p3.Y*theCos - p3.X*theSin);
    p3.X = int(newX);
    newX = p4.X*theCos + p4.Y*theSin;
    p4.Y = int(p4.Y*theCos - p4.X*theSin);
    p4.X = (int)newX;

    //fails if the lines are parallel
    if(p3.Y == p4.Y)
        return false;

    //get position of Int32ersection of line A-B
    ABpos = (RF_Type::Float32)(p4.X + (p3.X - p4.X)*p4.Y) / (RF_Type::Float32)(p4.Y - p3.Y);

    Point.X = int(p1.X + ABpos*theCos);
    Point.Y = int(p1.Y + ABpos*theSin);

    return true;
}

RF_Type::Bool Line2D::IsIntersect(const Line2D &Other)const
{
    Point2D<> p1;
    //get Int32ersection point
    if(Intersection(Other, p1))
        //if the point lay inside the bounding box of this line its a real Int32ersection
        return BoundingBox().IsIntersect(p1);
    return false;
}

RF_Type::Bool Line2D::IsIntersect(const Point2D<> &Other)const
{
    //If the point lay inside the bounding box the check can do with Pythagoras law.
    if(BoundingBox().IsIntersect(Other))
    {
        RF_Type::Float32 u, x, y;
        //looking for delta on the line
        u = (RF_Type::Float32)((Other - m_Point1)*(m_Point2 - m_Point1)).Sum() / (RF_Type::Float32)m_Point1.SquareDistance(m_Point2);
        //nearest point on the line
        x = m_Point1.X + u*(m_Point2.X - m_Point1.X);
        y = m_Point1.Y + u*(m_Point2.Y - m_Point1.Y);
        return (int)x == Other.X && (int)y == Other.Y;
    }
    return false;
}

// http://local.wasp.uwa.edu.au/~pbourke/geometry/pointline/
RF_Type::Float32 Line2D::PointDistance(const Point2D<> &Other)const
{
    return Float32::Sqrt(PointSquareDistance(Other));
}

RF_Type::Float32 Line2D::PointSquareDistance(const Point2D<> &Other)const
{
    RF_Type::Float32 u, x, y;
    //looking for delta on the line
    u = (RF_Type::Float32)((Other.X - m_Point1.X)*(m_Point2.X - m_Point1.X) + (Other.Y - m_Point1.Y)*(m_Point2.Y - m_Point1.Y)) / (RF_Type::Float32)m_Point1.SquareDistance(m_Point2);
    //nearest point on the line
    x = m_Point1.X + u*(m_Point2.X - m_Point1.X);
    y = m_Point1.Y + u*(m_Point2.Y - m_Point1.Y);
    //clamp to line
    Rectangle<> r = BoundingBox();
    if(x < r.Left())
        x = (RF_Type::Float32)r.Left();
    if(x > r.Right())
        x = (RF_Type::Float32)r.Right();
    if(y < r.Bottom())
        y = (RF_Type::Float32)r.Bottom();
    if(y > r.Top())
        y = (RF_Type::Float32)r.Top();
    //calculate distance
    x -= Other.X;
    y -= Other.Y;
    return x*x + y*y;
}

RF_Type::Float32 Line2D::Length()const
{
    return m_Point1.Distance(m_Point2);
}

RF_Type::Float32 Line2D::SquareLength()const
{
    return (RF_Type::Float32)m_Point1.SquareDistance(m_Point2);
}

Rectangle<> Line2D::BoundingBox()const
{
    Point2D<> min(m_Point1.X < m_Point2.X ? m_Point1.X : m_Point2.X, m_Point1.Y < m_Point2.Y ? m_Point1.Y : m_Point2.Y);
    Point2D<> max(m_Point1.X > m_Point2.X ? m_Point1.X : m_Point2.X, m_Point1.Y > m_Point2.Y ? m_Point1.Y : m_Point2.Y);
    Rectangle<> bb(min, max);
    return bb;
}

Point2D<> Line2D::Start()const
{
    return m_Point1;
}

Point2D<> Line2D::End()const
{
    return m_Point2;
}

}