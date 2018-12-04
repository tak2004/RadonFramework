#ifndef RF_NET_SERVICE_HPP
#define RF_NET_SERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Core/Idioms/PImpl.hpp>
#include <RadonFramework/Core/Pattern/Event.hpp>

namespace RadonFramework::Time
{
struct TimeSpan;
}

namespace RadonFramework::Net
{
class EndPoint;
struct ServerEvent;
struct ServerProcessPacketEvent;
class Server;

enum class ServiceInterfaceBinding
{
  All,
  Private,
  Public
};

enum class ServiceIPVersion
{
  All,
  IP4,
  IP6
};

class Service : public RF_Pattern::IObserver
{
public:
  Service();
  virtual ~Service();
  virtual void Setup(ServiceInterfaceBinding Binding, ServiceIPVersion Version);
  virtual RF_Type::Bool Shutdown(const Time::TimeSpan& ReturnAfter);
  virtual void Update();
  virtual void Start();
  virtual void Stop();

  ServiceInterfaceBinding GetBinding() const;
  ServiceIPVersion GetUsedIPVersion() const;

protected:
  RF_Idiom::PImpl<Service> m_PImpl;

  const RF_Collect::AutoVector<Server>& GetServerList() const;
  virtual void PostBindConfigureSocket(ServerEvent& Sender);
  virtual void PreBindConfigureSocket(ServerEvent& Sender);
  virtual void PacketReceived(ServerProcessPacketEvent& Sender);
};

}  // namespace RadonFramework::Net

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif