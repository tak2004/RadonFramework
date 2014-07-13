#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Collections/BitArray.hpp>

#include <RadonFramework/System/Threading/Thread.hpp>

using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;

class BitArrayTest:public TestSuite
{
public:
    BitArrayTest()
    :TestSuite("RadonFramework::Collections::BitArray-Test")
    {        
        AddTest(MakeDelegate(this, &BitArrayTest::Constructor),
            "BitArrayTest::Constructor",
            "Constructor");

        AddTest(MakeDelegate(this, &BitArrayTest::CopyConstructor),
            "BitArrayTest::CopyConstructor",
            "Copy constructor");

        AddTest(MakeDelegate(this, &BitArrayTest::Constructor1Dimension),
            "BitArrayTest::Constructor1Dimension",
            "Constructor which create a 1 dimensional BitArray.");

        AddTest(MakeDelegate(this, &BitArrayTest::Constructor1DimensionC),
            "BitArrayTest::Constructor1DimensionC",
            "Constructor which copy from a 1 dimensional c BitArray.");

        AddTest(MakeDelegate(this, &BitArrayTest::Resize),
            "BitArrayTest::Resize",
            "Changes the number of elements of an BitArray to the specified new size.");

        AddTest(MakeDelegate(this, &BitArrayTest::Copy),
            "BitArrayTest::Copy",
            "Copies a range of elements from an BitArray to an other.");

        AddTest(MakeDelegate(this, &BitArrayTest::ConstrainedCopy),
            "BitArrayTest::ConstrainedCopy",
            "Copies a range of elements from an BitArray to an other if the \
                        BitArrays have the same structure.");

        AddTest(MakeDelegate(this, &BitArrayTest::Clone),
            "BitArrayTest::Clone",
            "Creates a shallow copy of the BitArray.");
    }

    Bool Constructor()
    {
        BitArray<> m_BitArray;
        return (0 == m_BitArray.Count());
    }

    Bool CopyConstructor()
    {
        BitArray<> BitArray1(1);
        BitArray<> BitArray2(BitArray1);
        return (1 == BitArray1.Count() && 1 == BitArray2.Count());
    }

    Bool Constructor1Dimension()
    {
        BitArray<> BitArray(1);
        return (1 == BitArray.Count());
    }

    Bool Constructor1DimensionC()
    {
        AutoPointer<BitArray<> > m_BitArray;
        // test stack allocation
        UInt32 cBitArray[3] = {1, 2, 3};
        m_BitArray = BitArray<>::CreateInstance(reinterpret_cast<UInt8*>(cBitArray), 96);
        return m_BitArray;
    }

    Bool Resize()
    {
        BitArray<> vec(1);
        vec.Set(0);
        vec.Resize(5);
        vec.Reset(1);
        vec.Set(2);
        vec.Set(3);
        vec.Set(4);
        vec.Resize(3);
        return true == vec.Test(0) && false == vec.Test(1) && true == vec.Test(2);
    }

    Bool Copy()
    {
        BitArray<> vec1(2);
        BitArray<> vec2(2);
        vec1.Set(0);
        vec1.Set(1);
        vec1.Copy(vec2, 2);
        return true == vec2.Test(0) && true == vec2.Test(1);
    }

    Bool ConstrainedCopy()
    {
        BitArray<> vec1(2);
        BitArray<> vec2(2);
        BitArray<> vec3(3);
        vec1.Set(0);
        vec1.Set(1);
        return true == vec1.ConstrainedCopy(vec2, 2) &&
            false == vec1.ConstrainedCopy(vec3, 3) &&
            true == vec2.Test(0) && true == vec2.Test(1);
    }

    Bool Clone()
    {
        BitArray<> vec1(2);
        vec1.Set(0);
        vec1.Set(1);
        AutoPointer<BitArray<> > results = vec1.Clone();
        return results && results->Count() == 2 && true == results->Test(0) &&
            true == results->Test(1);
    }
};

BitArrayTest collectionsGenericBitArrayTestInstance;
