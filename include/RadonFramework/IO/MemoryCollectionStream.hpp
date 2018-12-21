#ifndef RF_IO_MEMORYCOLLECTIONSTREAM_HPP
#define RF_IO_MEMORYCOLLECTIONSTREAM_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/IO/Stream.hpp>

namespace RadonFramework::IO
{
/// This class allow to work like MemoryStream but on multiple memory chunks.
class MemoryCollectionStream : public Stream
{
public:
  using Iterator =
      Collections::List<Memory::AutoPointerArray<RF_Type::UInt8>>::Iterator;

  using ConstIterator = Collections::List<
      Memory::AutoPointerArray<RF_Type::UInt8>>::ConstIterator;

  MemoryCollectionStream();
  MemoryCollectionStream(const MemoryCollectionStream& Copy);
  ~MemoryCollectionStream() override;
  MemoryCollectionStream& operator=(const MemoryCollectionStream& Other);

  RF_Type::Bool
  AddAfter(const Iterator& It, Memory::AutoPointerArray<RF_Type::UInt8>& Item);

  RF_Type::Bool
  AddBefore(const Iterator& it, Memory::AutoPointerArray<RF_Type::UInt8>& Item);

  void AddLast(const Memory::AutoPointerArray<RF_Type::UInt8>& Item);

  void AddFirst(Memory::AutoPointerArray<RF_Type::UInt8>& Item);

  void Insert(const RF_Type::UInt32 Index,
              Memory::AutoPointerArray<RF_Type::UInt8>& Item);

  void Clear();

  void Close() override;

  Memory::AutoPointerArray<RF_Type::UInt8> Remove(Iterator& It);

  Memory::AutoPointerArray<RF_Type::UInt8> RemoveLast();

  Memory::AutoPointerArray<RF_Type::UInt8> RemoveFirst();

  Memory::AutoPointerArray<RF_Type::UInt8> RemoveAt(RF_Type::UInt32 Index);

  /// Remove all packet befor the current position.
  void RemoveBefore();

  RF_Type::UInt64 Count();

  void Flush() override;

  RF_Type::UInt64 Read(RF_Type::UInt8* Buffer,
                       const RF_Type::UInt64 Index,
                       const RF_Type::UInt64 Count) override;

  RF_Type::UInt64
  Seek(const RF_Type::Int64 Offset, const SeekOrigin::Type Origin) override;

  RF_Type::UInt64 Write(const RF_Type::UInt8* Buffer,
                        const RF_Type::UInt64 Offset,
                        const RF_Type::UInt64 Count) override;

  RF_Type::UInt64 Peek(RF_Type::UInt8* Buffer,
                       const RF_Type::UInt64 Index,
                       const RF_Type::UInt64 Count) override;

  const RF_Type::UInt8* Peek(RF_Type::Size& BytesLeft) const;

  /// Return pointer to T if enough space left in current pointer.
  template <class T>
  T* Value();

  void SetLength(const RF_Type::UInt64 Value);

  RF_Type::Bool CanRead() const override;
  RF_Type::Bool CanSeek() const override;
  RF_Type::Bool CanWrite() const override;
  RF_Type::Bool CanTimeout() const override;
  RF_Type::Bool CanPeek() const override;
  RF_Type::UInt64 Length() const override;
  RF_Type::UInt64 Position() const override;
  Time::TimeSpan ReadTimeout() const override;
  Time::TimeSpan WriteTimeout() const override;

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
  Collections::List<Memory::AutoPointerArray<RF_Type::UInt8>> m_Collection;
  RF_Type::UInt64 m_CursorIndex;
  RF_Type::UInt64 m_CursorOffset;
};

template <class T>
T* MemoryCollectionStream::Value()
{
  if(m_Collection[m_CursorIndex].Size() - m_CursorOffset >= sizeof(T))
    return reinterpret_cast<T*>(m_Collection[m_CursorIndex].Get() +
                                m_CursorOffset);
  else
    return 0;
}

}  // namespace RadonFramework::IO

#endif  // RF_IO_MEMORYCOLLECTIONSTREAM_HPP
