#ifndef RF_REFLECTIONMANAGER_HPP
#define RF_REFLECTIONMANAGER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/Collections/List.hpp>

#define REFLECT(__CLASS)\
    virtual RadonFramework::Reflection::ReflectionClass& GetReflectionClass(){return __CLASS::DescriptionClass;}\
    virtual const RadonFramework::Reflection::ReflectionClass& GetReflectionClass()const {return __CLASS::DescriptionClass;}\
    static RadonFramework::Reflection::ReflectionClass DescriptionClass;\
    static void ConfigureDescriptionClass##__CLASS(RadonFramework::Reflection::ReflectionClass* Cls)

#define PROPERTY(__NAME,__TYPE,__SETTER,__GETTER)\
    RadonFramework::Memory::AutoPointer<RadonFramework::Reflection::ReflectionProperty> propertyptr##__NAME(new RadonFramework::Reflection::ReflectionProperty(#__NAME,__TYPE,(RadonFramework::Reflection::Callback)__SETTER,(RadonFramework::Reflection::Callback)__GETTER));\
    Cls->Properties.PushBack(propertyptr##__NAME);

#define METHODE(__NAME,__FUNCTIONPTR)\
    RadonFramework::Memory::AutoPointer<RadonFramework::Reflection::ReflectionMethode> methodeptr##__NAME(new RadonFramework::Reflection::ReflectionMethode(#__NAME,(RadonFramework::Reflection::Callback)__FUNCTIONPTR));\
    Cls->Methodes.PushBack(methodeptr##__NAME);

#define REGISTER_REFLECTION_CLASS(__CLASS,__NAME)\
    RadonFramework::Reflection::ReflectionClass __CLASS::DescriptionClass(__NAME,&__CLASS::ConfigureDescriptionClass##__CLASS,&RadonFramework::Reflection::CreateInstance<__CLASS>);

namespace RadonFramework
{
    namespace Reflection
    {
        //forward decleration
        class ReflectionClass;

        class ReflectionManager:public Singleton<ReflectionManager>
        {
            public:
                RadonFramework::Collections::List<ReflectionClass*> Classes;
        };
    }
}

#endif
