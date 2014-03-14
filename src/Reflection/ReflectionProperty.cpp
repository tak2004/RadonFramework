#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Reflection/ReflectionProperty.hpp>
#include <RadonFramework/Reflection/Reflectable.hpp>

using namespace RadonFramework::Reflection;
using namespace RadonFramework::Core::Types;

ReflectionProperty::ReflectionProperty(const RadonFramework::Core::Types::String &Name,const TypeKind::Type Type,Callback Setter,Callback Getter)
:m_Name(Name),
 m_Type(Type),
 m_Getter(Getter),
 m_Setter(Setter)
{
}

const String& ReflectionProperty::GetName()const
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
