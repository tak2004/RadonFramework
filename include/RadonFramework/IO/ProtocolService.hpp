#ifndef RF_PROTOCOLSERVICE_HPP
#define RF_PROTOCOLSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Pattern/Service.hpp>

namespace RadonFramework { namespace IO {

class Uri;
class Stream;

class ProtocolService:public RF_Pattern::Service
{
public:
    ProtocolService(const RF_Type::String &Name);

    virtual RF_Type::Bool Exists(const Uri& URI) = 0;

    virtual Stream* GenerateInterface(const Uri& URI) = 0;

    virtual void FreeInterface(const Uri& URI) = 0;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif // RF_PROTOCOLSERVICE_HPP
