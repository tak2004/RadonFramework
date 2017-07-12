#ifndef RF_MEMORYPROTOCOLSERVICE_HPP
#define RF_MEMORYPROTOCOLSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/ProtocolService.hpp>
#include <RadonFramework/Core/Idioms/PImpl.hpp>

namespace RadonFramework::IO {

class MemoryProtocolService:public ProtocolService
{
public:
    MemoryProtocolService(const RF_Type::String &Name);

    virtual RF_Type::Bool Exists(const Uri& URI) override;

    virtual Stream* GenerateInterface(const Uri& URI) override;

    virtual void FreeInterface(const Uri& URI) override;
private:
    RF_Idiom::PImpl<MemoryProtocolService> m_PImpl;
};

}

#endif // RF_MEMORYPROTOCOLSERVICE_HPP
