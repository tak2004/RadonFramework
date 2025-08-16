export module rf.core.types:limits;
import :builtin;

export namespace rf {
template <class T> struct limit {};

template <> struct limit<u32> {
  static const u32 max = 0xffffffff;
  static const u32 min = 0;
};
}