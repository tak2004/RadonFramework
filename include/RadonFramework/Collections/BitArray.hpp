#ifndef RF_COLLECTIONSBITARRAY_HPP
#define RF_COLLECTIONSBITARRAY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <type_traits>

#include <RadonFramework/Core/Policies/CMemoryOperation.hpp>
#include <RadonFramework/Core/Policies/CPPAllocator.hpp>
#include <RadonFramework/Core/Policies/LazyResize.hpp>
#include <RadonFramework/Math/Integer.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>

namespace RadonFramework::Collections
{
/** \brief This is a policy based template for BitArrays.
 *
 * \tparam RB Resize behaviour policy
 * \tparam MA Memory allocator policy
 * \tparam MO Memory operation policy
 */
template <typename RB = Core::Policies::LazyResize<8, 1>,
          typename MA = Core::Policies::CPPAllocator,
          typename MO = Core::Policies::CMemoryOperation>
class BitArray
{
public:
  /// Create an instance of the BitArray class.
  BitArray();

  /** \brief Create a copy of a given BitArray.
   *
   * The copy constructor make a deep copy.
   *
   * \param Copy The object from which the copy will be done.
   */
  BitArray(const BitArray<RB, MA, MO>& Copy);

  /** \brief Create a BitArray.
   *
   * \param Length The size of the BitArray in bits.
   */
  BitArray(const RF_Type::Size Length);

  /** \brief Creates a BitArray of the specified length.
   *         The data of the BitArray are copied from the C array.
   *         You have to ensure to cleanup the array by yourself!
   *
   * \param CArray An array which commonly provided by C code.
   * \param Length Specify the length of the BitArray in bits.
   */
  static Memory::AutoPointer<BitArray<RB, MA, MO>>
  CreateInstance(const RF_Type::UInt8 CArray[], const RF_Type::Size Length);

  ~BitArray();

  /** \brief Creates a deep copy of the BitArray.
   *
   * A deep copy of an BitArray copies the elements
   * and everything directly or indirectly referenced by the
   * elements.
   *
   * This method is an O(n) operation, where n is Count/8.
   */
  Memory::AutoPointer<BitArray<RB, MA, MO>> Clone() const;

  /** \brief Copies a range of elements from an BitArray starting
   *         at the specified source index and pastes them to
   *         another BitArray starting at the specified destination
   *         index. Guarantees that all changes are undone if
   *         the copy does not succeed completely.
   *
   * \param SourceIndex A 32-bit unsigned integer that represents
   *                    the index in the source BitArray at which
   *                    copying begins.
   * \param DestinationArray The BitArray that receives the data.
   * \param DestinationIndex A 32-bit unsigned integer that
   *                         represents the index in the
   *                         destination BitArray at which storing
   *                         begins.
   * \param Length A 32-bit unsigned integer that represents
   *               the number of elements to copy.
   */
  RF_Type::Bool ConstrainedCopy(RF_Type::Size SourceIndex,
                                BitArray<RB, MA, MO>& DestinationArray,
                                RF_Type::Size DestinationIndex,
                                RF_Type::Size Length);

  /** \brief Copies a range of elements from an BitArray starting
   *         at the specified source index and pastes them to
   *         another BitArray starting at the specified destination
   *         index. Guarantees that all changes are undone if
   *         the copy does not succeed completely.
   *
   * \param DestinationArray The BitArray that receives the data.
   * \param Length A 32-bit unsigned integer that represents
   *               the number of elements to copy.
   */
  RF_Type::Bool
  ConstrainedCopy(BitArray<RB, MA, MO>& DestinationArray, RF_Type::Size Length);

  /** \brief Copies a range of elements from an BitArray starting
   *         at the first element and pastes them into another
   *         BitArray starting at the first element. The length
   *         is specified as a 32-bit integer.
   *
   * \param DestinationArray The BitArray that receives the data.
   * \param Length A 32-bit unsigned integer that represents
   *               the number of elements to copy.
   */
  void Copy(BitArray<RB, MA, MO>& DestinationArray, RF_Type::Size Length);

