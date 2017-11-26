#ifndef RF_REFLECTIONMANAGER_HPP
#define RF_REFLECTIONMANAGER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/Collections/List.hpp>

#define REFLECT(__CLASS)\
    virtual RF_Reflect::ReflectionClass& GetReflectionClass(){return __CLASS::DescriptionClass;}\
    virtual const RF_Reflect::ReflectionClass& GetReflectionClass()const {return __CLASS::DescriptionClass;}\
    static RF_Reflect::ReflectionClass DescriptionClass;\
    static void ConfigureDescriptionClass##__CLASS(RF_Reflect::ReflectionClass* Cls)

#define PROPERTY(__NAME,__TYPE,__SETTER,__GETTER)\
    RF_Mem::AutoPointer<RF_Reflect::ReflectionProperty> propertyptr##__NAME(new RF_Reflect::ReflectionProperty(#__NAME##_rfs,__TYPE,(RF_Reflect::Callback)__SETTER,(RF_Reflect::Callback)__GETTER));\
    Cls->Properties.PushBack(propertyptr##__NAME);

#define METHODE(__NAME,__FUNCTIONPTR)\
    RF_Mem::AutoPointer<RF_Reflect::ReflectionMethode> methodeptr##__NAME(new RF_Reflect::ReflectionMethode(#__NAME,(RF_Reflect::Callback)__FUNCTIONPTR));\
    Cls->Methodes.PushBack(methodeptr##__NAME);

#define REGISTER_REFLECTION_CLASS(__CLASS,__NAME)\
    RF_Reflect::ReflectionClass __CLASS::DescriptionClass(__NAME,&__CLASS::ConfigureDescriptionClass##__CLASS,&RF_Reflect::CreateInstance<__CLASS>);

namespace RadonFramework::Reflection {

//forward declaration
class ReflectionClass;

class ReflectionManager:public RF_Pattern::Singleton<ReflectionManager>
{
public:
    RF_Collect::List<ReflectionClass*> Classes;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_REFLECT
#define RF_SHORTHAND_NAMESPACE_REFLECT
namespace RF_Reflect = RadonFramework::Reflection;
#endif

#endif
