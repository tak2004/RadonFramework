#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Core/Types/AtomicInt32.hpp>
#include <RadonFramework/System/Threading/Interlocked.hpp>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::Threading;

AtomicInt32::AtomicInt32(Int32 Value)
:m_Data(Value)
{
}

AtomicInt32::AtomicInt32(const AtomicInt32& Other)
:m_Data(Other.m_Data)
{
}

Int32 AtomicInt32::Increment()
{
    return Interlocked::InterlockedInc32(&m_Data);
}

Int32 AtomicInt32::Decrement()
{
    return Interlocked::InterlockedDec32(&m_Data);
}

Int32 AtomicInt32::FetchAndAdd(Int32 Addend)
{
    return Interlocked::InterlockedAdd32(&m_Data,Addend);
}

Int32 AtomicInt32::FetchAndExchange(Int32 Value)
{
    return Interlocked::InterlockedExchange32(&m_Data,Value);
}

Int32 AtomicInt32::CompareAndExchange(Int32 Compare, Int32 Value)
{
    return Interlocked::InterlockedCompareExchange32(&m_Data,Compare,Value);
}

Int32 AtomicInt32::Add(Int32 Value)
{
    return Interlocked::InterlockedAdd32(&m_Data, Value);
}

AtomicInt32::operator Int32()const
{
    return m_Data;
}

bool AtomicInt32::operator !()const
{
    return m_Data==0?true:false;
}

bool AtomicInt32::operator !=(Int32 Value)const
{
    return m_Data!=Value;
}

AtomicInt32& AtomicInt32::operator =(Int32 Value)
{
    m_Data=Value;
    return *this;
}

AtomicInt32& AtomicInt32::operator =(const AtomicInt32& Other)
{
    m_Data=Other.m_Data;
    return *this;
}

bool AtomicInt32::operator ==(Int32 Value)const
{
    return m_Data==Value;
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