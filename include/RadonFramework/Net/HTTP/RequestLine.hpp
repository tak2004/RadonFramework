#ifndef RF_NET_HTTP_REQUESTLINE_HPP
#define RF_NET_HTTP_REQUESTLINE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/HTTP/Tokenizer.hpp>
#include <RadonFramework/Net/HTTP/1.1/Method.hpp>

namespace RadonFramework
{
    namespace Net
    {
        namespace HTTP
        {
            template<typename M=V1_1::Method>
            struct RequestLine
            {
                // Returns the length of the written bytes if no error occurred.                
                static RFTYPE::UInt32 Create(
                    Memory::AutoPointerArray<RFTYPE::UInt8>& Buffer,
                    const RFTYPE::UInt32 BufferBoundaryStart,
                    const RFTYPE::UInt32 BufferBoundaryEnd,
                    const typename M::Type Method, 
                    const RFTYPE::String& URI, 
                    const RFTYPE::UInt32 MajorHTTPVersion,
                    const RFTYPE::UInt32 MinorHTTPVersion)
                {
                    Assert(Buffer.Count()>0,"Invalid operation!");
                    return RFTYPE::String::Format(Buffer, BufferBoundaryStart, 
                        BufferBoundaryEnd, "%s /%s HTTP/%d.%d\015\012",
                        M::Value[Method], URI.c_str(), MajorHTTPVersion,
                        MinorHTTPVersion);                    
                }

                void Parse(const RFTYPE::UInt8* Buffer, 
                           const RFTYPE::UInt32 Bytes)
                {
                    Tokenizer tokenizer;
                    tokenizer.Parse(Buffer,Bytes);
                    
                    if (tokenizer.Expect(Tokenizer::Token))// method
                    {       
                        M::Type method=M::Parse(Buffer+tokenizer.Start(),tokenizer.Length());
                        if (method!=M::Unknown && 
                            tokenizer.Expect(Tokenizer::SP) &&
                            tokenizer.Expect(Tokenizer::Token))
                        {
                            RFTYPE::String uri(Buffer+tokenizer.Start(),tokenizer.Length());
                            if (tokenizer.Expect(Tokenizer::SP) &&
                                tokenizer.Expect(Tokenizer::Token) &&
                                tokenizer.Length()>=7 && 
                                strcmp("HTTP",Buffer+tokenizer.Start(),4))
                            {
                                if (tokenizer.Expect(Tokenizer::CRLF))
                                    return AutoPointer<RequestLine>(new RequestLine);
                            }
                        }                        
                    }
                }


            };
        }
    }
}

#endif // RF_NET_HTTP_REQUESTLINE_HPP