export module rf.core.types:time;
export import :builtin;

export namespace rf {
using timeval = unsigned long long;

constexpr timeval operator""_ns(u64 Value) { return 10 * Value; }
constexpr timeval operator""_us(u64 Value) { return 10000 * Value; }
constexpr timeval operator""_ms(u64 Value) { return 10000000 * Value; }
constexpr timeval operator""_s(u64 Value) { return 10000000000 * Value; }
constexpr timeval operator""_min(u64 Value) { return 600000000000 * Value; }
constexpr timeval operator""_h(u64 Value) { return 36000000000000 * Value; }
constexpr timeval operator""_d(u64 Value) { return 864000000000000 * Value; }

constexpr timeval operator""_am(u64 Value) { return 36000000000000 * Value; }
constexpr timeval operator""_pm(u64 Value) {
  return 36000000000000 * (Value + 12);
}
} // namespace rf