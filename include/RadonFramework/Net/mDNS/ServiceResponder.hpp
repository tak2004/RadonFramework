#ifndef RF_NET_MDNS_SERVICERESPONDER_HPP
#define RF_NET_MDNS_SERVICERESPONDER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/Server.hpp>
#include <RadonFramework/Net/mDNS/NetworkService.hpp>

namespace RadonFramework { namespace Net { namespace mDNS {

class ServiceResponder: public Server
{
public:
    ServiceResponder();
    virtual ~ServiceResponder() override;

    void Setup(const NetworkService& NewConfiguration, RF_Type::Bool Blocking = true);

    const NetworkService& Info()const;

    virtual RF_Type::Bool Start() override;

    virtual void Update() override;
protected:
    NetworkService m_Service;
    RF_Time::DateTime m_LastPush;
    virtual void Setup(const ServerConfig& NewConfiguration) override;
    void SendServiceInfo();
};

} } }

#endif // RF_NET_MDNS_SERVICERESPONDER_HPP