#include "RadonFramework/Collections/RingBuffer.hpp"
#include "RadonFramework/Core/Types/AtomicUInt64.hpp"
#include "RadonFramework/System/Memory.hpp"
#include "RadonFramework/precompiled.hpp"

namespace RadonFramework::Collections
{
template <>
class RingBufferAccess<ConcurrencyModel::None>
{
public:
  explicit RingBufferAccess(RF_Type::Size& UsableBytes,
                            RF_Type::UInt8*& MemoryBlock)
  : m_ReadCursor(0),
    m_WriteCursor(0),
    m_UsedBytes(0),
    m_UsableBytes(UsableBytes),
    m_View(MemoryBlock)
  {
  }

  RF_Type::Bool Read(RF_Type::UInt8* Data, RF_Type::Size Bytes)
  {
    if(Bytes <= m_UsedBytes)
    {
      RF_SysMem::Copy(Data, m_View + m_ReadCursor, Bytes);
      m_ReadCursor = (m_ReadCursor + Bytes) % m_UsableBytes;
      m_UsedBytes -= Bytes;
      return true;
    }
    return false;
  }

  RF_Type::Bool Write(RF_Type::UInt8* Data, const RF_Type::Size Bytes)
  {
    auto writeableBytes = m_UsableBytes - m_UsedBytes;
    if(Bytes <= writeableBytes)
    {
      RF_SysMem::Copy(m_View + m_WriteCursor, Data, Bytes);
      m_WriteCursor = (m_WriteCursor + Bytes) % m_UsableBytes;
      m_UsedBytes += Bytes;
      return true;
    }
    return false;
  }

private:
  RF_Type::Size m_ReadCursor;
  RF_Type::Size m_WriteCursor;
  RF_Type::Size m_UsedBytes;
  RF_Type::Size& m_UsableBytes;
  RF_Type::UInt8*& m_View;
};

template <>
class RingBufferAccess<ConcurrencyModel::SPSC>
{
public:
  explicit RingBufferAccess(RF_Type::Size& UsableBytes,
                            RF_Type::UInt8*& MemoryBlock)
  : m_ReadCursor(0),
    m_WriteCursor(0),
    m_UsedBytes(0),
    m_UsableBytes(UsableBytes),
    m_View(MemoryBlock)
  {
  }

  RF_Type::Bool Read(RF_Type::UInt8* Data, RF_Type::Size Bytes)
  {
    if(Bytes <= m_UsedBytes)
    {
      RF_SysMem::Copy(Data, m_View + m_ReadCursor, Bytes);
      m_ReadCursor = (m_ReadCursor + Bytes) % m_UsableBytes;
      m_UsedBytes.Add(-Bytes);
      return true;
    }
    return false;
  }

  RF_Type::Bool Write(RF_Type::UInt8* Data, const RF_Type::Size Bytes)
  {
    auto writeableBytes = m_UsableBytes - m_UsedBytes;
    if(Bytes <= writeableBytes)
    {
      RF_SysMem::Copy(m_View + m_WriteCursor, Data, Bytes);
      m_WriteCursor = (m_WriteCursor + Bytes) % m_UsableBytes;
      m_UsedBytes.Add(Bytes);
      return true;
    }
    return false;
  }

private:
  RF_Type::Size m_ReadCursor;
  RF_Type::Size m_WriteCursor;
  RF_Type::AtomicUInt64 m_UsedBytes;
  RF_Type::Size& m_UsableBytes;
  RF_Type::UInt8*& m_View;
};

template <>
class RingBufferAccess<ConcurrencyModel::MPSC>
{
public:
  explicit RingBufferAccess(RF_Type::Size& UsableBytes,
                            RF_Type::UInt8*& MemoryBlock)
  : m_ReadCursor(0),
    m_WriteCursor(0),
    m_UsableBytes(UsableBytes),
    m_View(MemoryBlock)
  {
  }

  RF_Type::Bool Read(RF_Type::UInt8* Data, RF_Type::Size Bytes)
  {
    if(Bytes <= m_UsedBytes)
    {
      RF_SysMem::Copy(Data, m_View + m_ReadCursor, Bytes);
      m_ReadCursor = (m_ReadCursor + Bytes) % m_UsableBytes;
      m_UsedBytes.Add(-Bytes);
      return true;
    }
    return false;
  }

