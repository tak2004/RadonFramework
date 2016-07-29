#ifndef RF_IO_MEMORYCOLLECTIONSTREAM_HPP
#define RF_IO_MEMORYCOLLECTIONSTREAM_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/Stream.hpp>
#include <RadonFramework/Collections/List.hpp>

namespace RadonFramework { namespace IO {


/// This class allow to work like MemoryStream but on multiple memory chunks.
class MemoryCollectionStream:public Stream
{
public:
    typedef Collections::List<
        Memory::AutoPointerArray<RF_Type::UInt8> >::Iterator Iterator;

    typedef Collections::List<
        Memory::AutoPointerArray<RF_Type::UInt8> >::ConstIterator ConstIterator;

    MemoryCollectionStream();
    MemoryCollectionStream(const MemoryCollectionStream& Copy);
    virtual ~MemoryCollectionStream() override;
    MemoryCollectionStream& operator =(const MemoryCollectionStream& Other);

    RF_Type::Bool AddAfter(const Iterator& It,
        Memory::AutoPointerArray<RF_Type::UInt8> &Item);

    RF_Type::Bool AddBefore(const Iterator& it,
        Memory::AutoPointerArray<RF_Type::UInt8> &Item);

    void AddLast(const Memory::AutoPointerArray<RF_Type::UInt8> &Item);

    void AddFirst(Memory::AutoPointerArray<RF_Type::UInt8> &Item);

    void Insert(const RF_Type::UInt32 Index, 
        Memory::AutoPointerArray<RF_Type::UInt8> &Item);

    void Clear();

    virtual void Close() override;

    Memory::AutoPointerArray<RF_Type::UInt8> Remove(Iterator& It);

    Memory::AutoPointerArray<RF_Type::UInt8> RemoveLast();

    Memory::AutoPointerArray<RF_Type::UInt8> RemoveFirst();

    Memory::AutoPointerArray<RF_Type::UInt8> RemoveAt(RF_Type::UInt32 Index);

    /// Remove all packet befor the current position.
    void RemoveBefore();

    RF_Type::UInt64 Count();

    virtual void Flush() override;

    virtual RF_Type::UInt64 Read(RF_Type::UInt8* Buffer,
        const RF_Type::UInt64 Index, const RF_Type::UInt64 Count) override;

    virtual RF_Type::UInt64 Seek(const RF_Type::Int64 Offset,
        const SeekOrigin::Type Origin) override;

    virtual RF_Type::UInt64 Write(const RF_Type::UInt8* Buffer,
        const RF_Type::UInt64 Offset, const RF_Type::UInt64 Count) override;

    virtual RF_Type::UInt64 Peek(RF_Type::UInt8* Buffer,
        const RF_Type::UInt64 Index, const RF_Type::UInt64 Count) override;

    const RF_Type::UInt8* Peek(RF_Type::Size& BytesLeft)const;

    /// Return pointer to T if enough space left in current pointer.
    template<class T>
    T* Value();

    void SetLength(const RF_Type::UInt64 Value);

    virtual RF_Type::Bool CanRead()const override;
    virtual RF_Type::Bool CanSeek()const override;
    virtual RF_Type::Bool CanWrite()const override;
    virtual RF_Type::Bool CanTimeout()const override;
    virtual RF_Type::Bool CanPeek()const override;
    virtual RF_Type::UInt64 Length()const override;
    virtual RF_Type::UInt64 Position()const override;
    virtual Time::TimeSpan ReadTimeout()const override;
    virtual Time::TimeSpan WriteTimeout()const override;
protected:
    Time::TimeSpan m_ReadTimeout;
    Time::TimeSpan m_WriteTimeout;
    RF_Type::UInt64 m_Length;
    RF_Type::UInt64 m_Position;
    RF_Type::Bool m_CanRead;
    RF_Type::Bool m_CanSeek;
    RF_Type::Bool m_CanWrite;
    RF_Type::Bool m_CanTimeout;
    RF_Type::Bool m_CanPeek;
    Collections::List<
        Memory::AutoPointerArray<RF_Type::UInt8> > m_Collection;
    RF_Type::UInt64 m_CursorIndex;
    RF_Type::UInt64 m_CursorOffset;
};

template<class T>
T* MemoryCollectionStream::Value()
{
    if (m_Collection[m_CursorIndex].Size()-m_CursorOffset>=sizeof(T))
        return reinterpret_cast<T*>(m_Collection[m_CursorIndex].Get()+m_CursorOffset);
    else
        return 0;
}

} }

#endif // RF_IO_MEMORYCOLLECTIONSTREAM_HPP
