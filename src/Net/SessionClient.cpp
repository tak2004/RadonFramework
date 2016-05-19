#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/SessionClient.hpp"
#include "RadonFramework/Net/Socket.hpp"
#include "RadonFramework/Net/PacketStream.hpp"

namespace RadonFramework { namespace Net {

RF_Type::Bool SessionClient::ProcessPacket(Socket& Socket, const IPAddress& Source,
    RF_Mem::AutoPointerArray<RF_Type::UInt8>& In)
{
    RF_Type::Bool result = false;
    result = Client::ProcessPacket(Socket, Source, In);
    if(m_PacketStream)
    {
        m_PacketStream->Enqueue(In);
        result = true;
    }
    return result;
}

void SessionClient::SetLogicFactory(RF_Mem::AutoPointer<PacketLogicFactory>& Factory)
{
    m_Factory = Factory;
}

void SessionClient::Connect(const IPAddress& IP, const RF_Type::UInt16 Port)
{
    if(IsConnected())
    {
        m_PacketStream.Release();
    }

    Client::Connect(IP, Port);

    if(IsConnected())
    {
        m_PacketStream = m_Factory->Generate();
    }
}

} }