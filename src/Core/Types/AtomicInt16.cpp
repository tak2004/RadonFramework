#include <RadonFramework/Core/Types/AtomicInt16.hpp>
#include <RadonFramework/System/Threading/Interlocked.hpp>
#include "RadonFramework/precompiled.hpp"

namespace RadonFramework::Core::Types
{
AtomicInt16::AtomicInt16(DataType Value) : m_Data(Value) {}

AtomicInt16::AtomicInt16(const AtomicInt16& Other) : m_Data(Other.m_Data) {}

AtomicInt16::DataType AtomicInt16::Increment()
{
  return RF_SysThread::Interlocked::InterlockedInc16(&m_Data);
}

AtomicInt16::DataType AtomicInt16::Decrement()
{
  return RF_SysThread::Interlocked::InterlockedDec16(&m_Data);
}

AtomicInt16::DataType AtomicInt16::FetchAndAdd(DataType Addend)
{
  return RF_SysThread::Interlocked::InterlockedAdd16(&m_Data, Addend);
}

AtomicInt16::DataType AtomicInt16::FetchAndExchange(DataType Value)
{
  return RF_SysThread::Interlocked::InterlockedExchange16(&m_Data, Value);
}

AtomicInt16::DataType
AtomicInt16::CompareAndExchange(DataType Compare, DataType Value)
{
  return RF_SysThread::Interlocked::InterlockedCompareExchange16(&m_Data, Value,
                                                                 Compare);
}

AtomicInt16::DataType AtomicInt16::Add(DataType Value)
{
  return RF_SysThread::Interlocked::InterlockedAdd16(&m_Data, Value);
}

AtomicInt16::operator Int16() const
{
  return m_Data;
}

bool AtomicInt16::operator!() const
{
  return m_Data == 0 ? true : false;
}

bool AtomicInt16::operator!=(DataType Value) const
{
  return m_Data != Value;
}

AtomicInt16& AtomicInt16::operator=(DataType Value)
{
  m_Data = Value;
  return *this;
}

AtomicInt16& AtomicInt16::operator=(const AtomicInt16& Other)
{
  m_Data = Other.m_Data;
  return *this;
}

bool AtomicInt16::operator==(DataType Value) const
{
  return m_Data == Value;
}

AtomicInt16& AtomicInt16::operator++()
{
  Increment();
  return *this;
}

AtomicInt16 AtomicInt16::operator++(int)
{
  AtomicInt16 result(*this);
  Increment();
  return result;
}

AtomicInt16& AtomicInt16::operator--()
{
  Decrement();
  return *this;
}

AtomicInt16 AtomicInt16::operator--(int)
{
  AtomicInt16 result(*this);
  Decrement();
  return result;
}

}  // namespace RadonFramework::Core::Types