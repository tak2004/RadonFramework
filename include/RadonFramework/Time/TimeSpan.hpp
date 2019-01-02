#ifndef RF_TIME_TIMESPAN_HPP
#define RF_TIME_TIMESPAN_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/UInt64.hpp>
#include <RadonFramework/Core/Types/Float64.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework::Time {

using TimeValue = RF_Type::UInt64;

struct TimeSpan
{
    static TimeValue TicksPerDay;
    static TimeValue TicksPerHour;
    static TimeValue TicksPerMinute;
    static TimeValue TicksPerSecond;
    static TimeValue TicksPerMillisecond;
    static TimeValue TicksPerMicrosecond;
    static TimeSpan Zero;
    static TimeSpan Max;

    static TimeSpan CreateByTicks(TimeValue Value);
    static TimeSpan CreateByTime(RF_Type::UInt32 Hours, RF_Type::UInt32 Minutes,
                                 RF_Type::UInt32 Seconds);
    static TimeSpan CreateByTime(RF_Type::UInt32 Days, RF_Type::UInt32 Hours,
        RF_Type::UInt32 Minutes, RF_Type::UInt32 Seconds, RF_Type::UInt32 Milliseconds = 0,
        RF_Type::UInt32 Microseconds = 0);

    RF_Type::UInt32 Days()const;
    RF_Type::UInt32 Hours()const;
    RF_Type::UInt32 Minutes()const;
    RF_Type::UInt32 Seconds()const;
    RF_Type::UInt32 Milliseconds()const;
    RF_Type::UInt32 Microseconds()const;

    TimeValue Ticks()const;

    RF_Type::Float64 TotalDays()const;
    RF_Type::Float64 TotalHours()const;
    RF_Type::Float64 TotalMinutes()const;
    RF_Type::Float64 TotalSeconds()const;
    RF_Type::Float64 TotalMilliseconds()const;
    RF_Type::Float64 TotalMicroseconds()const;
    RF_Type::String ToString()const;

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

}  // namespace RadonFramework::Time

#ifndef RF_SHORTHAND_NAMESPACE_TIME
#define RF_SHORTHAND_NAMESPACE_TIME
namespace RF_Time = RadonFramework::Time;
#endif

//namespace RadonFramework::System::IO {
//
//class Console;
//
//}
//
//RadonFramework::System::IO::Console& operator<<(RadonFramework::System::IO::Console& stream,
//                                                const RF_Time::TimeSpan& Other);

#endif // RF_TIME_TIMESPAN_HPP
