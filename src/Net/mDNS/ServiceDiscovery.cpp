#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/mDNS/ServiceDiscovery.hpp"
#include "RadonFramework/Net/mDNS/NetworkService.hpp"
#include "RadonFramework/Collections/AutoVector.hpp"
#include "RadonFramework/Collections/HashMap.hpp"
#include "RadonFramework/Net/Socket.hpp"
#include "RadonFramework/Net/MulticastRequest.hpp"

template<>
struct RF_Idiom::PImpl<RF_mDNS::ServiceDiscovery>::Data
{
    Data()
    {

    }

    ~Data()
    {

    }

    RF_Collect::AutoVector<RF_mDNS::NetworkService> m_KnownServices;
    RF_Collect::HashMap<const char*, RF_mDNS::NetworkService*> m_KnownServicesDictionary;
};

namespace RadonFramework { namespace Net { namespace mDNS {

ServiceDiscovery::ServiceDiscovery()
:Server()
{

}

ServiceDiscovery::~ServiceDiscovery()
{

}

const RF_Collect::AutoVector<NetworkService>& ServiceDiscovery::KnownServices() const
{
    return m_PImpl->m_KnownServices;
}

RF_Type::Bool ServiceDiscovery::IsKnown(const RF_Type::String& Servicename) const
{
    return false;
}

NetworkService* ServiceDiscovery::FindService(const RF_Type::String& Servicename) const
{
    return 0;
}

void ServiceDiscovery::ConfigureSocket(Socket& Socket, IPAddress& Interface)
{
    Server::ConfigureSocket(Socket, Interface);

    SocketError error;
    error.Code = Error::Ok;
    IPAddress ip;
    IPAddress::Resolve("224.0.0.251", ip);
    MulticastRequest multicastRequest;
    multicastRequest.MulticastAddress = ip;
    multicastRequest.Interface = Interface;

    error = Socket.SetSocketOption(SocketOptionLevel::Socket, SocketOptionName::ReusePort, true);
    error = Socket.SetSocketOption(SocketOptionLevel::IPv4, SocketOptionName::MutlicastTimeToLive, RF_Type::UInt8(255));
    error = Socket.SetSocketOption(SocketOptionLevel::IPv4, SocketOptionName::MulticastLoopback, true);
    error = Socket.SetSocketOption(SocketOptionLevel::IPv4, SocketOptionName::MulticastInterface, Interface);
    error = Socket.SetSocketOption(SocketOptionLevel::IPv4, SocketOptionName::AddMembership, multicastRequest);
}

RF_Type::Bool ServiceDiscovery::ProcessPacket(RF_Mem::AutoPointerArray<RF_Type::UInt8>& In)
{
    int i = 0;
    return false;
}

RF_Type::Bool ServiceDiscovery::Shutdown(const Time::TimeSpan& ReturnAfter)
{
    RF_Type::Bool result = Server::Shutdown(ReturnAfter);
    if(result)
    {
        IPAddress ip, multicastIP;
        IPAddress::Resolve("224.0.0.251", ip);
        IPAddress::Resolve("0.0.0.0", multicastIP);
        MulticastRequest multicastRequest;
        multicastRequest.MulticastAddress = ip;
        multicastRequest.Interface = multicastIP;
        GetSocket()->SetSocketOption(SocketOptionLevel::IPv4, SocketOptionName::DropMembership, multicastRequest);
    }
    return result;
}

} } }