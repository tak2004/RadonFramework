#ifndef RF_ADDRESSFAMILY_HPP
#define RF_ADDRESSFAMILY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Net
{
enum class AddressFamily
{
  InterNetwork,   // IPv4
  InterNetwork6,  // IPv6
  Unix,  // unix domain socket(very fast, tcp base designed and for local
         // process communication)
  None,
  MAX
};
}

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif
