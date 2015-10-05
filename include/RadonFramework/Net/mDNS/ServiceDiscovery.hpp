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

    void Setup();
    const Collections::AutoVector<NetworkService>& KnownServices()const;
    RF_Type::Bool IsKnown(const RF_Type::String& Servicename)const;
    NetworkService* FindService(const RF_Type::String& Servicename)const;
    virtual RF_Type::Bool Shutdown(const Time::TimeSpan& ReturnAfter)override;
    virtual void Update()override;

    RF_Type::Bool UseIPv4()const;
    void UseIPv4(RF_Type::Bool NewValue);

    RF_Type::Bool UseIPv6()const;
    void UseIPv6(RF_Type::Bool NewValue);

    const RF_Time::TimeSpan& UpdateCycle()const;
    void UpdateCycle(const RF_Time::TimeSpan& NewValue);
protected:
    virtual void PostBindConfigureSocket(Socket& Socket, IPAddress& Interface) override;
    virtual void PreBindConfigureSocket(Socket& Socket, IPAddress& Interface) override;
    virtual RF_Type::Bool ProcessPacket(RF_Mem::AutoPointerArray<RF_Type::UInt8>& In) override;
private:
    RF_Idiom::PImpl<ServiceDiscovery> m_PImpl;
};

} } }

#endif // RF_NET_MDNS_SERVICEDISCOVERY_HPP