export module rf.core.time:timespan;
import rf.core.types;

export namespace rf {
struct TimeSpan {
  timeval ticks;

  static TimeSpan Zero;
  static TimeSpan Max;

  static TimeSpan CreateByTicks(timeval Value);
  static TimeSpan CreateByTime(u32 Hours, u32 Minutes, u32 Seconds);
  static TimeSpan CreateByTime(u32 Days, u32 Hours, u32 Minutes, u32 Seconds,
                               u32 Milliseconds = 0, u32 Microseconds = 0);

  u32 days() const;
  u32 hours() const;
  u32 minutes() const;
  u32 seconds() const;
  u32 milliseconds() const;
  u32 microseconds() const;

  f64 totalDays() const;
  f64 totalHours() const;
  f64 totalMinutes() const;
  f64 totalSeconds() const;
  f64 totalMilliseconds() const;
  f64 totalMicroseconds() const;

  TimeSpan add(const TimeSpan &TS) const;
  TimeSpan sub(const TimeSpan &TS) const;
  TimeSpan &operator+=(const TimeSpan &TS);
  TimeSpan &operator-=(const TimeSpan &TS);
  TimeSpan operator+(const TimeSpan &TS) const;
  TimeSpan operator-(const TimeSpan &TS) const;
  bool operator>(const TimeSpan &TS) const;
  bool operator<(const TimeSpan &TS) const;
  bool operator>=(const TimeSpan &TS) const;
  bool operator<=(const TimeSpan &TS) const;
  bool operator!=(const TimeSpan &TS) const;
  bool operator==(const TimeSpan &TS) const;
};

TimeSpan TimeSpan::Zero = TimeSpan::CreateByTicks(0);
TimeSpan TimeSpan::Max = TimeSpan::CreateByTicks(0xffffffffffffffffull);

TimeSpan TimeSpan::CreateByTicks(timeval Value) {
  TimeSpan result;
  result.ticks = Value;
  return result;
}

TimeSpan TimeSpan::CreateByTime(u32 Hours, u32 Minutes, u32 Seconds) {
  TimeSpan result;
  result.ticks = Hours * 1_h + Minutes * 1_min + Seconds * 1_s;
  return result;
}

TimeSpan TimeSpan::CreateByTime(u32 Days, u32 Hours, u32 Minutes, u32 Seconds,
                                u32 Milliseconds, u32 Microseconds) {
  TimeSpan result;
  result.ticks = Days * 1_d + Hours * 1_h + Minutes * 1_min + Seconds * 1_s +
                 Milliseconds * 1_ms + Microseconds * 1_us;
  return result;
}

u32 TimeSpan::days() const { return static_cast<u32>(ticks / 1_d); }

u32 TimeSpan::hours() const { return ticks / 1_h % 24; }

u32 TimeSpan::minutes() const { return ticks / 1_min % 60; }

u32 TimeSpan::seconds() const { return ticks / 1_s % 60; }

u32 TimeSpan::milliseconds() const { return ticks / 1_ms % 1000; }

u32 TimeSpan::microseconds() const { return ticks / 1_us % 1000; }

f64 TimeSpan::totalDays() const {
  return static_cast<f64>(ticks) / static_cast<f64>(1_d);
}

f64 TimeSpan::totalHours() const {
  return static_cast<f64>(ticks) / static_cast<f64>(1_h);
}

f64 TimeSpan::totalMinutes() const {
  return static_cast<f64>(ticks) / static_cast<f64>(1_min);
}

f64 TimeSpan::totalSeconds() const {
  return static_cast<f64>(ticks) / static_cast<f64>(1_s);
}

f64 TimeSpan::totalMilliseconds() const {
  return static_cast<f64>(ticks) / static_cast<f64>(1_ms);
}

f64 TimeSpan::totalMicroseconds() const {
  return static_cast<f64>(ticks) / static_cast<f64>(1_us);
}

TimeSpan TimeSpan::add(const TimeSpan &TS) const {
  TimeSpan result;
  result.ticks = ticks + TS.ticks;
  return result;
}

TimeSpan TimeSpan::sub(const TimeSpan &TS) const {
  TimeSpan result;
  result.ticks = ticks - TS.ticks;
  return result;
}

TimeSpan &TimeSpan::operator+=(const TimeSpan &TS) {
  ticks += TS.ticks;
  return *this;
}

TimeSpan &TimeSpan::operator-=(const TimeSpan &TS) {
  ticks -= TS.ticks;
  return *this;
}

TimeSpan TimeSpan::operator+(const TimeSpan &TS) const {
  TimeSpan result;
  result.ticks = ticks + TS.ticks;
  return result;
}

TimeSpan TimeSpan::operator-(const TimeSpan &TS) const {
  TimeSpan result;
  result.ticks = ticks - TS.ticks;
  return result;
}

bool TimeSpan::operator>(const TimeSpan &TS) const { return ticks > TS.ticks; }

bool TimeSpan::operator<(const TimeSpan &TS) const { return ticks < TS.ticks; }

bool TimeSpan::operator>=(const TimeSpan &TS) const {
  return ticks >= TS.ticks;
}

bool TimeSpan::operator<=(const TimeSpan &TS) const {
  return ticks <= TS.ticks;
}

bool TimeSpan::operator!=(const TimeSpan &TS) const {
  return ticks != TS.ticks;
}

bool TimeSpan::operator==(const TimeSpan &TS) const {
  return ticks == TS.ticks;
}
} // namespace rf