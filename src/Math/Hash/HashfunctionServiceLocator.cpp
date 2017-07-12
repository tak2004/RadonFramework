#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Hash/HashfunctionServiceLocator.hpp"

namespace RadonFramework::Math::Hash {

RF_Type::UInt32 HashfunctionServiceLocator::m_Default32 = 0;
RF_Type::UInt32 HashfunctionServiceLocator::m_Default64 = 0;

NullHashfunctionService::NullHashfunctionService(const RF_Type::String &Name)
:HashfunctionService(Name)
{
}

IHashfunction* NullHashfunctionService::Create()
{
    return nullptr;
}

void NullHashfunctionService::Free(IHashfunction*& Instance)
{
}

RF_Type::Size NullHashfunctionService::BitLength() const
{
    return 0;
}

HashfunctionService& HashfunctionServiceLocator::Default64()
{
    if(Locator::m_Services.Count() && Locator::m_Services[m_Default64]->BitLength() == 64)
        return *Locator::m_Services[m_Default64];
    else
        return Locator::m_NullService;
}

HashfunctionService& HashfunctionServiceLocator::Default32()
{
    if(Locator::m_Services.Count() && Locator::m_Services[m_Default32]->BitLength() == 32)
        return *Locator::m_Services[m_Default32];
    else
        return Locator::m_NullService;
}

void HashfunctionServiceLocator::SetDefault64(const RF_Type::String& Name)
{
    RF_Type::UInt32 i = 0;
    for(Iterator it = Locator::m_Services.Begin(); it != Locator::m_Services.End(); ++it)
    {
        if((*it)->Name() == Name && (*it)->BitLength() == 64)
            break;
        i++;
    }
    if(i < Locator::m_Services.Count())
        m_Default64 = i;
}

void HashfunctionServiceLocator::SetDefault32(const RF_Type::String& Name)
{
    RF_Type::UInt32 i = 0;
    for(Iterator it = Locator::m_Services.Begin(); it != Locator::m_Services.End(); ++it)
    {
        if((*it)->Name() == Name && (*it)->BitLength() == 32)
            break;
        i++;
    }
    if(i < Locator::m_Services.Count())
        m_Default32 = i;
}

void HashfunctionServiceLocator::Remove(const RF_Type::String& Name)
{
    if(Name == RF_Pattern::Locator<HashfunctionService, NullHashfunctionService>::m_Services[m_Default64]->Name())
        m_Default64 = 0;
    if(Name == RF_Pattern::Locator<HashfunctionService, NullHashfunctionService>::m_Services[m_Default32]->Name())
        m_Default32 = 0;
    RF_Pattern::Locator<HashfunctionService, NullHashfunctionService>::Remove(Name);
}

}