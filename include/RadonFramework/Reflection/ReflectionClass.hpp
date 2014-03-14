#ifndef RF_REFLECTIONCLASS_HPP
#define RF_REFLECTIONCLASS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Reflection/ReflectionProperty.hpp>
#include <RadonFramework/Reflection/ReflectionMethode.hpp>

namespace RadonFramework
{
    namespace Reflection
    {
        class ReflectionClassInstance;

        template<typename T>
        ReflectionClassInstance* CreateInstance()
        {
            return (ReflectionClassInstance*)new T;
        }

        typedef ReflectionClassInstance* (*CreateInstanceFunction)();

        class ReflectionClass
        {
            public:
                ReflectionClass(const RFTYPE::String& Name,
                                void (*Configure)(ReflectionClass* Cls),
                                CreateInstanceFunction Function);
                RadonFramework::Collections::AutoVector<ReflectionProperty> Properties;
                RadonFramework::Collections::AutoVector<ReflectionMethode> Methodes;
                const RFTYPE::String& GetName()const;
                ReflectionClassInstance* CreateInstance();
            private:
                RFTYPE::String m_Name;
                CreateInstanceFunction m_CreateInstanceFunction;
        };
    }
}

#endif

