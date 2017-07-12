#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/ClientPool.hpp"
#include "RadonFramework/Net/Client.hpp"
#include "RadonFramework/System/Network/SelectObjectCollector.hpp"


namespace RadonFramework::Net {

void ClientPool::AttachClient(RF_Mem::AutoPointer<RF_Net::Client>& NewClient)
{
	NewClient->GetSocket()->AssignSelectObjectCollector(*m_Pool);
}

void ClientPool::DetachClient(const RF_Net::Client& Instance)
{
	Instance.GetSocket()->DetachFromSelectObjectCollector(*m_Pool);
}

const RadonFramework::Net::ClientPool::ClientList& ClientPool::GetClients() const
{
	return m_Clients;
}

void ClientPool::Update()
{
	
}

}