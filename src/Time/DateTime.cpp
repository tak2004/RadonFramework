#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Time/DateTime.hpp"
#include "RadonFramework/System/Time.hpp"
#include "RadonFramework/Core/Types/String.hpp"
#include "RadonFramework/IO/Log.hpp"
#include "RadonFramework/Diagnostics/Debugging/Assert.hpp"

using namespace RadonFramework::Time;
using namespace RadonFramework::Core::Types;

DateTime::DateTime(TimeValue Value)
:m_Ticks(Value)
{
    Assert(false==IsInvalid(Value),"Invalid parameter.");
    m_Kind=DateTimeKind::Undefined;
}

DateTime::DateTime(TimeValue Value, DateTimeKind::Type Kind)
:m_Ticks(Value),m_Kind(Kind)
{
}

DateTime::DateTime(Int32 Year, Int32 Month, Int32 Day)
:m_Ticks(0)
{
  Init(Year,Month,Day,0,0,0,0,0,DateTimeKind::Undefined);
}

DateTime::DateTime(Int32 Year, Int32 Month, Int32 Day, Int32 Hour, Int32 Minute, Int32 Second)
:m_Ticks(0)
{
  Init(Year,Month,Day,Hour,Minute,Second,0,0,DateTimeKind::Undefined);
}

DateTime::DateTime(Int32 Year, Int32 Month, Int32 Day, Int32 Hour, Int32 Minute, Int32 Second,
                   Int32 Millisecond, Int32 Microsecond)
:m_Ticks(0)
{
    Init(Year, Month, Day, Hour, Minute, Second, Millisecond, Microsecond,
         DateTimeKind::Undefined);
}

void DateTime::Init(Int32 Year, Int32 Month, Int32 Day, Int32 Hour, Int32 Minute,
                    Int32 Second, Int32 Millisecond, Int32 Microsecond,
                    DateTimeKind::Type Kind)
{
    Assert(Hour>=0 && Hour<24 && Minute>=0 && Minute<60 && Second>=0 && Second<60 &&
           Millisecond>=0 && Millisecond<1000 && Microsecond>=0 && Microsecond<1000,
           "Index out of bound.");

    if (Day*Month<1)//check if time and not a datetime
    {
        Assert(Year==0,"Index out of bound.");
        //is time
        m_Ticks=TimeSpan(0, Hour, Minute, Second, Millisecond, Microsecond);
        return;
    }

    Assert(Year>=0 && Year<10000 && Month>=0 && Month<13 && Day>=0 && Day<=DaysInMonth(Year,Month),"Index out of bound.");

    //is datetime
    m_Ticks=TimeSpan(AbsoluteDays(Year,Month,Day), Hour, Minute, Second,
                     Millisecond, Microsecond);
}

