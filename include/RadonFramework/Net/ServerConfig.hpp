#ifndef RF_NET_SERVERCONFIG_HPP
#define RF_NET_SERVERCONFIG_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/Char.hpp>

namespace RadonFramework
{
    namespace Net
    {
        struct ServerConfigData
        {
            static const RFTYPE::UInt32 RF_NET_HTTP_MAXHOSTNAME=256;

            /** If the Port is set to 0 then the Server use the first 
              * available port and change this value.
              **/
            RFTYPE::UInt32 Port;

            /** The number of maximal concurrent sessions, each new session
              * will be denied.
              **/
            RFTYPE::UInt32 MaxConcurrentSessions;

            /** Can contain a IP, hostname or * to use the first available IP.
              * If is set the value will be replaced by the choosen IP. 
              **/
            RFTYPE::Char Hostname[RF_NET_HTTP_MAXHOSTNAME]; 
        };

        class ServerConfig
        {
            public:
                ServerConfig();
                ~ServerConfig();
                ServerConfig(const ServerConfig& Copy);
                ServerConfig& operator=(const ServerConfig& Other);
                // Reader functionality
                RFTYPE::Bool ReadFromBinaryData(
                    Memory::AutoPointerArray<RFTYPE::UInt8> Data);
                // Writer functionality
                Memory::AutoPointerArray<RFTYPE::UInt8> GenerateBinaryData();
            protected:
                Memory::AutoPointer<ServerConfigData> m_Data;
        };
    }
}

#endif // RF_NET_SERVERCONFIG_HPP