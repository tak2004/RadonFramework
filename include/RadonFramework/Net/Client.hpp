#ifndef RF_NET_CLIENT_HPP
#define RF_NET_CLIENT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Event.hpp>
#include <RadonFramework/Core/Pattern/Signal.hpp>

namespace RadonFramework { namespace Net {

class IPAddress;
class Socket;

struct ClientProcessPacketEvent
{
    Socket* Target;
    const IPAddress* Source;
    RF_Mem::AutoPointerArray<RF_Type::UInt8>* Data;
};

class Client
{
public:
    Client();
    virtual void Connect(const IPAddress& IP, const RF_Type::UInt16 Port);
    virtual void Update();
    RF_Type::Bool IsConnected();
    virtual void Send(RF_Mem::AutoPointerArray<RF_Type::UInt8> Data);

    RF_Pattern::Event<ClientProcessPacketEvent&> OnPacketReceived;
    RF_Pattern::Signal OnDisconnect;
protected:
    virtual RF_Type::Bool ProcessPacket(Socket& Socket,
        const IPAddress& Source, RF_Mem::AutoPointerArray<RF_Type::UInt8>& In);
private:
    RF_Idiom::PImpl<Client> m_Data;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif