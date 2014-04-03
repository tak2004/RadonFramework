#ifndef RF_MATH_GEOMETRY_SIZE2D_HPP
#define RF_MATH_GEOMETRY_SIZE2D_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Math
    {
        namespace Geometry
        {
            template<class T=RFTYPE::Int32>
            class Size2D
            {
                public:
                    Size2D();
                    Size2D(T Width, T Height);
                    T Width;
                    T Height;

                    RFTYPE::Bool Equals(const Size2D<T>& Other);
                    RFTYPE::Float32 Ratio();
            };
        }
    }
}

template<class T>
RadonFramework::Math::Geometry::Size2D<T>::Size2D()
:Width(0)
,Height(0)
{
}

template<class T>
RadonFramework::Math::Geometry::Size2D<T>::Size2D(T Width, T Height)
:Width(Width)
,Height(Height)
{
}

template<class T>
RFTYPE::Bool RadonFramework::Math::Geometry::Size2D<T>::Equals(const Size2D<T> &Other)
{
  return Width==Other.Width && Height==Other.Height;
}

template<class T>
RFTYPE::Float32 RadonFramework::Math::Geometry::Size2D<T>::Ratio()
{
  return Width<Height?static_cast<RFTYPE::Float32>(Height)/static_cast<RFTYPE::Float32>(Width):
                      static_cast<RFTYPE::Float32>(Width)/static_cast<RFTYPE::Float32>(Height);
}

#endif // RF_MATH_GEOMETRY_SIZE2D_HPP
