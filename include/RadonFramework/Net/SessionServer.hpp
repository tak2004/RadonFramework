#ifndef RF_NET_SESSIONSERVER_HPP
#define RF_NET_SESSIONSERVER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/Server.hpp>
#include <RadonFramework/Net/PacketLogicFactory.hpp>
#include <RadonFramework/Collections/HashList.hpp>
#include <RadonFramework/Collections/Queue.hpp>

namespace RadonFramework { namespace Net {

class SessionServer : public Server, public RF_Pattern::IObserver
{
public: 
    virtual ~SessionServer()override;
    virtual void Update()override;
    void SetLogicFactory(RF_Mem::AutoPointer<PacketLogicFactory>& Factory);
    void SessionResponse(RF_Type::UInt32 Session);
protected:
    virtual void AddedSocket(Socket& Socket, IPAddress& Interface)override;
    virtual void RemoveSocket(Socket& Socket, IPAddress& Interface)override;
    virtual RF_Type::Bool ProcessPacket(Socket& Socket,
        const IPAddress& Source, RF_Mem::AutoPointerArray<RF_Type::UInt8>& In)override;
private:
    RF_Collect::HashList m_Sessions;
    RF_Mem::AutoPointer<PacketLogicFactory> m_Factory;
    RF_Collect::Queue<RF_Type::UInt32> m_SessionsWithResponses;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif // RF_NET_SESSIONSERVER_HPP