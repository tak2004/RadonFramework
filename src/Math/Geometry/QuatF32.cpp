/*
*
* THIS FILE IS GENERATED FROM build/code_templates/Quaternion.cxx !!!
*
*/
#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Geometry/QuatF32.hpp"
#include "RadonFramework/Math/Float32.hpp"

namespace RadonFramework { namespace Math { namespace Geometry {

const QuatF32 QuatF32::Identity;

QuatF32::QuatF32()
{
    m_Vec[0] = 1;
    m_Vec[1] = 0;
    m_Vec[2] = 0;
    m_Vec[3] = 0;
}

QuatF32::QuatF32(const QuatF32& Copy):m_Vec(Copy.m_Vec)
{}

QuatF32& QuatF32::operator=(const QuatF32& Copy)
{
    m_Vec = Copy.m_Vec;
        return *this;
}

QuatF32::QuatF32(const RF_Type::Float32 Alpha, const Vector<RF_Type::Float32, 3>& Direction)
{
    RF_Type::Float32 a = RF_Math::Float32::DegToRad(Alpha*static_cast<RF_Type::Float32>(0.5));
    Assert(Direction.Length() >= RF_Math::Float32::EPSILION, "Invalid parameter.");
    RF_Type::Float32 s = RF_Math::Float32::Sin(a);
    m_Vec[0] = RF_Math::Float32::Cos(a);
    m_Vec[1] = s*Direction[0];
    m_Vec[2] = s*Direction[1];
    m_Vec[3] = s*Direction[2];
}

QuatF32::QuatF32(const RF_Type::Float32 w, const RF_Type::Float32 X, const RF_Type::Float32 Y, const RF_Type::Float32 Z)
{
    m_Vec[0] = w;
    m_Vec[1] = X;
    m_Vec[2] = Y;
    m_Vec[3] = Z;
}

QuatF32::QuatF32(const Vector<RF_Type::Float32, 3>& Direction)
{
    Vector<RF_Type::Float32, 3> up(0, 1, 0);
    Vector<RF_Type::Float32, 3> right(up.CrossProduct(Direction));
    up = Direction.CrossProduct(right);

    Matrix<RF_Type::Float32, 3, 3> rotmat;
    rotmat.SetColumn(0, right);
    rotmat.SetColumn(1, up);
    rotmat.SetColumn(2, Direction);
    rotmat.Transpose();//setcolum is faster as setrow
    m_Vec = QuatF32(rotmat).m_Vec;
    /*m_Vec[0]=Math::Sqrt(1.0+rotmat[0]+rotmat[3]+rotmat[6])/2.0;
    RF_Type::Float32 scale=m_Vec[0]*4.0;
    m_Vec[1]=(rotmat[7]-rotmat[5])/scale;
    m_Vec[2]=(rotmat[2]-rotmat[6])/scale;
    m_Vec[3]=(rotmat[3]-rotmat[1])/scale;*/
}

QuatF32::QuatF32(const Matrix<RF_Type::Float32, 3, 3>& RotationMatrix)
{
    RF_Type::Float32 tr = RotationMatrix[0] + RotationMatrix[4] + RotationMatrix[8];
    RF_Type::Float32 s;
    if(tr >= 0.0)
    {
        s = RF_Math::Float32::Sqrt(tr + static_cast<RF_Type::Float32>(1))*static_cast<RF_Type::Float32>(2);
        m_Vec[0] = static_cast<RF_Type::Float32>(0.25)*s;
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
                s = RF_Math::Float32::Sqrt(RotationMatrix[0] - (RotationMatrix[4] + RotationMatrix[8]) + static_cast<RF_Type::Float32>(1.0));
                m_Vec[1] = static_cast<RF_Type::Float32>(0.5)*s;
                s = static_cast<RF_Type::Float32>(0.5) / s;
                m_Vec[2] = (RotationMatrix[1] + RotationMatrix[3])*s;
                m_Vec[3] = (RotationMatrix[6] + RotationMatrix[2])*s;
                m_Vec[0] = (RotationMatrix[7] + RotationMatrix[2])*s;
                break;
            case 4:
                s = RF_Math::Float32::Sqrt(RotationMatrix[4] - (RotationMatrix[8] + RotationMatrix[0]) + static_cast<RF_Type::Float32>(1.0));
                m_Vec[2] = static_cast<RF_Type::Float32>(0.5)*s;
                s = static_cast<RF_Type::Float32>(0.5) / s;
                m_Vec[3] = (RotationMatrix[5] + RotationMatrix[7])*s;
                m_Vec[1] = (RotationMatrix[1] + RotationMatrix[3])*s;
                m_Vec[0] = (RotationMatrix[2] + RotationMatrix[6])*s;
                break;
            case 8:
                s = RF_Math::Float32::Sqrt(RotationMatrix[8] - (RotationMatrix[0] + RotationMatrix[4]) + static_cast<RF_Type::Float32>(1.0));
                m_Vec[3] = static_cast<RF_Type::Float32>(0.5)*s;
                s = static_cast<RF_Type::Float32>(0.5) / s;
                m_Vec[1] = (RotationMatrix[6] + RotationMatrix[2])*s;
                m_Vec[2] = (RotationMatrix[5] + RotationMatrix[7])*s;
                m_Vec[0] = (RotationMatrix[3] + RotationMatrix[1])*s;
                break;
        }
    }
}

QuatF32::QuatF32(const RF_Type::Float32 Roll, const RF_Type::Float32 Pitch, const RF_Type::Float32 Yaw)
{
    RF_Type::Float32 r = RF_Math::Float32::DegToRad(Roll * static_cast<RF_Type::Float32>(0.5));
    RF_Type::Float32 p = RF_Math::Float32::DegToRad(Pitch * static_cast<RF_Type::Float32>(0.5));
    RF_Type::Float32 y = RF_Math::Float32::DegToRad(Yaw * static_cast<RF_Type::Float32>(0.5));

    RF_Type::Float32 sx = RF_Math::Float32::Sin(r);
    RF_Type::Float32 cx = RF_Math::Float32::Cos(r);

    RF_Type::Float32 sy = RF_Math::Float32::Sin(p);
    RF_Type::Float32 cy = RF_Math::Float32::Cos(p);

    RF_Type::Float32 sz = RF_Math::Float32::Sin(y);
    RF_Type::Float32 cz = RF_Math::Float32::Cos(y);

    m_Vec[0] = (cx*cy*cz) - (sx*sy*sz);
    m_Vec[1] = (sx*sy*cz) + (cx*cy*sz);
    m_Vec[2] = (sx*cy*cz) + (cx*sy*sz);
    m_Vec[3] = (cx*sy*cz) - (sx*cy*sz);
}

QuatF32 QuatF32::operator+(const QuatF32& Other)
{
    QuatF32 quat(*this);
    quat.m_Vec += Other.m_Vec;
        return quat;
}

QuatF32 QuatF32::operator-(const QuatF32& Other)
{
    QuatF32 quat(*this);
    quat.m_Vec -= Other.m_Vec;
        return quat;
}

QuatF32 QuatF32::operator*(const QuatF32& Other)
{
    QuatF32 quat;
    quat.m_Vec[0] = m_Vec[0] * Other.m_Vec[0] - m_Vec[1] * Other.m_Vec[1] - m_Vec[2] * Other.m_Vec[2] - m_Vec[3] * Other.m_Vec[3];
    quat.m_Vec[1] = m_Vec[0] * Other.m_Vec[1] + m_Vec[1] * Other.m_Vec[0] + m_Vec[2] * Other.m_Vec[3] - m_Vec[3] * Other.m_Vec[2];
    quat.m_Vec[2] = m_Vec[0] * Other.m_Vec[2] + m_Vec[2] * Other.m_Vec[0] + m_Vec[3] * Other.m_Vec[1] - m_Vec[1] * Other.m_Vec[3];
    quat.m_Vec[3] = m_Vec[0] * Other.m_Vec[3] + m_Vec[3] * Other.m_Vec[0] + m_Vec[1] * Other.m_Vec[2] - m_Vec[2] * Other.m_Vec[1];
    return quat;
}

QuatF32 QuatF32::operator/(const QuatF32& Other)
{
    QuatF32 quat(*this);
    quat *= Other.Inverse();
    return quat;
}

QuatF32& QuatF32::operator+=(const QuatF32& Other)
{
    m_Vec += Other.m_Vec;
        return *this;
}

QuatF32& QuatF32::operator-=(const QuatF32& Other)
{
    m_Vec -= Other.m_Vec;
        return *this;
}

QuatF32& QuatF32::operator*=(const QuatF32& Other)
{
    m_Vec = (*this*Other).m_Vec;
        return *this;
}

QuatF32& QuatF32::operator/=(const QuatF32& Other)
{
    m_Vec = (*this*Other.Inverse()).m_Vec;
        return *this;
}

QuatF32& QuatF32::SetIdentity()
{
    m_Vec = Identity.m_Vec;
        return *this;
}

QuatF32& QuatF32::Invert()
{
    RF_Type::Float32 val = SquareLength();
    Assert(val != static_cast<RF_Type::Float32>(0.0), "Invalid value.");
    Conjugate().m_Vec /= val;
    return *this;
}

QuatF32& QuatF32::Conjugate()
{
    Vector<RF_Type::Float32, 4> vec(1, -1, -1, -1);
    m_Vec *= vec;
    return *this;
}

QuatF32& QuatF32::Normalize()
{
    RF_Type::Float32 v = Length();
    m_Vec /= v;
    return *this;
}

RF_Type::Float32 QuatF32::DotProduct(const QuatF32& Other)
{
    return m_Vec[0] * Other.m_Vec[0] +
    m_Vec[1] * Other.m_Vec[1] +
    m_Vec[2] * Other.m_Vec[2] +
    m_Vec[3] * Other.m_Vec[3];
}

QuatF32 QuatF32::Inverse()const
{
    QuatF32 quat(*this);
    quat.Invert();
    return quat;
}

Vector<RF_Type::Float32, 4> QuatF32::operator*(const Vector<RF_Type::Float32, 4>& Vec)
{
    Vector<RF_Type::Float32, 3> v(Vec[0], Vec[1], Vec[2]);
    v = (*this)*v;
    Vector<RF_Type::Float32, 4> res(v[0], v[1], v[2], Vec[3]);
    return res;
}

Vector<RF_Type::Float32, 3> QuatF32::operator*(const Vector<RF_Type::Float32, 3>& Vec)
{
    Vector<RF_Type::Float32, 3> vecNormalized(Vec);
    vecNormalized.Normalize();
    QuatF32 quatFromVec(0, vecNormalized[0], vecNormalized[1], vecNormalized[2]);
    QuatF32 q(*this);
    q.Conjugate();
    q = quatFromVec * q;
    q = (*this) * q;
    return q.GetAxis();
}

RF_Type::Bool QuatF32::operator==(const QuatF32& Other)
{
    return m_Vec == Other.m_Vec;
}

RF_Type::Bool QuatF32::operator!=(const QuatF32& Other)
{
    return m_Vec != Other.m_Vec;
}

QuatF32 QuatF32::Exponential()
{
    QuatF32 result;
    RF_Type::Float32 angle = RF_Math::Float32::Sqrt(m_Vec[1] * m_Vec[1] +
    m_Vec[2] * m_Vec[2] +
    m_Vec[3] * m_Vec[3]);
    RF_Type::Float32 sn = RF_Math::Float32::Sin(angle);
    result.m_Vec[0] = RF_Math::Float32::Cos(angle);

    RF_Type::UInt32 i;
    if(RF_Math::Float32::FAbs(sn) > static_cast<RF_Type::Float32>(0))
    {
        RF_Type::Float32 coeff = sn / angle;
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

RF_Type::Bool QuatF32::IsInfinite()
{
    return RF_Math::Float32::IsInfinity(m_Vec[0]) ||
        RF_Math::Float32::IsInfinity(m_Vec[1]) ||
        RF_Math::Float32::IsInfinity(m_Vec[2]) ||
        RF_Math::Float32::IsInfinity(m_Vec[3]);
}

RF_Type::Bool QuatF32::IsNaN()
{
    return RF_Math::Float32::IsNaN(m_Vec[0]) ||
        RF_Math::Float32::IsNaN(m_Vec[1]) ||
        RF_Math::Float32::IsNaN(m_Vec[2]) ||
        RF_Math::Float32::IsNaN(m_Vec[3]);
}

QuatF32 QuatF32::LengthAsQuat()
{
    QuatF32 q;
    RF_Type::Float32 len = Length();
    for(RF_Type::UInt32 i = 0; i<4; ++i)
        q[i] = len;
    return q;
}

RF_Type::Float32 QuatF32::Length()
{
    if(m_Vec[0] == 0.0 && m_Vec[1] == 0.0 &&
    m_Vec[2] == 0.0 && m_Vec[3] == 0.0)
        return 0.0;
    return RF_Math::Float32::Sqrt((m_Vec*m_Vec).Sum());;
}

QuatF32 QuatF32::SquareLengthAsQuat()
{
    QuatF32 q;
    RF_Type::Float32 sqrlen = SquareLength();
    for(RF_Type::UInt32 i = 0; i<4; ++i)
        q[i] = sqrlen;
    return q;
}

RF_Type::Float32 QuatF32::SquareLength()
{
    RF_Type::Float32 len = Length();
    len *= len;
    return len;
}

QuatF32 QuatF32::CrossProduct(const QuatF32& Other)
{
    Vector<RF_Type::Float32, 3> v1(m_Vec[1], m_Vec[2], m_Vec[3]);
    Vector<RF_Type::Float32, 3> v2(Other.m_Vec[1], Other.m_Vec[2], Other.m_Vec[3]);
    Vector<RF_Type::Float32, 3> v3 = v1.CrossProduct(v2);
    QuatF32 q(0, v3[0], v3[1], v3[2]);
    return q;
}

QuatF32 QuatF32::Slerp(const QuatF32& Other, RF_Type::Float32 t)
{
    QuatF32 ret;
    RF_Type::Float32 cs = DotProduct(Other);
    RF_Type::Float32 angle = RF_Math::Float32::ACos(cs);

    if(RF_Math::Float32::FAbs(angle) > static_cast<RF_Type::Float32>(0))
    {
        RF_Type::Float32 sn = RF_Math::Float32::Sin(angle);
        RF_Type::Float32 invSn = static_cast<RF_Type::Float32>(1) / sn;
        RF_Type::Float32 tAngle = t*angle;
        RF_Type::Float32 coeff0 = RF_Math::Float32::Sin(angle - tAngle)*invSn;
        RF_Type::Float32 coeff1 = RF_Math::Float32::Sin(tAngle)*invSn;

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

void QuatF32::ToAxisAngle(Vector<RF_Type::Float32, 3>& Axis, RF_Type::Float32& Angle)
{
    if(m_Vec[0]>static_cast<RF_Type::Float32>(1))
        Normalize();

    Angle = RF_Math::Float32::RadToDeg(static_cast<RF_Type::Float32>(2) * RF_Math::Float32::ACos(m_Vec[0]));
    RF_Type::Float32 s = RF_Math::Float32::Sqrt(static_cast<RF_Type::Float32>(1) - m_Vec[0] * m_Vec[0]);

    if(RF_Math::Float32::EPSILION<s)
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

Vector<RF_Type::Float32, 3> QuatF32::GetAxis()
{
    Vector<RF_Type::Float32, 3> axis;
    axis[0] = m_Vec[1];
    axis[1] = m_Vec[2];
    axis[2] = m_Vec[3];
    return axis;
}

RF_Type::Float32 QuatF32::GetAngle()
{
    return m_Vec[0];
}

Matrix<RF_Type::Float32, 3, 3> QuatF32::AsRotationMatrix()
{
    RF_Type::Float32 twoX = static_cast<RF_Type::Float32>(2) * m_Vec[1];
    RF_Type::Float32 twoY = static_cast<RF_Type::Float32>(2) * m_Vec[2];
    RF_Type::Float32 twoZ = static_cast<RF_Type::Float32>(2) * m_Vec[3];
    RF_Type::Float32 twoWX = twoX*m_Vec[0];
    RF_Type::Float32 twoWY = twoY*m_Vec[0];
    RF_Type::Float32 twoWZ = twoZ*m_Vec[0];
    RF_Type::Float32 twoXX = twoX*m_Vec[1];
    RF_Type::Float32 twoXY = twoY*m_Vec[1];
    RF_Type::Float32 twoXZ = twoZ*m_Vec[1];
    RF_Type::Float32 twoYY = twoY*m_Vec[2];
    RF_Type::Float32 twoYZ = twoZ*m_Vec[2];
    RF_Type::Float32 twoZZ = twoZ*m_Vec[3];

    Matrix<RF_Type::Float32, 3, 3> rot;
    rot[0] = static_cast<RF_Type::Float32>(1) - (twoYY + twoZZ);
    rot[1] = twoXY - twoWZ;
    rot[2] = twoXZ + twoWY;
    rot[3] = twoXY + twoWZ;
    rot[4] = static_cast<RF_Type::Float32>(1) - (twoXX + twoZZ);
    rot[5] = twoYZ - twoWX;
    rot[6] = twoXZ - twoWY;
    rot[7] = twoYZ + twoWX;
    rot[8] = static_cast<RF_Type::Float32>(1) - (twoXX + twoYY);
    return rot;
}

Matrix<RF_Type::Float32, 4, 4> QuatF32::AsMatrix()const
{
    RF_Type::Float32 twoX = static_cast<RF_Type::Float32>(2) * m_Vec[1];
    RF_Type::Float32 twoY = static_cast<RF_Type::Float32>(2) * m_Vec[2];
    RF_Type::Float32 twoZ = static_cast<RF_Type::Float32>(2) * m_Vec[3];
    RF_Type::Float32 twoWX = twoX*m_Vec[0];
    RF_Type::Float32 twoWY = twoY*m_Vec[0];
    RF_Type::Float32 twoWZ = twoZ*m_Vec[0];
    RF_Type::Float32 twoXX = twoX*m_Vec[1];
    RF_Type::Float32 twoXY = twoY*m_Vec[1];
    RF_Type::Float32 twoXZ = twoZ*m_Vec[1];
    RF_Type::Float32 twoYY = twoY*m_Vec[2];
    RF_Type::Float32 twoYZ = twoZ*m_Vec[2];
    RF_Type::Float32 twoZZ = twoZ*m_Vec[3];

    Matrix<RF_Type::Float32, 4, 4> rot;
    rot[0] = static_cast<RF_Type::Float32>(1) - (twoYY + twoZZ);
    rot[1] = twoXY - twoWZ;
    rot[2] = twoXZ + twoWY;
    rot[3] = static_cast<RF_Type::Float32>(0);
    rot[4] = twoXY + twoWZ;
    rot[5] = static_cast<RF_Type::Float32>(1) - (twoXX + twoZZ);
    rot[6] = twoYZ - twoWX;
    rot[7] = static_cast<RF_Type::Float32>(0);
    rot[8] = twoXZ - twoWY;
    rot[9] = twoYZ + twoWX;
    rot[10] = static_cast<RF_Type::Float32>(1) - (twoXX + twoYY);
    rot[11] = static_cast<RF_Type::Float32>(0);
    rot[12] = static_cast<RF_Type::Float32>(0);
    rot[13] = static_cast<RF_Type::Float32>(0);
    rot[14] = static_cast<RF_Type::Float32>(0);
    rot[15] = static_cast<RF_Type::Float32>(1);
    return rot;
}

RF_Type::Float32& QuatF32::operator[](const RF_Type::UInt32 Index)
{
    Assert(Index<4, "Index out of bound.");
    return m_Vec[Index];
}

const RF_Type::Float32 QuatF32::operator[](const RF_Type::UInt32 Index)const
{
    Assert(Index<4, "Index out of bound.");
    return m_Vec[Index];
}

} } }
