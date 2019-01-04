#pragma once

#include <RadonFramework/Collections/ArrayEnumeratorType.hpp>
#include <RadonFramework/Collections/Enumerator.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Common/Assert.hpp>
#include <type_traits>

namespace RadonFramework::Memory
{
template <typename T>
struct AutoPointerArrayData
{
  T* Ptr;
  RF_Type::Size Count;
};

template <typename T>
struct AutoPointerArrayReference
{
  AutoPointerArrayData<T> m_Data;

  explicit AutoPointerArrayReference(AutoPointerArrayData<T> Ptr);
};

template <typename T>
class AutoPointerArray
{
public:
  using ElementType = T;
  using EnumeratorType =
      Collections::Enumerator<T, Collections::ArrayEnumeratorType>;
  using ConstEnumeratorType =
      Collections::Enumerator<const T, Collections::ArrayEnumeratorType>;

  explicit AutoPointerArray();

  explicit AutoPointerArray(RF_Type::Size Count);

  AutoPointerArray(ElementType* Ptr, RF_Type::Size Count);

  AutoPointerArray(const AutoPointerArray& Copy);

  AutoPointerArray(AutoPointerArray&& Move);

  template <typename T1>
  AutoPointerArray(AutoPointerArray<T1>& Ref);

  AutoPointerArray(AutoPointerArrayReference<ElementType> Ref);

  ~AutoPointerArray();

  /**
   * Returns an Enumerator for the Array.
   */
  EnumeratorType GetEnumerator() const;

  /**
   * Returns an Enumerator for the Array.
   */
  ConstEnumeratorType GetConstEnumerator() const;

  ElementType* Get() const;

  /**
   * \brief Returns the element count.
   */
  RF_Type::Size Count() const;

  /**
   * \brief Returns the size in bytes.
   */
  RF_Type::Size Size() const;

  AutoPointerArray& operator=(const AutoPointerArray& Copy);

  AutoPointerArray& operator=(AutoPointerArray&& Move);

  template <typename T1>
  AutoPointerArray& operator=(AutoPointerArray<T1>& Copy);

  AutoPointerArray&
  operator=(const AutoPointerArrayReference<ElementType>& Ref);

  AutoPointerArrayData<T> Release();

  void Reset();

  void Reset(AutoPointerArrayData<T> Data);

  AutoPointerArray<T>& New(const RF_Type::Size ElementCount);

  AutoPointerArray Clone() const;

  template <typename T1>
  operator AutoPointerArrayReference<T1>();

  template <typename T1>
  operator AutoPointerArray<T1>();

  T& operator[](const RF_Type::Size Index);

  const T& operator[](const RF_Type::Size Index) const;

  /// Return true if it contains a null-pointer or the size is 0 else false.
  RF_Type::Bool IsEmpty() const;

  void Swap(AutoPointerArray<T>& Other);

  RF_Type::Size
  Copy(const void* From, RF_Type::Size Bytes, RF_Type::Size Offset = 0);

  RF_Type::Bool operator==(const AutoPointerArray& Other) const;

  EnumeratorType begin() const;

