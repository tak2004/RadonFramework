#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Reflection/ReflectionClass.hpp"
#include "RadonFramework/Reflection/ReflectionManager.hpp"

using namespace RadonFramework::Reflection;
using namespace RadonFramework::Core::Types;


ReflectionClass::ReflectionClass(const String& Name,
                                 void (*Configure)(ReflectionClass* Cls),
                                 CreateInstanceFunction Function)
{
  m_Name=Name;
  m_CreateInstanceFunction=Function;
  ReflectionManager::GetInstance().Classes.AddLast(this);
  Configure(this);
}

const String& ReflectionClass::GetName()const
{
  return m_Name;
}

ReflectionClassInstance* ReflectionClass::CreateInstance()
{
  return m_CreateInstanceFunction();
}
