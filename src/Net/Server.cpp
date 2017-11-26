#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/Server.hpp"
#include "RadonFramework/Net/ServerConfig.hpp"
#include "RadonFramework/Net/Socket.hpp"
#include "RadonFramework/Net/IPAddress.hpp"
#include "RadonFramework/Time/TimeSpan.hpp"
#include <RadonFramework/System/Network/SelectObjectCollector.hpp>

namespace RadonFramework::Core::Idioms {
template<>
struct PImpl<RF_Net::Server>::Data
{
    Data()
    {}

    ~Data()
    {}

    RF_Net::ServerConfig m_Config;
    RF_Collect::List<RF_Mem::AutoPointer<RF_Net::Socket> > m_Sockets;
    RF_Mem::AutoPointer<RF_SysNet::SelectObjectCollector> m_Pool;
    RF_Net::IPAddress m_IP;
    RF_Net::EndPoint m_RemoteEndpoint;
};
}

namespace RadonFramework::Net {

Server::Server()
{

}

Server::~Server()
{

}

void Server::Setup(const ServerConfig& NewConfiguration)
{
    m_PImpl->m_Config = NewConfiguration;
}

RF_Type::Bool Server::Start()
{
    RF_Type::Bool result = false;
    RF_Mem::AutoPointer<Socket> serverSocket = Socket::Create(m_PImpl->m_Config.Family, m_PImpl->m_Config.Protocol);
    if(serverSocket)
    {
        RF_Type::String hostname(m_PImpl->m_Config.Hostname);
        IPAddress ip;
        if(hostname == "*")
        {
            switch(m_PImpl->m_Config.Family)
            {
            case AddressFamily::InterNetwork:
                ip = IPAddress::IPv4Any;
                result = true;
                break;
            case AddressFamily::InterNetwork6:
                ip = IPAddress::IPv6Any;
                result = true;
                break;
            }
        }
        else
        {
            result = IPAddress::Resolve(hostname, ip);
        }

        if(result)
        {
            PreBindConfigureSocket(*serverSocket, ip);

            RF_Net::EndPoint endPoint(ip, m_PImpl->m_Config.Port);
            if(serverSocket->Bind(endPoint))
            {
                if(m_PImpl->m_Config.Protocol == RF_Net::SocketType::Stream)
                {
                    result = serverSocket->Listen(m_PImpl->m_Config.MaxConcurrentSessions);
                    if(result)
                    {
                        m_PImpl->m_Pool = RF_SysNet::SelectObjectCollector::Create(*serverSocket);
                    }
                }
                else
                {
                    result = true;
                }
            }

            PostBindConfigureSocket(*serverSocket, ip);
        }

        if(result)
        {
            m_PImpl->m_IP = serverSocket->LocalEndPoint().Address();
            m_PImpl->m_Sockets.AddFirst(serverSocket);
        }
    }
    return result;
}

void Server::Stop()
{
    Shutdown(Time::TimeSpan());
    m_PImpl->m_Pool.Reset();
    m_PImpl->m_Sockets.Clear();
    m_PImpl->m_IP = IPAddress::IPv4None;
}

RF_Type::Bool Server::Shutdown(const Time::TimeSpan& ReturnAfter)
{
    return true;
}

const ServerConfig& Server::Configuration() const
{
    return m_PImpl->m_Config;
}

void Server::Update()
{
    if(m_PImpl->m_Config.Protocol == RF_Net::SocketType::Stream)
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> packet;
        RF_Mem::AutoPointer<RF_Net::Socket> newSession;
        
        if(m_PImpl->m_Pool->Select(SelectMode::Read) == Error::Ok)
        {
            for(RF_Type::Size i = 0; i < m_PImpl->m_Pool->Count(); ++i)
            {
                if(m_PImpl->m_Pool->IsSet(i))
                {
                    if(i > 0)
                    {
                        if(m_PImpl->m_Sockets[i]->Receive(packet).Code != Error::ConnectionReset)
                        {
                            ProcessPacket(*m_PImpl->m_Sockets[i], m_PImpl->m_Sockets[i]->LocalEndPoint().Address(), packet);
                        }
                        else
                        {
                            RemoveSocket(*m_PImpl->m_Sockets[i], m_PImpl->m_IP);
                            m_PImpl->m_Pool->Remove(i);
                            m_PImpl->m_Sockets.RemoveAt(i);                            
                        }
                    }
                    else
                    {
                        if(m_PImpl->m_Sockets[0]->Accept(newSession))
                        {
                            newSession->AssignSelectObjectCollector(*m_PImpl->m_Pool);
                            auto* session = newSession.Get();
                            m_PImpl->m_Sockets.AddLast(newSession);
                            AddedSocket(*session, m_PImpl->m_IP);
                        }
                    }
                }
            }
        }
    }
    else
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> packet;
        EndPoint ep;
        m_PImpl->m_Sockets[0]->ReceiveFrom(packet, ep);
        if(packet)
        {
            ProcessPacket(*m_PImpl->m_Sockets[0], ep.Address(), packet);
        }
    }
}

const IPAddress& Server::InterfaceIp()const
{
    return m_PImpl->m_IP;
}

RF_Type::Bool Server::ProcessPacket(Socket& Socket, 
    const IPAddress& Source, RF_Mem::AutoPointerArray<RF_Type::UInt8>& In)
{
    ServerProcessPacketEvent event;
    event.Config = &m_PImpl->m_Config;
    event.Target = &Socket;
    event.Data = &In;
    event.Source = &Source;
    OnPacketReceived(event);
    return true;
}

Socket* Server::GetSocket() const
{
    Socket* result = 0;
    if(m_PImpl->m_Sockets.Count())
    {
        result = m_PImpl->m_Sockets[0].Get();
    }
    return result;
}

void Server::PostBindConfigureSocket(Socket& Socket, IPAddress& Interface)
{
    ServerEvent event;
    event.Config = &m_PImpl->m_Config;
    event.Target = &Socket;
    OnPostBind(event);
}

void Server::PreBindConfigureSocket(Socket& Socket, IPAddress& Interface)
{
    SocketError error;
    error.Code = Error::Ok;
    error = Socket.Blocking(m_PImpl->m_Config.Blocking);
    error = Socket.SetSocketOption(SocketOptionLevel::Socket, SocketOptionName::ReuseAddress, true);

    ServerEvent event;
    event.Config = &m_PImpl->m_Config;
    event.Target = &Socket;
    OnPreBind(event);
}

void Server::AddedSocket(Socket& Socket, IPAddress& Interface)
{
    ServerEvent event;
    event.Config = &m_PImpl->m_Config;
    event.Target = &Socket;
    OnAddedSocket(event);
}

void Server::RemoveSocket(Socket& Socket, IPAddress& Interface)
{
    ServerEvent event;
    event.Config = &m_PImpl->m_Config;
    event.Target = &Socket;
    OnRemoveSocket(event);
}

void Server::SendToAll(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data)
{
    for (auto socket: m_PImpl->m_Sockets)
    {
        RF_Type::UInt32 sendBytes;
        socket->Send(Data.Get(),Data.Count(),sendBytes);
    }    
}

}