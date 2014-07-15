#ifndef RF_NET_HTTP_REQUESTHEADER_HPP
#define RF_NET_HTTP_REQUESTHEADER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>

namespace RadonFramework { namespace Net { namespace HTTP {

template<typename F>
struct RequestHeader
{
    // Returns the length of the written bytes if no error occurred.
    static RF_Type::UInt32 Create(
        Memory::AutoPointerArray<RF_Type::UInt8>& Buffer,
        const RF_Type::UInt32 BufferBoundaryStart,
        const RF_Type::UInt32 BufferBoundaryEnd,
        const typename F::Type Field, 
        const RF_Type::String& Value)
    {
        Assert(Buffer.Count()>0,"Invalid Operation.");
        return RF_Type::String::Format(Buffer, BufferBoundaryStart, 
            BufferBoundaryEnd, "%s: %s\015\012",
            F::Value[Field], Value.c_str());                    
    }
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_HTTP
#define RF_SHORTHAND_NAMESPACE_HTTP
namespace RF_HTTP = RadonFramework::Net::HTTP;
#endif

#endif // RF_NET_HTTP_REQUESTHEADER_HPP