#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Time/TimeSpan.hpp"
#include "RadonFramework/System/IO/Console.hpp"
#include "RadonFramework/Core/Types/Utils/StringOperators.hpp"

using namespace RadonFramework::Time;
using namespace RadonFramework::Core::Types;

TimeValue TimeSpan::TicksPerDay=864000000000LL;
TimeValue TimeSpan::TicksPerHour=36000000000LL;
TimeValue TimeSpan::TicksPerMinute=600000000;
TimeValue TimeSpan::TicksPerSecond=10000000;
TimeValue TimeSpan::TicksPerMillisecond=10000;
TimeValue TimeSpan::TicksPerMicrosecond=10;

TimeSpan TimeSpan::Zero = TimeSpan::CreateByTicks(0);
TimeSpan TimeSpan::Max = TimeSpan::CreateByTicks(RF_Type::UInt64Max);

TimeSpan TimeSpan::CreateByTicks(TimeValue Value)
{
    TimeSpan result;
    result.m_TimeValue = Value;
    return result;
}

TimeSpan TimeSpan::CreateByTime(UInt32 Hours, UInt32 Minutes, UInt32 Seconds)
{
    TimeSpan result;
    result.m_TimeValue = Hours * TicksPerHour + Minutes * TicksPerMinute + Seconds * TicksPerSecond;
    return result;
}

TimeSpan TimeSpan::CreateByTime(UInt32 Days, UInt32 Hours, UInt32 Minutes,
    UInt32 Seconds, UInt32 Milliseconds, UInt32 Microseconds)
{
    TimeSpan result;
    result.m_TimeValue = Days * TicksPerDay + Hours * TicksPerHour + Minutes * TicksPerMinute +
        Seconds * TicksPerSecond + Milliseconds * TicksPerMillisecond + Microseconds * TicksPerMicrosecond;
    return result;
}

UInt32 TimeSpan::Days()const
{
    return UInt32(m_TimeValue/TimeSpan::TicksPerDay);
}

UInt32 TimeSpan::Hours()const
{
    return m_TimeValue/TimeSpan::TicksPerHour%24;
}

UInt32 TimeSpan::Minutes()const
{
    return m_TimeValue/TimeSpan::TicksPerMinute%60;
}

UInt32 TimeSpan::Seconds()const
{
    return m_TimeValue/TimeSpan::TicksPerSecond%60;
}

UInt32 TimeSpan::Milliseconds()const
{
    return m_TimeValue/TimeSpan::TicksPerMillisecond%1000;
}

UInt32 TimeSpan::Microseconds()const
{
    return m_TimeValue/TimeSpan::TicksPerMicrosecond%1000;
}

TimeValue TimeSpan::Ticks()const
{
    return m_TimeValue;
}

Float64 TimeSpan::TotalDays()const
{
    return static_cast<Float64>(m_TimeValue) / static_cast<Float64>(TicksPerDay);
}

Float64 TimeSpan::TotalHours()const
{
    return static_cast<Float64>(m_TimeValue) / static_cast<Float64>(TicksPerHour);
}

Float64 TimeSpan::TotalMinutes()const
{
    return static_cast<Float64>(m_TimeValue) / static_cast<Float64>(TicksPerMinute);
}

Float64 TimeSpan::TotalSeconds()const
{
    return static_cast<Float64>(m_TimeValue) / static_cast<Float64>(TicksPerSecond);
}

Float64 TimeSpan::TotalMilliseconds()const
{
    return static_cast<Float64>(m_TimeValue) / static_cast<Float64>(TicksPerMillisecond);
}

Float64 TimeSpan::TotalMicroseconds()const
{
    return static_cast<Float64>(m_TimeValue) / static_cast<Float64>(TicksPerMicrosecond);
}

TimeSpan TimeSpan::Add(const TimeSpan& TS)const
{
    TimeSpan result;
    result.m_TimeValue = m_TimeValue + TS.Ticks();
    return result;
}

TimeSpan TimeSpan::Sub(const TimeSpan& TS)const
{
    TimeSpan result;
    result.m_TimeValue = m_TimeValue - TS.Ticks();
    return result;
}

TimeSpan& TimeSpan::operator +=(const TimeSpan& TS)
{
    m_TimeValue += TS.Ticks();
    return *this;
}

TimeSpan& TimeSpan::operator -=(const TimeSpan& TS)
{
    m_TimeValue -= TS.Ticks();
    return *this;
}

TimeSpan TimeSpan::operator +(const TimeSpan& TS)const
{
    TimeSpan result;
    result.m_TimeValue = m_TimeValue + TS.Ticks();
    return result;
}

TimeSpan TimeSpan::operator -(const TimeSpan& TS)const
{
    TimeSpan result;
    result.m_TimeValue = m_TimeValue - TS.Ticks();
    return result;
}

bool TimeSpan::operator >(const TimeSpan& TS)const
{
    return m_TimeValue > TS.m_TimeValue;
}

bool TimeSpan::operator <(const TimeSpan& TS)const
{
    return m_TimeValue < TS.m_TimeValue;
}

bool TimeSpan::operator >=(const TimeSpan& TS)const
{
    return m_TimeValue >= TS.m_TimeValue;
}

bool TimeSpan::operator <=(const TimeSpan& TS)const
{
    return m_TimeValue <= TS.m_TimeValue;
}

bool TimeSpan::operator !=(const TimeSpan& TS)const
{
    return m_TimeValue != TS.m_TimeValue;
}

bool TimeSpan::operator ==(const TimeSpan& TS)const
{
    return m_TimeValue == TS.m_TimeValue;
}

RadonFramework::System::IO::Console& operator<<(RadonFramework::System::IO::Console& stream,
                                                const RadonFramework::Time::TimeSpan& Other)
{
    stream.WriteLine(Other.ToString());
    return stream;
}

RadonFramework::Core::Types::String RadonFramework::Time::TimeSpan::ToString() const
{
    String result;
    result << Days() << "days:" << Hours() << "hour:" << Minutes() << "min:" << 
        Seconds() << "sec," << Milliseconds() << "msec:" << Microseconds() << "microsec";
    return result;
}
