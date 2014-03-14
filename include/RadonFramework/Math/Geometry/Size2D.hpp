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
            template<class T=Core::Types::Int32>
            class Size2D
            {
                public:
                    Size2D();
                    Size2D(T Width, T Height);
                    T Width;
                    T Height;

                    Core::Types::Bool Equals(const Size2D<T>& Other);
                    Core::Types::Float32 Ratio();
            };
        }
    }
}

#define RMG RadonFramework::Math::Geometry
#define RCT RadonFramework::Core::Types

template<class T>
RMG::Size2D<T>::Size2D()
:Width(0)
,Height(0)
{
}

template<class T>
RMG::Size2D<T>::Size2D(T Width, T Height)
:Width(Width)
,Height(Height)
{
}

template<class T>
RCT::Bool RMG::Size2D<T>::Equals(const Size2D<T> &Other)
{
  return Width==Other.Width && Height==Other.Height;
}

template<class T>
RCT::Float32 RMG::Size2D<T>::Ratio()
{
  return Width<Height?static_cast<RCT::Float32>(Height)/static_cast<RCT::Float32>(Width):
                      static_cast<RCT::Float32>(Width)/static_cast<RCT::Float32>(Height);
}

#endif // RF_MATH_GEOMETRY_SIZE2D_HPP
