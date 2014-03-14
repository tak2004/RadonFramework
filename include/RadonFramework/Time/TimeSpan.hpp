#ifndef RF_TIME_TIMESPAN_HPP
#define RF_TIME_TIMESPAN_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/UInt64.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework
{
  namespace Time
  {
    typedef Core::Types::UInt64 TimeValue;

    class TimeSpan
    {
      protected:
        TimeValue m_TimeValue;
      public:
        static TimeValue TicksPerDay;
        static TimeValue TicksPerHour;
        static TimeValue TicksPerMinute;
        static TimeValue TicksPerSecond;
        static TimeValue TicksPerMillisecond;
        static TimeValue TicksPerMicrosecond;

        TimeSpan();
        TimeSpan(TimeValue Value);
        TimeSpan(Core::Types::UInt32 Hours, Core::Types::UInt32 Minutes, Core::Types::UInt32 Seconds);
        TimeSpan(Core::Types::UInt32 Days, Core::Types::UInt32 Hours, Core::Types::UInt32 Minutes, Core::Types::UInt32 Seconds);
        TimeSpan(Core::Types::UInt32 Days, Core::Types::UInt32 Hours, Core::Types::UInt32 Minutes, Core::Types::UInt32 Seconds, Core::Types::UInt32 Milliseconds);
        TimeSpan(Core::Types::UInt32 Days, Core::Types::UInt32 Hours, Core::Types::UInt32 Minutes, Core::Types::UInt32 Seconds, Core::Types::UInt32 Milliseconds,
                 Core::Types::UInt32 Microseconds);

        Core::Types::UInt32 Days()const;
        Core::Types::UInt32 Hours()const;
        Core::Types::UInt32 Minutes()const;
        Core::Types::UInt32 Seconds()const;
        Core::Types::UInt32 Milliseconds()const;
        Core::Types::UInt32 Microseconds()const;
        TimeValue Ticks()const;
        double TotalDays()const;
        double TotalHours()const;
        double TotalMinutes()const;
        double TotalSeconds()const;
        double TotalMilliseconds()const;
        double TotalMicroseconds()const;
        RadonFramework::Core::Types::String ToString()const;

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
    };
  }
}

namespace RadonFramework
{ 
    namespace System
    {
        namespace IO
        { 
            class Console;
        }
    }
}

RadonFramework::System::IO::Console& operator<<(RadonFramework::System::IO::Console& stream,
                                                const RadonFramework::Time::TimeSpan& Other);

#endif // RF_TIME_TIMESPAN_HPP
