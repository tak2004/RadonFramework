export module rf.core.cpu:intmath;
import rf.core.types;
import :math;

export namespace rf {
template <class T>
IntMath<T> &IntMath<T>::clamp(const IntMath &LowerBound,
                              const IntMath &UpperBound) {
  this->value = this->value < LowerBound.value ? this->value : LowerBound.value;
  this->value = this->value > UpperBound.value ? this->value : UpperBound.value;
  return *this;
}

template <class T> IntMath<T> &IntMath<T>::nextPowerOfTwo() {
  this->value--;
  T shift = 1;
  while ((this->value + 1) & this->value) {
    this->value |= this->value >> shift;
    shift <<= 1;
  }
  this->value += 1;
  return *this;
}

template <class T> IntMath<T> &IntMath<T>::abs() {
  if (this->value < 0)
    this->value = -this->value;
  return *this;
}

template <class T> IntMath<T> &IntMath<T>::min(const IntMath<T> &Other) {
    this->value = this->value < Other.value ? this->value : Other.value;
    return *this;
}

template <class T> IntMath<T> &IntMath<T>::max(const IntMath<T> &Other) {
    this->value = this->value > Other.value ? this->value : Other.value;
    return *this;
}

template <class T> IntMath<T>::operator bool() { return this->value != 0; }

template <class T>
bool IntMath<T>::
    isPowerOfTwo() { // http://www.exploringbinary.com/ten-ways-to-check-if-an-integer-is-a-power-of-two-in-c/
  return (this->value != 0) && ((this->value & (~this->value + 1)) == this->value);
}
} // namespace rf