#ifndef RF_NET_SOCKETERROR_HPP
#define RF_NET_SOCKETERROR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Net/Error.hpp>

namespace RadonFramework::Net {        

struct SocketError
{
    operator RF_Type::Bool();
    Error Code;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif // RF_NET_SOCKETERROR_HPP
