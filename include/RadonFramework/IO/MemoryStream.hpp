#ifndef RF_IO_MEMORYSTREAM_HPP
#define RF_IO_MEMORYSTREAM_HPP

#include <RadonFramework/IO/Stream.hpp>

namespace RadonFramework { namespace IO {

class MemoryStream: public Stream
{
public:
    MemoryStream();
    MemoryStream(const MemoryStream& Copy);
    MemoryStream(RF_Mem::AutoPointerArray<RF_Type::UInt8>& ConsumeBuffer, 
        RF_Type::Bool Writeable = true);
    MemoryStream(RF_Mem::AutoPointerArray<RF_Type::UInt8>& ConsumeBuffer,
        RF_Type::Size FenceStart, RF_Type::Size FenceByteSize,
        RF_Type::Bool Writeable = true);
    MemoryStream(RF_Type::Size ReserveBytes);

    /// Clone the MemoryStream and the internal memory.
    MemoryStream& operator =(const MemoryStream& Other);

    void Reserve(RF_Type::Size ReserveBytes);

    void Replace(RF_Mem::AutoPointerArray<RF_Type::UInt8>& ConsumeBuffer);

    virtual void Close() override;

    virtual void Flush() override;

    virtual RF_Type::UInt64 Read(RF_Type::UInt8* Buffer, const RF_Type::UInt64 Index, 
        const RF_Type::UInt64 Count) override;

    virtual RF_Type::UInt64 Seek(const RF_Type::Int64 Offset, 
        const SeekOrigin::Type Origin) override;

    virtual RF_Type::UInt64 Write(const RF_Type::UInt8* Buffer, 
        const RF_Type::UInt64 Offset, const RF_Type::UInt64 Count) override;

    virtual RF_Type::UInt64 Peek(RF_Type::UInt8* Buffer, const RF_Type::UInt64 Index,
        const RF_Type::UInt64 Count) override;

    virtual RF_Type::Bool CanRead() const override;

    virtual RF_Type::Bool CanSeek() const override;

    virtual RF_Type::Bool CanWrite() const override;

    virtual RF_Type::Bool CanTimeout() const override;

    virtual RF_Type::Bool CanPeek() const override;

    virtual RF_Type::UInt64 Length() const override;

    virtual RF_Type::UInt64 Position() const override;

    virtual RF_Time::TimeSpan ReadTimeout() const override;

    virtual RF_Time::TimeSpan WriteTimeout() const override;

    /// Return the pointer of the internal memory block.
    virtual RF_Type::UInt8* GetRawBuffer()const;
    /// Return the pointer of FenceStart.
    virtual RF_Type::UInt8* GetRestrictedBuffer()const;
    /// Return the position of the internal memory.
    virtual RF_Type::UInt64 GetAbsolutePosition()const;
    /// Return the size of the internal memory.
    virtual RF_Type::UInt64 GetRawBufferSize()const;
    /// Return true if the access to the memory is restricted else false.
    virtual RF_Type::Bool UseFence()const;
protected:
    RF_Mem::AutoPointerArray<RF_Type::UInt8> m_Data;
    RF_Type::Size m_FenceStart;
    RF_Type::Size m_FenceEnd;
    RF_Type::Size m_Position;
    RF_Type::Bool m_CanWrite;
    RF_Type::Bool m_CanPeek;
    RF_Type::Bool m_UseFence;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = namespace RadonFramework::IO;
#endif

#endif // !RF_IO_MEMORYSTREAM_HPP
