#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Geometry/Sphere32.hpp"

namespace RadonFramework::Math::Geometry {

Sphere32::Sphere32(const Vec3f& Position, const RF_Type::Float32 Radius)
:m_Position(Position)
,m_Radius(Radius)
{

}

Sphere32::Sphere32()
:m_Radius(1)
{
}

const Vec3f& Sphere32::GetPosition() const
{
    return m_Position;
}

RF_Type::Float32 Sphere32::GetRadius() const
{
    return m_Radius;
}

RF_Type::Bool Sphere32::operator==(const Sphere32& CompareWith)
{
    return m_Position == CompareWith.m_Position && m_Radius == CompareWith.m_Radius;
}

Sphere32& Sphere32::operator=(const Sphere32& AssignThis)
{
    m_Position = AssignThis.m_Position;
    m_Radius = AssignThis.m_Radius;
    return *this;
}

}