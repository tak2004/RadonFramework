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

namespace RadonFramework { namespace System { namespace Network {

class SelectObjectCollector;

} } }

namespace RadonFramework { namespace Net {
        
class PIMPL;
struct MulticastRequest;
        
class Socket
{
public:
    static RF_Mem::AutoPointer<Socket> Create(
        RF_SysNet::NetService::SocketHandler& Handler);

    static RF_Mem::AutoPointer<Socket> Create(
        const AddressFamily Family, const SocketType Type);
                
    static RF_Mem::AutoPointer<Socket> Create(
        const AddressFamily Family, const SocketType Type,
        SocketError& Error);

    ~Socket();
                
    SocketError Accept(RF_Mem::AutoPointer<Socket>& Client);

    SocketError Bind(const EndPoint& LocalEP);
                
    SocketError Connect(const EndPoint& RemoteEP);
    SocketError Connect(const IPAddress& IP, 
                        const RF_Type::UInt32 Port);
                
    SocketError Disconnect();
                
    SocketError Listen(const RF_Type::UInt32 MaxWaitingClients);
                
    SocketError Receive(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data);
                
    SocketError ReceiveFrom(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data,
                            const EndPoint &RemoteEP);                
                
    SocketError Send(const RF_Type::UInt8* Data, 
                        const RF_Type::UInt32 DataSize,
                        RF_Type::UInt32& SendDataSize);
    
    SocketError SendTo(const RF_Type::UInt8* Data,
                       const RF_Type::UInt32 DataSize, 
                       const EndPoint &RemoteEP, 
                       RF_Type::UInt32& SendDataSize);

    //SocketError::Type Shutdown(const SocketShutdown::Type How);              

    void AssignSelectObjectCollector(
        System::Network::SelectObjectCollector& Collector)const;

    SocketError Blocking(const RF_Type::Bool NewValue);
    RF_Type::Bool Blocking()const;

    EndPoint& LocalEndPoint()const;

    SocketError SetSocketOption(const SocketOptionLevel OptionLevel, 
        const SocketOptionName OptionName, const RF_Type::Bool Value);
    SocketError SetSocketOption(const SocketOptionLevel OptionLevel,
        const SocketOptionName OptionName, const RF_Type::UInt8 Value);
    SocketError SetSocketOption(const SocketOptionLevel OptionLevel, 
        const SocketOptionName OptionName, const RF_Type::Int32 Value);
    SocketError SetSocketOption(const SocketOptionLevel OptionLevel,
        const SocketOptionName OptionName, const IPAddress& Value);
    SocketError SetSocketOption(const SocketOptionLevel OptionLevel,
                                const SocketOptionName OptionName, 
                                const MulticastRequest& Value);
protected:
    PIMPL* m_Data;
private:
    Socket();
};
    
} }

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif // RF_NET_SOCKET_HPP
