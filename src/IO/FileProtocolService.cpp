#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/FileProtocolService.hpp"
#include "RadonFramework/IO/Resource.hpp"

using namespace RadonFramework::IO;
using namespace RadonFramework::Memory;

FileProtocolService::FileProtocolService(const RadonFramework::Core::Types::String &Name)
:ProtocolService(Name)
{
}

AutoPointer<Resource> FileProtocolService::GenerateResource(const Uri &Location)
{
    Memory::AutoPointer<Resource> result;
    return result;
}