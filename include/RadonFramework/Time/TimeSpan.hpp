#ifndef RF_TIME_TIMESPAN_HPP
#define RF_TIME_TIMESPAN_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Time {

typedef RFTYPE::UInt64 TimeValue;

struct TimeSpan
{
    static TimeValue TicksPerDay;
    static TimeValue TicksPerHour;
    static TimeValue TicksPerMinute;
    static TimeValue TicksPerSecond;
    static TimeValue TicksPerMillisecond;
    static TimeValue TicksPerMicrosecond;

    static TimeSpan CreateByTicks(TimeValue Value);
    static TimeSpan CreateByTime(RFTYPE::UInt32 Hours, RFTYPE::UInt32 Minutes,
                                 RFTYPE::UInt32 Seconds);
    static TimeSpan CreateByTime(RFTYPE::UInt32 Days, RFTYPE::UInt32 Hours,
        RFTYPE::UInt32 Minutes, RFTYPE::UInt32 Seconds, RFTYPE::UInt32 Milliseconds = 0,
        RFTYPE::UInt32 Microseconds = 0);

    RFTYPE::UInt32 Days()const;
    RFTYPE::UInt32 Hours()const;
    RFTYPE::UInt32 Minutes()const;
    RFTYPE::UInt32 Seconds()const;
    RFTYPE::UInt32 Milliseconds()const;
    RFTYPE::UInt32 Microseconds()const;

    TimeValue Ticks()const;

    RFTYPE::Float64 TotalDays()const;
    RFTYPE::Float64 TotalHours()const;
    RFTYPE::Float64 TotalMinutes()const;
    RFTYPE::Float64 TotalSeconds()const;
    RFTYPE::Float64 TotalMilliseconds()const;
    RFTYPE::Float64 TotalMicroseconds()const;
    RFTYPE::String ToString()const;

    TimeSpan Add(const TimeSpan& TS)const;
    TimeSpan Sub(const TimeSpan& TS)const;
    TimeSpan& operator +=(const TimeSpan& TS);
    TimeSpan& operator -=(const TimeSpan& TS);
    TimeSpan operator +(const TimeSpan& TS)const;
    TimeSpan operator -(const TimeSpan& TS)const;
    bool operator>(const TimeSpan& TS)const;
    bool operator<(const TimeSpan& TS)const;
    bool operator>=(const TimeSpan& TS)const;
    bool operator<=(const TimeSpan& TS)const;
    bool operator!=(const TimeSpan& TS)const;
    bool operator==(const TimeSpan& TS)const;
protected:
    TimeValue m_TimeValue;
};

} }

namespace RadonFramework { namespace System { namespace IO {
    // forward decleration
    class Console;
} } }

RadonFramework::System::IO::Console& operator<<(RadonFramework::System::IO::Console& stream,
                                                const RadonFramework::Time::TimeSpan& Other);

#endif // RF_TIME_TIMESPAN_HPP
