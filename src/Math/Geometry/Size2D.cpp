#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Geometry/Size2D.hpp"

namespace RadonFramework::Math::Geometry {

template<class T/*=RF_Type::UInt32*/, class FLOAT/*=RF_Type::Float32*/>
RF_Type::Bool Size2D<T, FLOAT>::operator==(const Size2D<T, FLOAT>& Other) const
{
    return Equals(Other);
}

template<class T/*=RF_Type::UInt32*/, class FLOAT /*= RF_Type::Float32*/>
Size2D<T, FLOAT> Size2D<T, FLOAT>::Max(const Size2D<T, FLOAT>& A,
                                       const Size2D<T, FLOAT>& B)
{
    Size2D<T, FLOAT> result;
    result.Width = A.Width < B.Width ? B.Width : A.Width;
    result.Height = A.Height < B.Height ? B.Height : A.Height;
    return result;
}

template<class T/*=RF_Type::UInt32*/, class FLOAT /*= RF_Type::Float32*/>
Size2D<T, FLOAT> Size2D<T, FLOAT>::Min(const Size2D<T, FLOAT>& A,
                                       const Size2D<T, FLOAT>& B)
{
    Size2D<T, FLOAT> result;
    result.Width = A.Width > B.Width ? B.Width : A.Width;
    result.Height = A.Height > B.Height ? B.Height : A.Height;
    return result;
}

template<class T/*=RF_Type::UInt32*/, class FLOAT /*= RF_Type::Float32*/>
Size2D<T, FLOAT>::Size2D()
:Width(0)
,Height(0)
{}

template<class T/*=RF_Type::UInt32*/, class FLOAT /*= RF_Type::Float32*/>
Size2D<T, FLOAT>::Size2D(T Width, T Height)
: Width(Width)
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
    return Width < Height ? static_cast<FLOAT>(Height) / static_cast<FLOAT>(Width) :
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

template<class T/*=RF_Type::UInt32*/, class FLOAT/*=RF_Type::Float32*/>
Fitting Size2D<T, FLOAT>::CanFitInto(const Size2D<T, FLOAT>& Other) const
{
    if(Width == Other.Width && Height == Other.Height)
        return Fitting::PerfectFit;
    if(Width == Other.Height && Height == Other.Width)
        return Fitting::PerfectFitIfFlip;
    if(Width <= Other.Width && Height <= Other.Height)
        return Fitting::Fit;
    if(Width <= Other.Height && Height <= Other.Width)
        return Fitting::FitIfFlip;
    return Fitting::No;
}

template class Size2D<RF_Type::Int32>;
template class Size2D<RF_Type::UInt32>;
template class Size2D<RF_Type::Float32>;
template class Size2D<RF_Type::Float64, RF_Type::Float64>;

}