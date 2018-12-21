#ifndef RF_DIAGNOSTICS_COUNTER_BUFFER_HPP
#define RF_DIAGNOSTICS_COUNTER_BUFFER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Diagnostics::Counter
{
template <typename T>
class Simplex;

template <typename ATOMIC>
class Buffer
{
public:
  using DataType = typename ATOMIC::DataType;
  Buffer(Simplex<ATOMIC>& StoreInto);
  ~Buffer();

  void operator+=(DataType Value);
  void operator-=(DataType Value);

  void operator++();
  void operator++(int);
  void operator--();
  void operator--(int);

  void Push();

  Buffer& operator=(const Buffer& Other) = delete;
  Buffer(const Buffer& Copy) = delete;

private:
  Simplex<ATOMIC>& m_StoreInto;
  DataType m_Counter;
};

using BufferU16 = Buffer<RF_Type::AtomicUInt16>;
using BufferU32 = Buffer<RF_Type::AtomicUInt32>;
using BufferU64 = Buffer<RF_Type::AtomicUInt64>;
using Buffer16 = Buffer<RF_Type::AtomicInt16>;
using Buffer32 = Buffer<RF_Type::AtomicInt32>;
using Buffer64 = Buffer<RF_Type::AtomicInt64>;

template <typename ATOMIC>
inline Buffer<ATOMIC>::Buffer(Simplex<ATOMIC>& StoreInto)
: m_StoreInto(StoreInto), m_Counter(0)
{
}

template <typename ATOMIC>
inline Buffer<ATOMIC>::~Buffer()
{
  m_StoreInto += m_Counter;
}

template <typename ATOMIC>
inline void Buffer<ATOMIC>::operator+=(DataType Value)
{
  m_Counter += Value;
}

template <typename ATOMIC>
inline void Buffer<ATOMIC>::operator-=(DataType Value)
{
  m_Counter -= Value;
}

template <typename ATOMIC>
inline void Buffer<ATOMIC>::operator++()
{
  ++m_Counter;
}

template <typename ATOMIC>
inline void Buffer<ATOMIC>::operator++(int)
{
  ++m_Counter;
}

template <typename ATOMIC>
inline void Buffer<ATOMIC>::operator--()
{
  --m_Counter;
}

template <typename ATOMIC>
inline void Buffer<ATOMIC>::operator--(int)
{
  --m_Counter;
}

template <typename ATOMIC>
inline void Buffer<ATOMIC>::Push()
{
  m_StoreInto += m_Counter;
  m_Counter = 0;
}

}  // namespace RadonFramework::Diagnostics::Counter

#ifndef RF_SHORTHAND_NAMESPACE_COUNTER
#define RF_SHORTHAND_NAMESPACE_COUNTER
namespace RF_Counter = RadonFramework::Diagnostics::Counter;
#endif

#endif  // RF_DIAGNOSTICS_COUNTER_BUFFER_HPP