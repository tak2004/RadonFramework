#ifndef RF_CORE_POLICIES_LAZYRESIZE_HPP
#define RF_CORE_POLICIES_LAZYRESIZE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Core::Policies
{
// all not specialized cased are forbidden as BLOCKSIZE
template <int BLOCKSIZE>
struct LazyResizeTraits
{
  struct AllowedBlockSize;
};

// 1 byte
template <>
struct LazyResizeTraits<8>
{
  struct AllowedBlockSize
  {
  };
};

// 2 byte
template <>
struct LazyResizeTraits<16>
{
  struct AllowedBlockSize
  {
  };
};

// 4 byte
template <>
struct LazyResizeTraits<32>
{
  struct AllowedBlockSize
  {
  };
};

// 8 byte
template <>
struct LazyResizeTraits<64>
{
  struct AllowedBlockSize
  {
  };
};

template <int BLOCKSIZE, int ELEMENTSIZEINBITS>
struct LazyResize : private LazyResizeTraits<BLOCKSIZE>::AllowedBlockSize
{
  void Init();
  void Free();
  Types::Size ByteSize() const;
  Types::Size BlockCount() const;
  void Resize(Types::Size NewElementCount);
  Types::Size BlockIndex(Types::Size ElementIndex) const;
  /** Return the bit index relative to the right side.
   * To access ElementIndex bit in Block use 0x01 << BlockIndex(n).
   */
  Types::Size BlockOffset(Types::Size ElementIndex) const;

  Types::Size elementCount;
};

template <int BLOCKSIZE, int ELEMENTSIZEINBITS>
inline void LazyResize<BLOCKSIZE, ELEMENTSIZEINBITS>::Init()
{
  elementCount = 0;
}

template <int BLOCKSIZE, int ELEMENTSIZEINBITS>
inline void LazyResize<BLOCKSIZE, ELEMENTSIZEINBITS>::Free()
{
}

template <int BLOCKSIZE, int ELEMENTSIZEINBITS>
inline Types::Size LazyResize<BLOCKSIZE, ELEMENTSIZEINBITS>::ByteSize() const
{
  return ((elementCount * ELEMENTSIZEINBITS) + 7) / 8;
}

template <int BLOCKSIZE, int ELEMENTSIZEINBITS>
inline Types::Size LazyResize<BLOCKSIZE, ELEMENTSIZEINBITS>::BlockCount() const
{
  return ((elementCount * ELEMENTSIZEINBITS) + (BLOCKSIZE - 1)) / BLOCKSIZE;
}

template <int BLOCKSIZE, int ELEMENTSIZEINBITS>
inline void
LazyResize<BLOCKSIZE, ELEMENTSIZEINBITS>::Resize(Types::Size NewElementCount)
{
  elementCount = NewElementCount;
}

template <int BLOCKSIZE, int ELEMENTSIZEINBITS>
inline Types::Size LazyResize<BLOCKSIZE, ELEMENTSIZEINBITS>::BlockIndex(
    Types::Size ElementIndex) const
{
  return ElementIndex / BLOCKSIZE;
}

template <int BLOCKSIZE, int ELEMENTSIZEINBITS>
inline Types::Size LazyResize<BLOCKSIZE, ELEMENTSIZEINBITS>::BlockOffset(
    Types::Size ElementIndex) const
{
  return (BLOCKSIZE - 1) - (ElementIndex & (BLOCKSIZE - 1));
}

}  // namespace RadonFramework::Core::Policies

#endif  // RF_CORE_POLICIES_LAZYRESIZE_HPP