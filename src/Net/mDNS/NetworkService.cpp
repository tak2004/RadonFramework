#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/mDNS/NetworkService.hpp"

namespace RadonFramework { namespace Net { namespace mDNS {

NetworkService::NetworkService()
{
}

NetworkService::NetworkService(const NetworkService& Copy)
:Name(Copy.Name)
,Domain(Copy.Domain)
{
    for(RF_Type::Size i = 0; i < Copy.Instances.Count(); ++i)
    {
        RF_Mem::AutoPointer<ServiceInstanceInfo> info(new ServiceInstanceInfo(*Copy.Instances[i]));
        Instances.PushBack(info);
    }
}

NetworkService& NetworkService::operator=(const NetworkService& Copy)
{
    Name = Copy.Name;
    Domain = Copy.Domain;
    Instances.Clear();
    for(RF_Type::Size i = 0; i < Copy.Instances.Count(); ++i)
    {
        RF_Mem::AutoPointer<ServiceInstanceInfo> info(new ServiceInstanceInfo(*Copy.Instances[i]));
        Instances.PushBack(info);
    }
    return *this;
}

ServiceInstanceInfo::ServiceInstanceInfo()
:Port(0)
{

}

ServiceInstanceInfo::ServiceInstanceInfo(const ServiceInstanceInfo& Copy)
:Name(Copy.Name)
,Port(Copy.Port)
,TimeToLive(Copy.TimeToLive)
{

}

ServiceInstanceInfo& ServiceInstanceInfo::operator=(const ServiceInstanceInfo& Copy)
{
    Name = Copy.Name;
    Port = Copy.Port;
    TimeToLive = Copy.TimeToLive;
    return *this;
}

} } }