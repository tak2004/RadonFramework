#ifndef RF_NET_MDNS_NETWORKSERVICE_HPP
#define RF_NET_MDNS_NETWORKSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/IPAddress.hpp>
#include <RadonFramework/Time/DateTime.hpp>

namespace RadonFramework { namespace Net { namespace mDNS {

class NetworkService
{
public:
    NetworkService();

    RF_Type::String Name;
    RF_Net::IPAddress IP;
    RF_Type::UInt16 Port;
    RF_Time::DateTime TimeToLive;
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_MDNS
#define RF_SHORTHAND_NAMESPACE_MDNS
namespace RF_mDNS = RadonFramework::Net::mDNS;
#endif

#endif // RF_NET_MDNS_NETWORKSERVICE_HPP