Int32 DateTime::FromTicks(TickDayConverterTyp::Type To)const
{
  Int32 num400,num100,num4,numyears;
  Int32 M=1;
  Int32 totaldays=m_Ticks.Days();
  Int32 dp400=146097;
  Int32 dp100=36524;
  Int32 dp4=1461;

  num400=totaldays/dp400;
  totaldays-=num400*dp400;

  num100=totaldays/dp100;
  if (num100==4)//leap
    num100=3;
  totaldays-=num100*dp100;

  num4=totaldays/dp4;
  totaldays-=num4*dp4;

  numyears=totaldays/365;

  if (numyears==4)//leap
    numyears=3;
  if (To==TickDayConverterTyp::Year)
    return num400*400+num100*100+num4*4+numyears+1;

  totaldays-=numyears*365;
  if (To==TickDayConverterTyp::DayYear)
    return totaldays+1;

  Int32 daysmonth[13]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  Int32 daysmonthleap[13]={ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  if ((numyears==3) && ((num100==3) || !(num4==24)))//31.Dec leapyear
    while(totaldays>=daysmonthleap[M])
      totaldays-=daysmonthleap[M++];
  else
    while(totaldays>=daysmonth[M])
      totaldays-=daysmonth[M++];

  if (To==TickDayConverterTyp::Month)
    return M;

  return totaldays+1;
}

Int32 DateTime::Year()const
{
  return FromTicks(TickDayConverterTyp::Year);
}

MonthOfYear::Type DateTime::GetMonthOfYear()const
{
  return (MonthOfYear::Type)(Month()-1);
}

Int32 DateTime::Month()const
{
  return FromTicks(TickDayConverterTyp::Month);
}

DayOfWeek::Type DateTime::GetDayOfWeek()const
{
  return (DayOfWeek::Type)((m_Ticks.Days()+1)%7);
}

Int32 DateTime::DayOfYear()const
{
  return FromTicks(TickDayConverterTyp::DayYear);
}

Int32 DateTime::Day()const
{
  return FromTicks(TickDayConverterTyp::Day);
}

Int32 DateTime::Hour()const
{
  return m_Ticks.Hours();
}

Int32 DateTime::Minute()const
{
  return m_Ticks.Minutes();
}

Int32 DateTime::Second()const
{
  return m_Ticks.Seconds();
}

Int32 DateTime::Millisecond()const
{
  return m_Ticks.Milliseconds();
}

Int32 DateTime::Microsecond()const
{
  return m_Ticks.Microseconds();
}

TimeSpan DateTime::TimeOfDay()const
{
  TimeSpan ts(m_Ticks.Ticks()%TimeSpan::TicksPerDay);
  return ts;
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
  DateTime dt=Now();
  DateTime result(dt.Year(),dt.Month(),dt.Day());
  return result;
}

DateTime DateTime::Now()
{
  TimeValue now=RadonFramework::System::Time::GetNow();
  TimeValue delta=RadonFramework::System::Time::GetMinutesWestOfGMT();

  DateTime dt(now,DateTimeKind::Local);
  dt.m_Ticks+=TimeSpan(delta);

  return dt;
}

DateTime DateTime::UtcNow()
{
    DateTime dt(RadonFramework::System::Time::GetNow(),DateTimeKind::UTC);
    return dt;
}

Int32 DateTime::DaysInMonth(Int32 Year, Int32 Month)
{
    Assert(Month>0 && Month<13 && Year>0 && Year<10000,"Index out of bound.");

    Int32 daysmonth[13]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    Int32 daysmonthleap[13]={ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    Int32 days=IsLeapYear(Year)?daysmonthleap[Month]:daysmonth[Month];
    return days;
}

Int32 DateTime::AbsoluteDays(Int32 Year, Int32 Month, Int32 Day)
{
  Int32 temp=0;
  Int32 daysmonth[13]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  Int32 daysmonthleap[13]={ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  if (IsLeapYear(Year))
    for (Int32 m=1;m<Month;m++)
      temp+=daysmonthleap[m];
  else
    for (Int32 m=1;m<Month;m++)
      temp+=daysmonth[m];

  return ((Day-1)+temp+(365*(Year-1))+((Year-1)/4)-((Year-1)/100)+((Year-1)/400));
}

bool DateTime::IsLeapYear(Int32 Year)
{
    Assert(Year>0 && Year<10000,"Index out of bound.");
    return ((Year%4==0 && Year%100!=0) || Year%400==0);
}

DateTime DateTime::MinValue=DateTime(0);

DateTime DateTime::MaxValue=DateTime(3155378975999999999LL);

bool DateTime::LessThan(DateTime t1, DateTime t2)
{
  return t1.Ticks()<t2.Ticks();
}

bool DateTime::GreaterThan(DateTime t1, DateTime t2)
{
  return t1.Ticks()>t2.Ticks();
}

RadonFramework::Core::Types::String RadonFramework::Time::DateTime::ToString() const
{
    String str;
    str<<Day()<<"."<<Month()<<"."<<Year();
    str<<" ";
    str<<Hour()<<":"<<Minute()<<":"<<Second();
    return str;
}

RadonFramework::Time::DateTime::DateTime()
:m_Ticks(0),
 m_Kind(DateTimeKind::Undefined)
{
}

bool DateTime::IsInvalid( const TimeValue& t )
{
    return ( t < MinValue.Ticks() ) || ( t > MaxValue.Ticks() ) ;
}
