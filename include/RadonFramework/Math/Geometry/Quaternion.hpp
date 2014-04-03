#ifndef RF_MATH_GEOMETRY_QUATERNION_HPP
#define RF_MATH_GEOMETRY_QUATERNION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Math.hpp>
#include <RadonFramework/Math/Geometry/Vector.hpp>
#include <RadonFramework/Math/Geometry/Matrix.hpp>
#include <RadonFramework/Diagnostics/Debugging/Assert.hpp>

namespace RadonFramework
{
    namespace Math
    {
        namespace Geometry
        {
            template<typename T>
            class Quaternion
            {
                public:
                    static const Quaternion Identity;

                    Quaternion(){
                        m_Quaternion[0]=(T)1;
                        m_Quaternion[1]=(T)0;
                        m_Quaternion[2]=(T)0;
                        m_Quaternion[3]=(T)0;
                    }

                    Quaternion(const Quaternion& Copy):m_Quaternion(Copy.m_Quaternion){}

                    Quaternion& operator=(const Quaternion& Copy)
                    {
                        m_Quaternion=Copy.m_Quaternion;
                        return *this;
                    }

                    Quaternion(const T Alpha,const Vector<T,3>& Direction)
                    {
                        T a=RadonFramework::Math::Math<T>::DegToRad(Alpha*static_cast<T>(0.5));
                        Assert(Direction.Length()>=RadonFramework::Math::Math<T>::EPSILION,"Invalid parameter.");
                        T s=RadonFramework::Math::Math<T>::Sin(a);
                        m_Quaternion[0]=RadonFramework::Math::Math<T>::Cos(a);
                        m_Quaternion[1]=s*Direction[0];
                        m_Quaternion[2]=s*Direction[1];
                        m_Quaternion[3]=s*Direction[2];
                    }

                    Quaternion(const T w,const T X,const T Y,const T Z)
                    {
                        m_Quaternion[0]=w;
                        m_Quaternion[1]=X;
                        m_Quaternion[2]=Y;
                        m_Quaternion[3]=Z;
                    }

                    Quaternion(const Vector<T,3>& Direction)
                    {
                        Vector<T,3> up(0,1,0);
                        Vector<T,3> right(up.CrossProduct(Direction));
                        up=Direction.CrossProduct(right);

                        Matrix<T,3,3> rotmat;
                        rotmat.SetColumn(0,right);
                        rotmat.SetColumn(1,up);
                        rotmat.SetColumn(2,Direction);
					    rotmat.Transpose();//setcolum is faster as setrow
					    m_Quaternion=Quaternion(rotmat).m_Quaternion;
					    /*m_Quaternion[0]=Math<T>::Sqrt(1.0+rotmat[0]+rotmat[3]+rotmat[6])/2.0;
					    T scale=m_Quaternion[0]*4.0;
					    m_Quaternion[1]=(rotmat[7]-rotmat[5])/scale;
					    m_Quaternion[2]=(rotmat[2]-rotmat[6])/scale;
					    m_Quaternion[3]=(rotmat[3]-rotmat[1])/scale;*/
                    }

                    Quaternion(const Matrix<T,3,3>& RotationMatrix)
                    {
                        T tr=RotationMatrix[0]+RotationMatrix[4]+RotationMatrix[8];
                        T s;
                        if (tr>=0.0)
                        {
                            s=RadonFramework::Math::Math<T>::Sqrt(tr+(T)1)*(T)2;
                            m_Quaternion[0]=static_cast<T>(0.25)*s;
                            m_Quaternion[1]=(RotationMatrix[7]-RotationMatrix[5])*s;
                            m_Quaternion[2]=(RotationMatrix[2]-RotationMatrix[6])*s;
                            m_Quaternion[3]=(RotationMatrix[3]-RotationMatrix[1])*s;
                        }
                        else
                        {
                            RFTYPE::UInt32 i=0;
                            if (RotationMatrix[4]>RotationMatrix[0])
                                i=4;
                            if (RotationMatrix[8]>RotationMatrix[i])
                                i=8;
                            switch(i)
                            {
                                case 0:
                                    s=RadonFramework::Math::Math<T>::Sqrt(RotationMatrix[0]-(RotationMatrix[4]+RotationMatrix[8])+static_cast<T>(1.0));
                                    m_Quaternion[1]=static_cast<T>(0.5)*s;
                                    s=static_cast<T>(0.5)/s;
                                    m_Quaternion[2]=(RotationMatrix[1]+RotationMatrix[3])*s;
                                    m_Quaternion[3]=(RotationMatrix[6]+RotationMatrix[2])*s;
                                    m_Quaternion[0]=(RotationMatrix[7]+RotationMatrix[2])*s;
                                    break;
                                case 4:
                                    s=RadonFramework::Math::Math<T>::Sqrt(RotationMatrix[4]-(RotationMatrix[8]+RotationMatrix[0])+static_cast<T>(1.0));
                                    m_Quaternion[2]=static_cast<T>(0.5)*s;
                                    s=static_cast<T>(0.5)/s;
                                    m_Quaternion[3]=(RotationMatrix[5]+RotationMatrix[7])*s;
                                    m_Quaternion[1]=(RotationMatrix[1]+RotationMatrix[3])*s;
                                    m_Quaternion[0]=(RotationMatrix[2]+RotationMatrix[6])*s;
                                    break;
                                case 8:
                                    s=RadonFramework::Math::Math<T>::Sqrt(RotationMatrix[8]-(RotationMatrix[0]+RotationMatrix[4])+static_cast<T>(1.0));
                                    m_Quaternion[3]=static_cast<T>(0.5)*s;
                                    s=static_cast<T>(0.5)/s;
                                    m_Quaternion[1]=(RotationMatrix[6]+RotationMatrix[2])*s;
                                    m_Quaternion[2]=(RotationMatrix[5]+RotationMatrix[7])*s;
                                    m_Quaternion[0]=(RotationMatrix[3]+RotationMatrix[1])*s;
                                    break;
                            }
                        }
                    }

