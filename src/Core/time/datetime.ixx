export module rf.core.time:datetime;
import rf.core.types;
import rf.core.os;
import :timespan;

export namespace rf {
enum class DayOfWeek { Monday, Tuesday, Wednesday, Thursday, Saturday, Sunday };

enum class MonthOfYear {
  January,
  Februrary,
  March,
  April,
  May,
  June,
  July,
  August,
  September,
  October,
  November,
  December
};

enum class TickDayConverterTyp { Day, DayYear, Month, Year };

enum class DateTimeKind { Undefined, Local, UTC };

struct DateTime {
  static DateTime CreateByTicks(timeval Value,
                                DateTimeKind Kind = DateTimeKind::Undefined);
  static DateTime CreateByTime(u32 Year, u32 Month, u32 Day,
                               DateTimeKind Kind = DateTimeKind::Undefined);
  static DateTime CreateByTime(u32 Year, u32 Month, u32 Day, u32 Hour,
                               u32 Minute, u32 Second,
                               DateTimeKind Kind = DateTimeKind::Undefined);
  static DateTime CreateByTime(const TimeSpan &Value,
                               DateTimeKind Kind = DateTimeKind::Undefined);
  static DateTime Now();
  static DateTime Today();
  static DateTime UtcNow();

  u32 year() const;
  MonthOfYear getMonthOfYear() const;
  u32 month() const;
  DayOfWeek getDayOfWeek() const;
  u32 dayOfYear() const;
  u32 day() const;
  u32 hour() const;
  u32 minute() const;
  u32 second() const;
  u32 millisecond() const;
  u32 microsecond() const;
  TimeSpan timeOfDay() const;
  TimeSpan asTimeSpan() const;
  timeval ticks() const;

  static u32 DaysInMonth(u32 Year, u32 Month);
  static bool IsLeapYear(u32 Year);
  static DateTime MinValue;
  static DateTime MaxValue;
  static bool LessThan(DateTime t1, DateTime t2);
  static bool GreaterThan(DateTime t1, DateTime t2);

protected:
  TimeSpan m_Ticks;
  DateTimeKind m_Kind;

