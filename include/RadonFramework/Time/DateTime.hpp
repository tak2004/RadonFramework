#ifndef RF_TIME_DATETIME_HPP
#define RF_TIME_DATETIME_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Time/TimeSpan.hpp>

namespace RadonFramework { namespace Time {

namespace DayOfWeek {
    enum Type{
        Monday, Tuesday, Wednesday, Thursday, Saturday, Sunday
    };
}

namespace MonthOfYear{
    enum Type{
        January, Februrary, March, April, May, June, July, August, September,
        October, November, December
    };
}

namespace TickDayConverterTyp{
    enum Type{
        Day, DayYear, Month, Year
    };
}

namespace DateTimeKind{
    enum Type{
        Undefined, Local, UTC
    };
}

struct DateTime
{
    static DateTime CreateByTicks(TimeValue Value, DateTimeKind::Type Kind = DateTimeKind::Undefined);
    static DateTime CreateByTime(RFTYPE::UInt32 Year, RFTYPE::UInt32 Month, RFTYPE::UInt32 Day,
        RFTYPE::UInt32 Hour = 0, RFTYPE::UInt32 Minute = 0, RFTYPE::UInt32 Second = 0,
        RFTYPE::UInt32 Millisecond = 0, RFTYPE::UInt32 Microsecond = 0,
        DateTimeKind::Type Kind = DateTimeKind::Undefined);
    static DateTime Now();
    static DateTime Today();
    static DateTime UtcNow();

    RFTYPE::UInt32 Year()const;
    MonthOfYear::Type GetMonthOfYear()const;
    RFTYPE::UInt32 Month()const;
    DayOfWeek::Type GetDayOfWeek()const;
    RFTYPE::UInt32 DayOfYear()const;
    RFTYPE::UInt32 Day()const;
    RFTYPE::UInt32 Hour()const;
    RFTYPE::UInt32 Minute()const;
    RFTYPE::UInt32 Second()const;
    RFTYPE::UInt32 Millisecond()const;
    RFTYPE::UInt32 Microsecond()const;

    TimeSpan TimeOfDay()const;
    TimeSpan AsTimeSpan()const;
    TimeValue Ticks()const;

    RFTYPE::String ToString()const;

    static RFTYPE::UInt32 DaysInMonth(RFTYPE::UInt32 Year, RFTYPE::UInt32 Month);
    static bool IsLeapYear(RFTYPE::UInt32 Year);
    static DateTime MinValue;
    static DateTime MaxValue;
    static bool LessThan(DateTime t1, DateTime t2);
    static bool GreaterThan(DateTime t1, DateTime t2);
protected:
    TimeSpan m_Ticks;
    DateTimeKind::Type m_Kind;
        
    RFTYPE::UInt32 FromTicks(TickDayConverterTyp::Type To)const;
        
    static RFTYPE::UInt32 AbsoluteDays(RFTYPE::UInt32 Year, RFTYPE::UInt32 Month, RFTYPE::UInt32 Day);
    static bool IsInvalid( const TimeValue& );
};

} }

#endif // RF_TIME_DATETIME_HPP
