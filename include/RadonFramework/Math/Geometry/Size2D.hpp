#ifndef RF_MATH_GEOMETRY_SIZE2D_HPP
#define RF_MATH_GEOMETRY_SIZE2D_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Math { namespace Geometry {

template<class T=RF_Type::UInt32, class FLOAT=RF_Type::Float32>
class Size2D
{
public:
    Size2D();
    Size2D(T Width, T Height);
    template<class NT, class NFLOAT>
    Size2D(const Size2D<NT,NFLOAT>& Convert);
    T Width;
    T Height;

    RF_Type::Bool Equals(const Size2D<T, FLOAT>& Other)const;
    RF_Type::Bool FitsInto(const Size2D<T,FLOAT>& Other)const;
    FLOAT Ratio()const;
    FLOAT GetArea()const;
    void Flip();

    static Size2D<T,FLOAT> Min(const Size2D<T, FLOAT>& A, const Size2D<T, FLOAT>& B);
    static Size2D<T,FLOAT> Max(const Size2D<T, FLOAT>& A, const Size2D<T, FLOAT>& B);

    RF_Type::Bool operator ==(const Size2D<T, FLOAT>& Other)const;
};

template<class T, class FLOAT>
template<class NT, class NFLOAT>
Size2D<T,FLOAT>::Size2D(const Size2D<NT, NFLOAT>& Convert)
:Width((T)Convert.Width)
,Height((T)Convert.Height)
{}

typedef Size2D<RF_Type::Int32> Size2Di;
typedef Size2D<RF_Type::UInt32> Size2Du;
typedef Size2D<RF_Type::Float32> Size2Df;
typedef Size2D<RF_Type::Float64, RF_Type::Float64> Size2Dd;

} } }

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif // RF_MATH_GEOMETRY_SIZE2D_HPP
