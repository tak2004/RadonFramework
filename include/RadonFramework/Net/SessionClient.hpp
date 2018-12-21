#ifndef RF_NET_SESSIONCLIENT_HPP
#define RF_NET_SESSIONCLIENT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/Client.hpp>
#include <RadonFramework/Net/PacketLogicFactory.hpp>

namespace RadonFramework::Net
{
class SessionClient : public Client
{
public:
  void SetLogicFactory(RF_Mem::AutoPointer<PacketLogicFactory>& Factory);
  void Connect(const IPAddress& IP, const RF_Type::UInt16 Port) override;

protected:
  RF_Type::Bool
  ProcessPacket(Socket& Socket,
                const IPAddress& Source,
                RF_Mem::AutoPointerArray<RF_Type::UInt8>& In) override;

private:
  RF_Mem::AutoPointer<PacketLogicFactory> m_Factory;
  RF_Mem::AutoPointer<PacketStream> m_PacketStream;
};

}  // namespace RadonFramework::Net

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif