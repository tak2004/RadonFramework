#ifndef RF_MATH_GEOMETRY_MATRIX_HPP
#define RF_MATH_GEOMETRY_MATRIX_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Geometry/Vector.hpp>
#include <RadonFramework/Math/Math.hpp>
#include <RadonFramework/Diagnostics/Debugging/Assert.hpp>
#include <RadonFramework/System/Memory.hpp>

namespace RadonFramework { namespace Math { namespace Geometry {

template<typename T, RF_Type::Size N, RF_Type::Size M>
class Matrix
{
public:
    T Value[N*M];
    Matrix();                  
    Matrix(const Matrix& Copy);

    Vector<T, M> GetRow(RF_Type::Size Row)const;
    Vector<T, N> GetColumn(RF_Type::Size Column)const;
    void SetColumn(RF_Type::Size Column, const Vector<T, N> & Vec);

    Matrix& LoadIdentity();
    Matrix& LoadZero();

    Matrix Transpose();
    Matrix& Scale(const Vector<T, M> &Other);

    Matrix& operator =(Matrix& Other);
    T& operator()(RF_Type::Size Col, RF_Type::Size Row)const;
    T& operator[](const RF_Type::Size Index)const;
    Matrix operator *(Matrix& Other)const;
    Matrix operator /(T Other)const;
    Vector<T, N> operator *(const Vector<T, M>& Other)const;
    Matrix& operator *=(Matrix& Other);
    Matrix& operator /=(T Other);
    RF_Type::Bool operator==(const Matrix& Other)const;
    RF_Type::Bool operator!=(const Matrix& Other)const;
};

template <typename T>
class Matrix<T,2,2>
{
public:
    T Value[4];
    Matrix();
    Matrix(const Matrix& Copy);

    Vector<T, 2> GetRow(RF_Type::Size Row)const;
    Vector<T, 2> GetColumn(RF_Type::Size Column)const;
    void SetColumn(RF_Type::Size Column, const Vector<T, 2> & Vec);

    Matrix& LoadIdentity();
    Matrix& LoadZero();

    Matrix Transpose();
    Matrix& Scale(const Vector<T, 2> &Other);

    Matrix& operator =(Matrix& Other);
    T& operator()(RF_Type::Size Col, RF_Type::Size Row);
    T operator()(RF_Type::Size Col, RF_Type::Size Row)const;
    T& operator[](const RF_Type::Size Index);
    T operator[](const RF_Type::Size Index)const;
    Matrix operator *(Matrix& Other)const;
    Matrix operator /(T Other)const;
    Vector<T, 2> operator *(const Vector<T, 2>& Other)const;
    Matrix& operator *=(Matrix& Other);
    Matrix& operator /=(T Other);

    Matrix& Rotate(T Angle);
    Matrix Inverse();

    T Determinants();    

    RF_Type::Bool operator==(const Matrix& Other)const;
    RF_Type::Bool operator!=(const Matrix& Other)const;
};

template <typename T>
class Matrix<T,3,3>
{
    public:
    T Value[9];
    Matrix();
    Matrix(const Matrix& Copy);

    Vector<T, 3> GetRow(RF_Type::Size Row)const;
    Vector<T, 3> GetColumn(RF_Type::Size Column)const;
    void SetColumn(RF_Type::Size Column, const Vector<T, 3> & Vec);

    Matrix& LoadIdentity();
    Matrix& LoadZero();

    Matrix Transpose();
    Matrix& Scale(const Vector<T, 3> &Other);

    Matrix& operator =(Matrix& Other);
    T& operator()(RF_Type::Size Col, RF_Type::Size Row);
    T operator()(RF_Type::Size Col, RF_Type::Size Row)const;
    T& operator[](const RF_Type::Size Index);
    T operator[](const RF_Type::Size Index)const;
    Matrix operator *(Matrix& Other)const;
    Matrix operator /(T Other)const;
    Vector<T, 3> operator *(const Vector<T, 3>& Other)const;
    Matrix& operator *=(Matrix& Other);
    Matrix& operator /=(T Other);

    Matrix& Translate(T x, T y, T z);  
    Matrix& Rotate(T w, T x, T y, T z);
    Matrix& Scale(T x, T y, T z);
    Matrix Inverse();

    T Determinants();

    RF_Type::Bool operator==(const Matrix& Other)const;
    RF_Type::Bool operator!=(const Matrix& Other)const;
};

template <typename T>
class Matrix<T,4,4>
{
    public:
    T Value[16];
    
    Matrix();
    Matrix(const Matrix& Copy);

    Vector<T, 4> GetRow(RF_Type::Size Row)const;
    Vector<T, 4> GetColumn(RF_Type::Size Column)const;
    
    void SetColumn(RF_Type::Size Column, const Vector<T, 4> & Vec);

    Matrix& LoadIdentity();
    Matrix& LoadZero();

    Matrix Transpose();
    Matrix& Scale(const Vector<T, 4> &Other);
    Matrix& Translate(T x, T y, T z);
    Matrix& Rotate(const T w, const T x, const T y, const T z);
    Matrix& Scale(T x, T y, T z);

