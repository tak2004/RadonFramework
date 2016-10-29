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

template<class T/*=RF_Type::UInt32*/, class FLOAT/*=RF_Type::Float32*/>
RF_Type::Bool Size2D<T, FLOAT>::operator==(const Size2D<T, FLOAT>& Other) const
{
    return Equals(Other);
}

template<class T/*=RF_Type::UInt32*/, class FLOAT /*= RF_Type::Float32*/>
Size2D<T, FLOAT> Size2D<T,FLOAT>::Max(const Size2D<T, FLOAT>& A, 
    const Size2D<T, FLOAT>& B)
{
    Size2D<T,FLOAT> result;
    result.Width = A.Width < B.Width ? B.Width : A.Width;
    result.Height = A.Height < B.Height ? B.Height : A.Height;
    return result;
}

template<class T/*=RF_Type::UInt32*/, class FLOAT /*= RF_Type::Float32*/>
Size2D<T, FLOAT> Size2D<T, FLOAT>::Min(const Size2D<T, FLOAT>& A, 
    const Size2D<T, FLOAT>& B)
{
    Size2D<T,FLOAT> result;
    result.Width = A.Width > B.Width ? B.Width : A.Width;
    result.Height = A.Height > B.Height ? B.Height : A.Height;
    return result;
}

template<class T/*=RF_Type::UInt32*/, class FLOAT /*= RF_Type::Float32*/>
Size2D<T, FLOAT>::Size2D()
:Width(0)
,Height(0)
{
}

template<class T/*=RF_Type::UInt32*/, class FLOAT /*= RF_Type::Float32*/>
Size2D<T, FLOAT>::Size2D(T Width, T Height)
:Width(Width)
,Height(Height)
{}

template<class T/*=RF_Type::UInt32*/, class FLOAT /*= RF_Type::Float32*/>
RF_Type::Bool Size2D<T, FLOAT>::Equals(const Size2D<T, FLOAT> &Other)const
{
    return Width == Other.Width && Height == Other.Height;
}

template<class T/*=RF_Type::UInt32*/, class FLOAT/*=RF_Type::Float32*/>
RF_Type::Bool Size2D<T, FLOAT>::FitsInto(const Size2D<T, FLOAT>& Other) const
{
    return Width <= Other.Width && Height <= Other.Height;
}

template<class T/*=RF_Type::UInt32*/, class FLOAT /*= RF_Type::Float32*/>
FLOAT Size2D<T, FLOAT>::Ratio()const
{
    return Width<Height ? static_cast<FLOAT>(Height) / static_cast<FLOAT>(Width) :
        static_cast<FLOAT>(Width) / static_cast<FLOAT>(Height);
}

template<class T/*=RF_Type::UInt32*/, class FLOAT/*=RF_Type::Float32*/>
FLOAT Size2D<T, FLOAT>::GetArea() const
{
    return static_cast<FLOAT>(Height) * static_cast<FLOAT>(Width);
}

template<class T/*=RF_Type::UInt32*/, class FLOAT/*=RF_Type::Float32*/>
void Size2D<T, FLOAT>::Flip()
{
    T tmp = Width;
    Width = Height;
    Height = tmp;
}

typedef Size2D<RF_Type::Float32> Size2Df;
typedef Size2D<RF_Type::Float64, RF_Type::Float64> Size2Dd;

} } }

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif // RF_MATH_GEOMETRY_SIZE2D_HPP
