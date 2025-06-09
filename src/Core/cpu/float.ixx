module;
#include <cfloat>
#include <cmath>
export module rf.core.cpu:floatmath;
import :math;

// It should be enough to use two quadrant, a sign flip and linear interpolation.
constexpr rf::u32 FastSinArrayLen = 1440;// 0.25°
constexpr double M_PI   = 3.141592653589793;
constexpr rf::f32 FastSinArraySteps = (M_PI/180.0f)/FastSinArrayLen;  
static rf::f32 *FastSinArray=[]()->rf::f32*{
  static rf::f32 result[FastSinArrayLen];
  for (rf::u32 i = 0; i< FastSinArrayLen;i++)
    result[i] = ::sin(i*FastSinArraySteps);
  return result;
}();

export namespace rf {
const f32 DEG_TO_RAD = (4.0f*atanf(1.0f)) / 180.0f;
const f32 RAD_TO_DEG = 180.0f / (4.0f*atanf(1.0f));
constexpr double PI_4 = 0.7853981633974483;
const f32 POS_INFINITY = INFINITY;
const f32 NEG_INFINITY = -INFINITY;
const f32 EPSILION = FLT_EPSILON;

template <> FPMath<f32> &FPMath<f32>::degToRad() {
  this->value = this->value * DEG_TO_RAD;
  return *this;
}
template <> FPMath<f32> &FPMath<f32>::radToDeg() {
  this->value = this->value * RAD_TO_DEG;
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::arcCos() {
  this->value = ::acos(this->value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::arcCos() {
  this->value = ::acos(this->value);
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::arcSin() {
  this->value = ::asin(this->value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::arcSin() {
  this->value = ::asin(this->value);
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::arcTan() {
  this->value = atan(this->value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::arcTan() {
  auto tmp = *this;
  tmp.abs();
  this->value = PI_4 * this->value - this->value * (tmp.value - 1) * (0.2447 + 0.0663 * tmp);
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::arcTan(const FPMath<f32>& Y) {
  this->value = atan2(this->value, Y.value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::arcTan(const FPMath<f32,true>& Y) {
  this->value = atan2(this->value, Y.value);
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::ceil() {
  this->value = ceilf(this->value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::ceil() {
  this->value = ceilf(this->value);
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::sin() {
  this->value = ::sin(this->value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::sin() {
  u32 index = static_cast<u32>((FastSinArrayLen / 360.0f)*this->value) % (360 * (FastSinArrayLen / 360));
  this->value = FastSinArray[index];
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::cos() {
  this->value = ::cos(this->value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::cos() {
  u32 index = (static_cast<u32>((FastSinArrayLen / 360.0f)*this->value)+90) % (360 * (FastSinArrayLen / 360));
  this->value = FastSinArray[index];
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::tan() {
  this->value = ::tan(this->value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::tan() {
  this->value = ::tan(this->value);
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::exp() {
  this->value = ::exp(this->value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::exp() {
  this->value = ::exp(this->value);
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::abs() {
  this->value = fabs(this->value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::abs() {
  // Set the sign bit to zero.
  *reinterpret_cast<u32*>(&this->value) &= 0xffffffff >> 1;
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::floor() {
  this->value = ::floor(this->value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::floor() {
  this->value = ::floor(this->value);
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::sqr() {
  this->value *= this->value;
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::sqr() {
  this->value *= this->value;
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::sqrt() {
  this->value = ::sqrt(this->value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::sqrt() {
  this->value = ::sqrt(this->value);
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::cubicRoot() {
  this->value = ::cbrt(this->value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::cubicRoot() {
  this->value = ::cbrt(this->value);
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::inverseSqrt() {
  this->value = 1.0f / ::sqrt(this->value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::inverseSqrt() {
  this->value = 1.0f / ::sqrt(this->value);
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::log() {
  this->value = ::log(this->value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::log() {
  this->value = ::log(this->value);
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::pow() {
  this->value = ::pow(this->value,2);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::pow() {
  this->value = ::pow(this->value,2);
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::negate() {
  this->value = -this->value;
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::negate() {
  this->value = -this->value;
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::sign() {
  this->value = ::signbit(this->value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::sign() {
  this->value = ::signbit(this->value);
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::round() {
  this->value = ::nearbyint(this->value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::round() {
  this->value = ::nearbyint(this->value);
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::nextPowerOfTwo() {
  i32 exp;
  if(frexp(this->value, &exp) != 0.5) {
    this->value=ldexp(1.0, exp);
  }
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::nextPowerOfTwo() {
  i32 exp;
  if(frexp(this->value, &exp) != 0.5) {
    this->value=ldexp(1.0, exp);
  }
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::mod(const FPMath<f32> &Value) {
  this->value = ::fmod(this->value, Value.value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::mod(const FPMath<f32,true> &Value) {
  this->value = ::pow(this->value, Value.value);
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::pow(const FPMath<f32> &Value) {
  this->value = ::pow(this->value, Value.value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::pow(const FPMath<f32,true> &Value) {
  this->value = ::pow(this->value, Value.value);
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::min(const FPMath<f32> &Other) {
  this->value = this->value < Other.value ? this->value : Other.value;
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::min(const FPMath<f32,true> &Other) {
  this->value = this->value < Other.value ? this->value : Other.value;
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::max(const FPMath<f32> &Other) {
  this->value = this->value > Other.value ? this->value : Other.value;
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::max(const FPMath<f32,true> &Other) {
  this->value = this->value > Other.value ? this->value : Other.value;
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::avg(const FPMath<f32> &Other) {
  this->value = (this->value+Other.value)/2.0f;
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::avg(const FPMath<f32,true> &Other) {
  this->value = (this->value+Other.value)/2.0f;
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::clamp(const FPMath<f32> &B, const FPMath<f32> &C) {
  if (this->value < B.value)
    this->value = B.value;
  if (this->value > C.value)
    this->value = C.value;
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::clamp(const FPMath<f32,true> &B, const FPMath<f32,true> &C) {
  if (this->value < B.value)
    this->value = B.value;
  if (this->value > C.value)
    this->value = C.value;
  return *this;
}

template <> FPMath<f32> &FPMath<f32>::fma(const FPMath<f32> &B, const FPMath<f32> &C) {
  this->value = fmaf(this->value, B.value, C.value);
  return *this;
}

template <> FPMath<f32,true> &FPMath<f32,true>::fma(const FPMath<f32,true> &B, const FPMath<f32,true> &C) {
  this->value = (this->value * B.value) + C.value;
  return *this;
}

template <> bool FPMath<f32>::isPowerOfTwo(){
  int exp;
    return frexp(this->value, &exp) == 0.5;
}

template <> bool FPMath<f32,true>::isPowerOfTwo(){
  int exp;
    return frexp(this->value, &exp) == 0.5;
}

template <> bool FPMath<f32>::isNaN(){// NAN is never equal, try equal it self
    return this->value != this->value;
}

template <> bool FPMath<f32,true>::isNaN(){// NAN is never equal, try equal it self
    return this->value != this->value;
}

template <> bool FPMath<f32>::isInfinity(){
  return this->value == POS_INFINITY || this->value == NEG_INFINITY;
}

template <> bool FPMath<f32,true>::isInfinity(){
  return this->value == POS_INFINITY || this->value == NEG_INFINITY;
}

template <> bool FPMath<f32>::isAlmostEqual(const FPMath<f32> &Other){
  return  (fabs(this->value - Other.value) <= EPSILION);
}

template <> bool FPMath<f32,true>::isAlmostEqual(const FPMath<f32,true> &Other){
  auto diff = this->value-Other.value;
  return  (*reinterpret_cast<u32*>(&diff) &= 0xffffffff >> 1) <= EPSILION;
}

template <> FPMath<f32>::operator bool() {
  return this->value;
}

template <> FPMath<f32,true>::operator bool() {
  return this->value;
}

} // namespace rf