#ifndef RF_TIME_DATETIME_HPP
#define RF_TIME_DATETIME_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Time/TimeSpan.hpp>

namespace RadonFramework
{
  namespace Time
  {
    namespace DayOfWeek{
      enum Type{
        Monday, Tuesday, Wednesday, Thursday, Saturday, Sunday
      };
    }

    namespace MonthOfYear{
      enum Type{
        January, Februrary, March, April, May, June, July, August, September, October, November, December
      };
    }

    namespace TickDayConverterTyp{
      enum Type{
        Day, DayYear, Month, Year
      };
    }

    namespace DateTimeKind{
      enum Type{
        Undefined,
        Local,
        UTC
      };
    }

    class DateTime
    {
      public:
        DateTime();
        DateTime(TimeValue Value);
        DateTime(TimeValue Value, DateTimeKind::Type Kind);
        DateTime(RFTYPE::Int32 Year, RFTYPE::Int32 Month, RFTYPE::Int32 Day);
        DateTime(RFTYPE::Int32 Year, RFTYPE::Int32 Month, RFTYPE::Int32 Day,
                 RFTYPE::Int32 Hour, RFTYPE::Int32 Minute, RFTYPE::Int32 Second);
        DateTime(RFTYPE::Int32 Year, RFTYPE::Int32 Month, RFTYPE::Int32 Day,
                 RFTYPE::Int32 Hour, RFTYPE::Int32 Minute, RFTYPE::Int32 Second,
                 RFTYPE::Int32 Millisecond, RFTYPE::Int32 Microsecond);
        RFTYPE::Int32 Year()const;
        MonthOfYear::Type GetMonthOfYear()const;
        RFTYPE::Int32 Month()const;
        DayOfWeek::Type GetDayOfWeek()const;
        RFTYPE::Int32 DayOfYear()const;
        RFTYPE::Int32 Day()const;
        RFTYPE::Int32 Hour()const;
        RFTYPE::Int32 Minute()const;
        RFTYPE::Int32 Second()const;
        RFTYPE::Int32 Millisecond()const;
        RFTYPE::Int32 Microsecond()const;

        TimeSpan TimeOfDay()const;
        TimeSpan AsTimeSpan()const;
        TimeValue Ticks()const;

        RadonFramework::Core::Types::String ToString()const;

        static DateTime Now();
        static DateTime Today();
        static DateTime UtcNow();
        static RFTYPE::Int32 DaysInMonth(RFTYPE::Int32 Year, RFTYPE::Int32 Month);
        static bool IsLeapYear(RFTYPE::Int32 Year);
        static DateTime MinValue;
        static DateTime MaxValue;
        static bool LessThan(DateTime t1, DateTime t2);
        static bool GreaterThan(DateTime t1, DateTime t2);
      protected:
        TimeSpan m_Ticks;
        DateTimeKind::Type m_Kind;
        
        RFTYPE::Int32 FromTicks(TickDayConverterTyp::Type To)const;
        void Init(RFTYPE::Int32 Year, RFTYPE::Int32 Month, RFTYPE::Int32 Day, RFTYPE::Int32 Hour, RFTYPE::Int32 Minute, RFTYPE::Int32 Second,
                  RFTYPE::Int32 Millisecond, RFTYPE::Int32 Microsecond, DateTimeKind::Type Kind);        
        
        static RFTYPE::Int32 AbsoluteDays(RFTYPE::Int32 Year, RFTYPE::Int32 Month, RFTYPE::Int32 Day);
        static bool IsInvalid( const TimeValue& );
    };
  }
}

#endif // RF_TIME_DATETIME_HPP
