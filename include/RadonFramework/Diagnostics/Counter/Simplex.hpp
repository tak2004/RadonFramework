#ifndef RF_DIAGNOSTICS_COUNTER_SIMPLEX_HPP
#define RF_DIAGNOSTICS_COUNTER_SIMPLEX_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Diagnostics::Counter
{
template <typename ATOMIC>
class Simplex
{
public:
  typedef typename ATOMIC::DataType DataType;
  Simplex();
  Simplex(DataType Value);

  void operator+=(DataType Value);
  void operator-=(DataType Value);

  void operator++();
  void operator++(int);
  void operator--();
  void operator--(int);

  DataType Load();
  DataType Exchange(DataType NewValue);

  Simplex& operator=(const Simplex& Other) = delete;
  Simplex(const Simplex& Copy) = delete;

private:
  ATOMIC m_Counter;
};

using SimplexU16 = Simplex<RF_Type::AtomicUInt16>;
using SimplexU32 = Simplex<RF_Type::AtomicUInt32>;
using SimplexU64 = Simplex<RF_Type::AtomicUInt64>;
using Simplex16 = Simplex<RF_Type::AtomicInt16>;
using Simplex32 = Simplex<RF_Type::AtomicInt32>;
using Simplex64 = Simplex<RF_Type::AtomicInt64>;

template <typename ATOMIC>
inline Simplex<ATOMIC>::Simplex() : m_Counter(0)
{
}

template <typename ATOMIC>
inline Simplex<ATOMIC>::Simplex(DataType Value) : m_Counter(Value)
{
}

template <typename ATOMIC>
inline void Simplex<ATOMIC>::operator+=(DataType Value)
{
  m_Counter.Add(Value);
}

template <typename ATOMIC>
inline void Simplex<ATOMIC>::operator-=(DataType Value)
{
  m_Counter.Add(-Value);
}

template <typename ATOMIC>
inline void Simplex<ATOMIC>::operator++()
{
  m_Counter.Increment();
}

template <typename ATOMIC>
inline void Simplex<ATOMIC>::operator++(int)
{
  m_Counter.Increment();
}

template <typename ATOMIC>
inline void Simplex<ATOMIC>::operator--()
{
  m_Counter.Decrement();
}

template <typename ATOMIC>
inline void Simplex<ATOMIC>::operator--(int)
{
  m_Counter.Decrement();
}

template <typename ATOMIC>
inline typename ATOMIC::DataType Simplex<ATOMIC>::Load()
{
  return m_Counter;
}

template <typename ATOMIC>
inline typename ATOMIC::DataType
Simplex<ATOMIC>::Exchange(DataType NewValue)
{
  return m_Counter.FetchAndExchange(NewValue);
}

}  // namespace RadonFramework::Diagnostics::Counter

#ifndef RF_SHORTHAND_NAMESPACE_COUNTER
#define RF_SHORTHAND_NAMESPACE_COUNTER
namespace RF_Counter = RadonFramework::Diagnostics::Counter;
#endif

#endif  // RF_DIAGNOSTICS_COUNTER_SIMPLEX_HPP