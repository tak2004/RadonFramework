#ifndef RF_MATH_GEOMETRY_MATRIX_HPP
#define RF_MATH_GEOMETRY_MATRIX_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Geometry/Vector.hpp>
#include <RadonFramework/Math/Math.hpp>
#include <RadonFramework/Diagnostics/Debugging/Assert.hpp>

namespace RadonFramework
{
    namespace Math
    {
      namespace Geometry
      {
        template<typename T, RFTYPE::Size N, RFTYPE::Size M>
        class Matrix
        {
          public:
            T Value[N*M];
            Matrix()
            {
              LoadIdentity();
            }

            Matrix(const Matrix& Copy)
            {
                RFMEM::Copy(Value, Copy.Value, sizeof(T)*M*N);
            }

            Vector<T,M> GetRow(RFTYPE::Size Row)const
            {
                Vector<T,M> vec;
                for (RFTYPE::Size i=0;i<M;++i)
                    vec[i]=Value[Row+M*i];
                return vec;
            }

            Vector<T,N> GetColumn(RFTYPE::Size Column)const
            {
                Vector<T,N> vec;
                for (RFTYPE::Size i=0;i<N;++i)
                    vec[i]=Value[i+N*Column];
                return vec;
            }

            void SetColumn(RFTYPE::Size Column,const Vector<T,N> & Vec)
            {
                RFMEM::Copy(&Value[Column*N], Vec.Value, sizeof(T)*N);
            }

            Matrix& LoadIdentity()
            {
              for (RFTYPE::Size i=0;i<N;i++)
                for (RFTYPE::Size j=0;j<M;j++)
                  Value[i*N+j]=(i==j)?1:0;
              return *this;
            }

            Matrix& LoadZero()
            {
                RFMEM::Set(Value,0,N*M*sizeof(T));
                return *this;
            }

            Matrix Transpose()
            {
              Matrix out;
              for (RFTYPE::Size i=0;i<N;i++)
                for (RFTYPE::Size j=0;j<M;j++)
                  out.Value[i+j*M]=Value[j+i*N];
              return out;
            }

            Matrix& Scale(const Vector<T,M> &Other)
            {
              for (RFTYPE::Size i=0;i<M;i++)
                for (RFTYPE::Size j=0;j<N;j++)
                  Value[i*N+j]*=Other[i];
              return *this;
            }

            Matrix& operator =(Matrix Other)
            {
                for (RFTYPE::Size i=0;i<N*M;i++)
                    Value[i]=Other.Value[i];
                return *this;
            }

            inline T& operator()(RFTYPE::Size Col, RFTYPE::Size Row)const
            {
                Assert(Col*M+Row>=0 && Col*M+Row<N*M,"Index out of bound.");
                return Value[Col*M+Row];
            }

            inline T& operator[](const RFTYPE::Size Index)const
            {
                Assert(Index>=0 && Index<N*M,"Index out of bound.");
                return Value[Index];
            }

            Matrix operator *(Matrix& Other)const
            {
              Matrix out;
              for (RFTYPE::Size j = 0; j < N*M; j += M)
                for(RFTYPE::Size i = 0; i<N; i++){
                  out.Value[i+j] = Other.Value[i] * Value[j];
                  for (RFTYPE::Size k = 1; k < M; k++)
                    out.Value[i+j] += Other.Value[i + N * k] * Value[j + k];
                  }
              return out;
            }

            Matrix operator /(T Other)const
            {
              Matrix out;
              for (RFTYPE::Size j=0;j<N*M;j++)
                out.Value[j]=Value[j]/Other;
              return out;
            }

            Vector<T,N> operator *(const Vector<T,M>& Other)const
            {
              Vector<T,N> out(0,0,0,0);
              for (RFTYPE::Size i=0;i<M;++i)
                out+=GetColumn(i)*Other[i];
              return out;
            }

            Matrix& operator *=(Matrix& Other)
            {
              Matrix out;
              for (RFTYPE::Size i = 0; i < M; i++)
                for(RFTYPE::Size j = 0; j<N; j++){
                  out(i,j) = T(0);
                  for (RFTYPE::Size k = 0; k < N; k++)
                    out(i,j) += Other(i,k) * (*this)(k,j);
                  }
              (*this)=out;
              return *this;
            }

            Matrix& operator /=(T Other)
            {
              for (RFTYPE::Size j = 0; j < N*M; j++)
                 Value[j] /= Other;
              return *this;
            }

