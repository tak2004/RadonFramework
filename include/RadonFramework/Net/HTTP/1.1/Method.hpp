#ifndef RF_NET_HTTP_1_1_METHOD_HPP
#define RF_NET_HTTP_1_1_METHOD_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>

namespace RadonFramework
{
    namespace Net
    {
        namespace HTTP
        {
            namespace V1_1
            {
                struct Method
                {
                    enum Type
                    {
                        Get,
                        Put,
                        Head,
                        Post,
                        Trace,
                        Delete,
                        Options,                        
                        Connect,
                        Unknown,
                        MAX
                    };

                    static const char* Value[MAX];

                    static RF_Type::UInt32 ValueLen[MAX];

                    static RF_Type::UInt32 MaxLen;

                    static Type Parse(const RF_Type::UInt8* Buffer, 
                        const RF_Type::UInt32 Bytes);
                };
            }            
        }
    }
}

#endif // RF_NET_HTTP_1_1_METHOD_HPP