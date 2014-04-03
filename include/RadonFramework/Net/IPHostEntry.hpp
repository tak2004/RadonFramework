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
            IPHostEntry(const RFTYPE::String &Hostname,
                        const Collections::List<RFTYPE::String> &Aliases,
                        const Collections::List<IPAddress> &AddressList);
            const RFTYPE::String& Hostname();
            const Collections::List<RFTYPE::String>& Aliases();
            const Collections::List<IPAddress>& AddressList();
        protected:
            RFTYPE::String m_Hostname;
            Collections::List<RFTYPE::String> m_Aliases;
            Collections::List<IPAddress> m_AddressList;
    };
} }

#endif
