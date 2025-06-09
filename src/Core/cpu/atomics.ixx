export module rf.core.cpu:atomics;
import rf.core.types;
import :intrinsics;

export namespace rf {

template <typename T> constexpr bool isSupportedAtomicType() { return false; }
template <> constexpr bool isSupportedAtomicType<i16>() { return true; }
template <> constexpr bool isSupportedAtomicType<i32>() { return true; }
template <> constexpr bool isSupportedAtomicType<i64>() { return true; }
template <> constexpr bool isSupportedAtomicType<u16>() { return true; }
template <> constexpr bool isSupportedAtomicType<u32>() { return true; }
template <> constexpr bool isSupportedAtomicType<u64>() { return true; }

template <typename T> struct Atomic {
  static_assert(isSupportedAtomicType<T>(), "Fail");

  Atomic(const T Value);

  T fetchAndAdd(const T Addend);
  T fetchAndExchange(const T Value);
  T compareAndExchange(const T Compare, const T Value);
  T add(const T Value);

  operator T() const;
  bool operator!() const;
  bool operator!=(const T Value) const;
  Atomic &operator=(const T Value);
  Atomic &operator=(const Atomic &Other) = default;
  bool operator==(const T Value) const;
  Atomic &operator++();
  Atomic operator++(int);
  Atomic &operator--();
  Atomic operator--(int);

private:
  T value;
  void increment();
  void decrement();
};

using AtomicInt16 = Atomic<i16>;
using AtomicInt32 = Atomic<i32>;
using AtomicInt64 = Atomic<i64>;
using AtomicUInt16 = Atomic<u16>;
using AtomicUInt32 = Atomic<u32>;
using AtomicUInt64 = Atomic<u64>;

struct AtomicPointer {
  ptr address;

  ptr fetchAndExchange(ptr Ptr);
  ptr compareAndExchange(ptr Compare, ptr Value);
};

template <typename T> Atomic<T>::Atomic(const T Value) : value(Value) {}

template <typename T> T Atomic<T>::fetchAndAdd(const T Addend) {
  return rf::fetchAndAdd(&this->value, Addend);
}

template <typename T> T Atomic<T>::fetchAndExchange(const T Value) {
  return rf::fetchAndExchange(&this->value, Value);
}

template <typename T>
T Atomic<T>::compareAndExchange(const T Compare, const T Value) {
  return rf::compareAndExchange(&this->value, Compare, Value);
}

template <typename T> T Atomic<T>::add(const T Value) {
  return fetchAndAdd(&this->value, Value);
}

template <typename T> void Atomic<T>::increment() { increase(&this->value); }

template <typename T> void Atomic<T>::decrement() { decrease(&this->value); }

template <typename T> Atomic<T>::operator T() const { return this->value; }

template <typename T> bool Atomic<T>::operator!() const {
  return this->value == 0 ? true : false;
}

template <typename T> bool Atomic<T>::operator!=(const T Value) const {
  return this->value != Value ? true : false;
}

template <typename T> Atomic<T> &Atomic<T>::operator=(const T Value) {
  this->value = Value;
  return *this;
}

template <typename T> bool Atomic<T>::operator==(const T Value) const {
  return this->value == Value;
}

template <typename T> Atomic<T> &Atomic<T>::operator++() {
  this->increment();
  return *this;
}

template <typename T> Atomic<T> Atomic<T>::operator++(int) {
  Atomic<T> result(*this);
  this->increment();
  return result;
}

template <typename T> Atomic<T> &Atomic<T>::operator--() {
  this->decrement();
  return *this;
}

template <typename T> Atomic<T> Atomic<T>::operator--(int) {
  Atomic<T> result(*this);
  this->decrement();
  return result;
}

ptr AtomicPointer::fetchAndExchange(ptr Ptr) {
  return rf::fetchAndExchange(&this->address, Ptr);
}

ptr AtomicPointer::compareAndExchange(ptr Compare, ptr Value) {
  return rf::compareAndExchange(
      reinterpret_cast<void *volatile *>(&this->address), Value, Compare);
}
} // namespace rf