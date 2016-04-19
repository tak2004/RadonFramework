#ifndef RF_NET_MDNS_SERVICEDISCOVERY_HPP
#define RF_NET_MDNS_SERVICEDISCOVERY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/Service.hpp>

namespace RadonFramework { namespace Time { class TimeSpan; } }

namespace RadonFramework { namespace Collections { template<class T> class AutoVector; } }

namespace RadonFramework { namespace Net { class IPHostEntry; } }

namespace RadonFramework { namespace Net { namespace mDNS {

class NetworkService;
class ServiceDiscoveryView;

class ServiceDiscovery: public Service
{
public:
    ServiceDiscovery();
    ~ServiceDiscovery();

    void Setup();
    const RF_Collect::AutoVector<NetworkService>& KnownServices()const;
    RF_Type::Bool IsKnown(const RF_Type::String& Servicename)const;
    NetworkService* FindService(const RF_Type::String& Servicename)const;

    const RF_Collect::AutoVector<IPHostEntry>& KnownDomainNames()const;
    RF_Type::Bool IsDomainNameKnown(const RF_Type::String& DomainName)const;
    IPHostEntry* FindDomainName(const RF_Type::String& DomainName)const;

    virtual RF_Type::Bool Shutdown(const Time::TimeSpan& ReturnAfter) override;
    virtual void Update() override;
    virtual void Start() override;
    virtual void Stop() override;

    const Time::TimeSpan& UpdateCycle()const;
    void UpdateCycle(const Time::TimeSpan& NewValue);

    void AttachView(ServiceDiscoveryView& View);
    RF_Type::Bool DetachView(ServiceDiscoveryView& View);
    const RF_Collect::List<ServiceDiscoveryView*>& Views()const;
protected:
    virtual void PostBindConfigureSocket(ServerEvent& Sender) override;
    virtual void PreBindConfigureSocket(ServerEvent& Sender) override;
    virtual void PacketReceived(ServerProcessPacketEvent& Sender) override;
private:
    RF_Idiom::PImpl<ServiceDiscovery> m_PImpl;
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_MDNS
#define RF_SHORTHAND_NAMESPACE_MDNS
namespace RF_mDNS = RadonFramework::Net::mDNS;
#endif

#endif // RF_NET_MDNS_SERVICEDISCOVERY_HPP