  EnumeratorType end() const;

private:
  T* m_Data;
  RF_Type::Size m_Elements{0};
};

template <typename T>
RF_Type::Bool AutoPointerArray<T>::
operator==(const AutoPointerArray& Other) const
{
  RF_Type::Bool result = true;
  result &= m_Elements == Other.m_Elements;
  if(result)
    result &= RF_SysMem::Compare(m_Data, Other.m_Data, m_Elements) == 0;
  return result;
}

template <typename T>
AutoPointerArray<T>& AutoPointerArray<T>::New(const RF_Type::Size ElementCount)
{
  Reset();
  m_Data = new T[ElementCount];
  m_Elements = ElementCount;
  return *this;
}

template <typename T>
RF_Type::Size AutoPointerArray<T>::Copy(const void* From,
                                        RF_Type::Size Bytes,
                                        RF_Type::Size Offset /*= 0*/)
{
  RF_Type::Size result = 0;
  if(Offset + (Bytes / sizeof(T)) <= m_Elements)
  {
    RF_SysMem::Copy(m_Data + Offset, From, Bytes);
    result = Bytes;
  }
  return result;
}

template <typename T>
RF_Type::Bool AutoPointerArray<T>::IsEmpty() const
{
  return m_Data == 0 || m_Elements == 0;
}

template <typename T>
AutoPointerArray<T>::AutoPointerArray(RF_Type::Size Count)
{
  m_Data = new T[Count];
  m_Elements = Count;
}

template <typename T>
AutoPointerArrayReference<T>::AutoPointerArrayReference(
    AutoPointerArrayData<T> Ptr)
: m_Data(Ptr)
{
}

template <typename T>
AutoPointerArray<T>::AutoPointerArray() : m_Data(nullptr)
{
}

template <typename T>
AutoPointerArray<T>::AutoPointerArray(ElementType* Ptr, RF_Type::Size Count)
{
  m_Elements = Count;
  m_Data = Ptr;
}

template <typename T>
AutoPointerArray<T>::AutoPointerArray(const AutoPointerArray<T>& Copy)
{
  *this = Copy.Clone();
}

template <typename T>
AutoPointerArray<T>::AutoPointerArray(AutoPointerArray<T>&& Move)
{
  m_Data = Move.m_Data;
  m_Elements = Move.m_Elements;
  Move.m_Data = nullptr;
  Move.m_Elements = 0;
}

template <typename T>
template <typename T1>
AutoPointerArray<T>::AutoPointerArray(AutoPointerArray<T1>& Ref)
{
  AutoPointerArrayData<T1> data = Ref.Release();
  m_Elements = data.Count;
  m_Data = data.Ptr;
}

template <typename T>
AutoPointerArray<T>::AutoPointerArray(
    AutoPointerArrayReference<ElementType> Ref)
: m_Data(Ref.m_Data.Ptr), m_Elements(Ref.m_Data.Count)
{
}

template <typename T>
AutoPointerArray<T>::~AutoPointerArray()
{
  delete[] m_Data;
  m_Data = nullptr;
  m_Elements = 0;
}

template <typename T>
typename AutoPointerArray<T>::EnumeratorType
AutoPointerArray<T>::GetEnumerator() const
{
  EnumeratorType result;
  result.m_Start = m_Data;
  result.m_Current = m_Data;
  result.m_Elements = m_Elements;
  return result;
}

template <typename T>
typename AutoPointerArray<T>::ConstEnumeratorType
AutoPointerArray<T>::GetConstEnumerator() const
{
  ConstEnumeratorType result;
  result.m_Start = m_Data;
  result.m_Current = m_Data;
  result.m_Elements = m_Elements;
  return result;
}

template <typename T>
T* AutoPointerArray<T>::Get() const
{
  return m_Data;
}

template <typename T>
RF_Type::Size AutoPointerArray<T>::Count() const
{
  return m_Elements;
}

template <typename T>
RF_Type::Size AutoPointerArray<T>::Size() const
{
  return m_Elements * sizeof(T);
}

template <typename T>
AutoPointerArray<T>& AutoPointerArray<T>::
operator=(const AutoPointerArray<T>& Copy)
{
  *this = Copy.Clone();
  return *this;
}

template <typename T>
AutoPointerArray<T>& AutoPointerArray<T>::operator=(AutoPointerArray<T>&& Move)
{
  Reset();
  m_Data = Move.m_Data;
  Move.m_Data = nullptr;
  m_Elements = Move.m_Elements;
  Move.m_Elements = 0;
  return *this;
}

template <typename T>
template <typename T1>
AutoPointerArray<T>& AutoPointerArray<T>::operator=(AutoPointerArray<T1>& Copy)
{
  AutoPointerArrayData<T1> data = Copy.Release();
  Reset(*reinterpret_cast<AutoPointerArrayData<T>*>(&data));
  return *this;
}

template <typename T>
AutoPointerArray<T>& AutoPointerArray<T>::
operator=(const AutoPointerArrayReference<ElementType>& Ref)
{
  if(Ref.m_Data.Ptr != this->Get())
  {
    delete[] m_Data;
    m_Data = Ref.m_Data.Ptr;
    m_Elements = Ref.m_Data.Count;
  }
  return *this;
}

template <typename T>
AutoPointerArrayData<T> AutoPointerArray<T>::Release()
{
  AutoPointerArrayData<T> arr;
  arr.Ptr = m_Data;
  arr.Count = m_Elements;
  m_Data = nullptr;
  m_Elements = 0;
  return arr;
}

template <typename T>
void AutoPointerArray<T>::Reset()
{
  delete[] m_Data;
  m_Data = nullptr;
  m_Elements = 0;
}

template <typename T>
void AutoPointerArray<T>::Reset(AutoPointerArrayData<T> Data)
{
  if(m_Data != Data.Ptr)
  {
    delete[] m_Data;
    m_Data = Data.Ptr;
    m_Elements = Data.Count;
  }
}

template <typename T>
AutoPointerArray<T> AutoPointerArray<T>::Clone() const
{
  AutoPointerArray arr;
  if(m_Elements > 0)
  {
    arr.m_Data = new ElementType[m_Elements];
    arr.m_Elements = m_Elements;
    RF_SysMem::Copy(arr.m_Data, m_Data, m_Elements * sizeof(T));
  }
  return arr;
}

template <typename T>
template <typename T1>
AutoPointerArray<T>::operator AutoPointerArrayReference<T1>()
{
  AutoPointerArrayData<T1> tmp(this->Release());
  AutoPointerArrayReference<T1> result(tmp);
  return result;
}

template <typename T>
template <typename T1>
AutoPointerArray<T>::operator AutoPointerArray<T1>()
{
  return AutoPointerArray<T1>(this->Release());
}

template <typename T>
T& AutoPointerArray<T>::operator[](const RF_Type::Size Index)
{
  RF_ASSERT(Index < m_Elements, "Out of bound.");
  return m_Data[Index];
}

template <typename T>
const T& AutoPointerArray<T>::operator[](const RF_Type::Size Index) const
{
  RF_ASSERT(Index < m_Elements, "Out of bound.");
  return m_Data[Index];
}

template <typename T>
void AutoPointerArray<T>::Swap(AutoPointerArray<T>& Other)
{
  T* p = m_Data;
  m_Data = Other.m_Data;
  Other.m_Data = p;
  RF_Type::Size s = m_Elements;
  m_Elements = Other.m_Elements;
  Other.m_Elements = s;
}

template <typename T>
typename AutoPointerArray<T>::EnumeratorType AutoPointerArray<T>::end() const
{
  EnumeratorType result;
  result.m_Start = m_Data;
  result.m_Current = m_Data + m_Elements;
  result.m_Elements = m_Elements;
  return result;
}

template <typename T>
typename AutoPointerArray<T>::EnumeratorType AutoPointerArray<T>::begin() const
{
  EnumeratorType result;
  result.m_Start = m_Data;
  result.m_Current = m_Data;
  result.m_Elements = m_Elements;
  return result;
}

}  // namespace RadonFramework::Memory

namespace RF_Mem = RadonFramework::Memory;