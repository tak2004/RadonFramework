#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Net/mDNS/ServiceDiscovery.hpp>
#include <RadonFramework/Net/mDNS/NetworkService.hpp>
#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Collections/HashMap.hpp>

template<>
struct RF_Idiom::PImpl<RF_mDNS::ServiceDiscovery>::Data
{
    Data()
    {

    }

    ~Data()
    {

    }

    RF_Collect::AutoVector<RF_mDNS::NetworkService> m_KnownServices;
    RF_Collect::HashMap<const char*, RF_mDNS::NetworkService*> m_KnownServicesDictionary;
};

namespace RadonFramework { namespace Net { namespace mDNS {

ServiceDiscovery::ServiceDiscovery()
:Server()
{

}

ServiceDiscovery::~ServiceDiscovery()
{

}

const RF_Collect::AutoVector<NetworkService>& ServiceDiscovery::KnownServices() const
{
    return m_PImpl->m_KnownServices;
}

RF_Type::Bool ServiceDiscovery::IsKnown(const RF_Type::String& Servicename) const
{
    return false;
}

NetworkService* ServiceDiscovery::FindService(const RF_Type::String& Servicename) const
{
    return 0;
}

} } }