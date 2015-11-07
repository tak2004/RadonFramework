#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Time/DateTime.hpp"
#include "RadonFramework/System/Time.hpp"
#include "RadonFramework/Core/Types/String.hpp"
#include "RadonFramework/IO/Log.hpp"
#include "RadonFramework/Diagnostics/Debugging/Assert.hpp"

using namespace RadonFramework::Time;
using namespace RadonFramework::Core::Types;

const UInt32 daysmonth[13]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const UInt32 daysmonthleap[13]={ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

DateTime DateTime::MinValue = DateTime::CreateByTicks(0);
DateTime DateTime::MaxValue = DateTime::CreateByTicks(3155378975999999999LL);

DateTime DateTime::CreateByTicks(TimeValue Value, DateTimeKind::Type Kind)
{
    DateTime result;
    result.m_Ticks = TimeSpan::CreateByTicks(Value);
    result.m_Kind = Kind;
    return result;
}

DateTime DateTime::CreateByTime(UInt32 Year, UInt32 Month, UInt32 Day, 
    DateTimeKind::Type Kind)
{
    DateTime result;
    result.m_Kind = Kind;

    if(Year >= 0 && Year < 10000 && Month >= 0 && Month < 13 && Day >= 0 &&
        Day <= DaysInMonth(Year, Month))
    {
        result.m_Ticks = TimeSpan::CreateByTime(AbsoluteDays(Year, Month, Day),
            0, 0, 0, 0, 0);
    }
    return result;
}

DateTime DateTime::CreateByTime(UInt32 Year, UInt32 Month, UInt32 Day, UInt32 Hour,
    UInt32 Minute, UInt32 Second, DateTimeKind::Type Kind)
{
    DateTime result;
    result.m_Kind = Kind;

    if(Hour >= 0 && Hour < 24 && Minute >= 0 && Minute < 60 && Second >= 0 && Second < 60)
    {
        //check if specified parameter represent time instead of date and time
        if(Day == 0 && Month == 0 && Year == 0)
        {
            result.m_Ticks = TimeSpan::CreateByTime(0, Hour, Minute, Second, 0, 0);
        }
        else
        {
            if(Year >= 0 && Year < 10000 && Month >= 0 && Month < 13 && Day >= 0 &&
                Day <= DaysInMonth(Year, Month))
            {//is datetime
                result.m_Ticks = TimeSpan::CreateByTime(AbsoluteDays(Year, Month, Day),
                    Hour, Minute, Second, 0, 0);
            }
        }
    }
    return result;
}

DateTime DateTime::CreateByTime(const TimeSpan& Value, DateTimeKind::Type Kind)
{
    DateTime result;
    result.m_Kind = Kind;
    result.m_Ticks = Value;
    return result;
}

UInt32 DateTime::FromTicks(TickDayConverterTyp::Type To)const
{
    UInt32 num400, num100, num4, numyears;
    UInt32 M = 1;
    UInt32 totaldays = m_Ticks.Days();
    UInt32 dp400 = 146097;
    UInt32 dp100 = 36524;
    UInt32 dp4 = 1461;

    num400 = totaldays / dp400;
    totaldays -= num400 * dp400;

    num100 = totaldays / dp100;
    if (num100 == 4)//leap
    {
        num100 = 3;
    }
    totaldays -= num100 * dp100;

    num4 = totaldays / dp4;
    totaldays -= num4 * dp4;

    numyears = totaldays / 365;

    if (numyears == 4)//leap
    {
        numyears = 3;
    }

    if (To == TickDayConverterTyp::Year)
    {
        return num400 * 400 + num100 * 100 + num4 * 4 + numyears + 1;
    }

    totaldays -= numyears * 365;
    if (To == TickDayConverterTyp::DayYear)
    {
        return totaldays + 1;
    }

    if ((numyears == 3) && ((num100 == 3) || !(num4 == 24)))//31.Dec leapyear
    {
        while(totaldays >= daysmonthleap[M])
        {
            totaldays -= daysmonthleap[M++];
        }
    }
    else
    {
        while(totaldays >= daysmonth[M])
        {
            totaldays -= daysmonth[M++];
        }
    }

    if (To == TickDayConverterTyp::Month)
    {
        return M;
    }

    return totaldays+1;
}

UInt32 DateTime::Year()const
{
    return FromTicks(TickDayConverterTyp::Year);
}

MonthOfYear::Type DateTime::GetMonthOfYear()const
{
    return (MonthOfYear::Type)(Month() - 1);
}

UInt32 DateTime::Month()const
{
    return FromTicks(TickDayConverterTyp::Month);
}

DayOfWeek::Type DateTime::GetDayOfWeek()const
{
    return (DayOfWeek::Type)((m_Ticks.Days() + 1) % 7);
}

UInt32 DateTime::DayOfYear()const
{
    return FromTicks(TickDayConverterTyp::DayYear);
}

UInt32 DateTime::Day()const
{
    return FromTicks(TickDayConverterTyp::Day);
}

UInt32 DateTime::Hour()const
{
    return m_Ticks.Hours();
}

UInt32 DateTime::Minute()const
{
    return m_Ticks.Minutes();
}

UInt32 DateTime::Second()const
{
    return m_Ticks.Seconds();
}

UInt32 DateTime::Millisecond()const
{
    return m_Ticks.Milliseconds();
}

UInt32 DateTime::Microsecond()const
{
    return m_Ticks.Microseconds();
}

TimeSpan DateTime::TimeOfDay()const
{
    TimeSpan result = TimeSpan::CreateByTicks(m_Ticks.Ticks() % TimeSpan::TicksPerDay);
    return result;
}

TimeSpan DateTime::AsTimeSpan()const
{
    TimeSpan ts(m_Ticks);
    return ts;
}

TimeValue DateTime::Ticks()const
{
    return m_Ticks.Ticks();
}

DateTime DateTime::Today()
{
    DateTime dt = Now();
    DateTime result = DateTime::CreateByTime(dt.Year(), dt.Month(), dt.Day());
    return result;
}

DateTime DateTime::Now()
{
    TimeValue now = RF_SysTime::GetNow();
    TimeValue delta = RF_SysTime::GetMinutesWestOfGMT();

    DateTime dt = DateTime::CreateByTicks(now, DateTimeKind::Local);
    dt.m_Ticks += TimeSpan::CreateByTicks(delta);

    return dt;
}

DateTime DateTime::UtcNow()
{
    DateTime dt = DateTime::CreateByTicks(RF_SysTime::GetNow(), DateTimeKind::UTC);
    return dt;
}

UInt32 DateTime::DaysInMonth(UInt32 Year, UInt32 Month)
{
    Assert(Month > 0 && Month < 13 && Year > 0 && Year < 10000, "Index out of bound.");

    UInt32 days = IsLeapYear(Year) ? daysmonthleap[Month] : daysmonth[Month];
    return days;
}

UInt32 DateTime::AbsoluteDays(UInt32 Year, UInt32 Month, UInt32 Day)
{
    UInt32 temp = 0;
    if (IsLeapYear(Year))
    {
        for (UInt32 m = 1; m < Month; ++m)
        {
            temp += daysmonthleap[m];
        }
    }
    else
    {
        for (UInt32 m=1;m<Month;m++)
        {
            temp += daysmonth[m];
        }
    }
    return ((Day - 1) + temp + (365 * (Year - 1)) + ((Year - 1) / 4) - 
           ((Year - 1) / 100) + ((Year - 1) / 400));
}

bool DateTime::IsLeapYear(UInt32 Year)
{
    Assert(Year > 0 && Year < 10000, "Index out of bound.");
    return ((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0);
}

bool DateTime::LessThan(DateTime t1, DateTime t2)
{
    return t1.Ticks() < t2.Ticks();
}

bool DateTime::GreaterThan(DateTime t1, DateTime t2)
{
    return t1.Ticks()>t2.Ticks();
}

RF_Type::String DateTime::ToString() const
{
    String str;
    str << Day() << "." << Month() << "." << Year();
    str << " ";
    str << Hour() << ":" << Minute() << ":" << Second();
    return str;
}

void RadonFramework::Time::DateTime::Format(const RF_Type::String& Format, 
                                            RF_Type::String& Result) const
{
    RF_SysTime::GetStringFormattedTime(*this, Format, Result);
}
