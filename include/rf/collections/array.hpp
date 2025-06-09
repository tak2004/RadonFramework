#pragma once
#include <rf/core/types/builtin.hpp>
#include <rf/core/types/memory.hpp>

namespace rf {

template<class T> struct arr{
    using ElementType = T;
    T* first;
    size elements;
};

/// <summary>
/// This class is a sequential, indexed container.
/// The size and values are changeable.
/// It's weakness is the resize, insert and remove operation which getting
/// slower with rising size. Use a link based container instead e.g. List.
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T> class Array {
public:
  using ElementType = T;

  Array() = default;
  Array(const size Capacity) : Array<T>(Capacity) {}

  const T &operator[](const size Index) const {
    return reinterpret_cast<T *>(this->data.address)[Index];
  }
  T &operator[](const size Index) {
    return reinterpret_cast<T *>(this->data.address)[Index];
  }
  void operator=(Array &&Other) noexcept {
    this->data = Other.data;
    this->elements = Other.elements;
  }
  void operator=(const Array &Copy) {
    m_Data = Copy.m_Data.Span(0, Copy.ElementCount());
    this->elements = Copy.elements;
  }
  // Access first element.
  T &operator()() { return m_Data[0]; }
  bool operator<<(const T &Value) { return Insert(m_Elements, Value); }
  bool operator>>(T &Value) { return Remove(0, Value); }
  size Capacity() const { return m_Data.ElementCount(); }
  bool IsEmpty() const { return m_Elements == 0; }
  bool IsFull() const { return m_Elements == m_Data.ElementCount(); }
  size ElementCount() const { return m_Elements; }
  bool Remove(const size Index, T &Out) {
    if (Index < m_Elements) {
      --m_Elements;
      Out = m_Data[Index];
      for (auto i = Index; i < m_Elements; ++i)
        m_Data[i] = m_Data[i + 1];
      return true;
    }
    return false;
  }
  bool Insert(const size Index, const T &Value) {
    if (IsFull())
      Resize(m_Elements + 1);
    for (auto i = m_Elements++; i > Index; ++i)
      m_Data[i] = m_Data[i - 1];
    m_Data[Index] = Value;
    return true;
  }
  void Resize(const size NewCapacity) {
    Array<T> tmp(NewCapacity);
    for (auto i = 0; i < m_Elements; ++i)
      tmp[i] = m_Data[i];
    m_Data = static_cast<Array<T> &&>(tmp);
  }

private:
  mem data;
  size elements = 0;
};
} // namespace rf