#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/MemoryCollectionStream.hpp"
#include "RadonFramework/Core/Policies/CMemoryOperation.hpp"

using namespace RadonFramework::IO;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Time;
using namespace RadonFramework::Core::Policies;

MemoryCollectionStream::MemoryCollectionStream()
:m_CanRead(true)
,m_CanSeek(true)
,m_CanWrite(true)
,m_CanTimeout(false)
,m_CursorIndex(0)
,m_CursorOffset(0)
,m_Length(0)
,m_Position(0)
{

}

MemoryCollectionStream::MemoryCollectionStream( const MemoryCollectionStream& Copy )
{
    *this=Copy;
}

MemoryCollectionStream::~MemoryCollectionStream()
{
    // nothing to do here
}

MemoryCollectionStream& MemoryCollectionStream::operator=( 
    const MemoryCollectionStream& Other )
{
    return *this;
}

void MemoryCollectionStream::Flush()
{
    // nothing to do here
}

UInt64 MemoryCollectionStream::Read( UInt8* Buffer, const UInt64 Index, 
                                     const UInt64 Count )
{
    if (m_Position<m_Length)
    {
        // expect the best case: a small enough read without process multiple buffers
        if (static_cast<UInt64>(m_Collection[static_cast<UInt32>(m_CursorIndex)].Size())-m_CursorOffset>Count)
        {
            CMemoryOperation::Copy(Buffer+Index,m_Collection[static_cast<UInt32>(m_CursorIndex)].Get()+m_CursorOffset,static_cast<UInt32>(Count));
            m_Position+=Count;
            m_CursorOffset+=Count;
            return Count;
        }
        else
        {// worst case: the read is larger as the size of the current buffer
            // get number of available bytes of current buffer
            UInt64 readbytes=static_cast<UInt64>(m_Collection[static_cast<UInt32>(m_CursorIndex)].Size())-m_CursorOffset;
            CMemoryOperation::Copy(Buffer+Index,m_Collection[static_cast<UInt32>(m_CursorIndex)].Get()+m_CursorOffset,static_cast<UInt32>(readbytes));
            // update cursor and properties
            m_Position+=readbytes;
            ++m_CursorIndex;
            m_CursorOffset=0;
            // try next buffer
            readbytes+=Read(Buffer,Index+readbytes,Count-readbytes);
            return readbytes;
        }
    }
    else
        return 0;
}

void MemoryCollectionStream::Close()
{

}

UInt64 MemoryCollectionStream::Seek( const UInt64 Offset, 
                                     const SeekOrigin::Type Origin )
{
    switch (Origin)
    {
        case SeekOrigin::Begin:
            {
                m_Position=Offset;
                m_CursorOffset=Offset;
                m_CursorIndex=0;
                return Offset;
            }
        case SeekOrigin::Current:
            {
                m_Position+=Offset;
                m_CursorOffset=m_Position;
                m_CursorIndex=0;
                return Offset;
            }
        case SeekOrigin::End:
            {
                m_Position=m_Length-Offset;
                m_CursorOffset=m_Position;
                m_CursorIndex=0;
                return Offset;
            }
    }
    return 0;    
}

UInt64 MemoryCollectionStream::Write( const UInt8* Buffer, const UInt64 Offset, 
                                      const UInt64 Count )
{
    if (m_Position+Count<=m_Length)
    {
        // expect the best case: a small enough write without process multiple buffers
        if (static_cast<UInt64>(m_Collection[static_cast<UInt32>(m_CursorIndex)].Size())-m_CursorOffset>Count)
        {
            RF_SysMem::Copy(m_Collection[static_cast<UInt32>(m_CursorIndex)].Get()+m_CursorOffset,Buffer+Offset,Count);    
            m_Position+=Count;
            m_CursorOffset+=Count;
            return Count;
        }
        else
        {// worst case: the write is larger as the size of the current buffer
            // get number of available bytes of current buffer
            UInt64 writtenBytes=static_cast<UInt64>(m_Collection[static_cast<UInt32>(m_CursorIndex)].Size())-m_CursorOffset;
            RF_SysMem::Copy(m_Collection[static_cast<UInt32>(m_CursorIndex)].Get()+m_CursorOffset,Buffer+Offset,writtenBytes);    
            // update cursor and properties
            m_Position+=writtenBytes;
            ++m_CursorIndex;
            m_CursorOffset=0;
            // try next buffer
            if (writtenBytes<Count)
                writtenBytes+=Write(Buffer,Offset+writtenBytes,Count-writtenBytes);
            return writtenBytes;
        }
    }
    else
        return 0;
}

void MemoryCollectionStream::SetLength( const UInt64 Value )
{
    m_Length=Value;
}

Bool MemoryCollectionStream::CanRead()const
{
    return m_CanRead;
}

Bool MemoryCollectionStream::CanSeek()const
{
    return m_CanSeek;
}

Bool MemoryCollectionStream::CanWrite()const
{
    return m_CanWrite;
}

Bool MemoryCollectionStream::CanTimeout()const
{
    return m_CanTimeout;
}

UInt64 MemoryCollectionStream::Length()const
{
    return m_Length;
}

UInt64 MemoryCollectionStream::Position()const
{
    return m_Position;
}

TimeSpan MemoryCollectionStream::ReadTimeout()const
{
    return m_ReadTimeout;
}

TimeSpan MemoryCollectionStream::WriteTimeout()const
{
    return m_WriteTimeout;
}

Bool MemoryCollectionStream::AddAfter( const Iterator& It, AutoPointerArray<UInt8> &Item )
{
    m_Length+=Item.Count();
    return m_Collection.AddAfter(It, Item);
}

Bool MemoryCollectionStream::AddBefore( const Iterator& it, AutoPointerArray<UInt8> &Item )
{
    m_Length+=Item.Count();
    return m_Collection.AddBefore(it, Item);
}

void MemoryCollectionStream::AddLast( const AutoPointerArray<UInt8> &Item )
{
    m_Length+=Item.Count();
    m_Collection.AddLast(Item);
}

void MemoryCollectionStream::AddFirst( AutoPointerArray<UInt8> &Item )
{
    m_Length+=Item.Count();
    m_Collection.AddFirst(Item);
}

void MemoryCollectionStream::Insert( const UInt32 Index, AutoPointerArray<UInt8> &Item )
{
    m_Length+=Item.Count();
    m_Collection.Insert(Index,Item);
}

void MemoryCollectionStream::Clear()
{
    m_Length=0;
    m_Collection.Clear();
}

AutoPointerArray<UInt8> MemoryCollectionStream::Remove( Iterator& It )
{
    AutoPointerArray<UInt8> result=*It;
    m_Collection.Remove(It);
    return result;
}

AutoPointerArray<UInt8> MemoryCollectionStream::RemoveLast()
{
    AutoPointerArray<UInt8> result=*m_Collection.Last();
    m_Collection.RemoveLast();
    return result;
}

AutoPointerArray<UInt8> MemoryCollectionStream::RemoveFirst()
{
    AutoPointerArray<UInt8> result=*m_Collection.First();
    m_Collection.RemoveFirst();
    return result;
}

AutoPointerArray<UInt8> MemoryCollectionStream::RemoveAt( UInt32 Index )
{
    AutoPointerArray<UInt8> result=m_Collection[Index];
    m_Collection.RemoveAt(Index);
    return result;
}

UInt64 MemoryCollectionStream::Count()
{
    return m_Collection.Size();
}
