#ifndef RF_NET_SOCKET_HPP
#define RF_NET_SOCKET_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Net/SocketType.hpp>
#include <RadonFramework/Net/AddressFamily.hpp>
#include <RadonFramework/Net/SocketError.hpp>
#include <RadonFramework/System/Network/NetService.hpp>

namespace RadonFramework
{
    namespace System
    {
        namespace Network
        {
            class SelectObjectCollector;
        }
    }
    namespace Net
    {
        class PIMPL;
        
        class Socket
        {
            public:
                static Memory::AutoPointer<Socket> Create(
                    System::Network::NetService::SocketHandler& Handler);

                static Memory::AutoPointer<Socket> Create(
                    const AddressFamily::Type Family, const SocketType::Type Type);
                
                static Memory::AutoPointer<Socket> Create(
                    const AddressFamily::Type Family, const SocketType::Type Type,
                    SocketError& Error);

                ~Socket();
                
                SocketError Accept(Memory::AutoPointer<Socket>& Client);

                SocketError Bind(const EndPoint& LocalEP);
                
                SocketError Connect(const EndPoint& RemoteEP);
                SocketError Connect(const IPAddress& IP, 
                                    const Core::Types::UInt32 Port);
                
                //SocketError Disconnect();
                
                SocketError Listen(const Core::Types::UInt32 MaxWaitingClients);
                
                SocketError Receive(Memory::AutoPointerArray<Core::Types::UInt8>& Data);
                
                SocketError ReceiveFrom(Memory::AutoPointerArray<Core::Types::UInt8>& Data, 
                                        const EndPoint &RemoteEP);                
                
                SocketError Send(const Core::Types::UInt8* Data, 
                                 const Core::Types::UInt32 DataSize,
                                 Core::Types::UInt32& SendDataSize);
                /*
                SocketError::Type SendTo(const Memory::AutoPointerArray<Core::Types::UInt8> Data,
                                         const Core::Types::UInt32 DataSize, 
                                         const EndPoint &RemoteEP, 
                                         Memory::AutoPointer<Core::Types::UInt32>& SendDataSize);

                SocketError::Type Shutdown(const SocketShutdown::Type How);              
               */
                void AssignSelectObjectCollector(
                    System::Network::SelectObjectCollector& Collector)const;
            protected:
                PIMPL* m_Data;
            private:
                Socket();
        };
    }
}

#endif // RF_NET_SOCKET_HPP
