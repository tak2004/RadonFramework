#ifndef RF_REFLECTABLE_HPP
#define RF_REFLECTABLE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Reflection/ReflectionManager.hpp>
#include <RadonFramework/Reflection/ReflectionClass.hpp>
#include <RadonFramework/Reflection/ReflectionProperty.hpp>
#include <RadonFramework/Reflection/ReflectionMethode.hpp>

namespace RadonFramework::Reflection {

class Reflectable
{
public:
    virtual const RF_Type::String& GetName()const;
    virtual RF_Type::UInt32 PropertiesCount();
    virtual RF_Type::UInt32 MethodeCount();
    virtual ReflectionProperty* Property(RF_Type::UInt32 Index);
    virtual ReflectionMethode* Methode(RF_Type::UInt32 Index);
    REFLECT(Reflectable){}
};

}

#endif
