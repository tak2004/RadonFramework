#ifndef RF_REFLECTIONMETHODE_HPP
#define RF_REFLECTIONMETHODE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Reflection/ReflectionTypes.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Reflection/ParameterStack.hpp>

namespace RadonFramework::Reflection {

class Reflectable;

typedef RF_Type::Int32 (Reflectable::*Callback)(ParameterStack &Stack);

class ReflectionMethode
{
    public:
        ReflectionMethode(const RF_Type::String &Name, Callback Ptr);
        const RF_Type::String& GetName()const;
        Callback GetCallback();
    protected:
        RF_Type::String m_Name;
        Callback m_Callback;
};

}

#endif

