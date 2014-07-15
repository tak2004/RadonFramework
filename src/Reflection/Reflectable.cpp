#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Reflection/Reflectable.hpp>

using namespace RadonFramework::Reflection;
using namespace RadonFramework::Core::Types;

const String& Reflectable::GetName()const
{
    return GetReflectionClass().GetName();
}

UInt32 Reflectable::PropertiesCount()
{
    return GetReflectionClass().Properties.Size();
}

UInt32 Reflectable::MethodeCount()
{
    return GetReflectionClass().Methodes.Size();
}

ReflectionProperty* Reflectable::Property(UInt32 Index)
{
    //To check if the index is in bound is much faster then throw an OutOfBoundException and this function will called very often.
    if (Index<GetReflectionClass().Properties.Size())
        return GetReflectionClass().Properties[Index];
    return 0;
}

ReflectionMethode* Reflectable::Methode(UInt32 Index)
{
    if (Index<GetReflectionClass().Methodes.Size())
        return GetReflectionClass().Methodes[Index];
    return 0;
}

REGISTER_REFLECTION_CLASS(Reflectable, RF_Type::String("Reflectable", sizeof("Reflectable")))
