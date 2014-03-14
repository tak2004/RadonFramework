#ifndef RF_REFLECTIONMETHODE_HPP
#define RF_REFLECTIONMETHODE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Reflection/ReflectionTypes.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Reflection/ParameterStack.hpp>

namespace RadonFramework
{
    namespace Reflection
    {
        class Reflectable;

        typedef RadonFramework::Core::Types::Int32 (Reflectable::*Callback)(ParameterStack &Stack);

        class ReflectionMethode
        {
            public:
                ReflectionMethode(const RadonFramework::Core::Types::String &Name, Callback Ptr);
                const RadonFramework::Core::Types::String& GetName()const;
                Callback GetCallback();
            protected:
                RadonFramework::Core::Types::String m_Name;
                Callback m_Callback;
        };
    }
}

#endif

