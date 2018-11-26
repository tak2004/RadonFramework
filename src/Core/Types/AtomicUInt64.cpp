#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Core/Types/AtomicUInt64.hpp>
#include <RadonFramework/System/Threading/Interlocked.hpp>

using namespace RadonFramework::System::Threading;

namespace RadonFramework::Core::Types {

AtomicUInt64::AtomicUInt64(DataType Value) :m_Data(Value)
{
}

AtomicUInt64::AtomicUInt64(const AtomicUInt64& Other)
:m_Data(Other.m_Data)
{
}

AtomicUInt64::DataType AtomicUInt64::Increment()
{
    return Interlocked::InterlockedInc64((Int64*)&m_Data);
}

AtomicUInt64::DataType AtomicUInt64::Decrement()
{
    return Interlocked::InterlockedDec64((Int64*)&m_Data);
}

AtomicUInt64::DataType AtomicUInt64::FetchAndAdd(DataType Addend)
{
    return Interlocked::InterlockedAdd64((Int64*)&m_Data,Addend);
}

AtomicUInt64::DataType AtomicUInt64::FetchAndExchange(DataType Value)
{
    return Interlocked::InterlockedExchange64((Int64*)&m_Data,Value);
}

AtomicUInt64::DataType
AtomicUInt64::CompareAndExchange(DataType Compare, DataType Value)
{
    return Interlocked::InterlockedCompareExchange64((Int64*)&m_Data, Value, Compare);
}

AtomicUInt64::DataType AtomicUInt64::Add(DataType Value)
{
    return Interlocked::InterlockedAdd64((Int64*)&m_Data, Value);
}

AtomicUInt64::operator UInt64()const
{
    return m_Data;
}

bool AtomicUInt64::operator !()const
{
    return m_Data==0?true:false;
}

bool AtomicUInt64::operator!=(DataType Value) const
{
    return m_Data!=Value;
}

AtomicUInt64& AtomicUInt64::operator=(DataType Value)
{
    m_Data=Value;
    return *this;
}

AtomicUInt64& AtomicUInt64::operator =(const AtomicUInt64& Other)
{
    m_Data=Other.m_Data;
    return *this;
}

bool AtomicUInt64::operator==(DataType Value) const
{
    return m_Data==Value;
}

AtomicUInt64& AtomicUInt64::operator++()
{
    Increment();
    return *this;
}

AtomicUInt64& AtomicUInt64::operator--()
{
    Decrement();
    return *this;
}

AtomicUInt64 AtomicUInt64::operator--(Int32)
{
    AtomicUInt64 result(*this);
    Decrement();
    return result;
}

AtomicUInt64 AtomicUInt64::operator++(Int32)
{
    AtomicUInt64 result(*this);
    Increment();
    return result;
}

}