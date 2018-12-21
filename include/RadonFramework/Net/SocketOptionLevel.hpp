#ifndef RF_SOCKETOPTIONLEVEL_HPP
#define RF_SOCKETOPTIONLEVEL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Net
{
enum class SocketOptionLevel
{
  Unset,
  Socket,
  IPv4,
  IPv6,
  TCP,
  UDP,
  MAX
};
}

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif
