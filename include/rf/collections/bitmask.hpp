#pragma once
#include <rf/core/types/builtin.hpp>
#include <rf/core/types/memory.hpp>

namespace rf {
class Bitmask {
public:
  static Bitmask CreateInstance(const u8 *Bytes, size Bits);
  /// Create an instance of the Bitmask class.
  Bitmask();
  /** \brief Create a copy of a given Bitmask.
   *
   * The copy constructor make a deep copy.
   *
   * \param Copy The object from which the copy will be done.
   */
  Bitmask(const Bitmask &Copy);
  /** \brief Create a Bitmask.
   *
   * \param Length The size of the Bitmask in bits.
   */
  Bitmask(size Length);
  ~Bitmask();

  /** \brief Creates a deep copy of the Bitmask.
   *
   * A deep copy of an Bitmask copies the elements
   * and everything directly or indirectly referenced by the
   * elements.
   *
   * This method is an O(n) operation, where n is Count/8.
   */
  Bitmask clone() const;
  /** \brief Copies a range of elements from an Bitmask starting
   *         at the specified source index and pastes them to
   *         another Bitmask starting at the specified destination
   *         index. Guarantees that all changes are undone if
   *         the copy does not succeed completely.
   *
   * \param SourceIndex The index in the source Bitmask at which
   *                    copying begins.
   * \param DestinationArray The Bitmask that receives the data.
   * \param DestinationIndex The index in the destination Bitmask 
   *                         at which storing begins.
   * \param Length The number of elements to copy.
   */
  bool Copy(size SourceIndex, Bitmask &DestinationArray,
                       size DestinationIndex, size Length);
  /** \brief Copies a range of elements from an Bitmask starting
   *         at the specified source index and pastes them to
   *         another Bitmask starting at the specified destination
   *         index. Guarantees that all changes are undone if
   *         the copy does not succeed completely.
   *
   * \param DestinationArray The Bitmask that receives the data.
   * \param Length The number of elements to copy.
   */
   bool Copy(Bitmask& DestinationArray, size Length);
  
  /** \brief Changes the number of elements of an array to the
   *        specified new size.
   *
   * \param NewSize The size of the new array.
   */
   void Resize(size NewSize);

   void Swap(Bitmask& Other);
 
   Bitmask& Set();
   Bitmask& Flip();
   Bitmask& Reset();
   Bitmask& Set(size Index);
   Bitmask& Reset(size Index);
   Bitmask& Flip(size Index);
   bool Test(size Index) const;
   size Size() const;
   /// Gets the number of elements contained in the Bitmask.
   size Count() const;
   bool IsAny() const;
   bool IsNone() const;
   size GetSetIndices(Array<size>& Indices) const;
   size GetUnsetIndices(Array<size>& Indices) const;
 
   Bitmask& operator=(const Bitmask& Other);
   Bitmask& operator&=(const Bitmask& Other);
   Bitmask& operator|=(const Bitmask& Other);
   Bitmask& operator^=(const Bitmask& Other);
   Bitmask& operator<<=(size Shift);
   Bitmask& operator>>=(size Shift);
   bool operator[](size Index) const;
   bool operator==(const Bitmask& Other) const;
   bool operator!=(const Bitmask& Other) const;
   Bitmask operator~() const;
   Bitmask operator<<(size Shift) const;
   Bitmask operator>>(size Shift) const;
protected:
  mem data;
  size bits;
};
} // namespace rf