  /** \brief Copies a range of elements from an BitArray starting
   *         at the first element and pastes them into another
   *         BitArray starting at the first element. The length
   *         is specified as a 32-bit integer.
   *
   * \param Index A 32-bit unsigned integer that represents
   *              the index in the sourceArray at which
   *              copying begins.
   * \param DestinationArray The BitArray that receives the data.
   * \param DestinationIndex A 32-bit unsigned integer that
   *                         represents the index in the DestinationArray
   *                         at which storing begins.
   * \param Length A 32-bit unsigned integer that represents
   *               the number of elements to copy.
   */
  void Copy(RF_Type::Size Index,
            BitArray<RB, MA, MO>& DestinationArray,
            RF_Type::Size DestinationIndex,
            RF_Type::Size Length);

  /** \brief Changes the number of elements of an array to the
   *        specified new size.
   *
   * \param NewSize The size of the new array.
   */
  void Resize(RF_Type::Size NewSize);

  void Swap(BitArray<RB, MA, MO>& Other);

  BitArray& Set();
  BitArray& Flip();
  BitArray& Reset();
  BitArray& Set(RF_Type::Size Index);
  BitArray& Reset(RF_Type::Size Index);
  BitArray& Flip(RF_Type::Size Index);
  RF_Type::Bool Test(const RF_Type::Size Index) const;

  RF_Type::Size Size() const;

  /// Gets the number of elements contained in the BitArray.
  RF_Type::Size Count() const;

  RF_Type::Bool IsAny() const;
  RF_Type::Bool IsNone() const;

  RF_Mem::AutoPointerArray<RF_Type::Size> GetSetIndices() const;
  RF_Mem::AutoPointerArray<RF_Type::Size> GetUnsetIndices() const;

  BitArray& operator=(const BitArray& Other);
  BitArray& operator&=(const BitArray& Other);
  BitArray& operator|=(const BitArray& Other);
  BitArray& operator^=(const BitArray& Other);
  BitArray& operator<<=(RF_Type::Size Shift);
  BitArray& operator>>=(RF_Type::Size Shift);
  RF_Type::Bool operator[](RF_Type::Size Index) const;
  RF_Type::Bool operator==(const BitArray& Other) const;
  RF_Type::Bool operator!=(const BitArray& Other) const;
  BitArray operator~() const;
  BitArray operator<<(RF_Type::Size Shift) const;
  BitArray operator>>(RF_Type::Size Shift) const;

private:
#pragma region Internal variables and helper functions
  RB m_ContainerInfo;
  RF_Type::UInt8* m_Data;

