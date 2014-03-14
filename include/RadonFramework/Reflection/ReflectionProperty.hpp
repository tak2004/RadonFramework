#ifndef RF_REFLECTIONPROPERTY_HPP
#define RF_REFLECTIONPROPERTY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Reflection/ReflectionTypes.hpp>
#include <RadonFramework/Reflection/ReflectionMethode.hpp>

namespace RadonFramework
{
    namespace Reflection
    {
        class ReflectionProperty
        {
            public:
                ReflectionProperty(const RadonFramework::Core::Types::String &Name,const TypeKind::Type Type,Callback Setter,Callback Getter);
                const RadonFramework::Core::Types::String& GetName()const;
                TypeKind::Type GetType()const;
                Callback GetGetter();
                Callback GetSetter();
            protected:
                RadonFramework::Core::Types::String m_Name;
                TypeKind::Type m_Type;
                Callback m_Getter;
                Callback m_Setter;
        };
    }
}

#endif

