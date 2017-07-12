#ifndef RF_IPHOSTENTRY_HPP
#define RF_IPHOSTENTRY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/IPAddress.hpp>
#include <RadonFramework/Collections/List.hpp>

namespace RadonFramework::Net {

class IPHostEntry
{
public:
    IPHostEntry(const RF_Type::String &Hostname);
    IPHostEntry(const RF_Type::String &Hostname,
                const Collections::List<RF_Type::String> &Aliases,
                const Collections::List<IPAddress> &AddressList);

    const RF_Type::String& Hostname()const;
    const Collections::List<RF_Type::String>& Aliases()const;
    const Collections::List<IPAddress>& AddressList()const;

    void AddAddress(const IPAddress& Address);
protected:
    RF_Type::String m_Hostname;
    Collections::List<RF_Type::String> m_Aliases;
    Collections::List<IPAddress> m_AddressList;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif
