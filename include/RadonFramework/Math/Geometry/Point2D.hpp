#ifndef RF_MATH_GEOMETRY_POINT2D_HPP
#define RF_MATH_GEOMETRY_POINT2D_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Math::Geometry {
            
template<class T=RF_Type::Int32>
class Point2D
{
public:
    Point2D();
    Point2D(const T x, const T y);
    template<typename OtherType>
    Point2D(const Point2D<OtherType>& CopyFrom);
    T X;
    T Y;

    RF_Type::Bool Equals(const Point2D<T> &Other)const;
    T Sum()const;
    RF_Type::Float32 Distance(const Point2D<T> &Other)const;
    RF_Type::Float32 SquareDistance(const Point2D<T> &Other)const;

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

    #define Operation(_A_)\
    inline RF_Type::Bool operator _A_(const Point2D<T>& op)const{\
    return X _A_ op.X &&  Y _A_ op.Y;\
    }

    Operation(>)
    Operation(<)
    Operation(>=)
    Operation(<=)
    #undef Operation
};

template<class T>
template<typename OtherType>
Point2D<T>::Point2D(const Point2D<OtherType>& CopyFrom)
:X(CopyFrom.X)
,Y(CopyFrom.Y)
{}

template<class T>
Point2D<T>::Point2D()
:X(0)
,Y(0)
{}

template<class T>
Point2D<T>::Point2D(const T x, const T y)
:X(x)
,Y(y)
{}

template<class T>
RF_Type::Bool Point2D<T>::Equals(const Point2D<T> &Other)const
{
    return X == Other.X &&
        Y == Other.Y;
}

template<class T>
T Point2D<T>::Sum()const
{
    return X + Y;
}

template<class T>
RF_Type::Float32 Point2D<T>::Distance(const Point2D<T> &Other)const
{
    return Float32::Sqrt(SquareDistance(Other));
}

template<class T>
RF_Type::Float32 Point2D<T>::SquareDistance(const Point2D<T> &Other)const
{
    return static_cast<RF_Type::Float32>(((X - Other.X) ^ 2) + ((Y - Other.Y) ^ 2));
}
     
typedef Point2D<RF_Type::Float32> Point2Df;
typedef Point2D<RF_Type::Float64> Point2Dd;

}

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif // RF_MATH_GEOMETRY_POINT2D_HPP