            Core::Types::Bool operator==(const Matrix& Other)const
            {
                return Math<T>::IsAlmostEqual(Value,Other.Value,N*M,5);
            }

            Core::Types::Bool operator!=(const Matrix& Other)const
            {
                return !(*this==Other);
            }
        };

        template <typename T>
        class Matrix<T,2,2>
        {
          public:
            T Value[4];
            Matrix()
            {
              LoadIdentity();
            }

            Matrix(const Matrix& Copy)
            {
                RFMEM::Copy(Value, Copy.Value, sizeof(T)*4);
            }

            Vector<T,2> GetRow(RFTYPE::Size Row)const
            {
                Vector<T,2> vec;
                for (RFTYPE::Size i=0;i<2;++i)
                    vec[i]=Value[Row+2*i];
                return vec;
            }

            Vector<T,2> GetColumn(RFTYPE::Size Column)const
            {
                Vector<T,2> vec;
                for (RFTYPE::Size i=0;i<2;++i)
                    vec[i]=Value[i+2*Column];
                return vec;
            }

            void SetColumn(RFTYPE::Size Column,const Vector<T,2> & Vec)
            {
                RFMEM::Copy(&Value[Column*2], Vec.Value, sizeof(T)*2);
            }

            Matrix& LoadIdentity()
            {
              for (RFTYPE::Size i=0;i<2;i++)
                for (RFTYPE::Size j=0;j<2;j++)
                  Value[i*2+j] = (i==j) ? static_cast<T>(1) : static_cast<T>(0);
              return *this;
            }

            Matrix& LoadZero()
            {
                RFMEM::Set(Value,0,4*sizeof(T));
                return *this;
            }

            Matrix Transpose()
            {
              Matrix out;
              for (RFTYPE::Size i=0;i<2;i++)
                for (RFTYPE::Size j=0;j<2;j++)
                  out.Value[i+j*2]=Value[j+i*2];
              return out;
            }

            Matrix& Scale(const Vector<T,2> &Other)
            {
              for (RFTYPE::Size i=0;i<2;i++)
                for (RFTYPE::Size j=0;j<2;j++)
                  Value[i*2+j]*=Other[i];
              return *this;
            }

            Matrix& operator =(Matrix Other)
            {
                for (RFTYPE::Size i=0;i<4;i++)
                    Value[i]=Other.Value[i];
                return *this;
            }

            inline T& operator()(RFTYPE::Size Col, RFTYPE::Size Row)
            {
                Assert(Col*2+Row>=0 && Col*2+Row<4,"Index out of bound.");
                return Value[Col*2+Row];
            }

            inline T operator()(RFTYPE::Size Col, RFTYPE::Size Row)const
            {
                Assert(Col*2+Row>=0 && Col*2+Row<4,"Index out of bound.");
                return Value[Col*2+Row];
            }

            inline T& operator[](const RFTYPE::Size Index)
            {
                Assert(Index>=0 && Index<4,"Index out of bound.");
                return Value[Index];
            }

            inline T operator[](const RFTYPE::Size Index)const
            {
                Assert(Index>=0 && Index<4,"Index out of bound.");
                return Value[Index];
            }

            Matrix operator *(Matrix& Other)const
            {
                Matrix out;
                for (RFTYPE::Size i=0;i<2;++i)
                    for (RFTYPE::Size j=0;j<2;++j)
                        out[i*2+j]=(*this)[i*2]*Other[j]+(*this)[i*2+1]*Other[2+j];
                return out;
            }

            Matrix operator /(T Other)const
            {
              Matrix out;
              for (RFTYPE::Size j=0;j<4;j++)
                out.Value[j]=Value[j]/Other;
              return out;
            }

            Vector<T,2> operator *(const Vector<T,2>& Other)const
            {
                Vector<T,2> out(0,0);
                for (RFTYPE::Size i=0;i<2;++i)
                    out[i]=(*this)[i]*Other[0]+(*this)[i+2]*Other[1];
                return out;
            }

            Matrix& operator *=(Matrix& Other)
            {
              Matrix out;
              for (RFTYPE::Size i = 0; i < 2; i++)
                for(RFTYPE::Size j = 0; j<2; j++){
                  out(i,j) = T(0);
                  for (RFTYPE::Size k = 0; k < 2; k++)
                    out(i,j) += Other(i,k) * (*this)(k,j);
                  }
              (*this)=out;
              return *this;
            }

