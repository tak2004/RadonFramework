#ifndef RF_DIAGNOSTICS_COUNTER_ARRAY_HPP
#define RF_DIAGNOSTICS_COUNTER_ARRAY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Diagnostics::Counter
{
template <typename T>
class Simplex;

template <typename ATOMIC, RF_Type::Size ELEMENTS>
class Array
{
public:
  using CounterType = Simplex<ATOMIC>;
  Array() {}
  CounterType& operator[](const RF_Type::Size Index);
  RF_Type::Size Size() const;

  Array& operator=(const Array& Other) = delete;
  Array(const Array& Copy) = delete;

private:
  CounterType m_Elements[ELEMENTS];
};

template <RF_Type::Size ELEMENTS>
using ArrayU16 = Array<RF_Type::AtomicUInt16, ELEMENTS>;
template <RF_Type::Size ELEMENTS>
using ArrayU32 = Array<RF_Type::AtomicUInt32, ELEMENTS>;
template <RF_Type::Size ELEMENTS>
using ArrayU64 = Array<RF_Type::AtomicUInt64, ELEMENTS>;
template <RF_Type::Size ELEMENTS>
using Array16 = Array<RF_Type::AtomicInt16, ELEMENTS>;
template <RF_Type::Size ELEMENTS>
using Array32 = Array<RF_Type::AtomicInt32, ELEMENTS>;
template <RF_Type::Size ELEMENTS>
using Array64 = Array<RF_Type::AtomicInt64, ELEMENTS>;

template <typename ATOMIC, RF_Type::Size ELEMENTS>
inline typename Array<ATOMIC, ELEMENTS>::CounterType& Array<ATOMIC, ELEMENTS>::
operator[](const RF_Type::Size Index)
{
  Assert(Index < ELEMENTS, "Index out of bound");
  return m_Elements[Index];
}

template <typename ATOMIC, RF_Type::Size ELEMENTS>
inline RF_Type::Size Array<ATOMIC, ELEMENTS>::Size() const
{
  return ELEMENTS;
}

}  // namespace RadonFramework::Diagnostics::Counter

#ifndef RF_SHORTHAND_NAMESPACE_COUNTER
#define RF_SHORTHAND_NAMESPACE_COUNTER
namespace RF_Counter = RadonFramework::Diagnostics::Counter;
#endif

#endif  // RF_DIAGNOSTICS_COUNTER_ARRAY_HPP