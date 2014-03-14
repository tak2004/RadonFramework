#ifndef RF_IO_STREAM_HPP
#define RF_IO_STREAM_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/SeekOrigin.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Time/TimeSpan.hpp>

namespace RadonFramework
{
    namespace IO
    {
        class Stream
        {
            public:
                virtual ~Stream(){};
                
                virtual void Close()=0;

                virtual void Flush()=0;
                
                virtual RFTYPE::UInt64 Read(RFTYPE::UInt8* Buffer,
                                          const RFTYPE::UInt64 Index,
                                          const RFTYPE::UInt64 Count)=0;

                virtual RFTYPE::UInt64 Seek(const RFTYPE::UInt64 Offset,
                                          const SeekOrigin::Type Origin)=0;
                
                virtual RFTYPE::UInt64 Write(const RFTYPE::UInt8* Buffer,
                                           const RFTYPE::UInt64 Offset,
                                           const RFTYPE::UInt64 Count)=0;

                template<class T>
                RFTYPE::UInt64 WriteType(const T& ByValue);

                virtual RFTYPE::Bool CanRead()const=0;
                virtual RFTYPE::Bool CanSeek()const=0;
                virtual RFTYPE::Bool CanWrite()const=0;
                virtual RFTYPE::Bool CanTimeout()const=0;
                virtual RFTYPE::UInt64 Length()const=0;
                virtual RFTYPE::UInt64 Position()const=0;
                virtual Time::TimeSpan ReadTimeout()const=0;
                virtual Time::TimeSpan WriteTimeout()const=0;
        };

        template<class T>
        RFTYPE::UInt64 Stream::WriteType(const T& ByValue)
        {
            return Write(reinterpret_cast<const RFTYPE::UInt8*>(&ByValue),0,sizeof(T));
        }
    }
}



#endif // RF_IO_STREAM_HPP
