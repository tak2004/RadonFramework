/*
*
* THIS FILE IS GENERATED FROM build/code_templates/Quaternion.cxx !!!
*
*/
#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Geometry/@ClassName@.hpp"
#include "RadonFramework/Math/@MathType@.hpp"

namespace RadonFramework { namespace Math { namespace Geometry {

const @ClassName@ @ClassName@::Identity;

@ClassName@::@ClassName@()
{
    m_Vec[0] = 1;
    m_Vec[1] = 0;
    m_Vec[2] = 0;
    m_Vec[3] = 0;
}

@ClassName@::@ClassName@(const @ClassName@& Copy):m_Vec(Copy.m_Vec)
{}

@ClassName@& @ClassName@::operator=(const @ClassName@& Copy)
{
    m_Vec = Copy.m_Vec;
        return *this;
}

@ClassName@::@ClassName@(const @ClassType@ Alpha, const Vector<@ClassType@, 3>& Direction)
{
    @ClassType@ a = RF_Math::@MathType@::DegToRad(Alpha*static_cast<@ClassType@>(0.5));
    Assert(Direction.Length() >= RF_Math::@MathType@::EPSILION, "Invalid parameter.");
    @ClassType@ s = RF_Math::@MathType@::Sin(a);
    m_Vec[0] = RF_Math::@MathType@::Cos(a);
    m_Vec[1] = s*Direction[0];
    m_Vec[2] = s*Direction[1];
    m_Vec[3] = s*Direction[2];
}

@ClassName@::@ClassName@(const @ClassType@ w, const @ClassType@ X, const @ClassType@ Y, const @ClassType@ Z)
{
    m_Vec[0] = w;
    m_Vec[1] = X;
    m_Vec[2] = Y;
    m_Vec[3] = Z;
}

@ClassName@::@ClassName@(const Vector<@ClassType@, 3>& Direction)
{
    Vector<@ClassType@, 3> up(0, 1, 0);
    Vector<@ClassType@, 3> right(up.CrossProduct(Direction));
    up = Direction.CrossProduct(right);

    Matrix<@ClassType@, 3, 3> rotmat;
    rotmat.SetColumn(0, right);
    rotmat.SetColumn(1, up);
    rotmat.SetColumn(2, Direction);
    rotmat.Transpose();//setcolum is faster as setrow
    m_Vec = @ClassName@(rotmat).m_Vec;
    /*m_Vec[0]=Math::Sqrt(1.0+rotmat[0]+rotmat[3]+rotmat[6])/2.0;
    @ClassType@ scale=m_Vec[0]*4.0;
    m_Vec[1]=(rotmat[7]-rotmat[5])/scale;
    m_Vec[2]=(rotmat[2]-rotmat[6])/scale;
    m_Vec[3]=(rotmat[3]-rotmat[1])/scale;*/
}

@ClassName@::@ClassName@(const Matrix<@ClassType@, 3, 3>& RotationMatrix)
{
    @ClassType@ tr = RotationMatrix[0] + RotationMatrix[4] + RotationMatrix[8];
    @ClassType@ s;
    if(tr >= 0.0)
    {
        s = RF_Math::@MathType@::Sqrt(tr + static_cast<@ClassType@>(1))*static_cast<@ClassType@>(2);
        m_Vec[0] = static_cast<@ClassType@>(0.25)*s;
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
                s = RF_Math::@MathType@::Sqrt(RotationMatrix[0] - (RotationMatrix[4] + RotationMatrix[8]) + static_cast<@ClassType@>(1.0));
                m_Vec[1] = static_cast<@ClassType@>(0.5)*s;
                s = static_cast<@ClassType@>(0.5) / s;
                m_Vec[2] = (RotationMatrix[1] + RotationMatrix[3])*s;
                m_Vec[3] = (RotationMatrix[6] + RotationMatrix[2])*s;
                m_Vec[0] = (RotationMatrix[7] + RotationMatrix[2])*s;
                break;
            case 4:
                s = RF_Math::@MathType@::Sqrt(RotationMatrix[4] - (RotationMatrix[8] + RotationMatrix[0]) + static_cast<@ClassType@>(1.0));
                m_Vec[2] = static_cast<@ClassType@>(0.5)*s;
                s = static_cast<@ClassType@>(0.5) / s;
                m_Vec[3] = (RotationMatrix[5] + RotationMatrix[7])*s;
                m_Vec[1] = (RotationMatrix[1] + RotationMatrix[3])*s;
                m_Vec[0] = (RotationMatrix[2] + RotationMatrix[6])*s;
                break;
            case 8:
                s = RF_Math::@MathType@::Sqrt(RotationMatrix[8] - (RotationMatrix[0] + RotationMatrix[4]) + static_cast<@ClassType@>(1.0));
                m_Vec[3] = static_cast<@ClassType@>(0.5)*s;
                s = static_cast<@ClassType@>(0.5) / s;
                m_Vec[1] = (RotationMatrix[6] + RotationMatrix[2])*s;
                m_Vec[2] = (RotationMatrix[5] + RotationMatrix[7])*s;
                m_Vec[0] = (RotationMatrix[3] + RotationMatrix[1])*s;
                break;
        }
    }
}

@ClassName@::@ClassName@(const @ClassType@ Roll, const @ClassType@ Pitch, const @ClassType@ Yaw)
{
    @ClassType@ r = RF_Math::@MathType@::DegToRad(Roll * static_cast<@ClassType@>(0.5));
    @ClassType@ p = RF_Math::@MathType@::DegToRad(Pitch * static_cast<@ClassType@>(0.5));
    @ClassType@ y = RF_Math::@MathType@::DegToRad(Yaw * static_cast<@ClassType@>(0.5));

    @ClassType@ sx = RF_Math::@MathType@::Sin(r);
    @ClassType@ cx = RF_Math::@MathType@::Cos(r);

    @ClassType@ sy = RF_Math::@MathType@::Sin(p);
    @ClassType@ cy = RF_Math::@MathType@::Cos(p);

    @ClassType@ sz = RF_Math::@MathType@::Sin(y);
    @ClassType@ cz = RF_Math::@MathType@::Cos(y);

    m_Vec[0] = (cx*cy*cz) - (sx*sy*sz);
    m_Vec[1] = (sx*sy*cz) + (cx*cy*sz);
    m_Vec[2] = (sx*cy*cz) + (cx*sy*sz);
    m_Vec[3] = (cx*sy*cz) - (sx*cy*sz);
}

@ClassName@ @ClassName@::operator+(const @ClassName@& Other)
{
    @ClassName@ quat(*this);
    quat.m_Vec += Other.m_Vec;
        return quat;
}

@ClassName@ @ClassName@::operator-(const @ClassName@& Other)
{
    @ClassName@ quat(*this);
    quat.m_Vec -= Other.m_Vec;
        return quat;
}

@ClassName@ @ClassName@::operator*(const @ClassName@& Other)
{
    @ClassName@ quat;
    quat.m_Vec[0] = m_Vec[0] * Other.m_Vec[0] - m_Vec[1] * Other.m_Vec[1] - m_Vec[2] * Other.m_Vec[2] - m_Vec[3] * Other.m_Vec[3];
    quat.m_Vec[1] = m_Vec[0] * Other.m_Vec[1] + m_Vec[1] * Other.m_Vec[0] + m_Vec[2] * Other.m_Vec[3] - m_Vec[3] * Other.m_Vec[2];
    quat.m_Vec[2] = m_Vec[0] * Other.m_Vec[2] + m_Vec[2] * Other.m_Vec[0] + m_Vec[3] * Other.m_Vec[1] - m_Vec[1] * Other.m_Vec[3];
    quat.m_Vec[3] = m_Vec[0] * Other.m_Vec[3] + m_Vec[3] * Other.m_Vec[0] + m_Vec[1] * Other.m_Vec[2] - m_Vec[2] * Other.m_Vec[1];
    return quat;
}

@ClassName@ @ClassName@::operator/(const @ClassName@& Other)
{
    @ClassName@ quat(*this);
    quat *= Other.Inverse();
    return quat;
}

@ClassName@& @ClassName@::operator+=(const @ClassName@& Other)
{
    m_Vec += Other.m_Vec;
        return *this;
}

@ClassName@& @ClassName@::operator-=(const @ClassName@& Other)
{
    m_Vec -= Other.m_Vec;
        return *this;
}

@ClassName@& @ClassName@::operator*=(const @ClassName@& Other)
{
    m_Vec = (*this*Other).m_Vec;
        return *this;
}

@ClassName@& @ClassName@::operator/=(const @ClassName@& Other)
{
    m_Vec = (*this*Other.Inverse()).m_Vec;
        return *this;
}

@ClassName@& @ClassName@::SetIdentity()
{
    m_Vec = Identity.m_Vec;
        return *this;
}

@ClassName@& @ClassName@::Invert()
{
    @ClassType@ val = SquareLength();
    Assert(val != static_cast<@ClassType@>(0.0), "Invalid value.");
    Conjugate().m_Vec /= val;
    return *this;
}

@ClassName@& @ClassName@::Conjugate()
{
    Vector<@ClassType@, 4> vec(1, -1, -1, -1);
    m_Vec *= vec;
    return *this;
}

@ClassName@& @ClassName@::Normalize()
{
    @ClassType@ v = Length();
    m_Vec /= v;
    return *this;
}

@ClassType@ @ClassName@::DotProduct(const @ClassName@& Other)
{
    return m_Vec[0] * Other.m_Vec[0] +
    m_Vec[1] * Other.m_Vec[1] +
    m_Vec[2] * Other.m_Vec[2] +
    m_Vec[3] * Other.m_Vec[3];
}

@ClassName@ @ClassName@::Inverse()const
{
    @ClassName@ quat(*this);
    quat.Invert();
    return quat;
}

Vector<@ClassType@, 4> @ClassName@::operator*(const Vector<@ClassType@, 4>& Vec)
{
    Vector<@ClassType@, 3> v(Vec[0], Vec[1], Vec[2]);
    v = (*this)*v;
    Vector<@ClassType@, 4> res(v[0], v[1], v[2], Vec[3]);
    return res;
}

Vector<@ClassType@, 3> @ClassName@::operator*(const Vector<@ClassType@, 3>& Vec)
{
    Vector<@ClassType@, 3> vecNormalized(Vec);
    vecNormalized.Normalize();
    @ClassName@ quatFromVec(0, vecNormalized[0], vecNormalized[1], vecNormalized[2]);
    @ClassName@ q(*this);
    q.Conjugate();
    q = quatFromVec * q;
    q = (*this) * q;
    return q.GetAxis();
}

RF_Type::Bool @ClassName@::operator==(const @ClassName@& Other)
{
    return m_Vec == Other.m_Vec;
}

RF_Type::Bool @ClassName@::operator!=(const @ClassName@& Other)
{
    return m_Vec != Other.m_Vec;
}

@ClassName@ @ClassName@::Exponential()
{
    @ClassName@ result;
    @ClassType@ angle = RF_Math::@MathType@::Sqrt(m_Vec[1] * m_Vec[1] +
    m_Vec[2] * m_Vec[2] +
    m_Vec[3] * m_Vec[3]);
    @ClassType@ sn = RF_Math::@MathType@::Sin(angle);
    result.m_Vec[0] = RF_Math::@MathType@::Cos(angle);

    RF_Type::UInt32 i;
    if(RF_Math::@MathType@::FAbs(sn) > static_cast<@ClassType@>(0))
    {
        @ClassType@ coeff = sn / angle;
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

RF_Type::Bool @ClassName@::IsInfinite()
{
    return RF_Math::@MathType@::IsInfinity(m_Vec[0]) ||
        RF_Math::@MathType@::IsInfinity(m_Vec[1]) ||
        RF_Math::@MathType@::IsInfinity(m_Vec[2]) ||
        RF_Math::@MathType@::IsInfinity(m_Vec[3]);
}

RF_Type::Bool @ClassName@::IsNaN()
{
    return RF_Math::@MathType@::IsNaN(m_Vec[0]) ||
        RF_Math::@MathType@::IsNaN(m_Vec[1]) ||
        RF_Math::@MathType@::IsNaN(m_Vec[2]) ||
        RF_Math::@MathType@::IsNaN(m_Vec[3]);
}

@ClassName@ @ClassName@::LengthAsQuat()
{
    @ClassName@ q;
    @ClassType@ len = Length();
    for(RF_Type::UInt32 i = 0; i<4; ++i)
        q[i] = len;
    return q;
}

@ClassType@ @ClassName@::Length()
{
    if(m_Vec[0] == 0.0 && m_Vec[1] == 0.0 &&
    m_Vec[2] == 0.0 && m_Vec[3] == 0.0)
        return 0.0;
    return RF_Math::@MathType@::Sqrt((m_Vec*m_Vec).Sum());;
}

@ClassName@ @ClassName@::SquareLengthAsQuat()
{
    @ClassName@ q;
    @ClassType@ sqrlen = SquareLength();
    for(RF_Type::UInt32 i = 0; i<4; ++i)
        q[i] = sqrlen;
    return q;
}

@ClassType@ @ClassName@::SquareLength()
{
    @ClassType@ len = Length();
    len *= len;
    return len;
}

@ClassName@ @ClassName@::CrossProduct(const @ClassName@& Other)
{
    Vector<@ClassType@, 3> v1(m_Vec[1], m_Vec[2], m_Vec[3]);
    Vector<@ClassType@, 3> v2(Other.m_Vec[1], Other.m_Vec[2], Other.m_Vec[3]);
    Vector<@ClassType@, 3> v3 = v1.CrossProduct(v2);
    @ClassName@ q(0, v3[0], v3[1], v3[2]);
    return q;
}

@ClassName@ @ClassName@::Slerp(const @ClassName@& Other, @ClassType@ t)
{
    @ClassName@ ret;
    @ClassType@ cs = DotProduct(Other);
    @ClassType@ angle = RF_Math::@MathType@::ACos(cs);

    if(RF_Math::@MathType@::FAbs(angle) > static_cast<@ClassType@>(0))
    {
        @ClassType@ sn = RF_Math::@MathType@::Sin(angle);
        @ClassType@ invSn = static_cast<@ClassType@>(1) / sn;
        @ClassType@ tAngle = t*angle;
        @ClassType@ coeff0 = RF_Math::@MathType@::Sin(angle - tAngle)*invSn;
        @ClassType@ coeff1 = RF_Math::@MathType@::Sin(tAngle)*invSn;

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

void @ClassName@::ToAxisAngle(Vector<@ClassType@, 3>& Axis, @ClassType@& Angle)
{
    if(m_Vec[0]>static_cast<@ClassType@>(1))
        Normalize();

    Angle = RF_Math::@MathType@::RadToDeg(static_cast<@ClassType@>(2) * RF_Math::@MathType@::ACos(m_Vec[0]));
    @ClassType@ s = RF_Math::@MathType@::Sqrt(static_cast<@ClassType@>(1) - m_Vec[0] * m_Vec[0]);

    if(RF_Math::@MathType@::EPSILION<s)
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

Vector<@ClassType@, 3> @ClassName@::GetAxis()
{
    Vector<@ClassType@, 3> axis;
    axis[0] = m_Vec[1];
    axis[1] = m_Vec[2];
    axis[2] = m_Vec[3];
    return axis;
}

@ClassType@ @ClassName@::GetAngle()
{
    return m_Vec[0];
}

Matrix<@ClassType@, 3, 3> @ClassName@::AsRotationMatrix()
{
    @ClassType@ twoX = static_cast<@ClassType@>(2) * m_Vec[1];
    @ClassType@ twoY = static_cast<@ClassType@>(2) * m_Vec[2];
    @ClassType@ twoZ = static_cast<@ClassType@>(2) * m_Vec[3];
    @ClassType@ twoWX = twoX*m_Vec[0];
    @ClassType@ twoWY = twoY*m_Vec[0];
    @ClassType@ twoWZ = twoZ*m_Vec[0];
    @ClassType@ twoXX = twoX*m_Vec[1];
    @ClassType@ twoXY = twoY*m_Vec[1];
    @ClassType@ twoXZ = twoZ*m_Vec[1];
    @ClassType@ twoYY = twoY*m_Vec[2];
    @ClassType@ twoYZ = twoZ*m_Vec[2];
    @ClassType@ twoZZ = twoZ*m_Vec[3];

    Matrix<@ClassType@, 3, 3> rot;
    rot[0] = static_cast<@ClassType@>(1) - (twoYY + twoZZ);
    rot[1] = twoXY - twoWZ;
    rot[2] = twoXZ + twoWY;
    rot[3] = twoXY + twoWZ;
    rot[4] = static_cast<@ClassType@>(1) - (twoXX + twoZZ);
    rot[5] = twoYZ - twoWX;
    rot[6] = twoXZ - twoWY;
    rot[7] = twoYZ + twoWX;
    rot[8] = static_cast<@ClassType@>(1) - (twoXX + twoYY);
    return rot;
}

Matrix<@ClassType@, 4, 4> @ClassName@::AsMatrix()const
{
    @ClassType@ twoX = static_cast<@ClassType@>(2) * m_Vec[1];
    @ClassType@ twoY = static_cast<@ClassType@>(2) * m_Vec[2];
    @ClassType@ twoZ = static_cast<@ClassType@>(2) * m_Vec[3];
    @ClassType@ twoWX = twoX*m_Vec[0];
    @ClassType@ twoWY = twoY*m_Vec[0];
    @ClassType@ twoWZ = twoZ*m_Vec[0];
    @ClassType@ twoXX = twoX*m_Vec[1];
    @ClassType@ twoXY = twoY*m_Vec[1];
    @ClassType@ twoXZ = twoZ*m_Vec[1];
    @ClassType@ twoYY = twoY*m_Vec[2];
    @ClassType@ twoYZ = twoZ*m_Vec[2];
    @ClassType@ twoZZ = twoZ*m_Vec[3];

    Matrix<@ClassType@, 4, 4> rot;
    rot[0] = static_cast<@ClassType@>(1) - (twoYY + twoZZ);
    rot[1] = twoXY - twoWZ;
    rot[2] = twoXZ + twoWY;
    rot[3] = static_cast<@ClassType@>(0);
    rot[4] = twoXY + twoWZ;
    rot[5] = static_cast<@ClassType@>(1) - (twoXX + twoZZ);
    rot[6] = twoYZ - twoWX;
    rot[7] = static_cast<@ClassType@>(0);
    rot[8] = twoXZ - twoWY;
    rot[9] = twoYZ + twoWX;
    rot[10] = static_cast<@ClassType@>(1) - (twoXX + twoYY);
    rot[11] = static_cast<@ClassType@>(0);
    rot[12] = static_cast<@ClassType@>(0);
    rot[13] = static_cast<@ClassType@>(0);
    rot[14] = static_cast<@ClassType@>(0);
    rot[15] = static_cast<@ClassType@>(1);
    return rot;
}

@ClassType@& @ClassName@::operator[](const RF_Type::UInt32 Index)
{
    Assert(Index<4, "Index out of bound.");
    return m_Vec[Index];
}

const @ClassType@ @ClassName@::operator[](const RF_Type::UInt32 Index)const
{
    Assert(Index<4, "Index out of bound.");
    return m_Vec[Index];
}

} } }