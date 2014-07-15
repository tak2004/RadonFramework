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
                    Memory::AutoPointerArray<RF_Type::UInt8> >::Iterator Iterator;

                typedef Collections::List<
                    Memory::AutoPointerArray<RF_Type::UInt8> >::ConstIterator ConstIterator;

                MemoryCollectionStream();
                MemoryCollectionStream(const MemoryCollectionStream& Copy);
                ~MemoryCollectionStream();
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

                void Close();

                Memory::AutoPointerArray<RF_Type::UInt8> Remove(Iterator& It);

                Memory::AutoPointerArray<RF_Type::UInt8> RemoveLast();

                Memory::AutoPointerArray<RF_Type::UInt8> RemoveFirst();

                Memory::AutoPointerArray<RF_Type::UInt8> RemoveAt(
                    RF_Type::UInt32 Index);

                RF_Type::UInt64 Count();

                void Flush();

                RF_Type::UInt64 Read(RF_Type::UInt8* Buffer,
                                         const RF_Type::UInt64 Index,
                                         const RF_Type::UInt64 Count);

                RF_Type::UInt64 Seek(const RF_Type::UInt64 Offset,
                                         const SeekOrigin::Type Origin);

                RF_Type::UInt64 Write(const RF_Type::UInt8* Buffer,
                                          const RF_Type::UInt64 Offset,
                                          const RF_Type::UInt64 Count);

                /// Return pointer to T if enough space left in current pointer.
                template<class T>
                T* Value();

                void SetLength(const RF_Type::UInt64 Value);

                RF_Type::Bool CanRead()const;
                RF_Type::Bool CanSeek()const;
                RF_Type::Bool CanWrite()const;
                RF_Type::Bool CanTimeout()const;
                RF_Type::UInt64 Length()const;
                RF_Type::UInt64 Position()const;
                Time::TimeSpan ReadTimeout()const;
                Time::TimeSpan WriteTimeout()const;
            protected:
                Time::TimeSpan m_ReadTimeout;
                Time::TimeSpan m_WriteTimeout;
                RF_Type::UInt64 m_Length;
                RF_Type::UInt64 m_Position;
                RF_Type::Bool m_CanRead;
                RF_Type::Bool m_CanSeek;
                RF_Type::Bool m_CanWrite;
                RF_Type::Bool m_CanTimeout;
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
    }
}

#endif // RF_IO_MEMORYCOLLECTIONSTREAM_HPP
