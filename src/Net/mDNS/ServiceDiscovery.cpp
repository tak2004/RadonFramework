#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/mDNS/ServiceDiscovery.hpp"
#include "RadonFramework/Net/mDNS/NetworkService.hpp"
#include "RadonFramework/Net/IPHostEntry.hpp"
#include "RadonFramework/Net/mDNS/MessageWriter.hpp"
#include "RadonFramework/Net/mDNS/MessageReader.hpp"
#include "RadonFramework/Collections/AutoVector.hpp"
#include "RadonFramework/Collections/HashList.hpp"
#include "RadonFramework/Net/Socket.hpp"
#include "RadonFramework/Net/Server.hpp"
#include "RadonFramework/Net/MulticastRequest.hpp"
#include "RadonFramework/Net/ServerConfig.hpp"
#include "RadonFramework/Net/mDNS/ServiceDiscoveryView.hpp"

namespace RadonFramework { namespace Core { namespace Idioms {

template<>
struct RF_Idiom::PImpl<RF_mDNS::ServiceDiscovery>::Data
{
    Data()        
    :m_KnownDomainNameDictionary(1024)
    ,m_KnownServiceDictionary(1024)
    {
        m_UpdatePeriod = RF_Time::TimeSpan::CreateByTime(0, 5, 0);
        m_NextQuery = RF_Time::DateTime::CreateByTicks(0, RF_Time::DateTimeKind::UTC);
    }

    ~Data()
    {

    }

    RF_Collect::AutoVector<RF_Net::IPHostEntry> m_KnownDomainNames;
    RF_Collect::HashList m_KnownDomainNameDictionary;
    RF_Collect::AutoVector<RF_mDNS::NetworkService> m_KnownServices;
    RF_Collect::HashList m_KnownServiceDictionary;
    RF_Time::DateTime m_NextQuery;
    RF_Time::TimeSpan m_UpdatePeriod;
    RF_Net::EndPoint m_EndpointIPv4;
    RF_Net::EndPoint m_EndpointIPv6;
    RF_Collect::List<RF_mDNS::ServiceDiscoveryView*> m_Views;
    RF_Type::Bool m_DataChanged;
};

} } }

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

