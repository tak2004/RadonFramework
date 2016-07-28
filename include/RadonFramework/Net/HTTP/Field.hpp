#ifndef RF_NET_HTTP_FIELD_HPP
#define RF_NET_HTTP_FIELD_HPP

namespace RadonFramework { namespace Net { namespace HTTP {

// Don't change this enum without adjusting the utility functions too!
enum class Field
{// HTTP 1.0
    Authorization,
    From,
    IfModifiedSince,
    Referer,
    UserAgent,
    // HTTP 1.1
    Accept,
    AcceptCharset,
    AcceptEncoding,
    AcceptLanguage,
    Expect,
    Host,
    IfMatch,
    IfNoneMatch,
    IfRange,
    IfUnmodifiedSince,
    MaxForwards,
    ProxyAuthorization,
    Range,
    TE
};

struct FieldUtils
{
    static const RF_Type::String& ToString(const Field Value);
    static const RF_Type::Bool FromString(const RF_Type::String& Value, Field& Result);
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_HTTP
#define RF_SHORTHAND_NAMESPACE_HTTP
namespace RF_HTTP = RadonFramework::Net::HTTP;
#endif

#endif // RF_NET_HTTP_FIELD_HPP