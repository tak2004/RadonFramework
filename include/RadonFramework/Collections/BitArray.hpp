#ifndef RF_COLLECTIONSBITARRAY_HPP
#define RF_COLLECTIONSBITARRAY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <type_traits>

#include <RadonFramework/Core/Policies/LazyResize.hpp>
#include <RadonFramework/Core/Policies/CMemoryOperation.hpp>
#include <RadonFramework/Core/Policies/CPPAllocator.hpp>
#include <RadonFramework/Math/Integer.hpp>

namespace RadonFramework { namespace Collections {

/** \brief This is a policy based template for BitArrays.
 *
 * \tparam RB Resize behaviour policy
 * \tparam MA Memory allocator policy
 * \tparam MO Memory operation policy
 */
template<typename RB = Core::Policies::LazyResize<8, 1>,
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
    BitArray(const RFTYPE::Size Length);

    /** \brief Creates a BitArray of the specified length.
     *         The data of the BitArray are copied from the C array.
     *         You have to ensure to cleanup the array by yourself!
     *
     * \param CArray An array which commonly provided by C code.
     * \param Length Specify the length of the BitArray in bits.
     */
    static Memory::AutoPointer<BitArray<RB, MA, MO> >
        CreateInstance(const RFTYPE::UInt8 CArray[], const RFTYPE::Size Length);

    ~BitArray();
    
    /** \brief Creates a deep copy of the BitArray.
     *
     * A deep copy of an BitArray copies the elements
     * and everything directly or indirectly referenced by the
     * elements.
     *
     * This method is an O(n) operation, where n is Count/8.
     */
    Memory::AutoPointer<BitArray<RB, MA, MO> > Clone()const;

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
    RFTYPE::Bool ConstrainedCopy(RFTYPE::Size SourceIndex,
        BitArray<RB, MA, MO>& DestinationArray, RFTYPE::Size DestinationIndex,
        RFTYPE::Size Length);

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
    RFTYPE::Bool ConstrainedCopy(BitArray<RB, MA, MO>& DestinationArray,
        RFTYPE::Size Length);

    /** \brief Copies a range of elements from an BitArray starting
     *         at the first element and pastes them into another
     *         BitArray starting at the first element. The length
     *         is specified as a 32-bit integer.
     *
     * \param DestinationArray The BitArray that receives the data.
     * \param Length A 32-bit unsigned integer that represents
     *               the number of elements to copy.
     */
    void Copy(BitArray<RB, MA, MO>& DestinationArray, RFTYPE::Size Length);

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
    void Copy(RFTYPE::Size Index, BitArray<RB, MA, MO>& DestinationArray,
        RFTYPE::Size DestinationIndex, RFTYPE::Size Length);

    /** \brief Changes the number of elements of an array to the
     *        specified new size.
     *
     * \param NewSize The size of the new array.
     */
    void Resize(RFTYPE::Size NewSize);

    void Swap(BitArray<RB, MA, MO>& Other);

    BitArray& Set();
    BitArray& Flip();
    BitArray& Reset();
    BitArray& Set(RFTYPE::Size Index);
    BitArray& Reset(RFTYPE::Size Index);
    BitArray& Flip(RFTYPE::Size Index);
    RFTYPE::Bool Test(const RFTYPE::Size Index)const;

    RFTYPE::Size Size()const;

    /// Gets the number of elements contained in the BitArray.
    RFTYPE::Size Count()const;

    RFTYPE::Bool IsAny()const;
    RFTYPE::Bool IsNone()const;

    Memory::AutoPointerArray<RFTYPE::Size> GetSetIndices()const;
    Memory::AutoPointerArray<RFTYPE::Size> GetUnsetIndices()const;

    BitArray& operator=(const BitArray& Other);
    BitArray& operator&=(const BitArray& Other);
    BitArray& operator|=(const BitArray& Other);
    BitArray& operator^=(const BitArray& Other);
    BitArray& operator<<=(RFTYPE::Size Shift);
    BitArray& operator>>=(RFTYPE::Size Shift);
    RFTYPE::Bool operator[](RFTYPE::Size Index)const;
    RFTYPE::Bool operator==(const BitArray& Other)const;
    RFTYPE::Bool operator!=(const BitArray& Other)const;
    BitArray operator~()const;
    BitArray operator<<(RFTYPE::Size Shift)const;
    BitArray operator>>(RFTYPE::Size Shift)const;
private:
#pragma region Internal variables and helper functions
    RB m_ContainerInfo;
    RFTYPE::UInt8* m_Data;