namespace RadonFramework { namespace Net { namespace mDNS {

ServiceDiscovery::ServiceDiscovery()
{
}

ServiceDiscovery::~ServiceDiscovery()
{

}

void ServiceDiscovery::Setup()
{
    Service::Setup(ServiceInterfaceBinding::Private, ServiceIPVersion::All);
    m_PImpl->m_EndpointIPv4 = EndPoint(IPAddress(224,0,0,251), 5353);
    m_PImpl->m_EndpointIPv6 = EndPoint(IPAddress(0xff02,0,0,0,0,0,0,0xFB), 5353);
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
    RF_Type::UInt32 hash = CalculateFNV(Servicename);
    NetworkService* result = 0;
    m_PImpl->m_KnownServiceDictionary.Get(hash, reinterpret_cast<void*&>(result));
    return result;
}

const RF_Collect::AutoVector<IPHostEntry>& ServiceDiscovery::KnownDomainNames() const
{
    return m_PImpl->m_KnownDomainNames;
}

RF_Type::Bool ServiceDiscovery::IsDomainNameKnown(const RF_Type::String& DomainName) const
{
    return false;
}

IPHostEntry* ServiceDiscovery::FindDomainName(const RF_Type::String& DomainName) const
{
    RF_Type::UInt32 hash = CalculateFNV(DomainName);
    IPHostEntry* result = 0;
    m_PImpl->m_KnownDomainNameDictionary.Get(hash, reinterpret_cast<void*&>(result));
    return result;
}

RF_Type::Bool ServiceDiscovery::Shutdown(const Time::TimeSpan& ReturnAfter)
{
    RF_Type::Bool result = Service::Shutdown(ReturnAfter);
    return result;
}

void ServiceDiscovery::Update()
{
    m_PImpl->m_DataChanged = false;
    Service::Update();

    RF_Time::DateTime now = RF_Time::DateTime::UtcNow();
    if(RF_Time::DateTime::LessThan(m_PImpl->m_NextQuery, now))
    {
        RF_Type::Size id = 0;
        for(RF_Type::Size i = 0; i < m_PImpl->m_Views.Count(); ++i)
        {
            for(RF_Type::Size j = 0; j < m_PImpl->m_Views[i]->Services().Count(); ++j)
            {
                ++id;
                MessageWriter writer;
                writer.WriteQueryHeader(id);
                RF_Type::String query;
                query = m_PImpl->m_Views[i]->Services()(j).Name + "." + m_PImpl->m_Views[i]->Services()(j).Domain;
                writer.WriteQuestion(query, RecordType::PTR);
                writer.Finalize();

                RF_Type::UInt32 sendBytes = 0;
                for (RF_Type::Size k = 0; k < GetServerList().Count(); ++k)
                {
                    if(GetServerList()[k]->Configuration().Family == AddressFamily::InterNetwork)
                    {
                        GetServerList()[k]->GetSocket()->SendTo(writer.Data(), writer.DataSize(), m_PImpl->m_EndpointIPv4, sendBytes);
                    }
                    else
                    {
                        GetServerList()[k]->GetSocket()->SendTo(writer.Data(), writer.DataSize(), m_PImpl->m_EndpointIPv6, sendBytes);
                    }
                }                
            }
        }
        m_PImpl->m_NextQuery = RF_Time::DateTime::CreateByTicks(now.Ticks() + m_PImpl->m_UpdatePeriod.Ticks());
    }

    if(m_PImpl->m_DataChanged)
    {
        for (RF_Type::Size i = 0; i < m_PImpl->m_Views.Count(); ++i)
        {
            m_PImpl->m_Views[i]->UpdateData(m_PImpl->m_KnownServices, m_PImpl->m_KnownDomainNames);
        }        
    }
}

void ServiceDiscovery::Start()
{
    Service::Start();
}

void ServiceDiscovery::Stop()
{
    Service::Stop();
}

const RF_Time::TimeSpan& ServiceDiscovery::UpdateCycle() const
{
    return m_PImpl->m_UpdatePeriod;
}

void ServiceDiscovery::UpdateCycle(const RF_Time::TimeSpan& NewValue)
{
    m_PImpl->m_UpdatePeriod = NewValue;
}

void ServiceDiscovery::AttachView(ServiceDiscoveryView& View)
{
    m_PImpl->m_Views.AddLast(&View);
}

RF_Type::Bool ServiceDiscovery::DetachView(ServiceDiscoveryView& View)
{
    RF_Type::Bool result = false;
    for (RF_Type::Size i = 0; i < m_PImpl->m_Views.Count(); ++i)
    {
        if(m_PImpl->m_Views[i] == &View)
        {
            m_PImpl->m_Views.RemoveAt(i);
            result = true;
            break;
        }
    }
    return result;
}

const RF_Collect::List<ServiceDiscoveryView*>& ServiceDiscovery::Views() const
{
    return m_PImpl->m_Views;
}

void ServiceDiscovery::PostBindConfigureSocket(ServerEvent& Sender)
{
    if(Sender.Config->Family == AddressFamily::InterNetwork)
    {
        SocketError error;
        error.Code = Error::Ok;

        MulticastRequest multicastRequest;
        multicastRequest.MulticastAddress = m_PImpl->m_EndpointIPv4.Address();
        multicastRequest.Interface = Sender.Target->LocalEndPoint().Address();
        // let us be part of the broadcast interface
        error = Sender.Target->SetSocketOption(SocketOptionLevel::IPv4, SocketOptionName::AddMembership, multicastRequest);
    }
}

void ServiceDiscovery::PreBindConfigureSocket(ServerEvent& Sender)
{
    if (Sender.Config->Family == AddressFamily::InterNetwork)
    {
        SocketError error;
        error.Code = Error::Ok;
        // send it till the internet modem
        error = Sender.Target->SetSocketOption(SocketOptionLevel::IPv4, SocketOptionName::MutlicastTimeToLive, RF_Type::UInt8(255));
        error = Sender.Target->SetSocketOption(SocketOptionLevel::IPv4, SocketOptionName::IPTimeToLive, RF_Type::UInt8(255));
        // don't process own packets
        error = Sender.Target->SetSocketOption(SocketOptionLevel::IPv4, SocketOptionName::MulticastLoopback, false);
    }
}

void ServiceDiscovery::PacketReceived(ServerProcessPacketEvent& Sender)
{
    MessageReader reader;
    reader.Reset(*Sender.Data);
    reader.ReadHeader();
    reader.ReadQuestions();
    reader.ReadAnswers();

    if(reader.IsResponse())
    {
        for(RF_Type::Size i = 0; i < reader.Answers().Count(); ++i)
        {
            if (reader.Answers()(i).Type == RecordType::SRV)
            {
                RF_Mem::AutoPointerArray<RF_Type::String> nameParts = reader.Answers()(i).Name.Split(RF_Type::String("."));

                RF_Type::Size j;
                for(j = 1; j < nameParts.Count(); ++j)
                {
                    if(nameParts[j] == "_tcp" || nameParts[j] == "_udp")
                    {
                        break;
                    }
                }

                if(nameParts.Count() > 2 && j < nameParts.Count())
                {
                    RF_Type::String name = nameParts[j - 1] + "." + nameParts[j];
                    RF_Type::UInt32 hash = CalculateFNV(name);

                    NetworkService* service = 0;

                    if(!m_PImpl->m_KnownServiceDictionary.Get(hash, reinterpret_cast<void*&>(service)))
                    {
                        RF_Mem::AutoPointer<NetworkService> newService(new NetworkService);
                        newService->Name = name;
                        service = newService.Get();
                        m_PImpl->m_KnownServiceDictionary.Add(hash, service);
                        m_PImpl->m_KnownServices.PushBack(newService);
                        m_PImpl->m_DataChanged = true;
                    }

                    auto& info = reader.ServiceInfos()(reader.Answers()(i).Index);
                    for(j = 0; j < service->Instances.Count(); ++j)
                    {
                        if(service->Instances[j]->Name == info.Target)
                        {
                            break;
                        }
                    }

                    if(j == service->Instances.Count())
                    {
                        RF_Mem::AutoPointer<ServiceInstanceInfo> instance(new ServiceInstanceInfo);
                        instance->Name = info.Target;
                        instance->Port = info.Port;
                        service->Instances.PushBack(instance);
                        m_PImpl->m_DataChanged = true;
                    }
                }
            }
            else
            if(reader.Answers()(i).Type == RecordType::A)
            {
                RF_Type::String name = reader.Answers()(i).Name;
                RF_Type::UInt32 ip = reader.IP4()(reader.Answers()(i).Index);
                RF_Type::UInt32 hash = CalculateFNV(name);
                
                IPHostEntry* entry = 0;
                if(!m_PImpl->m_KnownDomainNameDictionary.Get(hash, reinterpret_cast<void*&>(entry)))
                {
                    RF_Mem::AutoPointer<IPHostEntry> newEntry(new IPHostEntry(name));
                    entry = newEntry.Get();
                    m_PImpl->m_KnownDomainNameDictionary.Add(hash, entry);
                    m_PImpl->m_KnownDomainNames.PushBack(newEntry);
                    m_PImpl->m_DataChanged = true;
                }
                
                RF_Type::Size j;
                for(j = 0; j < entry->AddressList().Count(); ++j)
                {
                    if(entry->AddressList()[j].ToUInt32() == ip)
                    {
                        break;
                    }
                }

                if(j == entry->AddressList().Count())
                {
                    entry->AddAddress(ip);
                    m_PImpl->m_DataChanged = true;
                }
            }
        }
    }
}

} } }