            Matrix& operator /=(T Other)
            {
              for (RFTYPE::Size j = 0; j < 4; j++)
                 Value[j] /= Other;
              return *this;
            }

            Matrix& Rotate(T Angle)
            {
              T rad=RadonFramework::Math::Math<T>::DegToRad(Angle);
              T c=cos(rad);
              T s=sin(rad);
              Matrix m;
              m[0]=c;  m[1]=s;
              m[2]=-s; m[3]=c;

              (*this)*=m;
              return *this;
            }

            T Determinants()
            {
                return Value[0]*Value[3]-Value[2]*Value[1];
            }

            Matrix Inverse()
            {
                Matrix inverse;

                T det = Determinants();
                if (RadonFramework::Math::Math<T>::FAbs(det) > RadonFramework::Math::Math<T>::EPSILION)
                {
                    T invDet = ((T)1)/det;
                    inverse.Value[0] =  Value[3]*invDet;
                    inverse.Value[1] = -Value[1]*invDet;
                    inverse.Value[2] = -Value[2]*invDet;
                    inverse.Value[3] =  Value[0]*invDet;
                }
                else
                    inverse.LoadZero();
                return inverse;
            }

            Core::Types::Bool operator==(const Matrix& Other)const
            {
                return RadonFramework::Math::Math<T>::IsAlmostEqual(Value,Other.Value,4);
            }

            Core::Types::Bool operator!=(const Matrix& Other)const
            {
                return !(*this==Other);
            }
        };

        template <typename T>
        class Matrix<T,3,3>
        {
          public:
            T Value[9];
            Matrix()
            {
              LoadIdentity();
            }

            Matrix(const Matrix& Copy)
            {
                RFMEM::Copy(Value, Copy.Value, sizeof(T)*9);
            }

            Vector<T,3> GetRow(RFTYPE::Size Row)const
            {
                Vector<T,3> vec;
                for (RFTYPE::Size i=0;i<3;++i)
                    vec[i]=Value[Row+3*i];
                return vec;
            }

            Vector<T,3> GetColumn(RFTYPE::Size Column)const
            {
                Vector<T,3> vec;
                for (RFTYPE::Size i=0;i<3;++i)
                    vec[i]=Value[i+3*Column];
                return vec;
            }

            void SetColumn(RFTYPE::Size Column,const Vector<T,3> & Vec)
            {
                RFMEM::Copy(&Value[Column*3], Vec.Value, sizeof(T)*3);
            }

            Matrix& LoadIdentity()
            {
              for (RFTYPE::Size i=0;i<3;i++)
                for (RFTYPE::Size j=0;j<3;j++)
                  Value[i*3+j] = (i==j) ? static_cast<T>(1) : static_cast<T>(0);
              return *this;
            }

            Matrix& LoadZero()
            {
                RFMEM::Set(Value,0,9*sizeof(T));
                return *this;
            }

            Matrix Transpose()
            {
              Matrix out;
              for (RFTYPE::Size i=0;i<3;i++)
                for (RFTYPE::Size j=0;j<3;j++)
                  out.Value[i+j*3]=Value[j+i*3];
              return out;
            }

            Matrix& Scale(const Vector<T,3> &Other)
            {
              for (RFTYPE::Size i=0;i<3;i++)
                for (RFTYPE::Size j=0;j<3;j++)
                  Value[i*3+j]*=Other[i];
              return *this;
            }

            Matrix& operator =(Matrix Other)
            {
                for (RFTYPE::Size i=0;i<9;i++)
                    Value[i]=Other.Value[i];
                return *this;
            }

            inline T& operator()(RFTYPE::Size Col, RFTYPE::Size Row)
            {
                Assert(Col*3+Row>=0 && Col*3+Row<9,"Index out of bound.");
                return Value[Col*3+Row];
            }

            inline T operator()(RFTYPE::Size Col, RFTYPE::Size Row)const
            {
                Assert(Col*3+Row>=0 && Col*3+Row<9,"Index out of bound.");
                return Value[Col*3+Row];
            }

            inline T& operator[](const RFTYPE::Size Index)
            {
                Assert(Index>=0 && Index<9,"Index out of bound.");
                return Value[Index];
            }

            inline T operator[](const RFTYPE::Size Index)const
            {
                Assert(Index>=0 && Index<9,"Index out of bound.");
                return Value[Index];
            }

