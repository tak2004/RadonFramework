#ifndef RF_MATH_GEOMETRY_LINE_HPP
#define RF_MATH_GEOMETRY_LINE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Geometry/Point2D.hpp>
#include <RadonFramework/Math/Geometry/Rectangle.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/Float32.hpp>

namespace RadonFramework::Math::Geometry {

class Line2D
{
public:
    Line2D(const Point2D<> &First, const Point2D<> &Second);

    Line2D(const RF_Type::Int32 X1,const RF_Type::Int32 Y1,
            const RF_Type::Int32 X2,const RF_Type::Int32 Y2);

    RF_Type::Bool Equals(const Line2D &Other)const;

    RF_Type::Bool Intersection(const Line2D &Other, Point2D<> &Point)const;

    RF_Type::Bool IsIntersect(const Line2D &Other)const;

    RF_Type::Bool IsIntersect(const Point2D<> &Other)const;
                                
    RF_Type::Float32 PointDistance(const Point2D<> &Other)const;
    RF_Type::Float32 PointSquareDistance(const Point2D<> &Other)const;
    RF_Type::Float32 Length()const;
    RF_Type::Float32 SquareLength()const;
    Rectangle<> BoundingBox()const;
    Point2D<> Start()const;
    Point2D<> End()const;
protected:
    Point2D<> m_Point1;
    Point2D<> m_Point2;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif // RF_MATH_GEOMETRY_LINE_HPP
