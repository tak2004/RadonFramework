#ifndef RF_NET_HTTP_1_0_FIELD_HPP
#define RF_NET_HTTP_1_0_FIELD_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Net
    {
        namespace HTTP
        {
            namespace V1_0
            {
                struct Field
                {
                    enum Type
                    {                        
                        Authorization=0,
                        From,
                        IfModifiedSince,
                        Referer,
                        UserAgent,
                        MAX
                    };

                    static const char* Value[MAX];
                };
            }
        }
    }
}

#endif // RF_NET_HTTP_1_0_FIELD_HPP