            Matrix operator *(Matrix& Other)const
            {
                Matrix out;
                for (RFTYPE::Size i=0;i<3;++i)
                    for (RFTYPE::Size j=0;j<3;++j)
                        out[i*3+j]=(*this)[i*3]*Other[j]+(*this)[i*3+1]*Other[3+j]+(*this)[i*3+2]*Other[6+j];
                return out;
            }

            Matrix operator /(T Other)const
            {
              Matrix out;
              for (RFTYPE::Size j=0;j<9;j++)
                out.Value[j]=Value[j]/Other;
              return out;
            }

            Vector<T,3> operator *(const Vector<T,3>& Other)const
            {
              Vector<T,3> out(0,0,0);
              for (RFTYPE::Size i=0;i<3;++i)
                out+=GetColumn(i)*Other[i];
              return out;
            }

            Matrix& operator *=(Matrix& Other)
            {
              Matrix out;
              for (RFTYPE::Size i = 0; i < 3; i++)
                for(RFTYPE::Size j = 0; j<3; j++){
                  out(i,j) = T(0);
                  for (RFTYPE::Size k = 0; k < 3; k++)
                    out(i,j) += Other(i,k) * (*this)(k,j);
                  }
              (*this)=out;
              return *this;
            }

            Matrix& operator /=(T Other)
            {
              for (RFTYPE::Size j = 0; j < 9; j++)
                 Value[j] /= Other;
              return *this;
            }

            Matrix& Translate(T x,T y,T z)
            {
              Matrix m;
              m.Value[8]=x;
              m.Value[9]=y;
              (*this)*=m;
              return *this;
            }

            Matrix& Rotate(T w,T x,T y,T z)
            {
                Vector<T,3> v(x,y,z);
                T len=v.Length();
                Assert(len!=0,"Argument is not legal because the x,y,z components are zero.");
                T rad=Math<T>::DegToRad(w);
                T c=cos(rad);
                T ic=1.0-c;
                T s=sin(rad);

                v/=len;
                Matrix m;
                T xy=v[0]*v[1];
                T xz=v[0]*v[2];
                T yz=v[1]*v[2];
                m[0]=c+v[0]^2*ic;   m[1]=xy*ic+z*s; m[2]=xz*ic-y*s;
                m[3]=xy*ic-z*s; m[4]=c*v[1]^2*ic;   m[5]=yz*ic+x*s;
                m[6]=xz*ic+y*s; m[7]=yz*ic-x*s; m[8]=c+v[2]^2*ic;

                (*this)*=m;
                return *this;
            }

            Matrix& Scale(T x,T y,T z)
            {
              Vector<T,3> v(x,y,z);
              Scale(v);
              return *this;
            }

            T Determinants()
            {
                return Value[0]*Value[4]*Value[8]+Value[3]*Value[7]*Value[2]+Value[6]*Value[1]*Value[5]
                       -Value[6]*Value[4]*Value[2]-Value[0]*Value[7]*Value[5]-Value[3]*Value[1]*Value[8];
            }

            Matrix Inverse()
            {
                //base on http://www.geometrictools.com code
                Matrix inverse;
                // Compute the adjoint.
                inverse.Value[0] = Value[4]*Value[8] - Value[5]*Value[7];
                inverse.Value[1] = Value[2]*Value[7] - Value[1]*Value[8];
                inverse.Value[2] = Value[1]*Value[5] - Value[2]*Value[4];
                inverse.Value[3] = Value[5]*Value[6] - Value[3]*Value[8];
                inverse.Value[4] = Value[0]*Value[8] - Value[2]*Value[6];
                inverse.Value[5] = Value[2]*Value[3] - Value[0]*Value[5];
                inverse.Value[6] = Value[3]*Value[7] - Value[4]*Value[6];
                inverse.Value[7] = Value[1]*Value[6] - Value[0]*Value[7];
                inverse.Value[8] = Value[0]*Value[4] - Value[1]*Value[3];

                T det = Value[0]*inverse.Value[0] + Value[1]*inverse.Value[3] +
                        Value[2]*inverse.Value[6];

                if (RadonFramework::Math::Math<T>::FAbs(det) > RadonFramework::Math::Math<T>::EPSILION)
                {
                    T invDet = ((T)1)/det;
                    inverse.Value[0] *= invDet;
                    inverse.Value[1] *= invDet;
                    inverse.Value[2] *= invDet;
                    inverse.Value[3] *= invDet;
                    inverse.Value[4] *= invDet;
                    inverse.Value[5] *= invDet;
                    inverse.Value[6] *= invDet;
                    inverse.Value[7] *= invDet;
                    inverse.Value[8] *= invDet;
                }
                else
                    inverse.LoadZero();
                return inverse;
            }

