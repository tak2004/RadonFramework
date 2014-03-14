#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Reflection/ReflectionMethode.hpp>

using namespace RadonFramework::Reflection;

ReflectionMethode::ReflectionMethode(const RadonFramework::Core::Types::String &Name, Callback Ptr)
:m_Name(Name),
 m_Callback(Ptr)
{

}

const RadonFramework::Core::Types::String& ReflectionMethode::GetName()const
{
    return m_Name;
}

Callback ReflectionMethode::GetCallback()
{
    return m_Callback;
}
