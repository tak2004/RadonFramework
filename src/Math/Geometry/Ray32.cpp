#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Geometry/Ray32.hpp"

namespace RadonFramework::Math::Geometry {

Ray32::Ray32()
{
}

RF_Type::Bool Ray32::Equals(const Ray32 &Other) const
{
    return m_Direction == Other.m_Direction && m_Origin == Other.m_Origin;
}

Ray32& Ray32::operator=(const Ray32& AssignThis)
{
    m_Direction = AssignThis.m_Direction;
    m_Origin = AssignThis.m_Origin;
    return *this;
}

Ray32::Ray32(const Ray32& CopyFrom)
{
    *this = CopyFrom;
}

Vec3f Ray32::GetPoint(RF_Type::Float32 Delta) const
{
    Vec3f result(m_Origin);
    Norm3f dir = m_Direction * Delta;
    result[0] += dir[0];
    result[1] += dir[1];
    result[2] += dir[2];
    return result;
}

Ray32::Ray32(const Vec3f& Origin, const Norm3f& Direction)
:m_Origin(Origin)
,m_Direction(Direction)
{
}

const Vec3f& Ray32::GetOrigin()const
{
    return m_Origin;
}

const Norm3f& Ray32::GetDirection()const
{
    return m_Direction;
}

}