  RF_Type::Bool Write(RF_Type::UInt8* Data, const RF_Type::Size Bytes)
  {
    RF_Type::Size currentWriteCursor = m_WriteCursor;
    auto writeableBytes =
        ((m_UsableBytes + m_ReadCursor) - currentWriteCursor) % m_UsableBytes;
    while(Bytes < writeableBytes)
    {
      auto lastWriteCursor = m_WriteCursor.CompareAndExchange(
          currentWriteCursor, (currentWriteCursor + Bytes) % m_UsableBytes);
      if(lastWriteCursor == currentWriteCursor)
      {
        RF_SysMem::Copy(m_View + currentWriteCursor, Data, Bytes);
        return true;
      }
      currentWriteCursor = lastWriteCursor;
      writeableBytes =
          ((m_UsableBytes + m_ReadCursor) - currentWriteCursor) % m_UsableBytes;
    }
    return false;
  }

private:
  RF_Type::AtomicUInt64 m_ReadCursor;
  RF_Type::AtomicUInt64 m_WriteCursor;
  RF_Type::AtomicUInt64 m_UsedBytes;
  RF_Type::Size& m_UsableBytes;
  RF_Type::UInt8*& m_View;
};

template <>
class RingBufferAccess<ConcurrencyModel::SPMC>
{
public:
  explicit RingBufferAccess(RF_Type::Size& UsableBytes,
                            RF_Type::UInt8*& MemoryBlock)
  : m_ReadCursor(0),
    m_WriteCursor(0),
    m_UsableBytes(UsableBytes),
    m_View(MemoryBlock)
  {
  }

  RF_Type::Bool Read(RF_Type::UInt8* Data, RF_Type::Size Bytes)
  {
    RF_Type::Size currentReadCursor = m_ReadCursor;
    auto readableBytes =
        ((m_UsableBytes + m_WriteCursor) - m_ReadCursor) % m_UsableBytes;
    while(Bytes <= readableBytes)
    {
      auto lastReadCursor = m_ReadCursor.CompareAndExchange(
          currentReadCursor, (currentReadCursor + Bytes) % m_UsableBytes);
      if(lastReadCursor == currentReadCursor)
      {
        RF_SysMem::Copy(Data, m_View + currentReadCursor, Bytes);
        return true;
      }
      currentReadCursor = lastReadCursor;
      readableBytes =
          ((m_UsableBytes + m_WriteCursor) - currentReadCursor) % m_UsableBytes;
    }
    return false;
  }

  RF_Type::Bool Write(RF_Type::UInt8* Data, const RF_Type::Size Bytes)
  {
    auto writeableBytes =
        ((m_UsableBytes + m_ReadCursor) - m_WriteCursor) % m_UsableBytes;
    if(Bytes < writeableBytes)
    {
      RF_SysMem::Copy(m_View + m_WriteCursor, Data, Bytes);
      m_WriteCursor = (m_WriteCursor + Bytes) % m_UsableBytes;
      return true;
    }
    return false;
  }

private:
  RF_Type::AtomicUInt64 m_ReadCursor;
  RF_Type::AtomicUInt64 m_WriteCursor;
  RF_Type::Size& m_UsableBytes;
  RF_Type::UInt8*& m_View;
};

template <>
class RingBufferAccess<ConcurrencyModel::MPMC>
{
public:
  explicit RingBufferAccess(RF_Type::Size& UsableBytes,
                            RF_Type::UInt8*& MemoryBlock)
  : m_ReadCursor(0),
    m_WriteCursor(0),
    m_UsableBytes(UsableBytes),
    m_View(MemoryBlock)
  {
  }

  RF_Type::Bool Read(RF_Type::UInt8* Data, RF_Type::Size Bytes)
  {
    RF_Type::Size currentReadCursor = m_ReadCursor;
    auto readableBytes =
        ((m_UsableBytes + m_WriteCursor) - m_ReadCursor) % m_UsableBytes;
    while(Bytes <= readableBytes)
    {
      auto lastReadCursor = m_ReadCursor.CompareAndExchange(
          currentReadCursor, (currentReadCursor + Bytes) % m_UsableBytes);
      if(lastReadCursor == currentReadCursor)
      {
        RF_SysMem::Copy(Data, m_View + currentReadCursor, Bytes);
        return true;
      }
      currentReadCursor = lastReadCursor;
      readableBytes =
          ((m_UsableBytes + m_WriteCursor) - currentReadCursor) % m_UsableBytes;
    }
    return false;
  }

  RF_Type::Bool Write(RF_Type::UInt8* Data, const RF_Type::Size Bytes)
  {
    RF_Type::Size currentWriteCursor = m_WriteCursor;
    auto writeableBytes =
        ((m_UsableBytes + m_ReadCursor) - currentWriteCursor) % m_UsableBytes;
    while(Bytes < writeableBytes)
    {
      auto lastWriteCursor = m_WriteCursor.CompareAndExchange(
          currentWriteCursor, (currentWriteCursor + Bytes) % m_UsableBytes);
      if(lastWriteCursor == currentWriteCursor)
      {
        RF_SysMem::Copy(m_View + currentWriteCursor, Data, Bytes);
        return true;
      }
      currentWriteCursor = lastWriteCursor;
      writeableBytes =
          ((m_UsableBytes + m_ReadCursor) - currentWriteCursor) % m_UsableBytes;
    }
    return false;
  }

private:
  RF_Type::AtomicUInt64 m_ReadCursor;
  RF_Type::AtomicUInt64 m_WriteCursor;
  RF_Type::Size& m_UsableBytes;
  RF_Type::UInt8*& m_View;
};

}  // namespace RadonFramework::Collections