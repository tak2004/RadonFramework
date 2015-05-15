#ifndef RF_NET_MDNS_SERVICEDISCOVERY_HPP
#define RF_NET_MDNS_SERVICEDISCOVERY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/Server.hpp>

namespace RadonFramework { namespace Collections {

template<class T>
class AutoVector;

} }

namespace RadonFramework { namespace Net { namespace mDNS {

class NetworkService;

class ServiceDiscovery: public Server
{
public:
    ServiceDiscovery();
    virtual ~ServiceDiscovery();

    const Collections::AutoVector<NetworkService>& KnownServices()const;
    RF_Type::Bool IsKnown(const RF_Type::String& Servicename)const;
    NetworkService* FindService(const RF_Type::String& Servicename)const;
private:
    RF_Idiom::PImpl<ServiceDiscovery> m_PImpl;
};

} } }

#endif // RF_NET_MDNS_SERVICEDISCOVERY_HPP