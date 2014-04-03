#ifndef RF_MATH_GEOMETRY_POINT2D_HPP
#define RF_MATH_GEOMETRY_POINT2D_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Math.hpp>

namespace RadonFramework
{
    namespace Math
    {
        namespace Geometry
        {
            template<class T=RFTYPE::Int32>
            class Point2D
            {
                public:
                    Point2D();
                    Point2D(const T x, const T y);
                    T X;
                    T Y;

                    RFTYPE::Bool Equals(const Point2D<T> &Other)const;
                    T Sum()const;
                    RFTYPE::Float32 Distance(const Point2D<T> &Other)const;
                    RFTYPE::Float32 SquareDistance(const Point2D<T> &Other)const;

                    #define Operation(_A_)\
                    inline Point2D<T> operator _A_(const Point2D<T>& op)const{\
                    Point2D<T> out(*this);\
                    out.Y _A_##= op.Y;\
                    out.X _A_##= op.X;\
                    return out;\
                    }
                    Operation(+)
                    Operation(-)
                    Operation(*)
                    Operation(/)
                    #undef Operation

                    #define Operation(_A_)\
                    inline Point2D<T>& operator _A_##=(const Point2D<T>& op){\
                    Y _A_##= op.Y;\
                    X _A_##= op.X;\
                    return *this;\
                    }
                    Operation(+)
                    Operation(-)
                    Operation(*)
                    Operation(/)
                    #undef Operation
            };
        }
    }
}

#define RMG RadonFramework::Math::Geometry

template<class T>
RMG::Point2D<T>::Point2D()
:X(0)
,Y(0)
{
}

template<class T>
RMG::Point2D<T>::Point2D(const T x, const T y)
:X(x)
,Y(y)
{
}

template<class T>
RFTYPE::Bool RMG::Point2D<T>::Equals(const RMG::Point2D<T> &Other)const
{
    return X==Other.X && 
           Y==Other.Y;
}

template<class T>
T RMG::Point2D<T>::Sum()const
{
    return X+Y;
}

template<class T>
RFTYPE::Float32 RMG::Point2D<T>::Distance(const RMG::Point2D<T> &Other)const
{
    return Math<RFTYPE::Float32>::Sqrt(SquareDistance(Other));
}

template<class T>
RFTYPE::Float32 RMG::Point2D<T>::SquareDistance(const RMG::Point2D<T> &Other)const
{
    return static_cast<RFTYPE::Float32>(((X-Other.X)^2)+((Y-Other.Y)^2));
}

#endif // RF_MATH_GEOMETRY_POINT2D_HPP