            Core::Types::Bool operator==(const Matrix& Other)const
            {
                return RadonFramework::Math::Math<T>::IsAlmostEqual(Value,Other.Value,9);
            }

            Core::Types::Bool operator!=(const Matrix& Other)const
            {
                return !(*this==Other);
            }
        };

        template <typename T>
        class Matrix<T,4,4>
        {
          public:
            T Value[16];
            Matrix()
            {
              LoadIdentity();
            }

            Matrix(const Matrix& Copy)
            {
                RFMEM::Copy(Value, Copy.Value, sizeof(T)*16);
            }

            Vector<T,4> GetRow(RFTYPE::Size Row)const
            {
                Vector<T,4> vec;
                for (RFTYPE::Size i=0;i<4;++i)
                    vec[i]=Value[Row+4*i];
                return vec;
            }

            Vector<T,4> GetColumn(RFTYPE::Size Column)const
            {
                Vector<T,4> vec;
                for (RFTYPE::Size i=0;i<4;++i)
                    vec[i]=Value[i+4*Column];
                return vec;
            }

            void SetColumn(RFTYPE::Size Column,const Vector<T,4> & Vec)
            {
                RFMEM::Copy(&Value[Column*4], Vec.Value, sizeof(T)*4);
            }

            Matrix& LoadIdentity()
            {
              for (RFTYPE::Size i=0;i<4;i++)
                for (RFTYPE::Size j=0;j<4;j++)
                  Value[i*4+j]=(i==j)?static_cast<T>(1):static_cast<T>(0);
              return *this;
            }

            Matrix& LoadZero()
            {
                RFMEM::Set(Value,0,16*sizeof(T));
                return *this;
            }

            Matrix Transpose()
            {
              Matrix out;
              for (RFTYPE::Size i=0;i<4;i++)
                for (RFTYPE::Size j=0;j<4;j++)
                  out.Value[i+j*4]=Value[j+i*4];
              return out;
            }

            Matrix& Scale(const Vector<T,4> &Other)
            {
              for (RFTYPE::Size i=0;i<4;i++)
                for (RFTYPE::Size j=0;j<4;j++)
                  Value[i*4+j]*=Other[i];
              return *this;
            }

            Matrix& operator =(Matrix Other)
            {
                for (RFTYPE::Size i=0;i<16;i++)
                    Value[i]=Other.Value[i];
                return *this;
            }

            inline T& operator()(RFTYPE::Size Col, RFTYPE::Size Row)
            {
                Assert(Col*4+Row>=0 && Col*4+Row<16,"Index out of bound.");                
                return Value[Col*4+Row];
            }

            inline T operator()(RFTYPE::Size Col, RFTYPE::Size Row)const
            {
                Assert(Col*4+Row>=0 && Col*4+Row<16,"Index out of bound.");
                return Value[Col*4+Row];
            }

            inline T& operator[](const RFTYPE::Size Index)
            {
                Assert(Index>=0 && Index<16,"Index out of bound.")
                return Value[Index];
            }

            inline T operator[](const RFTYPE::Size Index)const
            {
                Assert(Index>=0 && Index<16,"Index out of bound.");
                return Value[Index];
            }

