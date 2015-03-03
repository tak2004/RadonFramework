#ifndef RF_PROTOCOLSERVICELOCATOR_HPP
#define RF_PROTOCOLSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/IO/ProtocolService.hpp>
#include <RadonFramework/IO/Resource.hpp>
#include <RadonFramework/IO/Uri.hpp>

namespace RadonFramework { namespace IO {

class NullProtocolService:public ProtocolService
{
    public:
        NullProtocolService(const RF_Type::String &Name):ProtocolService(Name){}
        Memory::AutoPointer<Resource> GenerateResource(const Uri&){return Memory::AutoPointer<Resource>();}
};

struct ProtocolServiceLocator:public RF_Pattern::Locator<ProtocolService, NullProtocolService>
{
    ProtocolServiceLocator() = delete;

    static Memory::AutoPointer<Resource> GenerateResource(const Uri& URI);
};

} }

#endif // RF_PROTOCOLSERVICELOCATOR_HPP
