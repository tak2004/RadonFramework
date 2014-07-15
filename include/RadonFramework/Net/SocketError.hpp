#ifndef RF_NET_SOCKETERROR_HPP
#define RF_NET_SOCKETERROR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Net/Error.hpp>

namespace RadonFramework
{
    namespace Net
    {        
        struct SocketError
        {
            operator RF_Type::Bool();
            Error::Type Code;
        };
    }
}

#endif // RF_NET_SOCKETERROR_HPP
