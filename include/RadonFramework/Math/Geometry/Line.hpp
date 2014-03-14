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

                    Line2D(const Core::Types::Int32 X1,const Core::Types::Int32 Y1,
                           const Core::Types::Int32 X2,const Core::Types::Int32 Y2);

                    Core::Types::Bool Equals(const Line2D &Other)const;

                    Core::Types::Bool Intersection(const Line2D &Other, Point2D<> &Point)const;

                    Core::Types::Bool IsIntersect(const Line2D &Other)const;

                    Core::Types::Bool IsIntersect(const Point2D<> &Other)const;
                                
                    Core::Types::Float32 PointDistance(const Point2D<> &Other)const;
                    Core::Types::Float32 PointSquareDistance(const Point2D<> &Other)const;
                    Core::Types::Float32 Length()const;
                    Core::Types::Float32 SquareLength()const;
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
