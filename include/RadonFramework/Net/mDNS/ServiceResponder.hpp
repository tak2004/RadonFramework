#ifndef RF_NET_MDNS_SERVICERESPONDER_HPP
#define RF_NET_MDNS_SERVICERESPONDER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/Server.hpp>
#include <RadonFramework/Net/mDNS/NetworkService.hpp>

namespace RadonFramework { namespace Net { namespace mDNS {

class NetworkServiceInfo
{
public:
    RF_Type::String Name;// "servicename._tcp" or "servicename._udp"
    RF_Type::String Description;
};

class ServiceResponder: public Server
{
public:
    ServiceResponder();
    virtual ~ServiceResponder() override;

    void Setup(const NetworkServiceInfo& NewConfiguration, RF_Type::Bool Blocking = true);

    const NetworkServiceInfo& Info()const;

    virtual RF_Type::Bool Start() override;

    virtual void Update() override;
protected:
    NetworkServiceInfo m_Service;
    RF_Time::DateTime m_LastPush;
    virtual void Setup(const ServerConfig& NewConfiguration) override;
    void SendServiceInfo();
};

} } }

#endif // RF_NET_MDNS_SERVICERESPONDER_HPP