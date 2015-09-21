#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/mDNS/ServiceDiscovery.hpp"
#include "RadonFramework/Net/mDNS/NetworkService.hpp"
#include "RadonFramework/Net/mDNS/MessageWriter.hpp"
#include "RadonFramework/Collections/AutoVector.hpp"
#include "RadonFramework/Collections/HashMap.hpp"
#include "RadonFramework/Net/Socket.hpp"
#include "RadonFramework/Net/MulticastRequest.hpp"

template<>
struct RF_Idiom::PImpl<RF_mDNS::ServiceDiscovery>::Data
{
    Data()        
    {
        m_UpdatePeriod = RF_Time::TimeSpan::CreateByTime(0, 0, 5);
        m_NextQuery = RF_Time::DateTime::CreateByTicks(0, RF_Time::DateTimeKind::UTC);
    }

    ~Data()
    {

    }

    RF_Collect::AutoVector<RF_mDNS::NetworkService> m_KnownServices;
    RF_Collect::HashMap<const char*, RF_mDNS::NetworkService*> m_KnownServicesDictionary;
    RF_Time::DateTime m_NextQuery;
    RF_Time::TimeSpan m_UpdatePeriod;
    RF_Net::EndPoint m_Endpoint;
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

void ServiceDiscovery::PreBindConfigureSocket(Socket& Socket, IPAddress& Interface)
{
    Server::PreBindConfigureSocket(Socket, Interface);

    SocketError error;
    error.Code = Error::Ok;
    error = Socket.SetSocketOption(SocketOptionLevel::Socket, SocketOptionName::ReusePort, true);
    error = Socket.SetSocketOption(SocketOptionLevel::IPv4, SocketOptionName::MulticastInterface, Interface);
}

void ServiceDiscovery::PostBindConfigureSocket(Socket& Socket, IPAddress& Interface)
{
    IPAddress ip;
    IPAddress::Resolve("224.0.0.251", ip);
    m_PImpl->m_Endpoint.Address(ip);
    m_PImpl->m_Endpoint.Port(5353);

    Server::PostBindConfigureSocket(Socket, ip);

    SocketError error;
    error.Code = Error::Ok;

    MulticastRequest multicastRequest;
    multicastRequest.MulticastAddress = ip;
    multicastRequest.Interface = Interface;

    error = Socket.SetSocketOption(SocketOptionLevel::IPv4, SocketOptionName::MutlicastTimeToLive, RF_Type::UInt8(255));
    //error = Socket.SetSocketOption(SocketOptionLevel::IPv4, SocketOptionName::MulticastLoopback, true);
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

void ServiceDiscovery::Update()
{
    Server::Update();

    RF_Time::DateTime now = RF_Time::DateTime::UtcNow();
    if(RF_Time::DateTime::LessThan(m_PImpl->m_NextQuery, now))
    {        
        m_PImpl->m_NextQuery = RF_Time::DateTime::CreateByTicks(now.Ticks() + m_PImpl->m_UpdatePeriod.Ticks());

        MessageWriter writer;
        writer.WriteQueryHeader(0);
        writer.WriteQuestion("_pbms._tcp.local", RecordType::PTR);
        RF_Type::UInt32 sendBytes = 0;
        writer.Finalize();
        GetSocket()->SendTo(writer.Data(), writer.DataSize(),m_PImpl->m_Endpoint, sendBytes);
    }
}

} } }