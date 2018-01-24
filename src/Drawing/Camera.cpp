#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Camera.hpp"

using namespace RadonFramework;
using namespace RadonFramework::Drawing;
using namespace RadonFramework::Math::Geometry;
using namespace RadonFramework::Core::Types;

Camera::Camera()
:m_Position(0,0,-5,1)
,m_Up(0,1,0)
,m_Front(0,0,1)
,m_Right(1,0,0)
{
}

Camera::~Camera()
{

}

void Camera::MoveVertical(Float32 Value)
{
    m_Position[1]-=Value;
}

void Camera::MoveHorizontal(Float32 Value)
{
    m_Position += m_Quat * Vec4f(Value, 0.0f, 0.0f, 0.0f);
}

void Camera::Move(Float32 Value)
{
    m_Position += m_Quat * Vec4f(0.0f, 0.0f, -Value, 0.0f);
}

void Camera::RotateX(Float32 Value)
{
    QuatF32 q(Value*Math::Float32::DEG_TO_RAD, Vec3f(1.0f, 0.0f, 0.0f));
    m_Quat=m_Quat*q;
}

void Camera::RotateY(Float32 Value)
{
    QuatF32 q(Value*Math::Float32::DEG_TO_RAD,Vec3f(0.0f,1.0f,0.0f));
    m_Quat=q*m_Quat;
}

Mat4f Camera::GetMatrix()const
{
    Mat4f m;
    m.SetColumn(3,m_Position);
    m=m_Quat.AsMatrix()*m;
    return m;
}