                    Quaternion(const T Roll, const T Pitch, const T Yaw)
                    {
                        T r=RadonFramework::Math::Math<T>::DegToRad(Roll * static_cast<T>(0.5));
                        T p=RadonFramework::Math::Math<T>::DegToRad(Pitch * static_cast<T>(0.5));
                        T y=RadonFramework::Math::Math<T>::DegToRad(Yaw * static_cast<T>(0.5));

                        T sx=RadonFramework::Math::Math<T>::Sin(r);
                        T cx=RadonFramework::Math::Math<T>::Cos(r);

                        T sy=RadonFramework::Math::Math<T>::Sin(p);
                        T cy=RadonFramework::Math::Math<T>::Cos(p);

                        T sz=RadonFramework::Math::Math<T>::Sin(y);
                        T cz=RadonFramework::Math::Math<T>::Cos(y);

                        m_Quaternion[0]=(cx*cy*cz)-(sx*sy*sz);
                        m_Quaternion[1]=(sx*sy*cz)+(cx*cy*sz);
                        m_Quaternion[2]=(sx*cy*cz)+(cx*sy*sz);
                        m_Quaternion[3]=(cx*sy*cz)-(sx*cy*sz);
                    }

                    /** @brief Addition of two Quaternion.
                      *
                      */
                    Quaternion operator+(const Quaternion& Other)
                    {
                        Quaternion quat(*this);
                        quat.m_Quaternion+=Other.m_Quaternion;
                        return quat;
                    }

                    /** @brief Subtraction of two Quaternion.
                      *
                      */
                    Quaternion operator-(const Quaternion& Other)
                    {
                        Quaternion quat(*this);
                        quat.m_Quaternion-=Other.m_Quaternion;
                        return quat;
                    }

                    /** @brief Multiply two Quaternion.
                      *
                      */
                    Quaternion operator*(const Quaternion& Other)
                    {
                        Quaternion quat;
                        quat.m_Quaternion[0]=m_Quaternion[0]*Other.m_Quaternion[0]-m_Quaternion[1]*Other.m_Quaternion[1]-m_Quaternion[2]*Other.m_Quaternion[2]-m_Quaternion[3]*Other.m_Quaternion[3];
                        quat.m_Quaternion[1]=m_Quaternion[0]*Other.m_Quaternion[1]+m_Quaternion[1]*Other.m_Quaternion[0]+m_Quaternion[2]*Other.m_Quaternion[3]-m_Quaternion[3]*Other.m_Quaternion[2];
                        quat.m_Quaternion[2]=m_Quaternion[0]*Other.m_Quaternion[2]+m_Quaternion[2]*Other.m_Quaternion[0]+m_Quaternion[3]*Other.m_Quaternion[1]-m_Quaternion[1]*Other.m_Quaternion[3];
                        quat.m_Quaternion[3]=m_Quaternion[0]*Other.m_Quaternion[3]+m_Quaternion[3]*Other.m_Quaternion[0]+m_Quaternion[1]*Other.m_Quaternion[2]-m_Quaternion[2]*Other.m_Quaternion[1];
                        return quat;
                    }

