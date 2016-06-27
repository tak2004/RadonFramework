#ifndef RF_MATH_GEOMETRY_MATRIX_HPP
#define RF_MATH_GEOMETRY_MATRIX_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Geometry/Vector.hpp>
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

    Matrix& operator =(const Matrix& Other);
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

    Matrix& operator =(const Matrix& Other);
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

    Matrix& operator =(const Matrix& Other);
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

template <typename T, RF_Type::Size N, RF_Type::Size M>
Matrix<T, N, M>::Matrix()
{
    LoadIdentity();
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
Matrix<T, N, M>::Matrix(const Matrix<T, N, M>& Copy)
{
    RF_SysMem::Copy(Value, Copy.Value, sizeof(T)*M*N);
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
    RF_SysMem::Copy(&Value[Column*N], Vec.Value, sizeof(T)*N);
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
    RF_SysMem::Set(Value, 0, N*M*sizeof(T));
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
Matrix<T, N, M>& Matrix<T, N, M>::operator =(const Matrix<T, N, M>& Other)
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
    Assert(Index < N*M, "Index out of bound.");
    return Value[Index];
}

template <typename T, RF_Type::Size N, RF_Type::Size M>
Matrix<T, N, M> Matrix<T, N, M>::operator *(Matrix<T, N, M>& Other)const
{
    Matrix out;
    for (RF_Type::Size j = 0; j < N*M; j += M)
    {
        for(RF_Type::Size i = 0; i < N; i++)
        {
            out.Value[i + j] = Other.Value[i] * Value[j];
            for(RF_Type::Size k = 1; k < M; k++)
            {
                out.Value[i + j] += Other.Value[i + N * k] * Value[j + k];
            }
        }
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
    return RF_Math::MathOfType<T>::IsAlmostEqual(Value, Other.Value, N*M, 5);
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
Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator =(const Matrix<T, 2, 2>& Other)
{
    for (RF_Type::Size i = 0; i < 4; i++)
        Value[i] = Other.Value[i];
    return *this;
}

template <typename T>
inline T& Matrix<T, 2, 2>::operator()(RF_Type::Size Col, RF_Type::Size Row)
{
    Assert(Col * 2 + Row < 4, "Index out of bound.");
    return Value[Col * 2 + Row];
}

template <typename T>
inline T Matrix<T, 2, 2>::operator()(RF_Type::Size Col, RF_Type::Size Row)const
{
    Assert(Col * 2 + Row < 4, "Index out of bound.");
    return Value[Col * 2 + Row];
}

template <typename T>
inline T& Matrix<T, 2, 2>::operator[](const RF_Type::Size Index)
{
    Assert(Index < 4, "Index out of bound.");
    return Value[Index];
}

template <typename T>
inline T Matrix<T, 2, 2>::operator[](const RF_Type::Size Index)const
{
    Assert(Index < 4, "Index out of bound.");
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
    T rad = RF_Math::MathOfType<T>::DegToRad(Angle);
    T c = RF_Math::MathOfType<T>::Cos(rad);
    T s = RF_Math::MathOfType<T>::Sin(rad);
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
    if (RF_Math::MathOfType<T>::FAbs(det) > RF_Math::MathOfType<T>::EPSILION)
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
    return RF_Math::MathOfType<T>::IsAlmostEqual(Value, Other.Value, 4);
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
Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator =(const Matrix& Other)
{
    for (RF_Type::Size i = 0; i < 9; i++)
        Value[i] = Other.Value[i];
    return *this;
}

template<typename T>
inline T& Matrix<T,3,3>::operator()(RF_Type::Size Col, RF_Type::Size Row)
{
    Assert(Col * 3 + Row < 9, "Index out of bound.");
    return Value[Col * 3 + Row];
}

template<typename T>
inline T Matrix<T,3,3>::operator()(RF_Type::Size Col, RF_Type::Size Row)const
{
    Assert(Col * 3 + Row < 9, "Index out of bound.");
    return Value[Col * 3 + Row];
}

template<typename T>
inline T& Matrix<T,3,3>::operator[](const RF_Type::Size Index)
{
    Assert(Index < 9, "Index out of bound.");
    return Value[Index];
}

template<typename T>
inline T Matrix<T, 3, 3>::operator[](const RF_Type::Size Index)const
{
    Assert(Index < 9, "Index out of bound.");
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
    T rad = RF_Math::MathOfType<T>::DegToRad(w);
    T c = RF_Math::MathOfType<T>::Cos(rad);
    T ic = 1.0 - c;
    T s = RF_Math::MathOfType<T>::Sin(rad);

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

    if (RF_Math::MathOfType<T>::FAbs(det) > RF_Math::MathOfType<T>::EPSILION)
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
    return RF_Math::MathOfType<T>::IsAlmostEqual(Value, Other.Value, 9);
}

template<typename T>
RF_Type::Bool Matrix<T,3,3>::operator!=(const Matrix<T,3,3>& Other)const
{
    return !(*this == Other);
}

using Matrix2f = Matrix<float,2,2>;
using Matrix3f = Matrix<float,3,3>;
using Mat2f = Matrix<float,2,2>;
using Mat3f = Matrix<float,3,3>;

} } }

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif // RF_MATH_GEOMETRY_MATRIX_HPP

#include <RadonFramework/Math/Geometry/Matrix4x4.inl>