#ifndef RF_NET_CLIENTPOOL_HPP
#define RF_NET_CLIENTPOOL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>

namespace RadonFramework::System::Network
{
class SelectObjectCollector;
}

namespace RadonFramework::Net
{
class Client;

class ClientPool
{
public:
  using ClientList = RF_Collect::List<RF_Mem::AutoPointer<Client>>;

  void AttachClient(RF_Mem::AutoPointer<Client>& NewClient);
  void DetachClient(const Client& Instance);
  const ClientList& GetClients() const;
  void Update();

private:
  ClientList m_Clients;
  RF_Mem::AutoPointer<System::Network::SelectObjectCollector> m_Pool;
};

}  // namespace RadonFramework::Net

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif  // !RF_NET_CLIENTPOOL_HPP
