#ifndef RF_PROTOCOLSERVICELOCATOR_HPP
#define RF_PROTOCOLSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/IO/ProtocolService.hpp>
#include <RadonFramework/IO/Resource.hpp>
#include <RadonFramework/IO/Uri.hpp>

namespace RadonFramework
{
    namespace IO
    {
        class NullProtocolService:public ProtocolService
        {
            public:
                NullProtocolService(const RadonFramework::Core::Types::String &Name):ProtocolService(Name){}
                Memory::AutoPointer<Resource> GenerateResource(const Uri&){return Memory::AutoPointer<Resource>();}
        };

        class ProtocolServiceLocator:public Core::Pattern::Locator<ProtocolService,NullProtocolService>
        {
            public:
                static Memory::AutoPointer<Resource> GenerateResource(const Uri& URI);
            private:
                ~ProtocolServiceLocator();
        };
    }
}

#endif // RF_PROTOCOLSERVICELOCATOR_HPP
