#ifndef RF_NET_MDNS_SERVICEDISCOVERYVIEW_HPP
#define RF_NET_MDNS_SERVICEDISCOVERYVIEW_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include "RadonFramework/Net/mDNS/NetworkService.hpp"

namespace RadonFramework { namespace Net { class IPHostEntry; } }

namespace RadonFramework { namespace Net { namespace mDNS {

class ServiceDiscoveryView
{
public:
    ServiceDiscoveryView();
    void UpdateData(const RF_Collect::AutoVector<NetworkService>& Services,
        const RF_Collect::AutoVector<IPHostEntry>& HostEntries);

    void AddServiceFilter(const RF_Type::String& Servicename);

    RF_Type::UInt32 GetHash();
    const RF_Collect::Array<NetworkService>& Services();
protected:
    RF_Type::UInt32 m_Hash;
    RF_Collect::Array<NetworkService> m_Services;

    void UpdateHash();
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_MDNS
#define RF_SHORTHAND_NAMESPACE_MDNS
namespace RF_mDNS = RadonFramework::Net::mDNS;
#endif

#endif