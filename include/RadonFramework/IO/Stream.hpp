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

namespace RadonFramework { namespace IO {

class Stream
{
public:
    virtual ~Stream();
                
    virtual void Close()=0;

    virtual void Flush()=0;
                
    virtual RF_Type::UInt64 Read(RF_Type::UInt8* Buffer,
        const RF_Type::UInt64 Index, const RF_Type::UInt64 Count)=0;

    virtual RF_Type::UInt64 Seek(const RF_Type::Int64 Offset,
        const SeekOrigin::Type Origin)=0;
                
    virtual RF_Type::UInt64 Write(const RF_Type::UInt8* Buffer,
        const RF_Type::UInt64 Offset, const RF_Type::UInt64 Count)=0;

    /// Like read but don't change the position in the stream.
    virtual RF_Type::UInt64 Peek(RF_Type::UInt8* Buffer,
        const RF_Type::UInt64 Index, const RF_Type::UInt64 Count) = 0;

    template<class T>
    RF_Type::UInt64 WriteType(const T& ByValue);

    template<class T>
    RF_Type::UInt64 ReadType(T& ByValue);

    template<class T>
    RF_Type::UInt64 PeekType(T& ByValue);

    RF_Mem::AutoPointerArray<RF_Type::UInt8> ReadBytes(RF_Type::Size Bytes);

    RF_Type::UInt64 WriteData(const RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data);

    RF_Mem::AutoPointerArray<RF_Type::UInt8> PeekBytes(RF_Type::Size Bytes);

    virtual RF_Type::Bool CanRead()const=0;
    virtual RF_Type::Bool CanSeek()const=0;
    virtual RF_Type::Bool CanWrite()const=0;
    virtual RF_Type::Bool CanTimeout()const=0;
    virtual RF_Type::Bool CanPeek()const = 0;
    virtual RF_Type::UInt64 Length()const=0;
    virtual RF_Type::UInt64 Position()const=0;
    virtual Time::TimeSpan ReadTimeout()const=0;
    virtual Time::TimeSpan WriteTimeout()const=0;
};

template<class T>
RF_Type::UInt64 Stream::WriteType(const T& ByValue)
{
    return Write(reinterpret_cast<const RF_Type::UInt8*>(&ByValue),0,sizeof(T));
}

template<class T>
RF_Type::UInt64 Stream::ReadType(T& ByValue)
{
    return Read(reinterpret_cast<RF_Type::UInt8*>(&ByValue),0,sizeof(T));
}

template<class T>
RF_Type::UInt64 Stream::PeekType(T& ByValue)
{
    return Peek(reinterpret_cast<RF_Type::UInt8*>(&ByValue),0,sizeof(T));
}

} }

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define  RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif // RF_IO_STREAM_HPP
