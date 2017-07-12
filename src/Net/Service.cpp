#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/Service.hpp"
#include "RadonFramework/Net/Server.hpp"
#include "RadonFramework/Time/TimeSpan.hpp"
#include "RadonFramework/Collections/AutoVector.hpp"
#include "RadonFramework/System/Network/NetService.hpp"
#include "RadonFramework/Net/ServerConfig.hpp"
#include "RadonFramework/Net/Socket.hpp"

namespace RadonFramework::Core::Idioms {

template<>
struct RF_Idiom::PImpl<RF_Net::Service>::Data
{
    Data()
    {
    }

    ~Data()
    {

    }

    RF_Net::ServiceIPVersion m_UsedIPVersion;
    RF_Net::ServiceInterfaceBinding m_Binding;
    RF_Collect::AutoVector<RF_Net::Server> m_ServerInstances;
};

}

namespace RadonFramework::Net {

Service::Service()
{

}

Service::~Service()
{

}

void Service::Setup(ServiceInterfaceBinding Binding, ServiceIPVersion Version)
{
    m_PImpl->m_Binding = Binding;
    m_PImpl->m_UsedIPVersion = Version;

    auto interfaces = RF_SysNet::NetService::GetLocalInterfaces();
    for(auto i = 0; i < interfaces.Count(); ++i)
    {
        if(IPAddress::IsPrivateNetworkAddress(interfaces(i).IP) && 
           (Binding==ServiceInterfaceBinding::Private || 
            Binding==ServiceInterfaceBinding::All))
        {
            RF_Mem::AutoPointer<Server> server(new Server);
            ServerConfig newConfig;
            newConfig.Blocking = false;
            newConfig.Family = interfaces(i).IP.GetAddressFamily();
            ServerConfig::AssignIPAsHostname(newConfig, interfaces(i).IP);
            newConfig.Port = 5353;
            newConfig.Protocol = SocketType::Datagram;
            server->Setup(newConfig);
            server->OnPreBind += Connector(&Service::PreBindConfigureSocket);
            server->OnPostBind += Connector(&Service::PostBindConfigureSocket);
            server->OnPacketReceived += Connector(&Service::PacketReceived);
            m_PImpl->m_ServerInstances.PushBack(server);
        }
    }
}

RF_Type::Bool Service::Shutdown(const Time::TimeSpan& ReturnAfter)
{
    RF_Type::Bool result = true;
    for(auto i = 0; i < m_PImpl->m_ServerInstances.Count(); ++i)
    {
        result |= m_PImpl->m_ServerInstances[i]->Shutdown(ReturnAfter);
    }
    return result;
}

void Service::Update()
{
    for(auto i = 0; i < m_PImpl->m_ServerInstances.Count(); ++i)
    {
        m_PImpl->m_ServerInstances[i]->Update();
    }
}

void Service::Start()
{
    for(auto i = 0; i < m_PImpl->m_ServerInstances.Count(); ++i)
    {
        m_PImpl->m_ServerInstances[i]->Start();
    }
}

void Service::Stop()
{
    for(auto i = 0; i < m_PImpl->m_ServerInstances.Count(); ++i)
    {
        m_PImpl->m_ServerInstances[i]->Stop();
    }
}

ServiceInterfaceBinding Service::GetBinding() const
{
    return m_PImpl->m_Binding;
}

ServiceIPVersion Service::GetUsedIPVersion() const
{
    return m_PImpl->m_UsedIPVersion;
}

void Service::PostBindConfigureSocket(ServerEvent& Sender)
{

}

void Service::PreBindConfigureSocket(ServerEvent& Sender)
{

}

void Service::PacketReceived(ServerProcessPacketEvent& Sender)
{

}

const RF_Collect::AutoVector<RF_Net::Server>& Service::GetServerList() const
{
    return m_PImpl->m_ServerInstances;
}

}