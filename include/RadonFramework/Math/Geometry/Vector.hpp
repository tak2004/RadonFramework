#ifndef RF_MATH_GEOMETRY_VECTOR_HPP
#define RF_MATH_GEOMETRY_VECTOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/Log.hpp>
#include <RadonFramework/Diagnostics/Debugging/Assert.hpp>

namespace RadonFramework
{
    namespace Math
    {
      namespace Geometry
      {
        template <typename T,RFTYPE::Size SIZE>
        class Vector
        {
          public:
            Vector()
            {
              for (RFTYPE::Size i=0;i<SIZE;++i)
                Value[i]=0;
            }

            Vector(const Vector& Val)
            {
                RFMEM::Copy(Value, Val.Value, sizeof(T)*SIZE);
            }

            Vector(const T Values[SIZE])
            {
                RFMEM::Copy(Value, Values, sizeof(T)*SIZE);
            }

            Vector(T a)
            {
                static_assert(SIZE>=1,"Vector dimension isn't large enough");//why you use a Vector of size zero ?
                Value[0]=a;
                for (RFTYPE::Size i=1;i<SIZE;++i)
                    Value[i]=0;
            }

            Vector(T a, T b)
            {
                static_assert(SIZE>=2,"Vector dimension isn't large enough");//if you get an error on this line you use to much parameter for a too small vector
                Value[0]=a;
                Value[1]=b;
                for (RFTYPE::Size i=2;i<SIZE;++i)
                    Value[i]=0;
            }

            Vector(T a, T b, T c)
            {
                static_assert(SIZE>=3,"Vector dimension isn't large enough");//if you get an error on this line you use to much parameter for a too small vector
                Value[0]=a;
                Value[1]=b;
                Value[2]=c;
                for (RFTYPE::Size i=3;i<SIZE;++i)
                    Value[i]=0;
            }

            Vector(T a, T b, T c, T d)
            {
                static_assert(SIZE>=4,"Vector dimension isn't large enough");//if you get an error on this line you use to much parameter for a too small vector
                Value[0]=a;
                Value[1]=b;
                Value[2]=c;
                Value[3]=d;
                for (RFTYPE::Size i=4;i<SIZE;++i)
                    Value[i]=0;
            }

            T Value[SIZE];

            Vector& operator =(const Vector& op)
            {
                Assert(this!=&op,"Self assignment is forbidden.");
                RFMEM::Copy(Value, op.Value, sizeof(T)*SIZE);
                return *this;
            }

            T& operator [](RFTYPE::Size Index)
            {
                Assert(Index>=0 && Index<SIZE,"Index out of bounds.");
                return Value[Index];
            }

            T operator [](RFTYPE::Size Index)const
            {
                Assert(Index>=0 && Index<SIZE,"Index out of bounds.");
                return Value[Index];
            }

            //Vector operation with a vector
            #define Operation(_A_)\
              Vector operator _A_(const Vector& op)const{\
                Vector out(*this);\
                for (RFTYPE::Size i=0;i<SIZE;++i)\
                  out.Value[i] _A_##= op.Value[i];\
                return out;\
              }
            Operation(+)
            Operation(-)
            Operation(*)
            Operation(/)
            #undef Operation

            //Vector asign operation with a vector
            #define AssignOperator(_A_)\
              const Vector& operator _A_(const Vector& op){\
                for (RFTYPE::Size i=0;i<SIZE;++i)\
                  Value[i] _A_ op.Value[i];\
                return *this;\
              }
            AssignOperator(+=)
            AssignOperator(-=)
            AssignOperator(*=)
            AssignOperator(/=)
            #undef AssignOperator

            //Vector operation with single value
            #define Operation(_A_)\
              Vector operator _A_(const T op){\
                Vector out(*this);\
                for (RFTYPE::Size i=0;i<SIZE;++i)\
                  out.Value[i] _A_##=op;\
                return out;\
              }
            Operation(+)
            Operation(-)
            Operation(*)
            Operation(/)
            #undef Operation

            //Vector asign operation with single value
            #define AssignOperator(_A_)\
              const Vector& operator _A_(const T op){\
                for (RFTYPE::Size i=0;i<SIZE;++i)\
                  Value[i] _A_ op;\
                return *this;\
              }
            AssignOperator(+=)
            AssignOperator(-=)
            AssignOperator(*=)
            AssignOperator(/=)
            #undef AssignOperator

            #define CompareOperator(_A_)\
              const bool operator _A_(const Vector& op)const{\
                bool b=true;\
                for (RFTYPE::Size i=0;i<SIZE;++i)\
                  b=b && Value[i] _A_ op.Value[i];\
                return b;\
              }
            CompareOperator(==)
            CompareOperator(!=)
            #undef CompareOperator

            T Sum()const
            {
              T out=0;
              for (RFTYPE::Size i=0;i<SIZE;++i)
                out+=Value[i];
              return out;
            }

            T Length()const
            {
              T out=0;
              for (RFTYPE::Size i=0;i<SIZE;++i)
                out+=(Value[i]*Value[i]);
              return sqrt(out);
            }

            T Distance(const Vector &Other)const
            {
              return ((*this)-Other).Length();
            }

            Vector& Normalize()
            {
                T len=Length();
                for (RFTYPE::Size i=0;i<SIZE;++i)
                    Value[i]/=len;
                return *this;
            }

            static Vector Normalize(const Vector& Vec)
            {
                Vector vec(Vec);
                return vec.Normalize();
            }

            static Vector Min(const Vector& V1,const Vector& V2)
            {
                Vector v;
                for (RFTYPE::Size i=0;i<SIZE;++i)
                    v.Value[i]=V1.Value[i]<V2.Value[i]?V1.Value[i]:V2.Value[i];
                return v;
            }

            static Vector Max(const Vector& V1,const Vector& V2)
            {
                Vector v;
                for (RFTYPE::Size i=0;i<SIZE;++i)
                    v.Value[i]=V1.Value[i]>V2.Value[i]?V1.Value[i]:V2.Value[i];
                return v;
            }

            T DotProduct(const Vector& Vec)const
            {
                T alpha=0;
                for (RFTYPE::Size i=0;i<SIZE;++i)
                    alpha+=this->Value[i]*Vec.Value[i];
                return alpha;
            }

            Vector CrossProduct(const Vector& Vec)const
            {
                Vector v;
                int nextnext,next;
                for (RFTYPE::Size i=0;i<SIZE;++i)
                {
                    next=(i+1)%SIZE;
                    nextnext=(i+2)%SIZE;
                    v.Value[i]=Value[next]*Vec.Value[nextnext]-Value[nextnext]*Vec.Value[next];
                }
                return v;
            }

            void Negate()
            {
                for (RFTYPE::Size i=0;i<SIZE;++i)
                    Value[i]*=-1.0;
            }
        };

        typedef Vector<float,2> Vec2f;
        typedef Vector<float,3> Vec3f;
        typedef Vector<float,4> Vec4f;
      }
    }
}

#endif // RF_MATH_GEOMETRY_VECTOR_HPP
