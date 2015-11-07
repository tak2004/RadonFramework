#ifndef RF_TIME_DATETIME_HPP
#define RF_TIME_DATETIME_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Time/TimeSpan.hpp>

namespace RadonFramework { namespace Time {

namespace DayOfWeek 
{
    enum Type
    {
        Monday, Tuesday, Wednesday, Thursday, Saturday, Sunday
    };
}

namespace MonthOfYear
{
    enum Type
    {
        January, Februrary, March, April, May, June, July, August, September,
        October, November, December
    };
}

namespace TickDayConverterTyp
{
    enum Type
    {
        Day, DayYear, Month, Year
    };
}

namespace DateTimeKind
{
    enum Type
    {
        Undefined, Local, UTC
    };
}

struct DateTime
{
    static DateTime CreateByTicks(TimeValue Value, 
        DateTimeKind::Type Kind = DateTimeKind::Undefined);

    static DateTime CreateByTime(RF_Type::UInt32 Year, RF_Type::UInt32 Month, 
        RF_Type::UInt32 Day, DateTimeKind::Type Kind = DateTimeKind::Undefined);

    static DateTime CreateByTime(RF_Type::UInt32 Year, RF_Type::UInt32 Month, 
        RF_Type::UInt32 Day, RF_Type::UInt32 Hour, RF_Type::UInt32 Minute, 
        RF_Type::UInt32 Second, DateTimeKind::Type Kind = DateTimeKind::Undefined);

    static DateTime CreateByTime(const TimeSpan& Value,
        DateTimeKind::Type Kind = DateTimeKind::Undefined);

    static DateTime Now();
    static DateTime Today();
    static DateTime UtcNow();

    RF_Type::UInt32 Year()const;
    MonthOfYear::Type GetMonthOfYear()const;
    RF_Type::UInt32 Month()const;
    DayOfWeek::Type GetDayOfWeek()const;
    RF_Type::UInt32 DayOfYear()const;
    RF_Type::UInt32 Day()const;
    RF_Type::UInt32 Hour()const;
    RF_Type::UInt32 Minute()const;
    RF_Type::UInt32 Second()const;
    RF_Type::UInt32 Millisecond()const;
    RF_Type::UInt32 Microsecond()const;

    TimeSpan TimeOfDay()const;
    TimeSpan AsTimeSpan()const;
    TimeValue Ticks()const;

    RF_Type::String ToString()const;
    void Format(const RF_Type::String& Format, RF_Type::String& Result)const;

    static RF_Type::UInt32 DaysInMonth(RF_Type::UInt32 Year, RF_Type::UInt32 Month);
    static bool IsLeapYear(RF_Type::UInt32 Year);
    static DateTime MinValue;
    static DateTime MaxValue;
    static bool LessThan(DateTime t1, DateTime t2);
    static bool GreaterThan(DateTime t1, DateTime t2);
protected:
    TimeSpan m_Ticks;
    DateTimeKind::Type m_Kind;
        
    RF_Type::UInt32 FromTicks(TickDayConverterTyp::Type To)const;
        
    static RF_Type::UInt32 AbsoluteDays(RF_Type::UInt32 Year, RF_Type::UInt32 Month, RF_Type::UInt32 Day);
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_TIME
#define RF_SHORTHAND_NAMESPACE_TIME
namespace RF_Time = RadonFramework::Time;
#endif

#endif // RF_TIME_DATETIME_HPP
