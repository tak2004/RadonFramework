#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Core/Types/AtomicInt64.hpp>
#include <RadonFramework/System/Threading/Interlocked.hpp>

using namespace RadonFramework::System::Threading;

namespace RadonFramework { namespace Core { namespace Types {

AtomicInt64::AtomicInt64(Int64 Value)
:m_Data(Value)
{
}

AtomicInt64::AtomicInt64(const AtomicInt64& Other)
:m_Data(Other.m_Data)
{
}

Int64 AtomicInt64::Increment()
{
    return Interlocked::InterlockedInc64(&m_Data);
}

Int64 AtomicInt64::Decrement()
{
    return Interlocked::InterlockedDec64(&m_Data);
}

Int64 AtomicInt64::FetchAndAdd(Int64 Addend)
{
    return Interlocked::InterlockedAdd64(&m_Data,Addend);
}

Int64 AtomicInt64::FetchAndExchange(Int64 Value)
{
    return Interlocked::InterlockedExchange64(&m_Data,Value);
}

Int64 AtomicInt64::CompareAndExchange(Int64 Compare, Int64 Value)
{
    return Interlocked::InterlockedCompareExchange64(&m_Data,Compare,Value);
}

Int64 AtomicInt64::Add(Int64 Value)
{
    return Interlocked::InterlockedAdd64(&m_Data, Value);
}

AtomicInt64::operator Int64()const
{
    return m_Data;
}

bool AtomicInt64::operator !()const
{
    return m_Data==0?true:false;
}

bool AtomicInt64::operator !=(Int64 Value)const
{
    return m_Data!=Value;
}

AtomicInt64& AtomicInt64::operator =(Int64 Value)
{
    m_Data=Value;
    return *this;
}

AtomicInt64& AtomicInt64::operator =(const AtomicInt64& Other)
{
    m_Data=Other.m_Data;
    return *this;
}

bool AtomicInt64::operator ==(Int64 Value)const
{
    return m_Data==Value;
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

AtomicInt64 AtomicInt64::operator--(Int64)
{
    AtomicInt64 result(*this);
    Decrement();
    return result;
}

AtomicInt64 AtomicInt64::operator++(Int64)
{
    AtomicInt64 result(*this);
    Increment();
    return result;
}

} } }