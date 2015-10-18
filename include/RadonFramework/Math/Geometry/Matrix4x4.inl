#ifndef RF_MATH_GEOMETRY_MATRIX4X4_INL
#define RF_MATH_GEOMETRY_MATRIX4X4_INL

#include <RadonFramework/Math/Geometry/Matrix.hpp>

namespace RadonFramework { namespace Math { namespace Geometry {

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

    Matrix& operator =(const Matrix& Other);
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
Matrix<T, 4, 4>& Matrix<T, 4, 4>::operator=(const Matrix<T, 4, 4>& Other)
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
    Matrix out;
    for (int i=0;i<4;++i)
    for (int j=0;j<4;++j)
    out[i*4+j] = (*this)[j]    * Other[i*4]   +
                 (*this)[j+4]  * Other[i*4+1] +
                 (*this)[j+8]  * Other[i*4+2] +
                 (*this)[j+12] * Other[i*4+3];
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
    Value[12] = x;
    Value[13] = y;
    Value[14] = z;
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

    Value[0] = (v[0] * v[0] * ic) + c;
    Value[1] = (v[0] * v[1] * ic) + (v[2] * s);
    Value[2] = (v[0] * v[2] * ic) - (v[1] * s);

    Value[4] = (v[0] * v[1] * ic) - (v[2] * s);
    Value[5] = (v[1] * v[1] * ic) + c;
    Value[6] = (v[1] * v[2] * ic) + (v[0] * s);

    Value[8] = (v[0] * v[2] * ic) + (v[1] * s);
    Value[9] = (v[1] * v[2] * ic) - (v[0] * s);
    Value[10] = (v[2] * v[2] * ic) + c;

    *this *= m;
    return *this;
}

template<typename T>
Matrix<T,4,4>& Matrix<T,4,4>::Scale(T x, T y, T z)
{
    Matrix m;
    Value[0] = x;
    Value[5] = y;
    Value[10] = z;
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
        Value[i*3+j]=this->Value[i*4+j];

    d=Determinant(*this);
    tnmat[0]=Value[4]*Value[8]-Value[5]*Value[7];
    tnmat[3]=Value[5]*Value[6]-Value[3]*Value[8];
    tnmat[6]=Value[3]*Value[7]-Value[4]*Value[6];

    tnmat[1]=Value[2]*Value[7]-Value[5]*Value[8];
    tnmat[4]=Value[0]*Value[8]-Value[2]*Value[6];
    tnmat[7]=Value[1]*Value[6]-Value[1]*Value[7];

    tnmat[2]=Value[1]*Value[5]-Value[2]*Value[4];
    tnmat[5]=Value[2]*Value[3]-Value[0]*Value[5];
    tnmat[8]=Value[0]*Value[4]-Value[1]*Value[3];

    for (unsigned int i=0;i<3;i++)
    for (unsigned int j=0;j<3;j++)
        Value[i*3+j]=tnmat[i*3+j]/d;
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

typedef Matrix<RF_Type::Float32, 4, 4> Mat4f;
typedef Matrix<RF_Type::Float64, 4, 4> Mat4d;
typedef Matrix<RF_Type::Float32, 4, 4> Matrix4f;
typedef Matrix<RF_Type::Float64, 4, 4> Matrix4d;

} } }

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif // RF_MATH_GEOMETRY_MATRIX4X4_INL
