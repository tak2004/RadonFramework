#ifndef RF_NET_SERVER_HPP
#define RF_NET_SERVER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Event.hpp>

namespace RadonFramework { namespace Time {

struct TimeSpan;

} }

namespace RadonFramework { namespace Net {

struct ServerConfig;
class IPAddress;
class Socket;

struct ServerEvent
{
    ServerConfig* Config;
    Socket* Target;
};

struct ServerProcessPacketEvent
{
    ServerConfig* Config;
    Socket* Target;
    const IPAddress* Source;
    RF_Mem::AutoPointerArray<RF_Type::UInt8>* Data;
};

class Server
{
public:
    Server();
    virtual ~Server();

    virtual void Setup(const ServerConfig& NewConfiguration);

    /// Setup and start the server.
    virtual RF_Type::Bool Start();

    /// The server will be forced to stop and cancel all pending requests.
    virtual void Stop();

    virtual void Update();

    /** The server will be deny new incoming request, process
    * all pending requests and shutdown after this. If the
    * ReturnAfter parameter is greater 0 then the Shutdown
    * method will return after waiting for the given time.
    * If the method take longer as the ReturnAfter time then
    * TimedOut will be returned else Ok.
    **/
    virtual RF_Type::Bool Shutdown(const Time::TimeSpan& ReturnAfter);

    /// Return the configuration from the server.
    const ServerConfig& Configuration()const;

    const IPAddress& InterfaceIp()const;

    Socket* GetSocket()const;
    
    RF_Pattern::Event<ServerEvent&> OnPreBind;
    RF_Pattern::Event<ServerEvent&> OnPostBind;
    RF_Pattern::Event<ServerProcessPacketEvent&> OnPacketReceived;
    RF_Pattern::Event<ServerEvent&> OnAddedSocket;
    RF_Pattern::Event<ServerEvent&> OnRemoveSocket;
protected:
    /// Will be called for every incoming packet.
    virtual RF_Type::Bool ProcessPacket(Socket& Socket, 
        const IPAddress& Source, RF_Mem::AutoPointerArray<RF_Type::UInt8>& In);
    /// Will be called after the server listen socket was created.
    virtual void PostBindConfigureSocket(Socket& Socket, IPAddress& Interface);
    /// Will be called before the server listen socket is created.
    virtual void PreBindConfigureSocket(Socket& Socket, IPAddress& Interface);
    /// Will be called right after the socket was added to the server.
    virtual void AddedSocket(Socket& Socket, IPAddress& Interface);
    /// Will be called before the socket will be removed from the server.
    virtual void RemoveSocket(Socket& Socket, IPAddress& Interface);
private:
    RF_Idiom::PImpl<Server> m_PImpl;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif // RF_NET_SERVER_HPP
