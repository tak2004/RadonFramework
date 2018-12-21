#ifndef RF_MEMORY_OBSERVERPOINTER_HPP
#define RF_MEMORY_OBSERVERPOINTER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Memory
{
template <typename T>
class ObserverPointer
{
public:
  using ValueType = T;
  using PointerType = T*;
  using ReferenceType = T&;

  ObserverPointer();
  explicit ObserverPointer(const PointerType Value);
  PointerType Get() const;
  ReferenceType operator*() const;
  PointerType operator->() const;
  explicit operator bool() const;
  explicit operator PointerType() const;
  PointerType Release();
  void Reset(const PointerType Value = nullptr);
  void Swap(ObserverPointer<T>& Other);

private:
  PointerType m_Pointer;
};

template <typename T>
void ObserverPointer<T>::Swap(ObserverPointer<T>& Other)
{
  PointerType tmp = Other.m_Pointer;
  Other.m_Pointer = m_Pointer;
  m_Pointer = tmp;
}

template <typename T>
void ObserverPointer<T>::Reset(const PointerType Value /*= nullptr*/)
{
  m_Pointer = Value;
}

template <typename T>
typename ObserverPointer<T>::PointerType ObserverPointer<T>::Release()
{
  auto result = m_Pointer;
  m_Pointer = nullptr;
  return result;
}

template <typename T>
ObserverPointer<T>::operator PointerType() const
{
  return m_Pointer;
}

template <typename T>
ObserverPointer<T>::operator bool() const
{
  return m_Pointer;
}

template <typename T>
typename ObserverPointer<T>::PointerType ObserverPointer<T>::operator->() const
{
  return m_Pointer;
}

template <typename T>
typename ObserverPointer<T>::ReferenceType ObserverPointer<T>::operator*() const
{
  return *m_Pointer;
}

template <typename T>
typename ObserverPointer<T>::PointerType ObserverPointer<T>::Get() const
{
  return m_Pointer;
}

template <typename T>
ObserverPointer<T>::ObserverPointer(const PointerType Value) : m_Pointer(Value)
{
}

template <typename T>
ObserverPointer<T>::ObserverPointer() : m_Pointer(nullptr)
{
}

}  // namespace RadonFramework::Memory

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif  // !RF_MEMORY_OBSERVERPOINTER_HPP