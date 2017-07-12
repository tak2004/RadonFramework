#ifndef RF_NET_MDNS_NETWORKSERVICE_HPP
#define RF_NET_MDNS_NETWORKSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/IPAddress.hpp>
#include <RadonFramework/Time/DateTime.hpp>
#include <RadonFramework/Collections/AutoVector.hpp>

namespace RadonFramework::Net::mDNS {

class ServiceInstanceInfo
{
public:
    ServiceInstanceInfo();
    ServiceInstanceInfo(const ServiceInstanceInfo& Copy);
    ServiceInstanceInfo& operator=(const ServiceInstanceInfo& Copy);

    RF_Type::String Name;
    RF_Type::UInt16 Port;
    RF_Time::DateTime TimeToLive;
};

class NetworkService
{
public:
    NetworkService();
    NetworkService(const NetworkService& Copy);
    NetworkService& operator=(const NetworkService& Copy);

    RF_Type::String Name;
    RF_Type::String Domain;
    RF_Collect::AutoVector<ServiceInstanceInfo> Instances;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_MDNS
#define RF_SHORTHAND_NAMESPACE_MDNS
namespace RF_mDNS = RadonFramework::Net::mDNS;
#endif

#endif // RF_NET_MDNS_NETWORKSERVICE_HPP