export module rf.core.os:time;
import rf.core.types;
import rf.core.time;

export namespace rf {
    timeval getSystemTime();
    timeval getMinutesWestOfGMT();
    u64 getHighResolutionCounter();
    u64 getHighResolutionCounterFrequency();
    bool isHighResolutionCounterSupported();

    DateTime today();
    DateTime now();
    DateTime nowUTC();

DateTime today() {
  DateTime dt = now();
  DateTime result = DateTime::CreateByTime(dt.year(), dt.month(), dt.day());
  return result;
}

DateTime now() {
  timeval now = getSystemTime();
  timeval delta = getMinutesWestOfGMT();

  DateTime dt = DateTime::CreateByTicks(now, DateTimeKind::Local);
  dt.refDelta += TimeSpan::CreateByTicks(delta);

  return dt;
}

DateTime nowUTC() {
  DateTime dt = DateTime::CreateByTicks(getSystemTime(), DateTimeKind::UTC);
  return dt;
}
}