#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/MemoryStream.hpp"
#include "RadonFramework/Core/Policies/CMemoryOperation.hpp"

namespace RadonFramework { namespace IO {

MemoryStream::MemoryStream()
:m_FenceStart(0)
,m_FenceEnd(0)
,m_Position(0)
,m_CanWrite(true)
,m_CanRead(false)
,m_UseFence(false)
,m_Expandable(true)
{

}

MemoryStream::MemoryStream(const MemoryStream& Copy)
{
    *this = Copy;
}

MemoryStream::MemoryStream(RF_Mem::AutoPointerArray<RF_Type::UInt8>& ConsumeBuffer, 
    RF_Type::Bool Writeable /*= true*/)
:m_FenceStart(0)
,m_FenceEnd(0)
,m_Position(0)
,m_CanWrite(Writeable)
,m_CanRead(true)
,m_UseFence(false)
,m_Expandable(false)
{
    m_Data = ConsumeBuffer;
}

MemoryStream::MemoryStream(RF_Mem::AutoPointerArray<RF_Type::UInt8>& ConsumeBuffer, 
    RF_Type::Size FenceStart, RF_Type::Size FenceByteSize, RF_Type::Bool Writeable /*= true*/)
:m_FenceStart(FenceStart)
,m_FenceEnd(FenceStart + FenceByteSize)
,m_Position(0)
,m_CanWrite(Writeable)
,m_CanRead(true)
,m_UseFence(true)
,m_Expandable(false)
{
    m_Data = ConsumeBuffer;
}

MemoryStream::MemoryStream(RF_Type::Size ReserveBytes)
:MemoryStream()
{
    Reserve(ReserveBytes);
}

MemoryStream& MemoryStream::operator=(const MemoryStream& Other)
{
    m_Data = Other.m_Data.Clone();
    m_FenceStart = Other.m_FenceStart;
    m_FenceEnd = Other.m_FenceEnd;
    m_Position = Other.m_Position;
    m_CanWrite = Other.m_CanWrite;
    m_UseFence = Other.m_UseFence;
    return *this;
}

void MemoryStream::Reserve(RF_Type::Size ReserveBytes)
{
    if (m_Expandable)
    {
        m_Data = RF_Mem::AutoPointerArray<RF_Type::UInt8>(ReserveBytes);
        m_Position = 0;
        m_CanRead = ReserveBytes > 0;
    }
}

void MemoryStream::Resize(RF_Type::Size NewByteSize)
{
    if(m_Expandable)
    {
        auto newData = RF_Mem::AutoPointerArray<RF_Type::UInt8>(NewByteSize);
        RF_SysMem::Copy(newData.Get(), m_Data.Get(), Position());
        m_Data.Swap(newData);
        m_CanRead = true;
    }
}

void MemoryStream::Replace(RF_Mem::AutoPointerArray<RF_Type::UInt8>& ConsumeBuffer)
{
    m_Data.Reset(ConsumeBuffer.Release());
}

void MemoryStream::Close()
{
    m_Data.Release();
    m_FenceStart = 0;
    m_FenceEnd = 0;
    m_Position = 0;
    m_CanWrite = false;
    m_UseFence = false;
}

void MemoryStream::Flush()
{
    // do nothing because the data already in the memory
}

RF_Type::UInt64 MemoryStream::Read(RF_Type::UInt8* Buffer, 
    const RF_Type::UInt64 Index, const RF_Type::UInt64 Count)
{
    RF_Type::UInt64 readbytes = 0;
    RF_Type::UInt64 length = Length();
    RF_Type::UInt64 position = Position();
    if(position < length)
    {
        readbytes = RF_Math::Integer<RF_Type::UInt64>::ClampUpperBound(Count, length - position);
        RF_Policy::CMemoryOperation::Copy(Buffer + Index, m_Data.Get()+m_Position, readbytes);
        m_Position += readbytes;
    }
    return readbytes;
}

RF_Type::UInt64 MemoryStream::Seek(const RF_Type::Int64 Offset, const SeekOrigin::Type Origin)
{
    RF_Type::UInt64 length = Length();
    RF_Type::UInt64 position = Position();
    RF_Type::UInt64 readbytes = 0;
    switch(Origin)
    {
    case SeekOrigin::Begin:
        readbytes = RF_Math::Integer<RF_Type::Int64>::ClampUpperBound(
            RF_Math::Integer<RF_Type::Int64>::ClampLowerBound(Offset,0), length);
        m_Position = readbytes + m_FenceStart;
        break;
    case SeekOrigin::Current:
        readbytes = RF_Math::Integer<RF_Type::Int64>::ClampUpperBound(Offset, 
            length - position);
        m_Position += readbytes;
        break;
    case SeekOrigin::End:
        readbytes = RF_Math::Integer<RF_Type::Int64>::ClampUpperBound(
            RF_Math::Integer<RF_Type::Int64>::ClampLowerBound(Offset,0), length);
        m_Position = m_FenceEnd - readbytes;
        break;
    }
    return readbytes;
}

RF_Type::UInt64 MemoryStream::Write(const RF_Type::UInt8* Buffer, 
    const RF_Type::UInt64 Offset, const RF_Type::UInt64 Count)
{
    RF_Type::UInt64 readbytes = 0;
    RF_Type::UInt64 length = Length();
    RF_Type::UInt64 position = Position();
    if(m_Expandable && position + Count >= length)
    {
        auto bytesPerPage = RF_SysMem::GetPageSize();
        RF_Type::Size pageCount = ((position + Count - 1) / bytesPerPage) + 1;
        Resize(pageCount * bytesPerPage);
    }
    
    if(position < length)
    {
        readbytes = RF_Math::Integer<RF_Type::UInt64>::ClampUpperBound(Count, length - position);
        RF_Policy::CMemoryOperation::Copy(m_Data.Get() + m_Position, Buffer + Offset, readbytes);
        m_Position += readbytes;
    }
    return readbytes;
}

RF_Type::UInt64 MemoryStream::Peek(RF_Type::UInt8* Buffer, 
    const RF_Type::UInt64 Index, const RF_Type::UInt64 Count)
{
    RF_Type::UInt64 readbytes = 0;
    RF_Type::UInt64 length = Length();
    RF_Type::UInt64 position = Position();
    if(position < length)
    {
        readbytes = RF_Math::Integer<RF_Type::UInt64>::ClampUpperBound(Count, length - position);
        RF_Policy::CMemoryOperation::Copy(Buffer + Index, m_Data.Get() + m_Position, Count);
    }
    return readbytes;
}

RF_Type::Bool MemoryStream::CanRead() const
{
    return m_CanRead;
}

RF_Type::Bool MemoryStream::CanSeek() const
{
    return true;
}

RF_Type::Bool MemoryStream::CanWrite() const
{
    return m_CanWrite;
}

RF_Type::Bool MemoryStream::CanTimeout() const
{
    return false;
}

RF_Type::Bool MemoryStream::CanPeek() const
{
    return true;
}

RF_Type::Bool MemoryStream::CanExpand() const
{
    return m_Expandable;
}

RF_Type::UInt64 MemoryStream::Length() const
{
    return m_UseFence ? m_FenceEnd - m_FenceStart : m_Data.Count();
}

RF_Type::UInt64 MemoryStream::Position() const
{
    return m_UseFence ? m_Position - m_FenceStart : m_Position;
}

RF_Time::TimeSpan MemoryStream::ReadTimeout() const
{
    return RF_Time::TimeSpan::Zero;
}

RF_Time::TimeSpan MemoryStream::WriteTimeout() const
{
    return RF_Time::TimeSpan::Zero;
}

RF_Type::UInt8* MemoryStream::GetRawBuffer() const
{
    return m_Data.Get();
}

RF_Type::UInt8* MemoryStream::GetRestrictedBuffer() const
{
    return m_Data.Get() + m_FenceStart;
}

RF_Type::UInt64 MemoryStream::GetAbsolutePosition() const
{
    return m_Position;
}

RF_Type::UInt64 MemoryStream::GetRawBufferSize() const
{
    return m_Data.Count();
}

RF_Type::Bool MemoryStream::UseFence() const
{
    return m_UseFence;
}

} }