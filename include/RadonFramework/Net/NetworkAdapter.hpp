#ifndef RF_NETWORKADAPTER_HPP
#define RF_NETWORKADAPTER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/IPAddress.hpp>

namespace RadonFramework
{
    namespace Net
    {
        struct NetworkAdapter
        {
            IPAddress IP;
            IPAddress Netmask;
        };
    }
}

#endif