                    /** @brief Division two Quaternion.
                      *
                      */
                    Quaternion operator/(const Quaternion& Other)
                    {
                        Quaternion quat(*this);
                        quat*=Other.Inverse();
                        return quat;
                    }

                    Quaternion& operator+=(const Quaternion& Other)
                    {
                        m_Quaternion+=Other.m_Quaternion;
                        return *this;
                    }

                    Quaternion& operator-=(const Quaternion& Other)
                    {
                        m_Quaternion-=Other.m_Quaternion;
                        return *this;
                    }

                    Quaternion& operator*=(const Quaternion& Other)
                    {
                        m_Quaternion=(*this*Other).m_Quaternion;
                        return *this;
                    }

                    Quaternion& operator/=(const Quaternion& Other)
                    {
                        m_Quaternion=(*this*Other.Inverse()).m_Quaternion;
                        return *this;
                    }

                    Quaternion& SetIdentity()
                    {
                        m_Quaternion=Identity.m_Quaternion;
                        return *this;
                    }

                    Quaternion& Invert()
                    {
                        T val=SquareLength();
                        Assert(val != static_cast<T>(0.0),"Invalid value.");
                        Conjugate().m_Quaternion/=val;
                        return *this;
                    }

                    /** @brief Conjugate of Quaternion.
                      *
                      */
                    Quaternion& Conjugate()
                    {
                        Vector<T,4> vec(1,-1,-1,-1);
                        m_Quaternion*=vec;
                        return *this;
                    }

                    /** @brief Normalize the Quaternion.
                      *
                      * This method will calculate the norm and divide every element
                      * by it.
                      */
                    Quaternion& Normalize()
                    {
                        T v=Length();
                        m_Quaternion/=v;
                        return *this;
                    }

                    T DotProduct(const Quaternion& Other)
                    {
                        return m_Quaternion[0]*Other.m_Quaternion[0]+
                               m_Quaternion[1]*Other.m_Quaternion[1]+
                               m_Quaternion[2]*Other.m_Quaternion[2]+
                               m_Quaternion[3]*Other.m_Quaternion[3];
                    }

                    /** @brief Inverse of Quaternion.
                      *
                      */
                    Quaternion Inverse()const
                    {
                        Quaternion quat(*this);
                        quat.Invert();
                        return quat;
                    }

                    /** @brief Apply the rotation on a vector.
                      *
                      */
                    Vector<T,4> operator*(const Vector<T,4>& Vec)
                    {
                        Vector<T,3> v(Vec[0],Vec[1],Vec[2]);
                        v=(*this)*v;
                        Vector<T,4> res(v[0],v[1],v[2],Vec[3]);
                        return res;
                    }

                    Vector<T,3> operator*(const Vector<T,3>& Vec)
                    {
                        Vector<T,3> res;
                        T a00=m_Quaternion[0]*m_Quaternion[0];
                        T a01=m_Quaternion[0]*m_Quaternion[1];
                        T a02=m_Quaternion[0]*m_Quaternion[2];
                        T a03=m_Quaternion[0]*m_Quaternion[3];
                        T a11=m_Quaternion[1]*m_Quaternion[1];
                        T a12=m_Quaternion[1]*m_Quaternion[2];
                        T a13=m_Quaternion[1]*m_Quaternion[3];
                        T a22=m_Quaternion[2]*m_Quaternion[2];
                        T a23=m_Quaternion[2]*m_Quaternion[3];
                        T a33=m_Quaternion[3]*m_Quaternion[3];
                        res[0]=Vec[0]*(a00+a11-a22-a33)+T(2)*(a12*Vec[1]+a13*Vec[2]+a02*Vec[2]-a03*Vec[1]);
                        res[1]=Vec[1]*(a00-a11+a22-a33)+T(2)*(a12*Vec[0]+a23*Vec[2]+a03*Vec[0]-a01*Vec[2]);
                        res[2]=Vec[2]*(a00-a11-a22+a33)+T(2)*(a13*Vec[0]+a23*Vec[1]-a02*Vec[0]+a01*Vec[1]);
                        return res;
                    }

                    RFTYPE::Bool operator==(const Quaternion& Other)
                    {
                        return m_Quaternion==Other.m_Quaternion;
                    }

                    RFTYPE::Bool operator!=(const Quaternion& Other)
                    {
                        return m_Quaternion!=Other.m_Quaternion;
                    }

                    Quaternion Exponential()
                    {
					    Quaternion result;
					    T angle = RadonFramework::Math::Math<T>::Sqrt(m_Quaternion[1]*m_Quaternion[1] +
											    m_Quaternion[2]*m_Quaternion[2] +
											    m_Quaternion[3]*m_Quaternion[3]);
					    T sn = RadonFramework::Math::Math<T>::Sin(angle);
					    result.m_Quaternion[0] = RadonFramework::Math::Math<T>::Cos(angle);

					    RFTYPE::UInt32 i;
					    if (RadonFramework::Math::Math<T>::FAbs(sn) > (T)0)
					    {
						    T coeff = sn/angle;
						    for (i = 1; i < 4; ++i)
						    {
							    result.m_Quaternion[i] = coeff*m_Quaternion[i];
						    }
					    }
					    else
					    {
						    for (i = 1; i < 4; ++i)
						    {
							    result.m_Quaternion[i] = m_Quaternion[i];
						    }
					    }

					    return result;
                    }

                    RFTYPE::Bool IsInfinite()
                    {
					    return RadonFramework::Math::Math<T>::IsInfinity(m_Quaternion[0]) ||
						       RadonFramework::Math::Math<T>::IsInfinity(m_Quaternion[1]) ||
						       RadonFramework::Math::Math<T>::IsInfinity(m_Quaternion[2]) ||
						       RadonFramework::Math::Math<T>::IsInfinity(m_Quaternion[3]);
                    }

                    RFTYPE::Bool IsNaN()
                    {
					    return RadonFramework::Math::Math<T>::IsNaN(m_Quaternion[0]) ||
						       RadonFramework::Math::Math<T>::IsNaN(m_Quaternion[1]) ||
						       RadonFramework::Math::Math<T>::IsNaN(m_Quaternion[2]) ||
						       RadonFramework::Math::Math<T>::IsNaN(m_Quaternion[3]);
                    }

                    Quaternion LengthAsQuat()
                    {
					    Quaternion q;
					    T len=Length();
					    for (RFTYPE::UInt32 i=0;i<4;++i)
						    q[i]=len;
					    return q;
                    }

                    T Length()
                    {
                        if (m_Quaternion[0]==0.0 && m_Quaternion[1]==0.0 &&
                            m_Quaternion[2]==0.0 && m_Quaternion[3]==0.0)
                            return 0.0;
                        return RadonFramework::Math::Math<T>::Sqrt((m_Quaternion*m_Quaternion).Sum());;
                    }

                    Quaternion SquareLengthAsQuat()
                    {
                        Quaternion q;
                        T sqrlen=SquareLength();
                        for (RFTYPE::UInt32 i=0;i<4;++i)
						    q[i]=sqrlen;
                        return q;
                    }

                    T SquareLength()
                    {
                        T len=Length();
                        len*=len;
                        return len;
                    }

                    Quaternion CrossProduct(const Quaternion& Other)
                    {
                        Vector<T,3> v1(m_Quaternion[1],m_Quaternion[2],m_Quaternion[3]);
                        Vector<T,3> v2(Other.m_Quaternion[1],Other.m_Quaternion[2],Other.m_Quaternion[3]);
                        Vector<T,3> v3=v1.CrossProduct(v2);
                        Quaternion q(0,v3[0],v3[1],v3[2]);
                        return q;
                    }

                    Quaternion Slerp(const Quaternion& Other, T t)
                    {
					    Quaternion ret;
					    T cs = DotProduct(Other);
					    T angle = RadonFramework::Math::Math<T>::ACos(cs);

					    if (RadonFramework::Math::Math<T>::FAbs(angle) > (T)0)
					    {
						    T sn = RadonFramework::Math::Math<T>::Sin(angle);
						    T invSn = (T)1/sn;
						    T tAngle = t*angle;
						    T coeff0 = RadonFramework::Math::Math<T>::Sin(angle - tAngle)*invSn;
						    T coeff1 = RadonFramework::Math::Math<T>::Sin(tAngle)*invSn;

						    ret[0] = coeff0*m_Quaternion[0] + coeff1*Other.m_Quaternion[0];
						    ret[1] = coeff0*m_Quaternion[1] + coeff1*Other.m_Quaternion[1];
						    ret[2] = coeff0*m_Quaternion[2] + coeff1*Other.m_Quaternion[2];
						    ret[3] = coeff0*m_Quaternion[3] + coeff1*Other.m_Quaternion[3];
					    }
					    else
					    {
						    ret[0] = m_Quaternion[0];
						    ret[1] = m_Quaternion[1];
						    ret[2] = m_Quaternion[2];
						    ret[3] = m_Quaternion[3];
					    }

					    return ret;
                    }

