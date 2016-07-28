#ifndef RF_NET_HTTP_METHOD_HPP
#define RF_NET_HTTP_METHOD_HPP

namespace RadonFramework { namespace Net { namespace HTTP {

enum class Method
{// HTTP 1.0
    Get,
    Head,
    Post,
// HTTP 1.1
    Put,
    Trace,
    Delete,
    Options,
    Connect
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_HTTP
#define RF_SHORTHAND_NAMESPACE_HTTP
namespace RF_HTTP = RadonFramework::Net::HTTP;
#endif

#endif // RF_NET_HTTP_METHOD_HPP