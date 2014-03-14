#ifndef RF_IO_URIHOSTNAMETYPE_HPP
#define RF_IO_URIHOSTNAMETYPE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace IO
    {
        namespace UriHostNameType
        {
            enum Type
            {
                // The type of the host name is not supplied.
                Unknown,
                // The host is set, but the type cannot be determined.
                Basic,
                // The host name is a domain name system (DNS) style host name.
                DomainName,
                // The host name is an Internet Protocol (IP) version 4 host address.
                IPv4,
                // The host name is an Internet Protocol (IP) version 6 host address.
                IPv6
            };
        }
    }
}

#endif // RF_IO_URIHOSTNAMETYPE_HPP