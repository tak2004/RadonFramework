#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/Client.hpp"
#include "RadonFramework/Net/Socket.hpp"

namespace RadonFramework { namespace Core { namespace Idioms {

template<>
struct PImpl<RF_Net::Client>::Data
{
    Data()
    :m_IsConnected(false)
    {
        m_Socket = RF_Net::Socket::Create(RF_Net::AddressFamily::InterNetwork, RF_Net::SocketType::Stream);
    }

    ~Data()
    {
    }

    RF_Mem::AutoPointer<RF_Net::Socket> m_Socket;
    RF_Type::Bool m_IsConnected;
};

} } }

namespace RadonFramework { namespace Net {

Client::Client()
{

}

void Client::Connect(const IPAddress& IP, const RF_Type::UInt16 Port)
{
    if(m_Data->m_IsConnected)
    {
        m_Data->m_Socket->Disconnect();
        m_Data->m_IsConnected = false;
    }

    auto status = m_Data->m_Socket->Connect(IP, Port);
    if(status)
    {
        m_Data->m_IsConnected = true;
        // wait till the connection is accomplished and then switch to non blocking
        m_Data->m_Socket->Blocking(false);
    }
}

void Client::Update()
{
    if(m_Data->m_IsConnected)
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> packet;
        auto status = m_Data->m_Socket->Receive(packet);
        switch(status.Code)
        {
        case Error::Ok:
            ProcessPacket(*m_Data->m_Socket, m_Data->m_Socket->LocalEndPoint().Address(), packet);
            break;
        case Error::ConnectionReset:
            m_Data->m_IsConnected = false;
            break;
        default:
            break;
        }
    }
}

RF_Type::Bool Client::IsConnected()
{
    return m_Data->m_IsConnected;
}

RF_Type::Bool Client::ProcessPacket(Socket& Socket, const IPAddress& Source,
    RF_Mem::AutoPointerArray<RF_Type::UInt8>& In)
{
    RF_Type::Bool result = true;
    ClientProcessPacketEvent event;
    event.Data = &In;
    event.Source = &Source;
    event.Target = &Socket;
    OnPacketReceived(event);
    return result;
}

} }