    /// setup the data part of the class
    RFTYPE::Bool InitArray(const RFTYPE::Size Length);
#pragma endregion
};

#pragma region Implementation
template<typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>::BitArray()
{
    InitArray(0);
}

template<typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>::BitArray(const BitArray<RB, MA, MO>& Copy)
{
    *this = Copy;
}

template<typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>::BitArray(const RFTYPE::Size Length)
{
    InitArray(Length);
}

template<typename RB, typename MA, typename MO>
Memory::AutoPointer<BitArray<RB, MA, MO> > BitArray<RB, MA, MO>::CreateInstance(
    const RFTYPE::UInt8 CArray[], const RFTYPE::Size Length)
{
    typename Memory::AutoPointer<BitArray<RB, MA, MO> > arr(MA::template New<BitArray<RB, MA, MO> >());
    if(arr.Get() != 0) // out of memory check
    {
        if(arr->InitArray(Length))
            MO::Copy(arr->m_Data, CArray, arr->m_ContainerInfo.ByteSize());
        else // something was going wrong, clean up
            arr.Reset();
    }
    return arr;
}

template<typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>::~BitArray()
{
    if(m_Data != 0)
    {
        MA::FreeArray(m_Data);
        m_Data = 0;
    }
}

template<typename RB, typename MA, typename MO>
RFTYPE::Size BitArray<RB, MA, MO>::Count()const
{
    return m_ContainerInfo.elementCount;
}

template<typename RB, typename MA, typename MO>
Memory::AutoPointer<BitArray<RB, MA, MO> > BitArray<RB, MA, MO>::Clone()const
{
    Memory::AutoPointer<BitArray<RB, MA, MO> > result(new BitArray(m_ContainerInfo.elementCount));
    MO::Copy(result->m_Data, m_Data, m_ContainerInfo.ByteSize());
    return result;
}

template<typename RB, typename MA, typename MO>
RFTYPE::Bool BitArray<RB, MA, MO>::ConstrainedCopy(RFTYPE::Size SourceIndex,
    BitArray<RB, MA, MO>& DestinationArray, RFTYPE::Size DestinationIndex,
    RFTYPE::Size Length)
{
    if(m_ContainerInfo.elementCount < SourceIndex + Length)
        return false;
    if(DestinationArray.m_ContainerInfo.elementCount < DestinationIndex + Length)
        return false;
    // byte aligned and a multiple of 1 byte, simply copy byte by byte
    if((SourceIndex & 7) == 0 && (DestinationIndex & 7) == 0 && (Length & 7) == 0)
    {
        MO::Move(&DestinationArray.m_Data[DestinationIndex], &m_Data[SourceIndex], Length);
    }
    else
    {// some of the conditions failed copy value bit by bit
        for(RFTYPE::Size i = 0; i < Length; ++i)
        {
            if(Test(SourceIndex + i))
                DestinationArray.Set(DestinationIndex + i);
            else
                DestinationArray.Reset(DestinationIndex + i);
        }
    }
    
    return true;
}

template<typename RB, typename MA, typename MO>
RFTYPE::Bool BitArray<RB, MA, MO>::ConstrainedCopy(
    BitArray<RB, MA, MO>& DestinationArray,
    RFTYPE::Size Length)
{
    return ConstrainedCopy(0, DestinationArray, 0, Length);
}

template<typename RB, typename MA, typename MO>
void BitArray<RB, MA, MO>::Copy(BitArray<RB, MA, MO>& DestinationArray,
    RFTYPE::Size Length)
{
    Copy(0, DestinationArray, 0, Length);
}

template<typename RB, typename MA, typename MO>
void BitArray<RB, MA, MO>::Copy(RFTYPE::Size Index, BitArray<RB, MA, MO>& DestinationArray,
    RFTYPE::Size DestinationIndex, RFTYPE::Size Length)
{
    Assert(m_ContainerInfo.elementCount >= Index + Length, "");
    Assert(DestinationArray.m_ContainerInfo.elementCount >= DestinationIndex + Length, "");
    MO::Move(&DestinationArray.m_Data[DestinationIndex], &m_Data[Index], Length);
}

template<typename RB, typename MA, typename MO>
void BitArray<RB, MA, MO>::Resize(RFTYPE::Size NewSize)
{
    InitArray(NewSize);

    if(NewSize != m_ContainerInfo.elementCount)
    {
        UInt8* data = MA::template NewArray<UInt8>(NewSize);
        MO::Copy(data, m_Data, Math::Integer<RFTYPE::UInt32>::ClampUpperBound(m_ContainerInfo.elementCount, NewSize));
        MA::FreeArray(m_Data);
        m_Data = data;
        m_ContainerInfo.elementCount = NewSize;
    }
}

template<typename RB, typename MA, typename MO>
void BitArray<RB, MA, MO>::Swap(BitArray<RB, MA, MO>& Other)
{
    T* tmpData = m_Data;
    m_Data = Other.m_Data;
    Other.m_Data = tmpData;

    RFTYPE::Size tmpCount = m_ContainerInfo.elementCount;
    m_ContainerInfo.elementCount = Other.m_ContainerInfo.elementCount;
    Other.m_ContainerInfo.elementCount = tmpCount;
}

template<typename RB, typename MA, typename MO>
RFTYPE::Bool BitArray<RB, MA, MO>::Test(const RFTYPE::Size Index)const
{
    Assert(Index < m_ContainerInfo.elementCount, "Out of bound.");
    RFTYPE::Size ind = m_ContainerInfo.BlockIndex(Index);
    return m_Data[ind] & (1 << m_ContainerInfo.BlockOffset(Index));
}

template<typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>& BitArray<RB, MA, MO>::Set(const RFTYPE::Size Index)
{
    Assert(Index < m_ContainerInfo.elementCount, "Out of bound.");
    RFTYPE::Size ind = m_ContainerInfo.BlockIndex(Index);
    m_Data[ind] |= 1 << m_ContainerInfo.BlockOffset(Index);
    return *this;
}

template<typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>& BitArray<RB, MA, MO>::Reset(const RFTYPE::Size Index)
{
    Assert(Index < m_ContainerInfo.elementCount, "Out of bound.");
    RFTYPE::Size ind = m_ContainerInfo.BlockIndex(Index);
    m_Data[ind] &= ~(1 << m_ContainerInfo.BlockOffset(Index));
    return *this;
}

template<typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>& BitArray<RB, MA, MO>::Flip(const RFTYPE::Size Index)
{
    Assert(Index < m_ContainerInfo.elementCount, "Out of bound.");
    RFTYPE::Size ind = m_ContainerInfo.BlockIndex(Index);
    m_Data[ind] ^= 1 << m_ContainerInfo.BlockOffset(Index);
    return *this;
}

template<typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>& BitArray<RB, MA, MO>::Flip()
{
    for (RFTYPE::Size i = 0, end = m_ContainerInfo.BlockCount(); i < end; ++i)
    {
        m_Data[i] = ~m_Data[i];
    }
    return *this;
}

template<typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>& BitArray<RB, MA, MO>::Set()
{
    RFMEM::Set(m_Data, 0xff, m_ContainerInfo.ByteSize());
    return *this;
}

template<typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>& BitArray<RB, MA, MO>::Reset()
{
    RFMEM::Set(m_Data, 0x00, m_ContainerInfo.ByteSize());
    return *this;
}

template<typename RB, typename MA, typename MO>
Memory::AutoPointerArray<RFTYPE::Size> BitArray<RB, MA, MO>::GetSetIndices() const
{

}

template<typename RB, typename MA, typename MO>
Memory::AutoPointerArray<RFTYPE::Size> BitArray<RB, MA, MO>::GetUnsetIndices() const
{

}

template<typename RB, typename MA, typename MO>
BitArray<RB, MA, MO>& BitArray<RB, MA, MO>::operator=(const BitArray<RB, MA, MO>& Other)
{
    InitArray(Other.m_ContainerInfo.elementCount);
    for(RFTYPE::Size i = 0, end = m_ContainerInfo.BlockCount(); i < end; ++i)
        m_Data[i] = Other.m_Data[i];
    return *this;
}

template<typename RB, typename MA, typename MO>
RFTYPE::Bool BitArray<RB, MA, MO>::InitArray(const RFTYPE::Size Length)
{
    m_Data = 0;

    if(Length > 0)
    {
        m_ContainerInfo.elementCount = Length;
        m_Data = MA::template NewArray<UInt8>(m_ContainerInfo.ByteSize());
        if(m_Data == 0)
            return false;        
    }
    return true;
}
#pragma endregion

} }

#endif // RF_COLLECTIONSBITARRAY_HPP