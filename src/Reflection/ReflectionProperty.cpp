#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Reflection/ReflectionProperty.hpp>
#include <RadonFramework/Reflection/Reflectable.hpp>

namespace RadonFramework::Reflection{

ReflectionProperty::ReflectionProperty(const RF_Type::String &Name,
    const TypeKind::Type Type, Callback Setter,Callback Getter)
:m_Name(Name),
 m_Type(Type),
 m_Getter(Getter),
 m_Setter(Setter)
{
}

const RF_Type::String& ReflectionProperty::GetName()const
{
  return m_Name;
}

TypeKind::Type ReflectionProperty::GetType()const
{
    return m_Type;
}

Callback ReflectionProperty::GetGetter()
{
  return m_Getter;
}

Callback ReflectionProperty::GetSetter()
{
  return m_Setter;
}

}