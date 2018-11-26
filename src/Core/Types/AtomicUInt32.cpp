#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Core/Types/AtomicUInt32.hpp"
#include "RadonFramework/System/Threading/Interlocked.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::Threading;

AtomicUInt32::AtomicUInt32(DataType Value) :m_Data(Value)
{
}

AtomicUInt32::AtomicUInt32(const AtomicUInt32& Other)
:m_Data(Other.m_Data)
{
}

AtomicUInt32::DataType AtomicUInt32::Increment()
{
    return Interlocked::InterlockedInc32((Int32*)&m_Data);
}

AtomicUInt32::DataType AtomicUInt32::Decrement()
{
    return Interlocked::InterlockedDec32((Int32*)&m_Data);
}

AtomicUInt32::DataType AtomicUInt32::FetchAndAdd(DataType Addend)
{
    return Interlocked::InterlockedAdd32((Int32*)&m_Data,Addend);
}

AtomicUInt32::DataType AtomicUInt32::FetchAndExchange(DataType Value)
{
    return Interlocked::InterlockedExchange32((Int32*)&m_Data,Value);
}

AtomicUInt32::DataType
AtomicUInt32::CompareAndExchange(DataType Compare, DataType Value)
{
    return Interlocked::InterlockedCompareExchange32((Int32*)&m_Data, Value, Compare);
}

AtomicUInt32::DataType AtomicUInt32::Add(DataType Value)
{
    return Interlocked::InterlockedAdd32((Int32*)&m_Data, Value);
}

AtomicUInt32::operator UInt32()const
{
    return m_Data;
}

bool AtomicUInt32::operator !()const
{
    return m_Data == 0 ? true : false;
}

bool AtomicUInt32::operator!=(DataType Value) const
{
    return m_Data!=Value;
}

AtomicUInt32& AtomicUInt32::operator=(DataType Value)
{
    m_Data=Value;
    return *this;
}

AtomicUInt32& AtomicUInt32::operator =(const AtomicUInt32& Other)
{
    m_Data=Other.m_Data;
    return *this;
}

bool AtomicUInt32::operator==(DataType Value) const
{
    return m_Data==Value;
}

AtomicUInt32& AtomicUInt32::operator++()
{
    Increment();
    return *this;
}

AtomicUInt32 AtomicUInt32::operator++(Int32)
{
    AtomicUInt32 result(*this);
    Increment();
    return result;
}

AtomicUInt32& AtomicUInt32::operator--()
{
    Decrement();
    return *this;
}

AtomicUInt32 AtomicUInt32::operator--(Int32)
{
    AtomicUInt32 result(*this);
    Decrement();
    return result;
}