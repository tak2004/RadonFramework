#ifndef RF_IO_MEMORYCOLLECTIONSTREAM_HPP
#define RF_IO_MEMORYCOLLECTIONSTREAM_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/Stream.hpp>
#include <RadonFramework/Collections/List.hpp>

namespace RadonFramework
{
    namespace IO
    {
        class MemoryCollectionStream:public Stream
        {
            public:
                typedef Collections::List<
                    Memory::AutoPointerArray<RFTYPE::UInt8> >::Iterator Iterator;

                typedef Collections::List<
                    Memory::AutoPointerArray<RFTYPE::UInt8> >::ConstIterator ConstIterator;

                MemoryCollectionStream();
                MemoryCollectionStream(const MemoryCollectionStream& Copy);
                ~MemoryCollectionStream();
                MemoryCollectionStream& operator =(const MemoryCollectionStream& Other);

                RFTYPE::Bool AddAfter(const Iterator& It,
                    Memory::AutoPointerArray<RFTYPE::UInt8> &Item);

                RFTYPE::Bool AddBefore(const Iterator& it,
                    Memory::AutoPointerArray<RFTYPE::UInt8> &Item);

                void AddLast(const Memory::AutoPointerArray<RFTYPE::UInt8> &Item);

                void AddFirst(Memory::AutoPointerArray<RFTYPE::UInt8> &Item);

                void Insert(const RFTYPE::UInt32 Index, 
                    Memory::AutoPointerArray<RFTYPE::UInt8> &Item);

                void Clear();

                void Close();

                Memory::AutoPointerArray<RFTYPE::UInt8> Remove(Iterator& It);

                Memory::AutoPointerArray<RFTYPE::UInt8> RemoveLast();

                Memory::AutoPointerArray<RFTYPE::UInt8> RemoveFirst();

                Memory::AutoPointerArray<RFTYPE::UInt8> RemoveAt(
                    RFTYPE::UInt32 Index);

                RFTYPE::UInt64 Count();

                void Flush();

                RFTYPE::UInt64 Read(RFTYPE::UInt8* Buffer,
                                         const RFTYPE::UInt64 Index,
                                         const RFTYPE::UInt64 Count);

                RFTYPE::UInt64 Seek(const RFTYPE::UInt64 Offset,
                                         const SeekOrigin::Type Origin);

                RFTYPE::UInt64 Write(const RFTYPE::UInt8* Buffer,
                                          const RFTYPE::UInt64 Offset,
                                          const RFTYPE::UInt64 Count);

                /// Return pointer to T if enough space left in current pointer.
                template<class T>
                T* Value();

                void SetLength(const RFTYPE::UInt64 Value);

                RFTYPE::Bool CanRead()const;
                RFTYPE::Bool CanSeek()const;
                RFTYPE::Bool CanWrite()const;
                RFTYPE::Bool CanTimeout()const;
                RFTYPE::UInt64 Length()const;
                RFTYPE::UInt64 Position()const;
                Time::TimeSpan ReadTimeout()const;
                Time::TimeSpan WriteTimeout()const;
            protected:
                Time::TimeSpan m_ReadTimeout;
                Time::TimeSpan m_WriteTimeout;
                RFTYPE::UInt64 m_Length;
                RFTYPE::UInt64 m_Position;
                RFTYPE::Bool m_CanRead;
                RFTYPE::Bool m_CanSeek;
                RFTYPE::Bool m_CanWrite;
                RFTYPE::Bool m_CanTimeout;
                Collections::List<
                    Memory::AutoPointerArray<RFTYPE::UInt8> > m_Collection;
                RFTYPE::UInt64 m_CursorIndex;
                RFTYPE::UInt64 m_CursorOffset;
        };

        template<class T>
        T* MemoryCollectionStream::Value()
        {
            if (m_Collection[m_CursorIndex].Size()-m_CursorOffset>=sizeof(T))
                return reinterpret_cast<T*>(m_Collection[m_CursorIndex].Get()+m_CursorOffset);
            else
                return 0;
        }
    }
}

#endif // RF_IO_MEMORYCOLLECTIONSTREAM_HPP
