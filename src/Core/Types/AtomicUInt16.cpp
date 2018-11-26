#include "RadonFramework/Core/Types/AtomicUInt16.hpp"
#include "RadonFramework/System/Threading/Interlocked.hpp"
#include "RadonFramework/precompiled.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::Threading;

AtomicUInt16::AtomicUInt16(DataType Value) : m_Data(Value) {}

AtomicUInt16::AtomicUInt16(const AtomicUInt16& Other) : m_Data(Other.m_Data) {}

AtomicUInt16::DataType AtomicUInt16::Increment()
{
  return Interlocked::InterlockedInc16((Int16*)&m_Data);
}

AtomicUInt16::DataType AtomicUInt16::Decrement()
{
  return Interlocked::InterlockedDec16((Int16*)&m_Data);
}

AtomicUInt16::DataType AtomicUInt16::FetchAndAdd(DataType Addend)
{
  return Interlocked::InterlockedAdd16((Int16*)&m_Data, Addend);
}

AtomicUInt16::DataType AtomicUInt16::FetchAndExchange(DataType Value)
{
  return Interlocked::InterlockedExchange16((Int16*)&m_Data, Value);
}

AtomicUInt16::DataType
AtomicUInt16::CompareAndExchange(DataType Compare, DataType Value)
{
  return Interlocked::InterlockedCompareExchange16((Int16*)&m_Data, Value,
                                                   Compare);
}

AtomicUInt16::DataType AtomicUInt16::Add(DataType Value)
{
  return Interlocked::InterlockedAdd16((Int16*)&m_Data, Value);
}

AtomicUInt16::operator UInt16() const
{
  return m_Data;
}

bool AtomicUInt16::operator!() const
{
  return m_Data == 0 ? true : false;
}

bool AtomicUInt16::operator!=(DataType Value) const
{
  return m_Data != Value;
}

AtomicUInt16& AtomicUInt16::operator=(DataType Value)
{
  m_Data = Value;
  return *this;
}

AtomicUInt16& AtomicUInt16::operator=(const AtomicUInt16& Other)
{
  m_Data = Other.m_Data;
  return *this;
}

bool AtomicUInt16::operator==(DataType Value) const
{
  return m_Data == Value;
}

AtomicUInt16& AtomicUInt16::operator++()
{
  Increment();
  return *this;
}

AtomicUInt16 AtomicUInt16::operator++(int)
{
  AtomicUInt16 result(*this);
  Increment();
  return result;
}

AtomicUInt16& AtomicUInt16::operator--()
{
  Decrement();
  return *this;
}

AtomicUInt16 AtomicUInt16::operator--(int)
{
  AtomicUInt16 result(*this);
  Decrement();
  return result;
}