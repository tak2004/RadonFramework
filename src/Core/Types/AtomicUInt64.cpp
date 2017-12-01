#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Core/Types/AtomicUInt64.hpp>
#include <RadonFramework/System/Threading/Interlocked.hpp>

using namespace RadonFramework::System::Threading;

namespace RadonFramework::Core::Types {

AtomicUInt64::AtomicUInt64(UInt64 Value)
:m_Data(Value)
{
}

AtomicUInt64::AtomicUInt64(const AtomicUInt64& Other)
:m_Data(Other.m_Data)
{
}

UInt64 AtomicUInt64::Increment()
{
    return Interlocked::InterlockedInc64((Int64*)&m_Data);
}

UInt64 AtomicUInt64::Decrement()
{
    return Interlocked::InterlockedDec64((Int64*)&m_Data);
}

UInt64 AtomicUInt64::FetchAndAdd(UInt64 Addend)
{
    return Interlocked::InterlockedAdd64((Int64*)&m_Data,Addend);
}

UInt64 AtomicUInt64::FetchAndExchange(UInt64 Value)
{
    return Interlocked::InterlockedExchange64((Int64*)&m_Data,Value);
}

UInt64 AtomicUInt64::CompareAndExchange(UInt64 Compare, UInt64 Value)
{
    return Interlocked::InterlockedCompareExchange64((Int64*)&m_Data, Value, Compare);
}

UInt64 AtomicUInt64::Add(UInt64 Value)
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

bool AtomicUInt64::operator !=(UInt64 Value)const
{
    return m_Data!=Value;
}

AtomicUInt64& AtomicUInt64::operator =(UInt64 Value)
{
    m_Data=Value;
    return *this;
}

AtomicUInt64& AtomicUInt64::operator =(const AtomicUInt64& Other)
{
    m_Data=Other.m_Data;
    return *this;
}

bool AtomicUInt64::operator ==(UInt64 Value)const
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

AtomicUInt64 AtomicUInt64::operator--(int)
{
    AtomicUInt64 result(*this);
    Decrement();
    return result;
}

AtomicUInt64 AtomicUInt64::operator++(int)
{
    AtomicUInt64 result(*this);
    Increment();
    return result;
}

}