  /// setup the data part of the class
  RF_Type::Bool InitArray(const RF_Type::Size Length);
#pragma endregion
};

#pragma region Implementation
template <typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>::BitArray()
{
  InitArray(0);
}

template <typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>::BitArray(const BitArray<RB, MA, MO>& Copy)
{
  *this = Copy;
}

template <typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>::BitArray(const RF_Type::Size Length)
{
  InitArray(Length);
}

template <typename RB, typename MA, typename MO>
Memory::AutoPointer<BitArray<RB, MA, MO>>
BitArray<RB, MA, MO>::CreateInstance(const RF_Type::UInt8 CArray[],
                                     const RF_Type::Size Length)
{
  typename Memory::AutoPointer<BitArray<RB, MA, MO>> arr(
      MA::template New<BitArray<RB, MA, MO>>());
  if(arr.Get() != 0)  // out of memory check
  {
    if(arr->InitArray(Length))
      MO::Copy(arr->m_Data, CArray, arr->m_ContainerInfo.ByteSize());
    else  // something was going wrong, clean up
      arr.Reset();
  }
  return arr;
}

template <typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>::~BitArray()
{
  if(m_Data != nullptr)
  {
    MA::FreeArray(m_Data);
    m_Data = nullptr;
  }
}

template <typename RB, typename MA, typename MO>
RF_Type::Size BitArray<RB, MA, MO>::Count() const
{
  return m_ContainerInfo.elementCount;
}

template <typename RB, typename MA, typename MO>
Memory::AutoPointer<BitArray<RB, MA, MO>> BitArray<RB, MA, MO>::Clone() const
{
  Memory::AutoPointer<BitArray<RB, MA, MO>> result(
      new BitArray(m_ContainerInfo.elementCount));
  MO::Copy(result->m_Data, m_Data, m_ContainerInfo.ByteSize());
  return result;
}

template <typename RB, typename MA, typename MO>
RF_Type::Bool
BitArray<RB, MA, MO>::ConstrainedCopy(RF_Type::Size SourceIndex,
                                      BitArray<RB, MA, MO>& DestinationArray,
                                      RF_Type::Size DestinationIndex,
                                      RF_Type::Size Length)
{
  if(m_ContainerInfo.elementCount < SourceIndex + Length)
    return false;
  if(DestinationArray.m_ContainerInfo.elementCount < DestinationIndex + Length)
    return false;
  // byte aligned and a multiple of 1 byte, simply copy byte by byte
  if((SourceIndex & 7) == 0 && (DestinationIndex & 7) == 0 && (Length & 7) == 0)
  {
    MO::Move(&DestinationArray.m_Data[DestinationIndex], &m_Data[SourceIndex],
             Length);
  }
  else
  {  // some of the conditions failed copy value bit by bit
    for(RF_Type::Size i = 0; i < Length; ++i)
    {
      if(Test(SourceIndex + i))
        DestinationArray.Set(DestinationIndex + i);
      else
        DestinationArray.Reset(DestinationIndex + i);
    }
  }

  return true;
}

template <typename RB, typename MA, typename MO>
RF_Type::Bool
BitArray<RB, MA, MO>::ConstrainedCopy(BitArray<RB, MA, MO>& DestinationArray,
                                      RF_Type::Size Length)
{
  return ConstrainedCopy(0, DestinationArray, 0, Length);
}

template <typename RB, typename MA, typename MO>
void BitArray<RB, MA, MO>::Copy(BitArray<RB, MA, MO>& DestinationArray,
                                RF_Type::Size Length)
{
  Copy(0, DestinationArray, 0, Length);
}

template <typename RB, typename MA, typename MO>
void BitArray<RB, MA, MO>::Copy(RF_Type::Size Index,
                                BitArray<RB, MA, MO>& DestinationArray,
                                RF_Type::Size DestinationIndex,
                                RF_Type::Size Length)
{
  RF_ASSERT(m_ContainerInfo.elementCount >= Index + Length, "");
  RF_ASSERT(DestinationArray.m_ContainerInfo.elementCount >=
             DestinationIndex + Length,
         "");
  MO::Move(&DestinationArray.m_Data[DestinationIndex], &m_Data[Index], Length);
}

template <typename RB, typename MA, typename MO>
void BitArray<RB, MA, MO>::Resize(RF_Type::Size NewSize)
{
  InitArray(NewSize);

  if(NewSize != m_ContainerInfo.elementCount)
  {
    RF_Type::UInt8* data = MA::template NewArray<RF_Type::UInt8>(NewSize);
    MO::Copy(data, m_Data,
             Math::Integer<RF_Type::UInt32>::Min(m_ContainerInfo.elementCount,
                                                 NewSize));
    MA::FreeArray(m_Data);
    m_Data = data;
    m_ContainerInfo.elementCount = NewSize;
  }
}

template <typename RB, typename MA, typename MO>
void BitArray<RB, MA, MO>::Swap(BitArray<RB, MA, MO>& Other)
{
  RF_Type::UInt8* tmpData = m_Data;
  m_Data = Other.m_Data;
  Other.m_Data = tmpData;

  RF_Type::Size tmpCount = m_ContainerInfo.elementCount;
  m_ContainerInfo.elementCount = Other.m_ContainerInfo.elementCount;
  Other.m_ContainerInfo.elementCount = tmpCount;
}

template <typename RB, typename MA, typename MO>
RF_Type::Bool BitArray<RB, MA, MO>::Test(const RF_Type::Size Index) const
{
  RF_ASSERT(Index < m_ContainerInfo.elementCount, "Out of bound.");
  RF_Type::Size ind = m_ContainerInfo.BlockIndex(Index);
  return m_Data[ind] & (1 << m_ContainerInfo.BlockOffset(Index));
}

template <typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>& BitArray<RB, MA, MO>::Set(const RF_Type::Size Index)
{
  RF_ASSERT(Index < m_ContainerInfo.elementCount, "Out of bound.");
  RF_Type::Size ind = m_ContainerInfo.BlockIndex(Index);
  m_Data[ind] |= 1 << m_ContainerInfo.BlockOffset(Index);
  return *this;
}

template <typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>& BitArray<RB, MA, MO>::Reset(const RF_Type::Size Index)
{
  RF_ASSERT(Index < m_ContainerInfo.elementCount, "Out of bound.");
  RF_Type::Size ind = m_ContainerInfo.BlockIndex(Index);
  m_Data[ind] &= ~(1 << m_ContainerInfo.BlockOffset(Index));
  return *this;
}

template <typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>& BitArray<RB, MA, MO>::Flip(const RF_Type::Size Index)
{
  RF_ASSERT(Index < m_ContainerInfo.elementCount, "Out of bound.");
  RF_Type::Size ind = m_ContainerInfo.BlockIndex(Index);
  m_Data[ind] ^= 1 << m_ContainerInfo.BlockOffset(Index);
  return *this;
}

template <typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>& BitArray<RB, MA, MO>::Flip()
{
  for(RF_Type::Size i = 0, end = m_ContainerInfo.BlockCount(); i < end; ++i)
  {
    m_Data[i] = ~m_Data[i];
  }
  return *this;
}

template <typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>& BitArray<RB, MA, MO>::Set()
{
  RF_SysMem::Set(m_Data, 0xff, m_ContainerInfo.ByteSize());
  return *this;
}

template <typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>& BitArray<RB, MA, MO>::Reset()
{
  RF_SysMem::Set(m_Data, 0x00, m_ContainerInfo.ByteSize());
  return *this;
}

template <typename RB, typename MA, typename MO>
RF_Mem::AutoPointerArray<RF_Type::Size>
BitArray<RB, MA, MO>::GetSetIndices() const
{
  RF_Mem::AutoPointerArray<RF_Type::Size> result;
  RF_Type::Size hits = 0;
  for(RF_Type::Size i = 0, end = m_ContainerInfo.elementCount; i < end; ++i)
  {
    if(Test(i))
    {
      ++hits;
    }
  }
  result.New(hits);
  hits = 0;
  for(RF_Type::Size i = 0, end = m_ContainerInfo.elementCount; i < end; ++i)
  {
    if(Test(i))
    {
      result[hits] = i;
      ++hits;
    }
  }
  return result;
}

template <typename RB, typename MA, typename MO>
RF_Mem::AutoPointerArray<RF_Type::Size>
BitArray<RB, MA, MO>::GetUnsetIndices() const
{
  RF_Mem::AutoPointerArray<RF_Type::Size> result;
  RF_Type::Size hits = 0;
  for(RF_Type::Size i = 0, end = m_ContainerInfo.elementCount; i < end; ++i)
  {
    if(!Test(i))
    {
      ++hits;
    }
  }
  result.New(hits);
  hits = 0;
  for(RF_Type::Size i = 0, end = m_ContainerInfo.elementCount; i < end; ++i)
  {
    if(!Test(i))
    {
      result[hits] = i;
      ++hits;
    }
  }
  return result;
}

template <typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>& BitArray<RB, MA, MO>::
operator=(const BitArray<RB, MA, MO>& Other)
{
  InitArray(Other.m_ContainerInfo.elementCount);
  for(RF_Type::Size i = 0, end = m_ContainerInfo.BlockCount(); i < end; ++i)
  {
    m_Data[i] = Other.m_Data[i];
  }
  return *this;
}

template <typename RB, typename MA, typename MO>
RF_Type::Bool BitArray<RB, MA, MO>::operator[](RF_Type::Size Index) const
{
  return Test(Index);
}

template <typename RB, typename MA, typename MO>
RF_Type::Bool BitArray<RB, MA, MO>::operator==(const BitArray& Other) const
{
  RF_Type::Bool result = true;
  for(RF_Type::Size i = 0, end = m_ContainerInfo.BlockCount(); i < end; ++i)
  {
    result &= m_Data[i] == Other.m_Data[i];
  }
  return result;
}

template <typename RB, typename MA, typename MO>
RF_Type::Bool BitArray<RB, MA, MO>::operator!=(const BitArray& Other) const
{
  RF_Type::Bool result = true;
  for(RF_Type::Size i = 0, end = m_ContainerInfo.BlockCount(); i < end; ++i)
  {
    result &= m_Data[i] == Other.m_Data[i];
  }
  return !result;
}

template <typename RB, typename MA, typename MO>
RF_Type::Bool BitArray<RB, MA, MO>::InitArray(const RF_Type::Size Length)
{
  m_Data = nullptr;

  if(Length > 0)
  {
    m_ContainerInfo.elementCount = Length;
    m_Data = MA::template NewArray<RF_Type::UInt8>(m_ContainerInfo.ByteSize());
    if(m_Data == nullptr)
    {
      return false;
    }
    Reset();
  }
  return true;
}
#pragma endregion

}  // namespace RadonFramework::Collections

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif  // RF_COLLECTIONSBITARRAY_HPP