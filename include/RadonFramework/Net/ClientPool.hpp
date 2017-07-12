#ifndef RF_NET_CLIENTPOOL_HPP
#define RF_NET_CLIENTPOOL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/List.hpp>

namespace RadonFramework::System::Network {

class SelectObjectCollector;

}

namespace RadonFramework::Net {

class Client;

class ClientPool
{
public:
	typedef RF_Collect::List<RF_Mem::AutoPointer<Client>> ClientList;

	void AttachClient(RF_Mem::AutoPointer<Client>& NewClient);
	void DetachClient(const Client& Instance);
	const ClientList& GetClients()const;
	void Update();
private:
	ClientList m_Clients;
	RF_Mem::AutoPointer<System::Network::SelectObjectCollector> m_Pool;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif // !RF_NET_CLIENTPOOL_HPP