                    void ToAxisAngle(Vector<T,3>& Axis, T& Angle)
                    {
                        if(m_Quaternion[0]>(T)1)
                            Normalize();

                        Angle = RadonFramework::Math::Math<T>::RadToDeg((T)2*RadonFramework::Math::Math<T>::ACos(m_Quaternion[0]));
                        T s = RadonFramework::Math::Math<T>::Sqrt((T)1-m_Quaternion[0]*m_Quaternion[0]);

					    if (RadonFramework::Math::Math<T>::EPSILION<s)
					    {
						    Axis[0] = m_Quaternion[1];
						    Axis[1] = m_Quaternion[2];
						    Axis[2] = m_Quaternion[3];
					    }
					    else
					    {
						    Axis[0] = m_Quaternion[1]/s;
						    Axis[1] = m_Quaternion[2]/s;
						    Axis[2] = m_Quaternion[3]/s;
					    }
                    }

                    Vector<T,3> GetAxis()
                    {
					    Vector<T,3> axis;
					    axis[0]=m_Quaternion[1];
					    axis[1]=m_Quaternion[2];
					    axis[2]=m_Quaternion[3];
					    return axis;
                    }

                    T GetAngle()
                    {
					    return m_Quaternion[0];
                    }

                    Matrix<T,3,3> AsRotationMatrix()
                    {
					    T twoX  = (T)2*m_Quaternion[1];
					    T twoY  = (T)2*m_Quaternion[2];
					    T twoZ  = (T)2*m_Quaternion[3];
					    T twoWX = twoX*m_Quaternion[0];
					    T twoWY = twoY*m_Quaternion[0];
					    T twoWZ = twoZ*m_Quaternion[0];
					    T twoXX = twoX*m_Quaternion[1];
					    T twoXY = twoY*m_Quaternion[1];
					    T twoXZ = twoZ*m_Quaternion[1];
					    T twoYY = twoY*m_Quaternion[2];
					    T twoYZ = twoZ*m_Quaternion[2];
					    T twoZZ = twoZ*m_Quaternion[3];

					    Matrix<T,3,3> rot;
					    rot[0] = (T)1 - (twoYY + twoZZ);
					    rot[1] = twoXY - twoWZ;
					    rot[2] = twoXZ + twoWY;
					    rot[3] = twoXY + twoWZ;
					    rot[4] = (T)1 - (twoXX + twoZZ);
					    rot[5] = twoYZ - twoWX;
					    rot[6] = twoXZ - twoWY;
					    rot[7] = twoYZ + twoWX;
					    rot[8] = (T)1 - (twoXX + twoYY);
					    return rot;
                    }

                    Matrix<T,4,4> AsMatrix()
                    {
					    T twoX  = (T)2*m_Quaternion[1];
					    T twoY  = (T)2*m_Quaternion[2];
					    T twoZ  = (T)2*m_Quaternion[3];
					    T twoWX = twoX*m_Quaternion[0];
					    T twoWY = twoY*m_Quaternion[0];
					    T twoWZ = twoZ*m_Quaternion[0];
					    T twoXX = twoX*m_Quaternion[1];
					    T twoXY = twoY*m_Quaternion[1];
					    T twoXZ = twoZ*m_Quaternion[1];
					    T twoYY = twoY*m_Quaternion[2];
					    T twoYZ = twoZ*m_Quaternion[2];
					    T twoZZ = twoZ*m_Quaternion[3];

					    Matrix<T,4,4> rot;
					    rot[0] = (T)1 - (twoYY + twoZZ);
					    rot[1] = twoXY - twoWZ;
					    rot[2] = twoXZ + twoWY;
					    rot[3] = (T)0;
					    rot[4] = twoXY + twoWZ;
					    rot[5] = (T)1 - (twoXX + twoZZ);
					    rot[6] = twoYZ - twoWX;
					    rot[7] = (T)0;
					    rot[8] = twoXZ - twoWY;
					    rot[9] = twoYZ + twoWX;
					    rot[10] = (T)1 - (twoXX + twoYY);
					    rot[11] = (T)0;
					    rot[12] = (T)0;
					    rot[13] = (T)0;
					    rot[14] = (T)0;
					    rot[15] = (T)1;
					    return rot;
                    }

                    T& operator[](const RFTYPE::UInt32 Index)
                    {
                        Assert(Index<4,"Index out of bound.");
                        return m_Quaternion[Index];
                    }

                    const T operator[](const RFTYPE::UInt32 Index)const
                    {
                        Assert(Index<4,"Index out of bound.");
                        return m_Quaternion[Index];
                    }
                protected:
                    Vector<T,4> m_Quaternion;
            };

            template<typename T>
            const Quaternion<T> Quaternion<T>::Identity;
        }
    }
}

#endif // RF_MATH_GEOMETRY_QUATERNION_HPP
