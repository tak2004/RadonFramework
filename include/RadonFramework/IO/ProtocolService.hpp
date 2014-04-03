#ifndef RF_PROTOCOLSERVICE_HPP
#define RF_PROTOCOLSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/IO/Resource.hpp>

namespace RadonFramework
{
    namespace IO
    {
        class Uri;

        class ProtocolService:public Core::Pattern::Service
        {
            public:
                ProtocolService(const RFTYPE::String &Name);

                virtual Memory::AutoPointer<Resource> GenerateResource(const Uri& URI)=0;
        };
    }
}

#endif // RF_PROTOCOLSERVICE_HPP
