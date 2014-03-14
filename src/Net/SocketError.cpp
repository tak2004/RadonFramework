#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/SocketError.hpp"

using namespace RadonFramework::Net;
using namespace RadonFramework::Core::Types;

SocketError::operator Bool()
{
    return Code == Error::Ok;
}