            Matrix operator *(const Matrix& Other)const
            {
                /*Matrix out;
                for (int i=0;i<4;++i)
                    for (int j=0;j<4;++j)
                        out[i*4+j]=(*this)[i*4]*Other[j]+(*this)[i*4+1]*Other[4+j]+(*this)[i*4+2]*Other[8+j]+(*this)[i*4+3]*Other[12+j];
                return out;*/
                Matrix out;
                    out[0]=Value[ 0]*Other.Value[ 0] +
                    Value[ 1]*Other.Value[ 4] +
                    Value[ 2]*Other.Value[ 8] +
                    Value[ 3]*Other.Value[12];

                    out[1]=Value[ 0]*Other.Value[ 1] +
                    Value[ 1]*Other.Value[ 5] +
                    Value[ 2]*Other.Value[ 9] +
                    Value[ 3]*Other.Value[13];

                    out[2]=Value[ 0]*Other.Value[ 2] +
                    Value[ 1]*Other.Value[ 6] +
                    Value[ 2]*Other.Value[10] +
                    Value[ 3]*Other.Value[14];

                    out[3]=Value[ 0]*Other.Value[ 3] +
                    Value[ 1]*Other.Value[ 7] +
                    Value[ 2]*Other.Value[11] +
                    Value[ 3]*Other.Value[15];

                    out[4]=Value[ 4]*Other.Value[ 0] +
                    Value[ 5]*Other.Value[ 4] +
                    Value[ 6]*Other.Value[ 8] +
                    Value[ 7]*Other.Value[12];

                    out[5]=Value[ 4]*Other.Value[ 1] +
                    Value[ 5]*Other.Value[ 5] +
                    Value[ 6]*Other.Value[ 9] +
                    Value[ 7]*Other.Value[13];

                    out[6]=Value[ 4]*Other.Value[ 2] +
                    Value[ 5]*Other.Value[ 6] +
                    Value[ 6]*Other.Value[10] +
                    Value[ 7]*Other.Value[14];

                    out[7]=Value[ 4]*Other.Value[ 3] +
                    Value[ 5]*Other.Value[ 7] +
                    Value[ 6]*Other.Value[11] +
                    Value[ 7]*Other.Value[15];

                    out[8]=Value[ 8]*Other.Value[ 0] +
                    Value[ 9]*Other.Value[ 4] +
                    Value[10]*Other.Value[ 8] +
                    Value[11]*Other.Value[12];

                    out[9]=Value[ 8]*Other.Value[ 1] +
                    Value[ 9]*Other.Value[ 5] +
                    Value[10]*Other.Value[ 9] +
                    Value[11]*Other.Value[13];

                    out[10]=Value[ 8]*Other.Value[ 2] +
                    Value[ 9]*Other.Value[ 6] +
                    Value[10]*Other.Value[10] +
                    Value[11]*Other.Value[14];

                    out[11]=Value[ 8]*Other.Value[ 3] +
                    Value[ 9]*Other.Value[ 7] +
                    Value[10]*Other.Value[11] +
                    Value[11]*Other.Value[15];

                    out[12]=Value[12]*Other.Value[ 0] +
                    Value[13]*Other.Value[ 4] +
                    Value[14]*Other.Value[ 8] +
                    Value[15]*Other.Value[12];

                    out[13]=Value[12]*Other.Value[ 1] +
                    Value[13]*Other.Value[ 5] +
                    Value[14]*Other.Value[ 9] +
                    Value[15]*Other.Value[13];

                    out[14]=Value[12]*Other.Value[ 2] +
                    Value[13]*Other.Value[ 6] +
                    Value[14]*Other.Value[10] +
                    Value[15]*Other.Value[14];

                    out[15]=Value[12]*Other.Value[ 3] +
                    Value[13]*Other.Value[ 7] +
                    Value[14]*Other.Value[11] +
                    Value[15]*Other.Value[15];
                return out;
            }

            Matrix operator /(T Other)const
            {
              Matrix out;
              for (RFTYPE::Size j=0;j<16;j++)
                out.Value[j]=Value[j]/Other;
              return out;
            }

            Vector<T,4> operator *(const Vector<T,4>& Other)const
            {
              Vector<T,4> out(0,0,0,0);
              for (RFTYPE::Size i=0;i<4;++i)
                out+=GetColumn(i)*Other[i];
              return out;
            }

            Matrix& operator *=(Matrix& Other)
            {
              Matrix out;
              for (RFTYPE::Size i = 0; i < 4; i++)
                for(RFTYPE::Size j = 0; j<4; j++){
                  out(i,j) = T(0);
                  for (RFTYPE::Size k = 0; k < 4; k++)
                    out(i,j) += Other(i,k) * (*this)(k,j);
                  }
              (*this)=out;
              return *this;
            }

            Matrix& operator /=(T Other)
            {
              for (RFTYPE::Size j = 0; j < 16; j++)
                 Value[j] /= Other;
              return *this;
            }

            Matrix& Translate(T x,T y,T z)
            {
              Matrix m;
              m[12]=x;
              m[13]=y;
              m[14]=z;
              (*this)*=m;
              return *this;
            }

