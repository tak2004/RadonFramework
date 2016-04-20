#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/mDNS/ServiceDiscoveryView.hpp"

namespace RadonFramework { namespace Net { namespace mDNS {

ServiceDiscoveryView::ServiceDiscoveryView()
:m_Hash(0)
{

}

void ServiceDiscoveryView::UpdateData(const RF_Collect::AutoVector<NetworkService>& Services, 
    const RF_Collect::AutoVector<IPHostEntry>& HostEntries)
{
    for(RF_Type::Size i = 0; i < m_Services.Count(); ++i)
    {
        m_Services(i).Instances.Clear();

        for(RF_Type::Size j = 0; j < Services.Count(); ++j)
        {
            if(Services[j]->Name == m_Services(i).Name)
            {
                for(RF_Type::Size k = 0; k < Services[j]->Instances.Count(); ++k)
                {
                    RF_Mem::AutoPointer<ServiceInstanceInfo> info(new ServiceInstanceInfo);
                    *info = *Services[j]->Instances[k];                    
                    m_Services(i).Instances.PushBack(info);
                }
                break;
            }
        }
    }    
    UpdateHash();
}

void ServiceDiscoveryView::AddServiceFilter(const RF_Type::String& Servicename,
    const RF_Type::String& Domain)
{
    m_Services.Resize(m_Services.Count() + 1);
    m_Services(m_Services.Count() - 1).Name = Servicename;
    m_Services(m_Services.Count() - 1).Domain = Domain;
    UpdateHash();
}

RF_Type::UInt32 ServiceDiscoveryView::GetHash()
{
    return m_Hash;
}

const RF_Collect::Array<NetworkService>& ServiceDiscoveryView::Services()
{
    return m_Services;
}

RF_Type::UInt32 CalculateFNV(const RF_Type::String& Value)
{
    const RF_Type::Size length = Value.Size() + 1;
    RF_Type::UInt32 hash = 2166136261u;
    for(RF_Type::Size i = 0; i < length; ++i)
    {
        hash ^= Value[i];
        hash *= 16777619u;
    }
    return hash;
}

void ServiceDiscoveryView::UpdateHash()
{
    m_Hash = 0;
    for(RF_Type::Size i = 0; i < m_Services.Count(); ++i)
    {
        for (RF_Type::Size j = 0; j < m_Services(i).Instances.Count(); ++j)
        {
            m_Hash += CalculateFNV(m_Services(i).Instances[j]->Name);
            m_Hash += m_Services(i).Instances[j]->Port;
            m_Hash += m_Services(i).Instances[j]->TimeToLive.Ticks();
        }        
    }
}

} } }