    Matrix& operator =(Matrix& Other);
    T& operator ()(RF_Type::Size Col, RF_Type::Size Row);
    T operator ()(RF_Type::Size Col, RF_Type::Size Row)const;
    T& operator [](const RF_Type::Size Index);
    T operator [](const RF_Type::Size Index)const;
    Matrix operator *(const Matrix& Other)const;
    Matrix operator /(T Other)const;
    Vector<T, 4> operator *(const Vector<T, 4>& Other)const;
    Matrix& operator *=(Matrix& Other);
    Matrix& operator /=(T Other);
    RF_Type::Bool operator==(const Matrix& Other)const;
    RF_Type::Bool operator!=(const Matrix& Other)const;

    Matrix MatNormalMatrix();
    T Determinants()const;
    Matrix Inverse()const;
};

template <typename T, RF_Type::Size N, RF_Type::Size M>
Matrix<T, N, M>::Matrix()
{
    LoadIdentity();
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
Matrix<T, N, M>::Matrix(const Matrix<T, N, M>& Copy)
{
    RF_Mem::Copy(Value, Copy.Value, sizeof(T)*M*N);
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
Vector<T, M> Matrix<T, N, M>::GetRow(RF_Type::Size Row)const
{
    Vector<T, M> vec;
    for (RF_Type::Size i = 0; i < M; ++i)
        vec[i] = Value[Row + M*i];
    return vec;
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
Vector<T, N> Matrix<T, N, M>::GetColumn(RF_Type::Size Column)const
{
    Vector<T, N> vec;
    for (RF_Type::Size i = 0; i < N; ++i)
        vec[i] = Value[i + N*Column];
    return vec;
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
void Matrix<T, N, M>::SetColumn(RF_Type::Size Column, const Vector<T, N> & Vec)
{
    RF_Mem::Copy(&Value[Column*N], Vec.Value, sizeof(T)*N);
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
Matrix<T, N, M>& Matrix<T, N, M>::LoadIdentity()
{
    for (RF_Type::Size i = 0; i < N; i++)
        for (RF_Type::Size j = 0; j < M; j++)
            Value[i*N + j] = (i == j) ? 1 : 0;
    return *this;
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
Matrix<T, N, M>& Matrix<T, N, M>::LoadZero()
{
    RF_Mem::Set(Value, 0, N*M*sizeof(T));
    return *this;
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
Matrix<T, N, M> Matrix<T, N, M>::Transpose()
{
    Matrix out;
    for (RF_Type::Size i = 0; i < N; i++)
        for (RF_Type::Size j = 0; j < M; j++)
            out.Value[i + j*M] = Value[j + i*N];
    return out;
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
Matrix<T, N, M>& Matrix<T, N, M>::Scale(const Vector<T, M> &Other)
{
    for (RF_Type::Size i = 0; i < M; i++)
        for (RF_Type::Size j = 0; j < N; j++)
            Value[i*N + j] *= Other[i];
    return *this;
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
Matrix<T, N, M>& Matrix<T, N, M>::operator =(Matrix<T, N, M>& Other)
{
    for (RF_Type::Size i = 0; i < N*M; i++)
        Value[i] = Other.Value[i];
    return *this;
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
inline T& Matrix<T, N, M>::operator()(RF_Type::Size Col, RF_Type::Size Row)const
{
    Assert(Col*M + Row >= 0 && Col*M + Row < N*M, "Index out of bound.");
    return Value[Col*M + Row];
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
inline T& Matrix<T, N, M>::operator[](const RF_Type::Size Index)const
{
    Assert(Index >= 0 && Index < N*M, "Index out of bound.");
    return Value[Index];
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
Matrix<T, N, M> Matrix<T, N, M>::operator *(Matrix<T, N, M>& Other)const
{
    Matrix out;
    for (RF_Type::Size j = 0; j < N*M; j += M)
        for (RF_Type::Size i = 0; i < N; i++){
        out.Value[i + j] = Other.Value[i] * Value[j];
        for (RF_Type::Size k = 1; k < M; k++)
            out.Value[i + j] += Other.Value[i + N * k] * Value[j + k];
        }
    return out;
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
Matrix<T, N, M> Matrix<T, N, M>::operator /(T Other)const
{
    Matrix out;
    for (RF_Type::Size j = 0; j < N*M; j++)
        out.Value[j] = Value[j] / Other;
    return out;
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
Vector<T, N> Matrix<T, N, M>::operator *(const Vector<T, M>& Other)const
{
    Vector<T, N> out(0, 0, 0, 0);
    for (RF_Type::Size i = 0; i < M; ++i)
        out += GetColumn(i)*Other[i];
    return out;
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
Matrix<T, N, M>& Matrix<T, N, M>::operator *=(Matrix<T, N, M>& Other)
{
    Matrix out;
    for (RF_Type::Size i = 0; i < M; i++)
        for (RF_Type::Size j = 0; j < N; j++){
        out(i, j) = T(0);
        for (RF_Type::Size k = 0; k < N; k++)
            out(i, j) += Other(i, k) * (*this)(k, j);
        }
    (*this) = out;
    return *this;
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
Matrix<T, N, M>& Matrix<T, N, M>::operator /=(T Other)
{
    for (RF_Type::Size j = 0; j < N*M; j++)
        Value[j] /= Other;
    return *this;
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
RF_Type::Bool Matrix<T, N, M>::operator==(const Matrix<T, N, M>& Other)const
{
    return Math<T>::IsAlmostEqual(Value, Other.Value, N*M, 5);
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
RF_Type::Bool Matrix<T, N, M>::operator!=(const Matrix<T, N, M>& Other)const
{
    return !(*this == Other);
}

template <typename T>
Matrix<T, 2, 2>::Matrix()
{
    LoadIdentity();
}

template <typename T>
Matrix<T, 2, 2>::Matrix(const Matrix<T, 2, 2>& Copy)
{
    RF_SysMem::Copy(Value, Copy.Value, sizeof(T) * 4);
}

template <typename T>
Vector<T, 2> Matrix<T, 2, 2>::GetRow(RF_Type::Size Row)const
{
    Vector<T, 2> vec;
    for (RF_Type::Size i = 0; i < 2; ++i)
        vec[i] = Value[Row + 2 * i];
    return vec;
}

template <typename T>
Vector<T, 2> Matrix<T, 2, 2>::GetColumn(RF_Type::Size Column)const
{
    Vector<T, 2> vec;
    for (RF_Type::Size i = 0; i < 2; ++i)
        vec[i] = Value[i + 2 * Column];
    return vec;
}

template <typename T>
void Matrix<T, 2, 2>::SetColumn(RF_Type::Size Column, const Vector<T, 2> & Vec)
{
    RF_SysMem::Copy(&Value[Column * 2], Vec.Value, sizeof(T) * 2);
}

template <typename T>
Matrix<T, 2, 2>& Matrix<T, 2, 2>::LoadIdentity()
{
    for (RF_Type::Size i = 0; i < 2; i++)
        for (RF_Type::Size j = 0; j < 2; j++)
            Value[i * 2 + j] = (i == j) ? static_cast<T>(1) : static_cast<T>(0);
    return *this;
}

template <typename T>
Matrix<T, 2, 2>& Matrix<T, 2, 2>::LoadZero()
{
    RF_SysMem::Set(Value, 0, 4 * sizeof(T));
    return *this;
}

template <typename T>
Matrix<T, 2, 2> Matrix<T, 2, 2>::Transpose()
{
    Matrix out;
    for (RF_Type::Size i = 0; i < 2; i++)
        for (RF_Type::Size j = 0; j < 2; j++)
            out.Value[i + j * 2] = Value[j + i * 2];
    return out;
}

template <typename T>
Matrix<T, 2, 2>& Matrix<T, 2, 2>::Scale(const Vector<T, 2> &Other)
{
    for (RF_Type::Size i = 0; i < 2; i++)
        for (RF_Type::Size j = 0; j < 2; j++)
            Value[i * 2 + j] *= Other[i];
    return *this;
}

template <typename T>
Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator =(Matrix<T, 2, 2>& Other)
{
    for (RF_Type::Size i = 0; i < 4; i++)
        Value[i] = Other.Value[i];
    return *this;
}

template <typename T>
inline T& Matrix<T, 2, 2>::operator()(RF_Type::Size Col, RF_Type::Size Row)
{
    Assert(Col * 2 + Row >= 0 && Col * 2 + Row < 4, "Index out of bound.");
    return Value[Col * 2 + Row];
}

template <typename T>
inline T Matrix<T, 2, 2>::operator()(RF_Type::Size Col, RF_Type::Size Row)const
{
    Assert(Col * 2 + Row >= 0 && Col * 2 + Row < 4, "Index out of bound.");
    return Value[Col * 2 + Row];
}

template <typename T>
inline T& Matrix<T, 2, 2>::operator[](const RF_Type::Size Index)
{
    Assert(Index >= 0 && Index < 4, "Index out of bound.");
    return Value[Index];
}

template <typename T>
inline T Matrix<T, 2, 2>::operator[](const RF_Type::Size Index)const
{
    Assert(Index >= 0 && Index < 4, "Index out of bound.");
    return Value[Index];
}

template <typename T>
Matrix<T, 2, 2> Matrix<T, 2, 2>::operator *(Matrix<T, 2, 2>& Other)const
{
    Matrix out;
    for (RF_Type::Size i = 0; i < 2; ++i)
        for (RF_Type::Size j = 0; j < 2; ++j)
            out[i * 2 + j] = (*this)[i * 2] * Other[j] + (*this)[i * 2 + 1] * Other[2 + j];
    return out;
}

template <typename T>
Matrix<T, 2, 2> Matrix<T, 2, 2>::operator /(T Other)const
{
    Matrix out;
    for (RF_Type::Size j = 0; j < 4; j++)
        out.Value[j] = Value[j] / Other;
    return out;
}

template <typename T>
Vector<T, 2> Matrix<T, 2, 2>::operator *(const Vector<T, 2>& Other)const
{
    Vector<T, 2> out(0, 0);
    for (RF_Type::Size i = 0; i < 2; ++i)
        out[i] = (*this)[i] * Other[0] + (*this)[i + 2] * Other[1];
    return out;
}

template <typename T>
Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator *=(Matrix<T, 2, 2>& Other)
{
    Matrix out;
    for (RF_Type::Size i = 0; i < 2; i++)
        for (RF_Type::Size j = 0; j < 2; j++){
        out(i, j) = T(0);
        for (RF_Type::Size k = 0; k < 2; k++)
            out(i, j) += Other(i, k) * (*this)(k, j);
        }
    (*this) = out;
    return *this;
}

template <typename T>
Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator /=(T Other)
{
    for (RF_Type::Size j = 0; j < 4; j++)
        Value[j] /= Other;
    return *this;
}

template <typename T>
Matrix<T, 2, 2>& Matrix<T, 2, 2>::Rotate(T Angle)
{
    T rad = RF_Math::Math<T>::DegToRad(Angle);
    T c = cos(rad);
    T s = sin(rad);
    Matrix m;
    m[0] = c;  m[1] = s;
    m[2] = -s; m[3] = c;

    (*this) *= m;
    return *this;
}

template <typename T>
T Matrix<T, 2, 2>::Determinants()
{
    return Value[0] * Value[3] - Value[2] * Value[1];
}

template <typename T>
Matrix<T, 2, 2> Matrix<T, 2, 2>::Inverse()
{
    Matrix inverse;

    T det = Determinants();
    if (RF_Math::Math<T>::FAbs(det) > RF_Math::Math<T>::EPSILION)
    {
        T invDet = ((T)1) / det;
        inverse.Value[0] = Value[3] * invDet;
        inverse.Value[1] = -Value[1] * invDet;
        inverse.Value[2] = -Value[2] * invDet;
        inverse.Value[3] = Value[0] * invDet;
    }
    else
        inverse.LoadZero();
    return inverse;
}

template <typename T>
RF_Type::Bool Matrix<T, 2, 2>::operator==(const Matrix<T, 2, 2>& Other)const
{
    return RF_Math::Math<T>::IsAlmostEqual(Value, Other.Value, 4);
}

template <typename T>
RF_Type::Bool Matrix<T, 2, 2>::operator!=(const Matrix<T, 2, 2>& Other)const
{
    return !(*this == Other);
}

template <typename T>
Matrix<T, 3, 3>::Matrix()
{
    LoadIdentity();
}

template <typename T>
Matrix<T, 3, 3>::Matrix(const Matrix& Copy)
{
    RF_SysMem::Copy(Value, Copy.Value, sizeof(T) * 9);
}

template <typename T>
Vector<T, 3> Matrix<T,3,3>::GetRow(RF_Type::Size Row)const
{
    Vector<T, 3> vec;
    for (RF_Type::Size i = 0; i < 3; ++i)
        vec[i] = Value[Row + 3 * i];
    return vec;
}

template<typename T>
Vector<T, 3> Matrix<T, 3, 3>::GetColumn(RF_Type::Size Column)const
{
    Vector<T, 3> vec;
    for (RF_Type::Size i = 0; i < 3; ++i)
        vec[i] = Value[i + 3 * Column];
    return vec;
}

template<typename T>
void Matrix<T, 3, 3>::SetColumn(RF_Type::Size Column, const Vector<T, 3> & Vec)
{
    RF_SysMem::Copy(&Value[Column * 3], Vec.Value, sizeof(T) * 3);
}

template<typename T>
Matrix<T, 3, 3>& Matrix<T, 3, 3>::LoadIdentity()
{
    for (RF_Type::Size i = 0; i < 3; i++)
        for (RF_Type::Size j = 0; j < 3; j++)
            Value[i * 3 + j] = (i == j) ? static_cast<T>(1) : static_cast<T>(0);
    return *this;
}

template<typename T>
Matrix<T, 3, 3>& Matrix<T, 3, 3>::LoadZero()
{
    RF_SysMem::Set(Value, 0, 9 * sizeof(T));
    return *this;
}

template<typename T>
Matrix<T,3,3> Matrix<T,3,3>::Transpose()
{
    Matrix out;
    for (RF_Type::Size i = 0; i < 3; i++)
        for (RF_Type::Size j = 0; j < 3; j++)
            out.Value[i + j * 3] = Value[j + i * 3];
    return out;
}

template<typename T>
Matrix<T,3,3>& Matrix<T,3,3>::Scale(const Vector<T, 3> &Other)
{
    for (RF_Type::Size i = 0; i < 3; i++)
        for (RF_Type::Size j = 0; j < 3; j++)
            Value[i * 3 + j] *= Other[i];
    return *this;
}

template<typename T>
Matrix<T,3,3>& Matrix<T,3,3>::operator =(Matrix& Other)
{
    for (RF_Type::Size i = 0; i < 9; i++)
        Value[i] = Other.Value[i];
    return *this;
}

template<typename T>
inline T& Matrix<T,3,3>::operator()(RF_Type::Size Col, RF_Type::Size Row)
{
    Assert(Col * 3 + Row >= 0 && Col * 3 + Row < 9, "Index out of bound.");
    return Value[Col * 3 + Row];
}

template<typename T>
inline T Matrix<T,3,3>::operator()(RF_Type::Size Col, RF_Type::Size Row)const
{
    Assert(Col * 3 + Row >= 0 && Col * 3 + Row < 9, "Index out of bound.");
    return Value[Col * 3 + Row];
}

template<typename T>
inline T& Matrix<T,3,3>::operator[](const RF_Type::Size Index)
{
    Assert(Index >= 0 && Index < 9, "Index out of bound.");
    return Value[Index];
}

template<typename T>
inline T Matrix<T, 3, 3>::operator[](const RF_Type::Size Index)const
{
    Assert(Index >= 0 && Index < 9, "Index out of bound.");
    return Value[Index];
}

template<typename T>
Matrix<T,3,3> Matrix<T,3,3>::operator *(Matrix<T,3,3>& Other)const
{
    Matrix out;
    for (RF_Type::Size i = 0; i < 3; ++i)
        for (RF_Type::Size j = 0; j < 3; ++j)
            out[i * 3 + j] = (*this)[i * 3] * Other[j] + (*this)[i * 3 + 1] * Other[3 + j] + (*this)[i * 3 + 2] * Other[6 + j];
    return out;
}

template<typename T>
Matrix<T,3,3> Matrix<T,3,3>::operator /(T Other)const
{
    Matrix out;
    for (RF_Type::Size j = 0; j < 9; j++)
        out.Value[j] = Value[j] / Other;
    return out;
}

template<typename T>
Vector<T, 3> Matrix<T,3,3>::operator *(const Vector<T, 3>& Other)const
{
    Vector<T, 3> out(0, 0, 0);
    for (RF_Type::Size i = 0; i < 3; ++i)
        out += GetColumn(i)*Other[i];
    return out;
}

template<typename T>
Matrix<T,3,3>& Matrix<T,3,3>::operator *=(Matrix<T,3,3>& Other)
{
    Matrix out;
    for (RF_Type::Size i = 0; i < 3; i++)
        for (RF_Type::Size j = 0; j < 3; j++){
        out(i, j) = T(0);
        for (RF_Type::Size k = 0; k < 3; k++)
            out(i, j) += Other(i, k) * (*this)(k, j);
        }
    (*this) = out;
    return *this;
}

template<typename T>
Matrix<T,3,3>& Matrix<T,3,3>::operator /=(T Other)
{
    for (RF_Type::Size j = 0; j < 9; j++)
        Value[j] /= Other;
    return *this;
}

template<typename T>
Matrix<T,3,3>& Matrix<T,3,3>::Translate(T x, T y, T z)
{
    Matrix m;
    m.Value[8] = x;
    m.Value[9] = y;
    (*this) *= m;
    return *this;
}

template<typename T>
Matrix<T,3,3>& Matrix<T,3,3>::Rotate(T w, T x, T y, T z)
{
    Vector<T, 3> v(x, y, z);
    T len = v.Length();
    Assert(len != 0, "Argument is not legal because the x,y,z components are zero.");
    T rad = Math<T>::DegToRad(w);
    T c = cos(rad);
    T ic = 1.0 - c;
    T s = sin(rad);

    v /= len;
    Matrix m;
    T xy = v[0] * v[1];
    T xz = v[0] * v[2];
    T yz = v[1] * v[2];
    m[0] = c + v[0] ^ 2 * ic;   m[1] = xy*ic + z*s; m[2] = xz*ic - y*s;
    m[3] = xy*ic - z*s; m[4] = c*v[1] ^ 2 * ic;   m[5] = yz*ic + x*s;
    m[6] = xz*ic + y*s; m[7] = yz*ic - x*s; m[8] = c + v[2] ^ 2 * ic;

    (*this) *= m;
    return *this;
}

template<typename T>
Matrix<T,3,3>& Matrix<T,3,3>::Scale(T x, T y, T z)
{
    Vector<T, 3> v(x, y, z);
    Scale(v);
    return *this;
}

template<typename T>
T Matrix<T,3,3>::Determinants()
{
    return Value[0] * Value[4] * Value[8] + Value[3] * Value[7] * Value[2] + Value[6] * Value[1] * Value[5]
        - Value[6] * Value[4] * Value[2] - Value[0] * Value[7] * Value[5] - Value[3] * Value[1] * Value[8];
}

template<typename T>
Matrix<T,3,3> Matrix<T,3,3>::Inverse()
{
    //base on http://www.geometrictools.com code
    Matrix inverse;
    // Compute the adjoint.
    inverse.Value[0] = Value[4] * Value[8] - Value[5] * Value[7];
    inverse.Value[1] = Value[2] * Value[7] - Value[1] * Value[8];
    inverse.Value[2] = Value[1] * Value[5] - Value[2] * Value[4];
    inverse.Value[3] = Value[5] * Value[6] - Value[3] * Value[8];
    inverse.Value[4] = Value[0] * Value[8] - Value[2] * Value[6];
    inverse.Value[5] = Value[2] * Value[3] - Value[0] * Value[5];
    inverse.Value[6] = Value[3] * Value[7] - Value[4] * Value[6];
    inverse.Value[7] = Value[1] * Value[6] - Value[0] * Value[7];
    inverse.Value[8] = Value[0] * Value[4] - Value[1] * Value[3];

    T det = Value[0] * inverse.Value[0] + Value[1] * inverse.Value[3] +
        Value[2] * inverse.Value[6];

    if (RF_Math::Math<T>::FAbs(det) > RF_Math::Math<T>::EPSILION)
    {
        T invDet = ((T)1) / det;
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

template<typename T>
RF_Type::Bool Matrix<T,3,3>::operator==(const Matrix<T,3,3>& Other)const
{
    return RF_Math::Math<T>::IsAlmostEqual(Value, Other.Value, 9);
}

template<typename T>
RF_Type::Bool Matrix<T,3,3>::operator!=(const Matrix<T,3,3>& Other)const
{
    return !(*this == Other);
}

template<typename T>
Matrix<T,4,4>::Matrix()
{
    LoadIdentity();
}

template<typename T>
Matrix<T,4,4>::Matrix(const Matrix& Copy)
{
    RF_SysMem::Copy(Value, Copy.Value, sizeof(T) * 16);
}

template<typename T>
Vector<T, 4> Matrix<T,4,4>::GetRow(RF_Type::Size Row)const
{
    Vector<T, 4> vec;
    for (RF_Type::Size i = 0; i < 4; ++i)
        vec[i] = Value[Row + 4 * i];
    return vec;
}

template<typename T>
Vector<T, 4> Matrix<T,4,4>::GetColumn(RF_Type::Size Column)const
{
    Vector<T, 4> vec;
    for (RF_Type::Size i = 0; i < 4; ++i)
        vec[i] = Value[i + 4 * Column];
    return vec;
}

template<typename T>
void Matrix<T,4,4>::SetColumn(RF_Type::Size Column, const Vector<T, 4> & Vec)
{
    RF_SysMem::Copy(&Value[Column * 4], Vec.Value, sizeof(T) * 4);
}

template<typename T>
Matrix<T,4,4>& Matrix<T,4,4>::LoadIdentity()
{
    for (RF_Type::Size i = 0; i < 4; i++)
        for (RF_Type::Size j = 0; j < 4; j++)
            Value[i * 4 + j] = (i == j) ? static_cast<T>(1) : static_cast<T>(0);
    return *this;
}

template<typename T>
Matrix<T,4,4>& Matrix<T,4,4>::LoadZero()
{
    RF_SysMem::Set(Value, 0, 16 * sizeof(T));
    return *this;
}

template<typename T>
Matrix<T,4,4> Matrix<T,4,4>::Transpose()
{
    Matrix out;
    for (RF_Type::Size i = 0; i < 4; i++)
        for (RF_Type::Size j = 0; j < 4; j++)
            out.Value[i + j * 4] = Value[j + i * 4];
    return out;
}

template<typename T>
Matrix<T,4,4>& Matrix<T,4,4>::Scale(const Vector<T, 4> &Other)
{
    for (RF_Type::Size i = 0; i < 4; i++)
        for (RF_Type::Size j = 0; j < 4; j++)
            Value[i * 4 + j] *= Other[i];
    return *this;
}

template<typename T>
Matrix<T,4,4>& Matrix<T,4,4>::operator=(Matrix<T,4,4>& Other)
{
    for (RF_Type::Size i = 0; i < 16; i++)
        Value[i] = Other.Value[i];
    return *this;
}

template<typename T>
inline T& Matrix<T,4,4>::operator()(RF_Type::Size Col, RF_Type::Size Row)
{
    Assert(Col * 4 + Row >= 0 && Col * 4 + Row < 16, "Index out of bound.");
    return Value[Col * 4 + Row];
}

template<typename T>
inline T Matrix<T,4,4>::operator()(RF_Type::Size Col, RF_Type::Size Row)const
{
    Assert(Col * 4 + Row >= 0 && Col * 4 + Row < 16, "Index out of bound.");
    return Value[Col * 4 + Row];
}

template<typename T>
inline T& Matrix<T,4,4>::operator[](const RF_Type::Size Index)
{
    Assert(Index >= 0 && Index < 16, "Index out of bound.")
        return Value[Index];
}

template<typename T>
inline T Matrix<T,4,4>::operator[](const RF_Type::Size Index)const
{
    Assert(Index >= 0 && Index < 16, "Index out of bound.");
    return Value[Index];
}

template<typename T>
Matrix<T,4,4> Matrix<T,4,4>::operator*(const Matrix<T,4,4>& Other)const
{
    /*Matrix out;
    for (int i=0;i<4;++i)
    for (int j=0;j<4;++j)
    out[i*4+j]=(*this)[i*4]*Other[j]+(*this)[i*4+1]*Other[4+j]+(*this)[i*4+2]*Other[8+j]+(*this)[i*4+3]*Other[12+j];
    return out;*/
    Matrix out;
    out[0] = Value[0] * Other.Value[0] +
        Value[1] * Other.Value[4] +
        Value[2] * Other.Value[8] +
        Value[3] * Other.Value[12];

    out[1] = Value[0] * Other.Value[1] +
        Value[1] * Other.Value[5] +
        Value[2] * Other.Value[9] +
        Value[3] * Other.Value[13];

    out[2] = Value[0] * Other.Value[2] +
        Value[1] * Other.Value[6] +
        Value[2] * Other.Value[10] +
        Value[3] * Other.Value[14];

    out[3] = Value[0] * Other.Value[3] +
        Value[1] * Other.Value[7] +
        Value[2] * Other.Value[11] +
        Value[3] * Other.Value[15];

    out[4] = Value[4] * Other.Value[0] +
        Value[5] * Other.Value[4] +
        Value[6] * Other.Value[8] +
        Value[7] * Other.Value[12];

    out[5] = Value[4] * Other.Value[1] +
        Value[5] * Other.Value[5] +
        Value[6] * Other.Value[9] +
        Value[7] * Other.Value[13];

    out[6] = Value[4] * Other.Value[2] +
        Value[5] * Other.Value[6] +
        Value[6] * Other.Value[10] +
        Value[7] * Other.Value[14];

    out[7] = Value[4] * Other.Value[3] +
        Value[5] * Other.Value[7] +
        Value[6] * Other.Value[11] +
        Value[7] * Other.Value[15];

    out[8] = Value[8] * Other.Value[0] +
        Value[9] * Other.Value[4] +
        Value[10] * Other.Value[8] +
        Value[11] * Other.Value[12];

    out[9] = Value[8] * Other.Value[1] +
        Value[9] * Other.Value[5] +
        Value[10] * Other.Value[9] +
        Value[11] * Other.Value[13];

    out[10] = Value[8] * Other.Value[2] +
        Value[9] * Other.Value[6] +
        Value[10] * Other.Value[10] +
        Value[11] * Other.Value[14];

    out[11] = Value[8] * Other.Value[3] +
        Value[9] * Other.Value[7] +
        Value[10] * Other.Value[11] +
        Value[11] * Other.Value[15];

    out[12] = Value[12] * Other.Value[0] +
        Value[13] * Other.Value[4] +
        Value[14] * Other.Value[8] +
        Value[15] * Other.Value[12];

    out[13] = Value[12] * Other.Value[1] +
        Value[13] * Other.Value[5] +
        Value[14] * Other.Value[9] +
        Value[15] * Other.Value[13];

    out[14] = Value[12] * Other.Value[2] +
        Value[13] * Other.Value[6] +
        Value[14] * Other.Value[10] +
        Value[15] * Other.Value[14];

    out[15] = Value[12] * Other.Value[3] +
        Value[13] * Other.Value[7] +
        Value[14] * Other.Value[11] +
        Value[15] * Other.Value[15];
    return out;
}

template<typename T>
Matrix<T,4,4> Matrix<T,4,4>::operator/(T Other)const
{
    Matrix out;
    for (RF_Type::Size j = 0; j < 16; j++)
        out.Value[j] = Value[j] / Other;
    return out;
}

template<typename T>
Vector<T, 4> Matrix<T,4,4>::operator*(const Vector<T, 4>& Other)const
{
    Vector<T, 4> out(0, 0, 0, 0);
    for (RF_Type::Size i = 0; i < 4; ++i)
        out += GetColumn(i)*Other[i];
    return out;
}

template<typename T>
Matrix<T,4,4>& Matrix<T,4,4>::operator*=(Matrix<T,4,4>& Other)
{
    Matrix out;
    for (RF_Type::Size i = 0; i < 4; i++)
        for (RF_Type::Size j = 0; j < 4; j++){
        out(i, j) = T(0);
        for (RF_Type::Size k = 0; k < 4; k++)
            out(i, j) += Other(i, k) * (*this)(k, j);
        }
    (*this) = out;
    return *this;
}

template<typename T>
Matrix<T,4,4>& Matrix<T,4,4>::operator /=(T Other)
{
    for (RF_Type::Size j = 0; j < 16; j++)
        Value[j] /= Other;
    return *this;
}

template<typename T>
Matrix<T,4,4>& Matrix<T,4,4>::Translate(T x, T y, T z)
{
    Matrix m;
    m[12] = x;
    m[13] = y;
    m[14] = z;
    (*this) *= m;
    return *this;
}

template<typename T>
Matrix<T,4,4>& Matrix<T,4,4>::Rotate(const T w, const T x, const T y, const T z)
{
    Matrix m;
    T rad = RF_Math::Math<T>::DegToRad(w);
    T c = cos(rad);
    T ic = 1.0f - c;
    T s = sin(rad);
    Vector<T, 4> v(x, y, z, 0.0);
    T mag = sqrt((v*v).Sum());

    if (mag <= 1.0e-4)
        return *this;

    v[0] = x / mag;
    v[1] = y / mag;
    v[2] = z / mag;

    m[0] = (v[0] * v[0] * ic) + c;
    m[1] = (v[0] * v[1] * ic) + (v[2] * s);
    m[2] = (v[0] * v[2] * ic) - (v[1] * s);

    m[4] = (v[0] * v[1] * ic) - (v[2] * s);
    m[5] = (v[1] * v[1] * ic) + c;
    m[6] = (v[1] * v[2] * ic) + (v[0] * s);

    m[8] = (v[0] * v[2] * ic) + (v[1] * s);
    m[9] = (v[1] * v[2] * ic) - (v[0] * s);
    m[10] = (v[2] * v[2] * ic) + c;

    *this *= m;
    return *this;
}

template<typename T>
Matrix<T,4,4>& Matrix<T,4,4>::Scale(T x, T y, T z)
{
    Matrix m;
    m[0] = x;
    m[5] = y;
    m[10] = z;
    *this *= m;
    return *this;
}

template<typename T>
Matrix<T,4,4> Matrix<T,4,4>::MatNormalMatrix()
{
    Matrix tnmat;
    float d;
    for (unsigned int i=0;i<3;i++)
    for (unsigned int j=0;j<3;j++)
        m_NormalMatrix.Value[i*3+j]=this->Value[i*4+j];

    d=Determinant(m_NormalMatrix);
    tnmat[0]=m_NormalMatrix[4]*m_NormalMatrix[8]-m_NormalMatrix[5]*m_NormalMatrix[7];
    tnmat[3]=m_NormalMatrix[5]*m_NormalMatrix[6]-m_NormalMatrix[3]*m_NormalMatrix[8];
    tnmat[6]=m_NormalMatrix[3]*m_NormalMatrix[7]-m_NormalMatrix[4]*m_NormalMatrix[6];

    tnmat[1]=m_NormalMatrix[2]*m_NormalMatrix[7]-m_NormalMatrix[5]*m_NormalMatrix[8];
    tnmat[4]=m_NormalMatrix[0]*m_NormalMatrix[8]-m_NormalMatrix[2]*m_NormalMatrix[6];
    tnmat[7]=m_NormalMatrix[1]*m_NormalMatrix[6]-m_NormalMatrix[1]*m_NormalMatrix[7];

    tnmat[2]=m_NormalMatrix[1]*m_NormalMatrix[5]-m_NormalMatrix[2]*m_NormalMatrix[4];
    tnmat[5]=m_NormalMatrix[2]*m_NormalMatrix[3]-m_NormalMatrix[0]*m_NormalMatrix[5];
    tnmat[8]=m_NormalMatrix[0]*m_NormalMatrix[4]-m_NormalMatrix[1]*m_NormalMatrix[3];

    for (unsigned int i=0;i<3;i++)
    for (unsigned int j=0;j<3;j++)
        m_NormalMatrix[i*3+j]=tnmat[i*3+j]/d;
    return tnmat;
}

template<typename T>
T Matrix<T,4,4>::Determinants()const
{
    T a0 = Value[0] * Value[5] - Value[1] * Value[4];
    T a1 = Value[0] * Value[6] - Value[2] * Value[4];
    T a2 = Value[0] * Value[7] - Value[3] * Value[4];
    T a3 = Value[1] * Value[6] - Value[2] * Value[5];
    T a4 = Value[1] * Value[7] - Value[3] * Value[5];
    T a5 = Value[2] * Value[7] - Value[3] * Value[6];
    T b0 = Value[8] * Value[13] - Value[9] * Value[12];
    T b1 = Value[8] * Value[14] - Value[10] * Value[12];
    T b2 = Value[8] * Value[15] - Value[11] * Value[12];
    T b3 = Value[9] * Value[14] - Value[10] * Value[13];
    T b4 = Value[9] * Value[15] - Value[11] * Value[13];
    T b5 = Value[10] * Value[15] - Value[11] * Value[14];
    T det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
    return det;
}

template<typename T>
Matrix<T,4,4> Matrix<T,4,4>::Inverse()const
{
    Matrix inverse;
    T a0 = Value[0] * Value[5] - Value[1] * Value[4];
    T a1 = Value[0] * Value[6] - Value[2] * Value[4];
    T a2 = Value[0] * Value[7] - Value[3] * Value[4];
    T a3 = Value[1] * Value[6] - Value[2] * Value[5];
    T a4 = Value[1] * Value[7] - Value[3] * Value[5];
    T a5 = Value[2] * Value[7] - Value[3] * Value[6];
    T b0 = Value[8] * Value[13] - Value[9] * Value[12];
    T b1 = Value[8] * Value[14] - Value[10] * Value[12];
    T b2 = Value[8] * Value[15] - Value[11] * Value[12];
    T b3 = Value[9] * Value[14] - Value[10] * Value[13];
    T b4 = Value[9] * Value[15] - Value[11] * Value[13];
    T b5 = Value[10] * Value[15] - Value[11] * Value[14];
    T det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
    if (RF_Math::Math<T>::FAbs(det) > RF_Math::Math<T>::EPSILION)
    {
        inverse.Value[0] = +Value[5] * b5 - Value[6] * b4 + Value[7] * b3;
        inverse.Value[4] = -Value[4] * b5 + Value[6] * b2 - Value[7] * b1;
        inverse.Value[8] = +Value[4] * b4 - Value[5] * b2 + Value[7] * b0;
        inverse.Value[12] = -Value[4] * b3 + Value[5] * b1 - Value[6] * b0;
        inverse.Value[1] = -Value[1] * b5 + Value[2] * b4 - Value[3] * b3;
        inverse.Value[5] = +Value[0] * b5 - Value[2] * b2 + Value[3] * b1;
        inverse.Value[9] = -Value[0] * b4 + Value[1] * b2 - Value[3] * b0;
        inverse.Value[13] = +Value[0] * b3 - Value[1] * b1 + Value[2] * b0;
        inverse.Value[2] = +Value[13] * a5 - Value[14] * a4 + Value[15] * a3;
        inverse.Value[6] = -Value[12] * a5 + Value[14] * a2 - Value[15] * a1;
        inverse.Value[10] = +Value[12] * a4 - Value[13] * a2 + Value[15] * a0;
        inverse.Value[14] = -Value[12] * a3 + Value[13] * a1 - Value[14] * a0;
        inverse.Value[3] = -Value[9] * a5 + Value[10] * a4 - Value[11] * a3;
        inverse.Value[7] = +Value[8] * a5 - Value[10] * a2 + Value[11] * a1;
        inverse.Value[11] = -Value[8] * a4 + Value[9] * a2 - Value[11] * a0;
        inverse.Value[15] = +Value[8] * a3 - Value[9] * a1 + Value[10] * a0;

        T invDet = ((T)1) / det;
        inverse.Value[0] *= invDet;
        inverse.Value[1] *= invDet;
        inverse.Value[2] *= invDet;
        inverse.Value[3] *= invDet;
        inverse.Value[4] *= invDet;
        inverse.Value[5] *= invDet;
        inverse.Value[6] *= invDet;
        inverse.Value[7] *= invDet;
        inverse.Value[8] *= invDet;
        inverse.Value[9] *= invDet;
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

template<typename T>
RF_Type::Bool Matrix<T,4,4>::operator==(const Matrix<T,4,4>& Other)const
{
    return RF_Math::Math<T>::IsAlmostEqual(Value, Other.Value, 16);
}

template<typename T>
RF_Type::Bool Matrix<T,4,4>::operator!=(const Matrix<T,4,4>& Other)const
{
    return !(*this == Other);
}

#define Matrix2f Matrix<float,2,2>
#define Matrix3f Matrix<float,3,3>
#define Matrix4f Matrix<float,4,4>
#define Mat2f Matrix<float,2,2>
#define Mat3f Matrix<float,3,3>
#define Mat4f Matrix<float,4,4>

} } }

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif // RF_MATH_GEOMETRY_MATRIX_HPP
