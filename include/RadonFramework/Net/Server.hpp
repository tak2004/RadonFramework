#ifndef RF_NET_SERVER_HPP
#define RF_NET_SERVER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Time {

class TimeSpan;

} }

namespace RadonFramework { namespace Net {

struct ServerConfig;
class IPAddress;
class Socket;

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
protected:
    virtual RF_Type::Bool ProcessPacket(RF_Mem::AutoPointerArray<RF_Type::UInt8>& In);
    Socket* GetSocket()const;
    virtual void PostBindConfigureSocket(Socket& Socket, IPAddress& Interface);
    virtual void PreBindConfigureSocket(Socket& Socket, IPAddress& Interface);
private:
    RF_Idiom::PImpl<Server> m_PImpl;
};

} }

#endif // RF_NET_SERVER_HPP
