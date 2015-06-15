#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/mDNS/ServiceResponder.hpp"
#include "RadonFramework/Net/ServerConfig.hpp"
#include "RadonFramework/Net/Socket.hpp"

namespace RadonFramework { namespace Net { namespace mDNS {

ServiceResponder::ServiceResponder()
:Server()
{
}

ServiceResponder::~ServiceResponder()
{

}

const NetworkService& ServiceResponder::Info() const
{
    return m_Service;
}

void ServiceResponder::Setup(const NetworkService& NewConfiguration,
                             RF_Type::Bool Blocking /*= true*/)
{
    m_Service = NewConfiguration;

    ServerConfig config;
    config.Blocking = Blocking;
    config.Family = AddressFamily::InterNetwork;
    config.Protocol = SocketType::Datagram;
    config.Port = 5353;
    config.MaxConcurrentSessions = 5;
    RF_SysMem::Copy(config.Hostname, "224.0.0.251", sizeof("224.0.0.251"));

    Setup(config);
}

void ServiceResponder::Setup(const ServerConfig& NewConfiguration)
{
    Server::Setup(NewConfiguration);
}

RF_Type::Bool ServiceResponder::Start()
{
    RF_Type::Bool result = Server::Start();
    if(result && GetSocket())
    {
        Socket* socket = GetSocket();
        RF_Net::SocketError error;
        error.Code = Error::Ok;
        // don't send data to loopback adapter
        error = socket->SetSocketOption(SocketOptionLevel::IPv4, SocketOptionName::MulticastLoopback, false);
        // data should pass the local network
        error = socket->SetSocketOption(SocketOptionLevel::IPv4, SocketOptionName::MutlicastTimeToLive, RF_Type::UInt8(255));
        // join the multicast group which tells the OS to stop dropping the packets with this destination
        IPAddress ip;
        IPAddress::Resolve("224.0.0.251", ip);

        MulticastRequest multicastRequest;
        multicastRequest.MulticastAddress = ip;
        multicastRequest.Interface = IPAddress::IPv4Any;
        error = socket->SetSocketOption(SocketOptionLevel::IPv4, SocketOptionName::AddMembership, multicastRequest);
        // specify the network adapter we want to work with
        error = socket->SetSocketOption(SocketOptionLevel::IPv4, SocketOptionName::MulticastInterface, IPAddress::IPv4Any);
    }
    else
    {
        result = false;
    }
    return result;
}

} } }