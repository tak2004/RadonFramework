#include <RadonFramework/Core/Types/AtomicInt32.hpp>
#include <RadonFramework/System/Threading/Interlocked.hpp>
#include "RadonFramework/precompiled.hpp"

namespace RadonFramework::Core::Types
{
AtomicInt32::AtomicInt32(DataType Value) : m_Data(Value) {}

AtomicInt32::DataType AtomicInt32::Increment()
{
  return RF_SysThread::Interlocked::InterlockedInc32(&m_Data);
}

AtomicInt32::DataType AtomicInt32::Decrement()
{
  return RF_SysThread::Interlocked::InterlockedDec32(&m_Data);
}

AtomicInt32::DataType AtomicInt32::FetchAndAdd(DataType Addend)
{
  return RF_SysThread::Interlocked::InterlockedAdd32(&m_Data, Addend);
}

AtomicInt32::DataType AtomicInt32::FetchAndExchange(DataType Value)
{
  return RF_SysThread::Interlocked::InterlockedExchange32(&m_Data, Value);
}

AtomicInt32::DataType
AtomicInt32::CompareAndExchange(DataType Compare, DataType Value)
{
  return RF_SysThread::Interlocked::InterlockedCompareExchange32(&m_Data, Value,
                                                                 Compare);
}

AtomicInt32::DataType AtomicInt32::Add(DataType Value)
{
  return RF_SysThread::Interlocked::InterlockedAdd32(&m_Data, Value);
}

AtomicInt32::operator Int32() const
{
  return m_Data;
}

bool AtomicInt32::operator!() const
{
  return m_Data == 0 ? true : false;
}

bool AtomicInt32::operator!=(DataType Value) const
{
  return m_Data != Value;
}

AtomicInt32& AtomicInt32::operator=(DataType Value)
{
  m_Data = Value;
  return *this;
}

bool AtomicInt32::operator==(DataType Value) const
{
  return m_Data == Value;
}

AtomicInt32& AtomicInt32::operator++()
{
  Increment();
  return *this;
}

AtomicInt32 AtomicInt32::operator++(Int32)
{
  AtomicInt32 result(*this);
  Increment();
  return result;
}

AtomicInt32& AtomicInt32::operator--()
{
  Decrement();
  return *this;
}

AtomicInt32 AtomicInt32::operator--(Int32)
{
  AtomicInt32 result(*this);
  Decrement();
  return result;
}

}  // namespace RadonFramework::Core::Types