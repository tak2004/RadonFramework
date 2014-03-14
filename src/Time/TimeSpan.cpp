#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Time/TimeSpan.hpp"
#include "RadonFramework/System/IO/Console.hpp"

using namespace RadonFramework::Time;
using namespace RadonFramework::Core::Types;

TimeValue TimeSpan::TicksPerDay=864000000000LL;
TimeValue TimeSpan::TicksPerHour=36000000000LL;
TimeValue TimeSpan::TicksPerMinute=600000000;
TimeValue TimeSpan::TicksPerSecond=10000000;
TimeValue TimeSpan::TicksPerMillisecond=10000;
TimeValue TimeSpan::TicksPerMicrosecond=10;

TimeSpan::TimeSpan()
{
  m_TimeValue=0;
}

TimeSpan::TimeSpan(TimeValue Value)
{
  m_TimeValue=Value;
}

TimeSpan::TimeSpan(UInt32 Hours, UInt32 Minutes, UInt32 Seconds)
{
  m_TimeValue=Hours*TicksPerHour+Minutes*TicksPerMinute+Seconds*TicksPerSecond;
}

TimeSpan::TimeSpan(UInt32 Days, UInt32 Hours, UInt32 Minutes, UInt32 Seconds)
{
  m_TimeValue=Days*TicksPerDay+Hours*TicksPerHour+Minutes*TicksPerMinute+Seconds*TicksPerSecond;
}

TimeSpan::TimeSpan(UInt32 Days, UInt32 Hours, UInt32 Minutes, UInt32 Seconds, UInt32 Milliseconds)
{
  m_TimeValue=Days*TicksPerDay+Hours*TicksPerHour+Minutes*TicksPerMinute+
              Seconds*TicksPerSecond+Milliseconds*TicksPerMillisecond;
}

TimeSpan::TimeSpan(UInt32 Days, UInt32 Hours, UInt32 Minutes, UInt32 Seconds, UInt32 Milliseconds,
                   UInt32 Microseconds)
{
  m_TimeValue=Days*TicksPerDay+Hours*TicksPerHour+Minutes*TicksPerMinute+
              Seconds*TicksPerSecond+Milliseconds*TicksPerMillisecond+
              Microseconds*TicksPerMicrosecond;
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

double TimeSpan::TotalDays()const
{
  return (double)m_TimeValue/(double)TicksPerDay;
}

double TimeSpan::TotalHours()const
{
  return (double)m_TimeValue/(double)TicksPerHour;
}

double TimeSpan::TotalMinutes()const
{
  return (double)m_TimeValue/(double)TicksPerMinute;
}

double TimeSpan::TotalSeconds()const
{
  return (double)m_TimeValue/(double)TicksPerSecond;
}

double TimeSpan::TotalMilliseconds()const
{
  return (double)m_TimeValue/(double)TicksPerMillisecond;
}

double TimeSpan::TotalMicroseconds()const
{
  return (double)m_TimeValue/(double)TicksPerMicrosecond;
}
// TODO (Thomas#1#): implement a more solid way
TimeSpan TimeSpan::Add(const TimeSpan& TS)const
{
  TimeSpan ts(m_TimeValue+TS.Ticks());
  return ts;
}

TimeSpan TimeSpan::Sub(const TimeSpan& TS)const
{
  TimeSpan ts(m_TimeValue-TS.Ticks());
  return ts;
}

TimeSpan& TimeSpan::operator +=(const TimeSpan& TS)
{
  m_TimeValue+=TS.Ticks();
  return *this;
}

TimeSpan& TimeSpan::operator -=(const TimeSpan& TS)
{
  m_TimeValue-=TS.Ticks();
  return *this;
}

TimeSpan TimeSpan::operator +(const TimeSpan& TS)const
{
  TimeSpan ts(m_TimeValue+TS.Ticks());
  return ts;
}

TimeSpan TimeSpan::operator -(const TimeSpan& TS)const
{
  TimeSpan ts(m_TimeValue-TS.Ticks());
  return ts;
}

bool TimeSpan::operator >(const TimeSpan& TS)const
{
    return m_TimeValue>TS.m_TimeValue;
}

bool TimeSpan::operator <(const TimeSpan& TS)const
{
    return m_TimeValue<TS.m_TimeValue;
}

bool TimeSpan::operator >=(const TimeSpan& TS)const
{
    return m_TimeValue>=TS.m_TimeValue;
}

bool TimeSpan::operator <=(const TimeSpan& TS)const
{
    return m_TimeValue<=TS.m_TimeValue;
}

bool TimeSpan::operator !=(const TimeSpan& TS)const
{
    return m_TimeValue!=TS.m_TimeValue;
}

bool TimeSpan::operator ==(const TimeSpan& TS)const
{
    return m_TimeValue==TS.m_TimeValue;
}

RadonFramework::System::IO::Console& operator<<(RadonFramework::System::IO::Console& stream,
                                                const RadonFramework::Time::TimeSpan& Other)
{
    stream<<Other.ToString().c_str();
    return stream;
}

RadonFramework::Core::Types::String RadonFramework::Time::TimeSpan::ToString() const
{
    String str;
    str<<Days()<<"days:"<<Hours()<<"hour:"<<Minutes()<<"min:"<<Seconds()<<
        "sec,"<<Milliseconds()<<"msec:"<<Microseconds()<<"microsec";
    return str;
}
