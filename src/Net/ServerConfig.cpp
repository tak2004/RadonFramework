#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/IPAddress.hpp"
#include "RadonFramework/Net/ServerConfig.hpp"

namespace RadonFramework { namespace Net {

void ServerConfig::AssignIPAsHostname(ServerConfig& Config, const IPAddress IP)
{
    RF_Type::String hostname = IP.ToString();
    if(hostname.Size() < 256)
    {
        RF_SysMem::Copy(Config.Hostname, hostname.c_str(), hostname.Size());
    }
}

} }