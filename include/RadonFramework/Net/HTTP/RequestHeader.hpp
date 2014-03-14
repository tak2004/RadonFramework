#ifndef RF_NET_HTTP_REQUESTHEADER_HPP
#define RF_NET_HTTP_REQUESTHEADER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>

namespace RadonFramework
{
    namespace Net
    {
        namespace HTTP
        {
            template<typename F>
            struct RequestHeader
            {
                // Returns the length of the written bytes if no error occurred.
                static Core::Types::UInt32 Create(
                    Memory::AutoPointerArray<Core::Types::UInt8>& Buffer,
                    const Core::Types::UInt32 BufferBoundaryStart,
                    const Core::Types::UInt32 BufferBoundaryEnd,
                    const typename F::Type Field, 
                    const Core::Types::String& Value)
                {
                    Assert(Buffer.Count()>0,"Invalid Operation.");
                    return Core::Types::String::Format(Buffer, BufferBoundaryStart, 
                        BufferBoundaryEnd, "%s: %s\015\012",
                        F::Value[Field], Value.c_str());                    
                }
            };
        }
    }
}

#endif // RF_NET_HTTP_REQUESTHEADER_HPP