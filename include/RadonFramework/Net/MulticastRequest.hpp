#ifndef RF_MULTICASTREQUEST_HPP
#define RF_MULTICASTREQUEST_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/IPAddress.hpp>

namespace RadonFramework { namespace Net { 

struct MulticastRequest
{
    IPAddress MulticastAddress;
    IPAddress Interface;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif // RF_MULTICASTREQUEST_HPP
