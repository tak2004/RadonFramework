#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/SessionServer.hpp"
#include "RadonFramework/Net/Socket.hpp"
#include "RadonFramework/Net/PacketStream.hpp"

namespace RadonFramework { namespace Net {

class Session
{
public:
    RF_Mem::AutoPointer<RF_Net::PacketStream> Stream;
    RF_Net::Socket* Socket;
};

void SessionServer::Update()
{
    Server::Update();

}

void SessionServer::SetLogicFactory(RF_Mem::AutoPointer<PacketLogicFactory>& Factory)
{
    m_Factory = Factory;
}

void SessionServer::AddedSocket(RF_Net::Socket& Socket, IPAddress& Interface)
{// never used by UDP
    Server::AddedSocket(Socket, Interface);
    
    Session* session = new Session;
    if(m_Sessions.Add(Socket.LocalEndPoint().Address().ToUInt32(), reinterpret_cast<void*>(session)))
    {
        session->Socket = &Socket;
        session->Stream = m_Factory->Generate();
    }
    else
    {
        delete session;
    }
}

void SessionServer::RemoveSocket(RF_Net::Socket& Socket, IPAddress& Interface)
{// never used by UDP
    Server::RemoveSocket(Socket, Interface);
    m_Sessions.Erase(Socket.LocalEndPoint().Address().ToUInt32());
}

RF_Type::Bool SessionServer::ProcessPacket(RF_Net::Socket& Socket,
    const IPAddress& Source, RF_Mem::AutoPointerArray<RF_Type::UInt8>& In)
{
    RF_Type::Bool result = false;
    result = Server::ProcessPacket(Socket, Source, In);
    Session* session = 0;
    if(m_Sessions.Get(Source.ToUInt32(), reinterpret_cast<void*&>(session)))
    {
        result = true;
    }
    else
    {// check if the packet is a UDP session start/stop message 

    }

    if(session)
    {
        session->Stream->Enqueue(In);
//        session->Stream->Dequeue();
    }
    return result;
}

} }