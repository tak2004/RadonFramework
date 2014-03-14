#ifndef RF_FILEPROTOCOLSERVICE_HPP
#define RF_FILEPROTOCOLSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/ProtocolService.hpp>

namespace RadonFramework
{
    class UniformResourceIdentifier;

    namespace IO
    {
        class FileProtocolService:public ProtocolService
        {
            public:
                FileProtocolService(const RFTYPE::String &Name);
                Memory::AutoPointer<Resource> GenerateResource(const Uri &Location);
        };
    }
}

#endif // RF_FILEPROTOCOLSERVICE_HPP
