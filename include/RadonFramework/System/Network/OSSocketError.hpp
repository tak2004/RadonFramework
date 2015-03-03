#ifndef RF_SYSTEM_NETWORK_OSSOCKETERROR_HPP
#define RF_SYSTEM_NETWORK_OSSOCKETERROR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/Error.hpp>
#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Defines.hpp>

namespace RadonFramework { namespace System { namespace Network {

struct OSSocketError
{
    enum
    {
        #if defined(RF_WINDOWS)
            First=10004,//WSAEINTR,
            Last=11004,//WSANO_DATA,
        #endif
        #if defined(RF_UNIX)
            First=4,//EINTR,
            Last=75,//EHOSTUNREACH,
        #endif
        Range=Last-First+1
    };
    static Net::Error* LookupTable;

    static Net::Error ConvertOSError();

    static Net::Error ConvertOSError(const RF_Type::Int32 Code);

    static void InitializeLookupTable();
};
        
} } }

#endif // RF_SYSTEM_NETWORK_OSSOCKETERROR_HPP