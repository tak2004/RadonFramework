#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/IO/ProtocolServiceLocator.hpp>
#include <RadonFramework/IO/Uri.hpp>
#include <RadonFramework/IO/Log.hpp>
#include <vector>

using namespace RadonFramework::IO;
using namespace RadonFramework::Memory;

AutoPointer<Resource> ProtocolServiceLocator::GenerateResource(const Uri& URI)
{
    ProtocolService& protocol=Find(URI.Scheme());
    if (protocol.Name() == RFTYPE::String("NullService", sizeof("NullService")))
    {
        LogError("Can't find a service for the requested protocol.");
        return AutoPointer<Resource>();
    }
    return protocol.GenerateResource(URI);
}
