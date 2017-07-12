#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/mDNS/ServiceResponder.hpp"
#include "RadonFramework/Net/ServerConfig.hpp"
#include "RadonFramework/Net/Socket.hpp"
#include "RadonFramework/Net/mDNS/MessageWriter.hpp"

namespace RadonFramework::Net::mDNS {

ServiceResponder::ServiceResponder()
:Server()
{
    m_LastPush = RF_Time::DateTime::UtcNow();
}

ServiceResponder::~ServiceResponder()
{

}

const NetworkServiceInfo& ServiceResponder::Info() const
{
    return m_Service;
}

void ServiceResponder::Setup(const NetworkServiceInfo& NewConfiguration,
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

void ServiceResponder::SendServiceInfo()
{
    RF_Type::UInt32 sendBytes = 0;
    IPAddress ip;
    IPAddress::Resolve("224.0.0.251"_rfs, ip);
    EndPoint destination;
    destination.Address(ip);
    destination.Port(5353);

    MessageWriter writer;
    writer.WriteQueryHeader(0);
    writer.WriteQuestion(m_Service.Name, RecordType::SRV);
    writer.Finalize();
    this->GetSocket()->SendTo(writer.Data(), writer.DataSize(), destination, sendBytes);

    auto hostname = RF_SysNet::NetService::GetHostname() + ".local"_rfs;
    writer.Reset();
    writer.WriteQueryHeader(0, 1<<15);
    writer.WriteAnswerServerSelection(m_Service.Name, hostname,
        m_Service.Port, RF_mDNS::RecordClass::Internet, true);

    writer.WriteAdditionalAnswer(hostname, m_Service.IPAddress, 
        RF_mDNS::RecordClass::Internet, true);

    writer.Finalize();
    this->GetSocket()->SendTo(writer.Data(), writer.DataSize(), destination, sendBytes);
}

void ServiceResponder::Update()
{
    Server::Update();
    RF_Time::DateTime now = RF_Time::DateTime::UtcNow();
    if(RF_Time::DateTime::GreaterThan(now, m_LastPush))
    {
        m_LastPush = RF_Time::DateTime::CreateByTicks(now.Ticks() + RF_Time::TimeSpan::TicksPerMinute);
        SendServiceInfo();
    }
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
        IPAddress::Resolve("224.0.0.251"_rfs, ip);

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

}