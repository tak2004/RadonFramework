#ifndef RF_ENDPOINT_HPP
#define RF_ENDPOINT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Net/IPAddress.hpp>

namespace RadonFramework::Net
{
class EndPoint
{
public:
  EndPoint();
  EndPoint(const IPAddress& Addr, RF_Type::UInt16 Port = 0);
  const RF_Type::String ToString() const;
  const IPAddress& Address() const;
  void Address(const IPAddress& Value);
  RF_Type::UInt16 Port() const;
  void Port(RF_Type::UInt16 Value);
  bool operator==(const EndPoint& Other);

protected:
  IPAddress m_IP;
  RF_Type::UInt16 m_Port;
};

}  // namespace RadonFramework::Net

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif
