/*
*
* THIS FILE IS GENERATED FROM build/code_templates/Quaternion.cxx !!!
*
*/
#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Geometry/QuatF64.hpp"
#include "RadonFramework/Math/Float64.hpp"

namespace RadonFramework::Math::Geometry {

const QuatF64 QuatF64::Identity;

QuatF64::QuatF64()
{
    m_Vec[0] = 1;
    m_Vec[1] = 0;
    m_Vec[2] = 0;
    m_Vec[3] = 0;
}

QuatF64::QuatF64(const QuatF64& Copy):m_Vec(Copy.m_Vec)
{}

QuatF64& QuatF64::operator=(const QuatF64& Copy)
{
    m_Vec = Copy.m_Vec;
        return *this;
}

QuatF64::QuatF64(const RF_Type::Float64 Alpha, const Vector<RF_Type::Float64, 3>& Direction)
{
    RF_Type::Float64 a = RF_Math::Float64::DegToRad(Alpha*static_cast<RF_Type::Float64>(0.5));
    RF_ASSERT(Direction.Length() >= RF_Math::Float64::EPSILION, "Invalid parameter.");
    RF_Type::Float64 s = RF_Math::Float64::Sin(a);
    m_Vec[0] = RF_Math::Float64::Cos(a);
    m_Vec[1] = s*Direction[0];
    m_Vec[2] = s*Direction[1];
    m_Vec[3] = s*Direction[2];
}

QuatF64::QuatF64(const RF_Type::Float64 w, const RF_Type::Float64 X, const RF_Type::Float64 Y, const RF_Type::Float64 Z)
{
    m_Vec[0] = w;
    m_Vec[1] = X;
    m_Vec[2] = Y;
    m_Vec[3] = Z;
}

QuatF64::QuatF64(const Vector<RF_Type::Float64, 3>& Direction)
{
    Vector<RF_Type::Float64, 3> up(0, 1, 0);
    Vector<RF_Type::Float64, 3> right(up.CrossProduct(Direction));
    up = Direction.CrossProduct(right);

    Matrix<RF_Type::Float64, 3, 3> rotmat;
    rotmat.SetColumn(0, right);
    rotmat.SetColumn(1, up);
    rotmat.SetColumn(2, Direction);
    rotmat.Transpose();//setcolum is faster as setrow
    m_Vec = QuatF64(rotmat).m_Vec;
    /*m_Vec[0]=Math::Sqrt(1.0+rotmat[0]+rotmat[3]+rotmat[6])/2.0;
    RF_Type::Float64 scale=m_Vec[0]*4.0;
    m_Vec[1]=(rotmat[7]-rotmat[5])/scale;
    m_Vec[2]=(rotmat[2]-rotmat[6])/scale;
    m_Vec[3]=(rotmat[3]-rotmat[1])/scale;*/
}

QuatF64::QuatF64(const Matrix<RF_Type::Float64, 3, 3>& RotationMatrix)
{
    RF_Type::Float64 tr = RotationMatrix[0] + RotationMatrix[4] + RotationMatrix[8];
    RF_Type::Float64 s;
    if(tr >= 0.0)
    {
        s = RF_Math::Float64::Sqrt(tr + static_cast<RF_Type::Float64>(1))*static_cast<RF_Type::Float64>(2);
        m_Vec[0] = static_cast<RF_Type::Float64>(0.25)*s;
        m_Vec[1] = (RotationMatrix[7] - RotationMatrix[5])*s;
        m_Vec[2] = (RotationMatrix[2] - RotationMatrix[6])*s;
        m_Vec[3] = (RotationMatrix[3] - RotationMatrix[1])*s;
    }
    else
    {
        RF_Type::UInt32 i = 0;
        if(RotationMatrix[4]>RotationMatrix[0])
            i = 4;
        if(RotationMatrix[8]>RotationMatrix[i])
            i = 8;
        switch(i)
        {
            case 0:
                s = RF_Math::Float64::Sqrt(RotationMatrix[0] - (RotationMatrix[4] + RotationMatrix[8]) + static_cast<RF_Type::Float64>(1.0));
                m_Vec[1] = static_cast<RF_Type::Float64>(0.5)*s;
                s = static_cast<RF_Type::Float64>(0.5) / s;
                m_Vec[2] = (RotationMatrix[1] + RotationMatrix[3])*s;
                m_Vec[3] = (RotationMatrix[6] + RotationMatrix[2])*s;
                m_Vec[0] = (RotationMatrix[7] + RotationMatrix[2])*s;
                break;
            case 4:
                s = RF_Math::Float64::Sqrt(RotationMatrix[4] - (RotationMatrix[8] + RotationMatrix[0]) + static_cast<RF_Type::Float64>(1.0));
                m_Vec[2] = static_cast<RF_Type::Float64>(0.5)*s;
                s = static_cast<RF_Type::Float64>(0.5) / s;
                m_Vec[3] = (RotationMatrix[5] + RotationMatrix[7])*s;
                m_Vec[1] = (RotationMatrix[1] + RotationMatrix[3])*s;
                m_Vec[0] = (RotationMatrix[2] + RotationMatrix[6])*s;
                break;
            case 8:
                s = RF_Math::Float64::Sqrt(RotationMatrix[8] - (RotationMatrix[0] + RotationMatrix[4]) + static_cast<RF_Type::Float64>(1.0));
                m_Vec[3] = static_cast<RF_Type::Float64>(0.5)*s;
                s = static_cast<RF_Type::Float64>(0.5) / s;
                m_Vec[1] = (RotationMatrix[6] + RotationMatrix[2])*s;
                m_Vec[2] = (RotationMatrix[5] + RotationMatrix[7])*s;
                m_Vec[0] = (RotationMatrix[3] + RotationMatrix[1])*s;
                break;
        }
    }
}

QuatF64::QuatF64(const RF_Type::Float64 Roll, const RF_Type::Float64 Pitch, const RF_Type::Float64 Yaw)
{
    RF_Type::Float64 r = RF_Math::Float64::DegToRad(Roll * static_cast<RF_Type::Float64>(0.5));
    RF_Type::Float64 p = RF_Math::Float64::DegToRad(Pitch * static_cast<RF_Type::Float64>(0.5));
    RF_Type::Float64 y = RF_Math::Float64::DegToRad(Yaw * static_cast<RF_Type::Float64>(0.5));

    RF_Type::Float64 sx = RF_Math::Float64::Sin(r);
    RF_Type::Float64 cx = RF_Math::Float64::Cos(r);

    RF_Type::Float64 sy = RF_Math::Float64::Sin(p);
    RF_Type::Float64 cy = RF_Math::Float64::Cos(p);

    RF_Type::Float64 sz = RF_Math::Float64::Sin(y);
    RF_Type::Float64 cz = RF_Math::Float64::Cos(y);

    m_Vec[0] = (cx*cy*cz) - (sx*sy*sz);
    m_Vec[1] = (sx*sy*cz) + (cx*cy*sz);
    m_Vec[2] = (sx*cy*cz) + (cx*sy*sz);
    m_Vec[3] = (cx*sy*cz) - (sx*cy*sz);
}

QuatF64 QuatF64::operator+(const QuatF64& Other)
{
    QuatF64 quat(*this);
    quat.m_Vec += Other.m_Vec;
        return quat;
}

QuatF64 QuatF64::operator-(const QuatF64& Other)
{
    QuatF64 quat(*this);
    quat.m_Vec -= Other.m_Vec;
        return quat;
}

QuatF64 QuatF64::operator*(const QuatF64& Other)
{
    QuatF64 quat;
    quat.m_Vec[0] = m_Vec[0] * Other.m_Vec[0] - m_Vec[1] * Other.m_Vec[1] - m_Vec[2] * Other.m_Vec[2] - m_Vec[3] * Other.m_Vec[3];
    quat.m_Vec[1] = m_Vec[0] * Other.m_Vec[1] + m_Vec[1] * Other.m_Vec[0] + m_Vec[2] * Other.m_Vec[3] - m_Vec[3] * Other.m_Vec[2];
    quat.m_Vec[2] = m_Vec[0] * Other.m_Vec[2] + m_Vec[2] * Other.m_Vec[0] + m_Vec[3] * Other.m_Vec[1] - m_Vec[1] * Other.m_Vec[3];
    quat.m_Vec[3] = m_Vec[0] * Other.m_Vec[3] + m_Vec[3] * Other.m_Vec[0] + m_Vec[1] * Other.m_Vec[2] - m_Vec[2] * Other.m_Vec[1];
    return quat;
}

QuatF64 QuatF64::operator/(const QuatF64& Other)
{
    QuatF64 quat(*this);
    quat *= Other.Inverse();
    return quat;
}

QuatF64& QuatF64::operator+=(const QuatF64& Other)
{
    m_Vec += Other.m_Vec;
        return *this;
}

QuatF64& QuatF64::operator-=(const QuatF64& Other)
{
    m_Vec -= Other.m_Vec;
        return *this;
}

QuatF64& QuatF64::operator*=(const QuatF64& Other)
{
    m_Vec = (*this*Other).m_Vec;
        return *this;
}

QuatF64& QuatF64::operator/=(const QuatF64& Other)
{
    m_Vec = (*this*Other.Inverse()).m_Vec;
        return *this;
}

QuatF64& QuatF64::SetIdentity()
{
    m_Vec = Identity.m_Vec;
        return *this;
}

QuatF64& QuatF64::Invert()
{
    RF_Type::Float64 val = SquareLength();
    RF_ASSERT(val != static_cast<RF_Type::Float64>(0.0), "Invalid value.");
    Conjugate().m_Vec /= val;
    return *this;
}

QuatF64& QuatF64::Conjugate()
{
    Vector<RF_Type::Float64, 4> vec(1, -1, -1, -1);
    m_Vec *= vec;
    return *this;
}

QuatF64& QuatF64::Normalize()
{
    RF_Type::Float64 v = Length();
    m_Vec /= v;
    return *this;
}

RF_Type::Float64 QuatF64::DotProduct(const QuatF64& Other)
{
    return m_Vec[0] * Other.m_Vec[0] +
    m_Vec[1] * Other.m_Vec[1] +
    m_Vec[2] * Other.m_Vec[2] +
    m_Vec[3] * Other.m_Vec[3];
}

QuatF64 QuatF64::Inverse()const
{
    QuatF64 quat(*this);
    quat.Invert();
    return quat;
}

Vector<RF_Type::Float64, 4> QuatF64::operator*(const Vector<RF_Type::Float64, 4>& Vec)
{
    Vector<RF_Type::Float64, 3> v(Vec[0], Vec[1], Vec[2]);
    v = (*this)*v;
    Vector<RF_Type::Float64, 4> res(v[0], v[1], v[2], Vec[3]);
    return res;
}

Vector<RF_Type::Float64, 3> QuatF64::operator*(const Vector<RF_Type::Float64, 3>& Vec)
{
    Vector<RF_Type::Float64, 3> vecNormalized(Vec);
    vecNormalized.Normalize();
    QuatF64 quatFromVec(0, vecNormalized[0], vecNormalized[1], vecNormalized[2]);
    QuatF64 q(*this);
    q.Conjugate();
    q = quatFromVec * q;
    q = (*this) * q;
    return q.GetAxis();
}

RF_Type::Bool QuatF64::operator==(const QuatF64& Other)
{
    return m_Vec == Other.m_Vec;
}

RF_Type::Bool QuatF64::operator!=(const QuatF64& Other)
{
    return m_Vec != Other.m_Vec;
}

QuatF64 QuatF64::Exponential()
{
    QuatF64 result;
    RF_Type::Float64 angle = RF_Math::Float64::Sqrt(m_Vec[1] * m_Vec[1] +
    m_Vec[2] * m_Vec[2] +
    m_Vec[3] * m_Vec[3]);
    RF_Type::Float64 sn = RF_Math::Float64::Sin(angle);
    result.m_Vec[0] = RF_Math::Float64::Cos(angle);

    RF_Type::UInt32 i;
    if(RF_Math::Float64::FAbs(sn) > static_cast<RF_Type::Float64>(0))
    {
        RF_Type::Float64 coeff = sn / angle;
        for(i = 1; i < 4; ++i)
        {
            result.m_Vec[i] = coeff*m_Vec[i];
        }
    }
    else
    {
        for(i = 1; i < 4; ++i)
        {
            result.m_Vec[i] = m_Vec[i];
        }
    }

    return result;
}

RF_Type::Bool QuatF64::IsInfinite()
{
    return RF_Math::Float64::IsInfinity(m_Vec[0]) ||
        RF_Math::Float64::IsInfinity(m_Vec[1]) ||
        RF_Math::Float64::IsInfinity(m_Vec[2]) ||
        RF_Math::Float64::IsInfinity(m_Vec[3]);
}

RF_Type::Bool QuatF64::IsNaN()
{
    return RF_Math::Float64::IsNaN(m_Vec[0]) ||
        RF_Math::Float64::IsNaN(m_Vec[1]) ||
        RF_Math::Float64::IsNaN(m_Vec[2]) ||
        RF_Math::Float64::IsNaN(m_Vec[3]);
}

QuatF64 QuatF64::LengthAsQuat()
{
    QuatF64 q;
    RF_Type::Float64 len = Length();
    for(RF_Type::UInt32 i = 0; i<4; ++i)
        q[i] = len;
    return q;
}

RF_Type::Float64 QuatF64::Length()
{
    if(m_Vec[0] == 0.0 && m_Vec[1] == 0.0 &&
    m_Vec[2] == 0.0 && m_Vec[3] == 0.0)
        return 0.0;
    return RF_Math::Float64::Sqrt((m_Vec*m_Vec).Sum());;
}

QuatF64 QuatF64::SquareLengthAsQuat()
{
    QuatF64 q;
    RF_Type::Float64 sqrlen = SquareLength();
    for(RF_Type::UInt32 i = 0; i<4; ++i)
        q[i] = sqrlen;
    return q;
}

RF_Type::Float64 QuatF64::SquareLength()
{
    RF_Type::Float64 len = Length();
    len *= len;
    return len;
}

QuatF64 QuatF64::CrossProduct(const QuatF64& Other)
{
    Vector<RF_Type::Float64, 3> v1(m_Vec[1], m_Vec[2], m_Vec[3]);
    Vector<RF_Type::Float64, 3> v2(Other.m_Vec[1], Other.m_Vec[2], Other.m_Vec[3]);
    Vector<RF_Type::Float64, 3> v3 = v1.CrossProduct(v2);
    QuatF64 q(0, v3[0], v3[1], v3[2]);
    return q;
}

QuatF64 QuatF64::Slerp(const QuatF64& Other, RF_Type::Float64 t)
{
    QuatF64 ret;
    RF_Type::Float64 cs = DotProduct(Other);
    RF_Type::Float64 angle = RF_Math::Float64::ACos(cs);

    if(RF_Math::Float64::FAbs(angle) > static_cast<RF_Type::Float64>(0))
    {
        RF_Type::Float64 sn = RF_Math::Float64::Sin(angle);
        RF_Type::Float64 invSn = static_cast<RF_Type::Float64>(1) / sn;
        RF_Type::Float64 tAngle = t*angle;
        RF_Type::Float64 coeff0 = RF_Math::Float64::Sin(angle - tAngle)*invSn;
        RF_Type::Float64 coeff1 = RF_Math::Float64::Sin(tAngle)*invSn;

        ret[0] = coeff0*m_Vec[0] + coeff1*Other.m_Vec[0];
        ret[1] = coeff0*m_Vec[1] + coeff1*Other.m_Vec[1];
        ret[2] = coeff0*m_Vec[2] + coeff1*Other.m_Vec[2];
        ret[3] = coeff0*m_Vec[3] + coeff1*Other.m_Vec[3];
    }
    else
    {
        ret[0] = m_Vec[0];
        ret[1] = m_Vec[1];
        ret[2] = m_Vec[2];
        ret[3] = m_Vec[3];
    }

    return ret;
}

void QuatF64::ToAxisAngle(Vector<RF_Type::Float64, 3>& Axis, RF_Type::Float64& Angle)
{
    if(m_Vec[0]>static_cast<RF_Type::Float64>(1))
        Normalize();

    Angle = RF_Math::Float64::RadToDeg(static_cast<RF_Type::Float64>(2) * RF_Math::Float64::ACos(m_Vec[0]));
    RF_Type::Float64 s = RF_Math::Float64::Sqrt(static_cast<RF_Type::Float64>(1) - m_Vec[0] * m_Vec[0]);

    if(RF_Math::Float64::EPSILION<s)
    {
        Axis[0] = m_Vec[1];
        Axis[1] = m_Vec[2];
        Axis[2] = m_Vec[3];
    }
    else
    {
        Axis[0] = m_Vec[1] / s;
        Axis[1] = m_Vec[2] / s;
        Axis[2] = m_Vec[3] / s;
    }
}

Vector<RF_Type::Float64, 3> QuatF64::GetAxis()
{
    Vector<RF_Type::Float64, 3> axis;
    axis[0] = m_Vec[1];
    axis[1] = m_Vec[2];
    axis[2] = m_Vec[3];
    return axis;
}

RF_Type::Float64 QuatF64::GetAngle()
{
    return m_Vec[0];
}

Matrix<RF_Type::Float64, 3, 3> QuatF64::AsRotationMatrix()
{
    RF_Type::Float64 twoX = static_cast<RF_Type::Float64>(2) * m_Vec[1];
    RF_Type::Float64 twoY = static_cast<RF_Type::Float64>(2) * m_Vec[2];
    RF_Type::Float64 twoZ = static_cast<RF_Type::Float64>(2) * m_Vec[3];
    RF_Type::Float64 twoWX = twoX*m_Vec[0];
    RF_Type::Float64 twoWY = twoY*m_Vec[0];
    RF_Type::Float64 twoWZ = twoZ*m_Vec[0];
    RF_Type::Float64 twoXX = twoX*m_Vec[1];
    RF_Type::Float64 twoXY = twoY*m_Vec[1];
    RF_Type::Float64 twoXZ = twoZ*m_Vec[1];
    RF_Type::Float64 twoYY = twoY*m_Vec[2];
    RF_Type::Float64 twoYZ = twoZ*m_Vec[2];
    RF_Type::Float64 twoZZ = twoZ*m_Vec[3];

    Matrix<RF_Type::Float64, 3, 3> rot;
    rot[0] = static_cast<RF_Type::Float64>(1) - (twoYY + twoZZ);
    rot[1] = twoXY - twoWZ;
    rot[2] = twoXZ + twoWY;
    rot[3] = twoXY + twoWZ;
    rot[4] = static_cast<RF_Type::Float64>(1) - (twoXX + twoZZ);
    rot[5] = twoYZ - twoWX;
    rot[6] = twoXZ - twoWY;
    rot[7] = twoYZ + twoWX;
    rot[8] = static_cast<RF_Type::Float64>(1) - (twoXX + twoYY);
    return rot;
}

Matrix<RF_Type::Float64, 4, 4> QuatF64::AsMatrix()const
{
    RF_Type::Float64 twoX = static_cast<RF_Type::Float64>(2) * m_Vec[1];
    RF_Type::Float64 twoY = static_cast<RF_Type::Float64>(2) * m_Vec[2];
    RF_Type::Float64 twoZ = static_cast<RF_Type::Float64>(2) * m_Vec[3];
    RF_Type::Float64 twoWX = twoX*m_Vec[0];
    RF_Type::Float64 twoWY = twoY*m_Vec[0];
    RF_Type::Float64 twoWZ = twoZ*m_Vec[0];
    RF_Type::Float64 twoXX = twoX*m_Vec[1];
    RF_Type::Float64 twoXY = twoY*m_Vec[1];
    RF_Type::Float64 twoXZ = twoZ*m_Vec[1];
    RF_Type::Float64 twoYY = twoY*m_Vec[2];
    RF_Type::Float64 twoYZ = twoZ*m_Vec[2];
    RF_Type::Float64 twoZZ = twoZ*m_Vec[3];

    Matrix<RF_Type::Float64, 4, 4> rot;
    rot[0] = static_cast<RF_Type::Float64>(1) - (twoYY + twoZZ);
    rot[1] = twoXY - twoWZ;
    rot[2] = twoXZ + twoWY;
    rot[3] = static_cast<RF_Type::Float64>(0);
    rot[4] = twoXY + twoWZ;
    rot[5] = static_cast<RF_Type::Float64>(1) - (twoXX + twoZZ);
    rot[6] = twoYZ - twoWX;
    rot[7] = static_cast<RF_Type::Float64>(0);
    rot[8] = twoXZ - twoWY;
    rot[9] = twoYZ + twoWX;
    rot[10] = static_cast<RF_Type::Float64>(1) - (twoXX + twoYY);
    rot[11] = static_cast<RF_Type::Float64>(0);
    rot[12] = static_cast<RF_Type::Float64>(0);
    rot[13] = static_cast<RF_Type::Float64>(0);
    rot[14] = static_cast<RF_Type::Float64>(0);
    rot[15] = static_cast<RF_Type::Float64>(1);
    return rot;
}

RF_Type::Float64& QuatF64::operator[](const RF_Type::UInt32 Index)
{
    RF_ASSERT(Index<4, "Index out of bound.");
    return m_Vec[Index];
}

const RF_Type::Float64 QuatF64::operator[](const RF_Type::UInt32 Index)const
{
    RF_ASSERT(Index<4, "Index out of bound.");
    return m_Vec[Index];
}

}
