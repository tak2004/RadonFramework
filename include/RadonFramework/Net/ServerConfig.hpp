#ifndef RF_NET_SERVERCONFIG_HPP
#define RF_NET_SERVERCONFIG_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/AddressFamily.hpp>
#include <RadonFramework/Net/SocketType.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/Char.hpp>

namespace RadonFramework::Net {

class IPAddress;

struct ServerConfig
{
    enum 
    {
        MAXHOSTNAME=256
    };

    AddressFamily Family;

    SocketType Protocol;

    /** If the Port is set to 0 then the Server use the first 
    * available port and change this value.
    **/
    RF_Type::UInt32 Port;

    /** The number of maximal concurrent sessions, each new session
    * will be denied.
    **/
    RF_Type::UInt32 MaxConcurrentSessions;

    /** Can contain a IP, hostname or * to use the first available IP.
    * If set the value will be replaced by the chosen IP. 
    **/
    RF_Type::Char Hostname[MAXHOSTNAME]; 

    RF_Type::Bool Blocking;

    static void AssignIPAsHostname(ServerConfig& Config, const IPAddress IP);
};
    
}

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif // RF_NET_SERVERCONFIG_HPP
