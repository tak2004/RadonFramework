#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/HTTP/Field.hpp"

namespace RadonFramework { namespace Net { namespace HTTP {

static RF_Type::String FieldToStringMap[] {
    "Authorization"_rfs,
    "From"_rfs,
    "If-Modified-Since"_rfs,
    "Referer"_rfs,
    "User-Agent"_rfs,
    "Accept"_rfs,
    "Accept-Charset"_rfs,
    "Accept-Encoding"_rfs,
    "Accept-Language"_rfs,
    "Expect"_rfs,
    "Host"_rfs,
    "If-Match"_rfs,
    "If-None-Match"_rfs,
    "If-Range"_rfs,
    "If-Unmodified-Since"_rfs,
    "Max-Forwards"_rfs,
    "Proxy-Authorization"_rfs,
    "Range"_rfs,
    "TE"_rfs
};

static Field StringToFieldMap[]{
    Field::Authorization,
    Field::From,
    Field::IfModifiedSince,
    Field::Referer,
    Field::UserAgent,
    Field::Accept,
    Field::AcceptCharset,
    Field::AcceptEncoding,
    Field::AcceptLanguage,
    Field::Expect,
    Field::Host,
    Field::IfMatch,
    Field::IfNoneMatch,
    Field::IfRange,
    Field::IfUnmodifiedSince,
    Field::MaxForwards,
    Field::ProxyAuthorization,
    Field::Range,
    Field::TE,
};

const RF_Type::String& FieldUtils::ToString(const Field Value)
{
    static RF_Type::String Unknown("Unknown");
    switch(Value)
    {
    case Field::Authorization: return FieldToStringMap[0];
    case Field::From: return FieldToStringMap[1];
    case Field::IfModifiedSince: return FieldToStringMap[2];
    case Field::Referer: return FieldToStringMap[3];
    case Field::UserAgent: return FieldToStringMap[4];
    case Field::Accept: return FieldToStringMap[5];
    case Field::AcceptCharset: return FieldToStringMap[6];
    case Field::AcceptEncoding: return FieldToStringMap[7];
    case Field::AcceptLanguage: return FieldToStringMap[8];
    case Field::Expect: return FieldToStringMap[9];
    case Field::Host: return FieldToStringMap[10];
    case Field::IfMatch: return FieldToStringMap[11];
    case Field::IfNoneMatch: return FieldToStringMap[12];
    case Field::IfRange: return FieldToStringMap[13];
    case Field::IfUnmodifiedSince: return FieldToStringMap[14];
    case Field::MaxForwards: return FieldToStringMap[15];
    case Field::ProxyAuthorization: return FieldToStringMap[16];
    case Field::Range: return FieldToStringMap[17];
    case Field::TE: return FieldToStringMap[18];
    default:
        return Unknown;
    }
}

template <typename T, RF_Type::Size N>
constexpr RF_Type::Size countof(T const (&)[N]) noexcept
{
    return N;
}

const RF_Type::Bool FieldUtils::FromString(const RF_Type::String& Value, Field& Result)
{
    RF_Type::Bool result = false;
    for(RF_Type::Size i = 0; i < countof(FieldToStringMap); ++i)
    {
        if(Value == FieldToStringMap[i])
        {
            Result = StringToFieldMap[i];
            result = true;
            break;
        }
    }
    return result;
}

} } }