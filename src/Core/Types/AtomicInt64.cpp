#include <RadonFramework/Core/Types/AtomicInt64.hpp>
#include <RadonFramework/System/Threading/Interlocked.hpp>

using namespace RadonFramework::System::Threading;

namespace RadonFramework::Core::Types
{
AtomicInt64::AtomicInt64(DataType Value) : m_Data(Value) {}

AtomicInt64::DataType AtomicInt64::Increment()
{
  return Interlocked::InterlockedInc64(&m_Data);
}

AtomicInt64::DataType AtomicInt64::Decrement()
{
  return Interlocked::InterlockedDec64(&m_Data);
}

AtomicInt64::DataType AtomicInt64::FetchAndAdd(DataType Addend)
{
  return Interlocked::InterlockedAdd64(&m_Data, Addend);
}

AtomicInt64::DataType AtomicInt64::FetchAndExchange(DataType Value)
{
  return Interlocked::InterlockedExchange64(&m_Data, Value);
}

AtomicInt64::DataType
AtomicInt64::CompareAndExchange(DataType Compare, DataType Value)
{
  return Interlocked::InterlockedCompareExchange64(&m_Data, Value, Compare);
}

AtomicInt64::DataType AtomicInt64::Add(DataType Value)
{
  return Interlocked::InterlockedAdd64(&m_Data, Value);
}

AtomicInt64::operator Int64() const
{
  return m_Data;
}

bool AtomicInt64::operator!() const
{
  return m_Data == 0 ? true : false;
}

bool AtomicInt64::operator!=(DataType Value) const
{
  return m_Data != Value;
}

AtomicInt64& AtomicInt64::operator=(DataType Value)
{
  m_Data = Value;
  return *this;
}

bool AtomicInt64::operator==(DataType Value) const
{
  return m_Data == Value;
}

AtomicInt64& AtomicInt64::operator++()
{
  Increment();
  return *this;
}

AtomicInt64& AtomicInt64::operator--()
{
  Decrement();
  return *this;
}

AtomicInt64 AtomicInt64::operator--(Int32)
{
  AtomicInt64 result(*this);
  Decrement();
  return result;
}

AtomicInt64 AtomicInt64::operator++(Int32)
{
  AtomicInt64 result(*this);
  Increment();
  return result;
}

}  // namespace RadonFramework::Core::Types