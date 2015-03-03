#ifndef RF_IPHOSTENTRY_HPP
#define RF_IPHOSTENTRY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/IPAddress.hpp>
#include <RadonFramework/Collections/List.hpp>

namespace RadonFramework { namespace Net {

class IPHostEntry
{
public:
    IPHostEntry(const RF_Type::String &Hostname,
                const Collections::List<RF_Type::String> &Aliases,
                const Collections::List<IPAddress> &AddressList);
    const RF_Type::String& Hostname();
    const Collections::List<RF_Type::String>& Aliases();
    const Collections::List<IPAddress>& AddressList();
protected:
    RF_Type::String m_Hostname;
    Collections::List<RF_Type::String> m_Aliases;
    Collections::List<IPAddress> m_AddressList;
};

} }

#endif
