#ifndef RF_REFLECTIONCLASS_HPP
#define RF_REFLECTIONCLASS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Reflection/ReflectionProperty.hpp>
#include <RadonFramework/Reflection/ReflectionMethode.hpp>

namespace RadonFramework::Reflection {

class ReflectionClassInstance;

template<typename T>
ReflectionClassInstance* CreateInstance()
{
    return reinterpret_cast<ReflectionClassInstance*>(new T);
}

using CreateInstanceFunction = ReflectionClassInstance* (*)();

class ReflectionClass
{
public:
    ReflectionClass(const RF_Type::String& Name,
                    void (*Configure)(ReflectionClass* Cls),
                    CreateInstanceFunction Function);
    RadonFramework::Collections::AutoVector<ReflectionProperty> Properties;
    RadonFramework::Collections::AutoVector<ReflectionMethode> Methodes;
    const RF_Type::String& GetName()const;
    ReflectionClassInstance* CreateInstance();
private:
    RF_Type::String m_Name;
    CreateInstanceFunction m_CreateInstanceFunction;
};

}

#endif