            Matrix& Rotate(const T w,const T x,const T y,const T z)
            {
              Matrix m;
              T rad=RadonFramework::Math::Math<T>::DegToRad(w);
              T c=cos(rad);
              T ic=1.0f-c;
              T s=sin(rad);
              Vector<T,4> v(x,y,z,0.0);
              T mag=sqrt((v*v).Sum());

              if (mag<=1.0e-4)
                return *this;

              v[0]=x/mag;
              v[1]=y/mag;
              v[2]=z/mag;

              m[0]=(v[0]*v[0]*ic)+c;
              m[1]=(v[0]*v[1]*ic)+(v[2]*s);
              m[2]=(v[0]*v[2]*ic)-(v[1]*s);

              m[4]=(v[0]*v[1]*ic)-(v[2]*s);
              m[5]=(v[1]*v[1]*ic)+c;
              m[6]=(v[1]*v[2]*ic)+(v[0]*s);

              m[8]=(v[0]*v[2]*ic)+(v[1]*s);
              m[9]=(v[1]*v[2]*ic)-(v[0]*s);
              m[10]=(v[2]*v[2]*ic)+c;

              *this*=m;
              return *this;
            }

            Matrix& Scale(T x,T y,T z)
            {
              Matrix m;
              m[0]=x;
              m[5]=y;
              m[10]=z;
              *this*=m;
              return *this;
            }

    //        Matrix NormalMatrix()
    //        {
    //          Matrix tnmat;
    //          float d;
    //          for (unsigned int i=0;i<3;i++)
    //            for (unsigned int j=0;j<3;j++)
    //              m_NormalMatrix.Value[i*3+j]=this->Value[i*4+j];
    //
    //          d=Determinant(m_NormalMatrix);
    //          tnmat[0]=m_NormalMatrix[4]*m_NormalMatrix[8]-m_NormalMatrix[5]*m_NormalMatrix[7];
    //          tnmat[3]=m_NormalMatrix[5]*m_NormalMatrix[6]-m_NormalMatrix[3]*m_NormalMatrix[8];
    //          tnmat[6]=m_NormalMatrix[3]*m_NormalMatrix[7]-m_NormalMatrix[4]*m_NormalMatrix[6];
    //
    //          tnmat[1]=m_NormalMatrix[2]*m_NormalMatrix[7]-m_NormalMatrix[5]*m_NormalMatrix[8];
    //          tnmat[4]=m_NormalMatrix[0]*m_NormalMatrix[8]-m_NormalMatrix[2]*m_NormalMatrix[6];
    //          tnmat[7]=m_NormalMatrix[1]*m_NormalMatrix[6]-m_NormalMatrix[1]*m_NormalMatrix[7];
    //
    //          tnmat[2]=m_NormalMatrix[1]*m_NormalMatrix[5]-m_NormalMatrix[2]*m_NormalMatrix[4];
    //          tnmat[5]=m_NormalMatrix[2]*m_NormalMatrix[3]-m_NormalMatrix[0]*m_NormalMatrix[5];
    //          tnmat[8]=m_NormalMatrix[0]*m_NormalMatrix[4]-m_NormalMatrix[1]*m_NormalMatrix[3];
    //
    //          for (unsigned int i=0;i<3;i++)
    //            for (unsigned int j=0;j<3;j++)
    //              m_NormalMatrix[i*3+j]=tnmat[i*3+j]/d;
    //          return tnmat;
    //        }
            T Determinants()const
            {
                T a0 = Value[ 0]*Value[ 5] - Value[ 1]*Value[ 4];
                T a1 = Value[ 0]*Value[ 6] - Value[ 2]*Value[ 4];
                T a2 = Value[ 0]*Value[ 7] - Value[ 3]*Value[ 4];
                T a3 = Value[ 1]*Value[ 6] - Value[ 2]*Value[ 5];
                T a4 = Value[ 1]*Value[ 7] - Value[ 3]*Value[ 5];
                T a5 = Value[ 2]*Value[ 7] - Value[ 3]*Value[ 6];
                T b0 = Value[ 8]*Value[13] - Value[ 9]*Value[12];
                T b1 = Value[ 8]*Value[14] - Value[10]*Value[12];
                T b2 = Value[ 8]*Value[15] - Value[11]*Value[12];
                T b3 = Value[ 9]*Value[14] - Value[10]*Value[13];
                T b4 = Value[ 9]*Value[15] - Value[11]*Value[13];
                T b5 = Value[10]*Value[15] - Value[11]*Value[14];
                T det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
                return det;
            }

