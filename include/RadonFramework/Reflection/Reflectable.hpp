#ifndef RF_REFLECTABLE_HPP
#define RF_REFLECTABLE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Reflection/ReflectionManager.hpp>
#include <RadonFramework/Reflection/ReflectionClass.hpp>
#include <RadonFramework/Reflection/ReflectionProperty.hpp>
#include <RadonFramework/Reflection/ReflectionMethode.hpp>

namespace RadonFramework
{
    namespace Reflection
    {
        class Reflectable
        {
          public:
            virtual const RFTYPE::String& GetName()const;
            virtual RFTYPE::UInt32 PropertiesCount();
            virtual RFTYPE::UInt32 MethodeCount();
            virtual ReflectionProperty* Property(RFTYPE::UInt32 Index);
            virtual ReflectionMethode* Methode(RFTYPE::UInt32 Index);
            REFLECT(Reflectable){}
        };
    }
}

#endif
