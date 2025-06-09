export module rf.core.cpu:math;
import rf.core.types;

export namespace rf {
// Approximation flag will trade precission for speed if possible else it use
// the usual implementation.
template <class T, bool Approximation = false> struct FPMath {
  // conversion
  FPMath &degToRad();
  FPMath &radToDeg();
  //
  FPMath &arcCos();
  FPMath &arcSin();
  FPMath &arcTan();
  FPMath &arcTan(const FPMath &Y);
  FPMath &ceil();
  FPMath &cos();
  FPMath &sin();
  FPMath &tan();
  //
  FPMath &exp();
  FPMath &abs();
  FPMath &floor();
  FPMath &sqr();
  FPMath &sqrt();
  FPMath &cubicRoot();
  FPMath &inverseSqrt();
  FPMath &log();
  FPMath &pow();
  FPMath &negate();
  FPMath &sign();
  FPMath &round();
  FPMath &nextPowerOfTwo();
  //
  FPMath &mod(const FPMath &Value);
  FPMath &pow(const FPMath &Value);
  FPMath &min(const FPMath &Other);
  FPMath &max(const FPMath &Other);
  FPMath &avg(const FPMath &Other);
  FPMath &clamp(const FPMath &Min, const FPMath &Max);
  // fused multiply-add A = (A*B)+C
  FPMath &fma(const FPMath &B, const FPMath &C);
  //
  bool isPowerOfTwo();
  bool isNaN();
  bool isInfinity();
  bool isAlmostEqual(const FPMath &Value);
  operator bool();

  T &value;
};

template <class T> struct IntMath {
  IntMath &clamp(const IntMath &LowerBound, const IntMath &UpperBound);
  IntMath &nextPowerOfTwo();
  IntMath &abs();
  IntMath &min(const IntMath &Other);
  IntMath &max(const IntMath &Other);
  operator bool();
  bool isPowerOfTwo();

  T &value;
};

struct UnsupportedMath {};

template <class T> auto math(T &self) { return UnsupportedMath{}; }
template <> auto math(f32 &self) { return FPMath<f32>{self}; }
template <> auto math(u8 &self) { return IntMath<u8>{self}; }
template <> auto math(i8 &self) { return IntMath<i8>{self}; }
template <> auto math(u16 &self) { return IntMath<u16>{self}; }
template <> auto math(i16 &self) { return IntMath<i16>{self}; }
template <> auto math(u32 &self) { return IntMath<u32>{self}; }
template <> auto math(i32 &self) { return IntMath<i32>{self}; }
template <> auto math(u64 &self) { return IntMath<u64>{self}; }
template <> auto math(i64 &self) { return IntMath<i64>{self}; }

template <class T> FPMath<T, true> fastmath(T &self) {
  return FPMath<T, true>{self};
}
} // namespace rf