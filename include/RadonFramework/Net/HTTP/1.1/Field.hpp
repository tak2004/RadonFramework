#ifndef RF_NET_HTTP_1_1_FIELD_HPP
#define RF_NET_HTTP_1_1_FIELD_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Net
    {
        namespace HTTP
        {
            namespace V1_1
            {
                struct Field
                {
                    enum Type
                    {
                        Accept=0,
                        AcceptCharset,
                        AcceptEncoding,
                        AcceptLanguage,
                        Authorization,
                        Exspect,
                        From,
                        Host,
                        IfMatch,
                        IfModifiedSince,
                        IfNoneMatch,
                        IfRange,
                        IfUnmodifiedSince,
                        MaxForwards,
                        ProxyAuthorization,
                        Range,
                        Referer,
                        TE,
                        UserAgent,
                        MAX
                    };

                    static const char* Value[MAX];
                };
            }
        }
    }
}

#endif // RF_NET_HTTP_1_1_FIELD_HPP