  u32 fromTicks(TickDayConverterTyp To) const;
  static u32 AbsoluteDays(u32 Year, u32 Month, u32 Day);
};

const u32 daysmonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const u32 daysmonthleap[13] = {0,  31, 29, 31, 30, 31, 30,
                               31, 31, 30, 31, 30, 31};

DateTime DateTime::MinValue = DateTime::CreateByTicks(0);
DateTime DateTime::MaxValue = DateTime::CreateByTicks(3155378975999999999LL);

DateTime DateTime::CreateByTicks(timeval Value, DateTimeKind Kind) {
  DateTime result;
  result.m_Ticks = TimeSpan::CreateByTicks(Value);
  result.m_Kind = Kind;
  return result;
}

DateTime DateTime::CreateByTime(u32 Year, u32 Month, u32 Day,
                                DateTimeKind Kind) {
  DateTime result;
  result.m_Kind = Kind;

  if (Year >= 0 && Year < 10000 && Month >= 0 && Month < 13 && Day >= 0 &&
      Day <= DaysInMonth(Year, Month)) {
    result.m_Ticks =
        TimeSpan::CreateByTime(AbsoluteDays(Year, Month, Day), 0, 0, 0, 0, 0);
  }
  return result;
}

DateTime DateTime::CreateByTime(u32 Year, u32 Month, u32 Day, u32 Hour,
                                u32 Minute, u32 Second, DateTimeKind Kind) {
  DateTime result;
  result.m_Kind = Kind;

  if (Hour >= 0 && Hour < 24 && Minute >= 0 && Minute < 60 && Second >= 0 &&
      Second < 60) {
    // check if specified parameter represent time instead of date and time
    if (Day == 0 && Month == 0 && Year == 0) {
      result.m_Ticks = TimeSpan::CreateByTime(0, Hour, Minute, Second, 0, 0);
    } else {
      if (Year >= 0 && Year < 10000 && Month >= 0 && Month < 13 && Day >= 0 &&
          Day <= DaysInMonth(Year, Month)) { // is datetime
        result.m_Ticks = TimeSpan::CreateByTime(AbsoluteDays(Year, Month, Day),
                                                Hour, Minute, Second, 0, 0);
      }
    }
  }
  return result;
}

DateTime DateTime::CreateByTime(const TimeSpan &Value, DateTimeKind Kind) {
  DateTime result;
  result.m_Kind = Kind;
  result.m_Ticks = Value;
  return result;
}

u32 DateTime::fromTicks(TickDayConverterTyp To) const {
  u32 num400, num100, num4, numyears;
  u32 M = 1;
  u32 totaldays = m_Ticks.days();
  u32 dp400 = 146097;
  u32 dp100 = 36524;
  u32 dp4 = 1461;

  num400 = totaldays / dp400;
  totaldays -= num400 * dp400;

  num100 = totaldays / dp100;
  if (num100 == 4) // leap
  {
    num100 = 3;
  }
  totaldays -= num100 * dp100;

  num4 = totaldays / dp4;
  totaldays -= num4 * dp4;

  numyears = totaldays / 365;

  if (numyears == 4) // leap
  {
    numyears = 3;
  }

  if (To == TickDayConverterTyp::Year) {
    return num400 * 400 + num100 * 100 + num4 * 4 + numyears + 1;
  }

  totaldays -= numyears * 365;
  if (To == TickDayConverterTyp::DayYear) {
    return totaldays + 1;
  }

  if ((numyears == 3) && ((num100 == 3) || !(num4 == 24))) // 31.Dec leapyear
  {
    while (totaldays >= daysmonthleap[M]) {
      totaldays -= daysmonthleap[M++];
    }
  } else {
    while (totaldays >= daysmonth[M]) {
      totaldays -= daysmonth[M++];
    }
  }

  if (To == TickDayConverterTyp::Month) {
    return M;
  }

  return totaldays + 1;
}

u32 DateTime::year() const { return fromTicks(TickDayConverterTyp::Year); }

MonthOfYear DateTime::getMonthOfYear() const {
  return static_cast<MonthOfYear>(month() - 1);
}

u32 DateTime::month() const { return fromTicks(TickDayConverterTyp::Month); }

DayOfWeek DateTime::getDayOfWeek() const {
  return static_cast<DayOfWeek>((m_Ticks.days() + 1) % 7);
}

u32 DateTime::dayOfYear() const {
  return fromTicks(TickDayConverterTyp::DayYear);
}

u32 DateTime::day() const { return fromTicks(TickDayConverterTyp::Day); }

u32 DateTime::hour() const { return m_Ticks.hours(); }

u32 DateTime::minute() const { return m_Ticks.minutes(); }

u32 DateTime::second() const { return m_Ticks.seconds(); }

u32 DateTime::millisecond() const { return m_Ticks.milliseconds(); }

u32 DateTime::microsecond() const { return m_Ticks.microseconds(); }

TimeSpan DateTime::timeOfDay() const {
  TimeSpan result = TimeSpan::CreateByTicks(m_Ticks.ticks() % 1_d);
  return result;
}

TimeSpan DateTime::asTimeSpan() const {
  TimeSpan ts(m_Ticks);
  return ts;
}

timeval DateTime::ticks() const { return m_Ticks.ticks(); }

DateTime DateTime::Today() {
  DateTime dt = Now();
  DateTime result = DateTime::CreateByTime(dt.year(), dt.month(), dt.day());
  return result;
}

DateTime DateTime::Now() {
  timeval now = getSystemTime();
  timeval delta = getMinutesWestOfGMT();

  DateTime dt = DateTime::CreateByTicks(now, DateTimeKind::Local);
  dt.m_Ticks += TimeSpan::CreateByTicks(delta);

  return dt;
}

DateTime DateTime::UtcNow() {
  DateTime dt = DateTime::CreateByTicks(getSystemTime(), DateTimeKind::UTC);
  return dt;
}

u32 DateTime::DaysInMonth(u32 Year, u32 Month) {
  u32 days = IsLeapYear(Year) ? daysmonthleap[Month] : daysmonth[Month];
  return days;
}

u32 DateTime::AbsoluteDays(u32 Year, u32 Month, u32 Day) {
  u32 temp = 0;
  if (IsLeapYear(Year)) {
    for (u32 m = 1; m < Month; ++m) {
      temp += daysmonthleap[m];
    }
  } else {
    for (u32 m = 1; m < Month; m++) {
      temp += daysmonth[m];
    }
  }
  return ((Day - 1) + temp + (365 * (Year - 1)) + ((Year - 1) / 4) -
          ((Year - 1) / 100) + ((Year - 1) / 400));
}

bool DateTime::IsLeapYear(u32 Year) {
  return ((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0);
}

bool DateTime::LessThan(DateTime t1, DateTime t2) {
  return t1.ticks() < t2.ticks();
}

bool DateTime::GreaterThan(DateTime t1, DateTime t2) {
  return t1.ticks() > t2.ticks();
}
} // namespace rf