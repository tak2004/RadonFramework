#ifndef RF_MATH_GEOMETRY_SIZE2D_HPP
#define RF_MATH_GEOMETRY_SIZE2D_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Math { namespace Geometry {

template<class T=RF_Type::Int32>
class Size2D
{
public:
    Size2D();
    Size2D(T Width, T Height);
    T Width;
    T Height;

    RF_Type::Bool Equals(const Size2D<T>& Other);
    RF_Type::Float32 Ratio();
};

template<class T>
Size2D<T>::Size2D()
:Width(0)
,Height(0)
{
}

template<class T>
Size2D<T>::Size2D(T Width, T Height)
:Width(Width)
,Height(Height)
{}

template<class T>
RF_Type::Bool Size2D<T>::Equals(const Size2D<T> &Other)
{
    return Width == Other.Width && Height == Other.Height;
}

template<class T>
RF_Type::Float32 Size2D<T>::Ratio()
{
    return Width<Height ? static_cast<RF_Type::Float32>(Height) / static_cast<RF_Type::Float32>(Width) :
        static_cast<RF_Type::Float32>(Width) / static_cast<RF_Type::Float32>(Height);
}

} } }

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif // RF_MATH_GEOMETRY_SIZE2D_HPP
