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

namespace RadonFramework
{
    namespace Math
    {
        namespace Geometry
        {
            class Line2D
            {
                public:
                    Line2D(const Point2D<> &First, const Point2D<> &Second);

                    Line2D(const RFTYPE::Int32 X1,const RFTYPE::Int32 Y1,
                           const RFTYPE::Int32 X2,const RFTYPE::Int32 Y2);

                    RFTYPE::Bool Equals(const Line2D &Other)const;

                    RFTYPE::Bool Intersection(const Line2D &Other, Point2D<> &Point)const;

                    RFTYPE::Bool IsIntersect(const Line2D &Other)const;

                    RFTYPE::Bool IsIntersect(const Point2D<> &Other)const;
                                
                    RFTYPE::Float32 PointDistance(const Point2D<> &Other)const;
                    RFTYPE::Float32 PointSquareDistance(const Point2D<> &Other)const;
                    RFTYPE::Float32 Length()const;
                    RFTYPE::Float32 SquareLength()const;
                    Rectangle<> BoundingBox()const;
                    Point2D<> Start()const;
                    Point2D<> End()const;
                protected:
                    Point2D<> m_Point1;
                    Point2D<> m_Point2;
            };
        }
    }
}

#endif // RF_MATH_GEOMETRY_LINE_HPP
