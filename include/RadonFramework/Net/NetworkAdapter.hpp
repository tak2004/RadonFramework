#ifndef RF_NETWORKADAPTER_HPP
#define RF_NETWORKADAPTER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/IPAddress.hpp>

namespace RadonFramework::Net { 

struct NetworkAdapter
{
    IPAddress IP;
    IPAddress Netmask;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif // RF_NETWORKADAPTER_HPP