            Matrix Inverse()const
            {
                Matrix inverse;
                T a0 = Value[ 0]*Value[ 5] - Value[ 1]*Value[ 4];
                T a1 = Value[ 0]*Value[ 6] - Value[ 2]*Value[ 4];
                T a2 = Value[ 0]*Value[ 7] - Value[ 3]*Value[ 4];
                T a3 = Value[ 1]*Value[ 6] - Value[ 2]*Value[ 5];
                T a4 = Value[ 1]*Value[ 7] - Value[ 3]*Value[ 5];
                T a5 = Value[ 2]*Value[ 7] - Value[ 3]*Value[ 6];
                T b0 = Value[ 8]*Value[13] - Value[ 9]*Value[12];
                T b1 = Value[ 8]*Value[14] - Value[10]*Value[12];
                T b2 = Value[ 8]*Value[15] - Value[11]*Value[12];
                T b3 = Value[ 9]*Value[14] - Value[10]*Value[13];
                T b4 = Value[ 9]*Value[15] - Value[11]*Value[13];
                T b5 = Value[10]*Value[15] - Value[11]*Value[14];
                T det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
                if (RadonFramework::Math::Math<T>::FAbs(det) > RadonFramework::Math::Math<T>::EPSILION)
                {
                    inverse.Value[ 0] = + Value[ 5]*b5 - Value[ 6]*b4 + Value[ 7]*b3;
                    inverse.Value[ 4] = - Value[ 4]*b5 + Value[ 6]*b2 - Value[ 7]*b1;
                    inverse.Value[ 8] = + Value[ 4]*b4 - Value[ 5]*b2 + Value[ 7]*b0;
                    inverse.Value[12] = - Value[ 4]*b3 + Value[ 5]*b1 - Value[ 6]*b0;
                    inverse.Value[ 1] = - Value[ 1]*b5 + Value[ 2]*b4 - Value[ 3]*b3;
                    inverse.Value[ 5] = + Value[ 0]*b5 - Value[ 2]*b2 + Value[ 3]*b1;
                    inverse.Value[ 9] = - Value[ 0]*b4 + Value[ 1]*b2 - Value[ 3]*b0;
                    inverse.Value[13] = + Value[ 0]*b3 - Value[ 1]*b1 + Value[ 2]*b0;
                    inverse.Value[ 2] = + Value[13]*a5 - Value[14]*a4 + Value[15]*a3;
                    inverse.Value[ 6] = - Value[12]*a5 + Value[14]*a2 - Value[15]*a1;
                    inverse.Value[10] = + Value[12]*a4 - Value[13]*a2 + Value[15]*a0;
                    inverse.Value[14] = - Value[12]*a3 + Value[13]*a1 - Value[14]*a0;
                    inverse.Value[ 3] = - Value[ 9]*a5 + Value[10]*a4 - Value[11]*a3;
                    inverse.Value[ 7] = + Value[ 8]*a5 - Value[10]*a2 + Value[11]*a1;
                    inverse.Value[11] = - Value[ 8]*a4 + Value[ 9]*a2 - Value[11]*a0;
                    inverse.Value[15] = + Value[ 8]*a3 - Value[ 9]*a1 + Value[10]*a0;

                    T invDet = ((T)1)/det;
                    inverse.Value[ 0] *= invDet;
                    inverse.Value[ 1] *= invDet;
                    inverse.Value[ 2] *= invDet;
                    inverse.Value[ 3] *= invDet;
                    inverse.Value[ 4] *= invDet;
                    inverse.Value[ 5] *= invDet;
                    inverse.Value[ 6] *= invDet;
                    inverse.Value[ 7] *= invDet;
                    inverse.Value[ 8] *= invDet;
                    inverse.Value[ 9] *= invDet;
                    inverse.Value[10] *= invDet;
                    inverse.Value[11] *= invDet;
                    inverse.Value[12] *= invDet;
                    inverse.Value[13] *= invDet;
                    inverse.Value[14] *= invDet;
                    inverse.Value[15] *= invDet;
                }
                else
                    inverse.LoadZero();
                return inverse;
            }

            Core::Types::Bool operator==(const Matrix& Other)const
            {
                return RadonFramework::Math::Math<T>::IsAlmostEqual(Value,Other.Value,16);
            }

            Core::Types::Bool operator!=(const Matrix& Other)const
            {
                return !(*this==Other);
            }
        };

        #define Matrix2f Matrix<float,2,2>
        #define Matrix3f Matrix<float,3,3>
        #define Matrix4f Matrix<float,4,4>
        #define Mat2f Matrix<float,2,2>
        #define Mat3f Matrix<float,3,3>
        #define Mat4f Matrix<float,4,4>
      }
    }
}

#endif // RF_MATH_GEOMETRY_MATRIX_HPP
