#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

//#include <RadonFramework/Collections/BitArray.hpp>

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
            /*
            AddTest(MakeDelegate(this,&BitArrayTest::Constructor),
                "Constructor");

            AddTest(MakeDelegate(this,&BitArrayTest::CopyConstructor),
                "Copy constructor");

            AddTest(MakeDelegate(this,&BitArrayTest::Constructor1Dimension),
                "Constructor which create a 1 dimensional BitArray.");
                        
            AddTest(MakeDelegate(this,&BitArrayTest::Constructor1DimensionC),
                "Constructor which copy from a 1 dimensional c BitArray.");

            AddTest(MakeDelegate(this,&BitArrayTest::Reverse),
                "Reverses the sequence of the elements in the entire 1D BitArray.");

            AddTest(MakeDelegate(this,&BitArrayTest::Resize),
                "Changes the number of elements of an BitArray to the specified new size.");

            AddTest(MakeDelegate(this,&BitArrayTest::Copy),
                "Copies a range of elements from an BitArray to an other.");

            AddTest(MakeDelegate(this,&BitArrayTest::ConstrainedCopy),
                "Copies a range of elements from an BitArray to an other if the \
                BitArrays have the same structure.");

            AddTest(MakeDelegate(this,&BitArrayTest::Clone),
                "Creates a shallow copy of the BitArray.");*/
        }
        /*
        Bool Constructor()
        {
            BitArray m_BitArray;
            return (0==m_BitArray.Count());
        }

        Bool CopyConstructor()
        {
            BitArray BitArray1(1);
            BitArray BitArray2(BitArray1);
            return (1==BitArray1.Count() && 1==BitArray2.Count());
        }

        Bool Constructor1Dimension()
        {
            BitArray BitArray(1);
            return (1==BitArray.Count());
        }

        Bool Constructor1DimensionC()
        {
            AutoPointer<BitArray > m_BitArray;
            // test stack allocation
            UInt32 cBitArray[3]={1,2,3};
            m_BitArray=BitArray::CreateInstance(reinterpret_cast<char*>(cBitArray),96);
            return (m_BitArray);
        }

        Bool Reverse()
        {
            BitArray vec1(3);
            vec1.Set(0,1);
            vec1.Set(1,0);
            vec1.Set(2,0);
            vec1.Reverse();
            return 0==vec1.Get(0) && 0==vec1.Get(1) && 
                   1==vec1.Get(2);
        }

        Bool Resize()
        {
            BitArray vec(1);
            vec.Set(0,1);
            vec.Resize(5);
            vec.Set(1,0);
            vec.Set(2,1);
            vec.Set(3,1);
            vec.Set(4,1);
            vec.Resize(3);
            return 1==vec.Get(0) && 0==vec.Get(1) && 1==vec.Get(2);
        }

        Bool Copy()
        {
            BitArray vec1(2);
            BitArray vec2(2);
            vec1.Set(0,1);
            vec1.Set(1,1);
            vec1.Copy(vec2,2);
            return 1==vec2.Get(0) && 1==vec2.Get(1);
        }
               
        Bool ConstrainedCopy()
        {
            BitArray vec1(2);
            BitArray vec2(2);
            BitArray vec3(3);
            vec1.Set(0,1);
            vec1.Set(1,1);            
            return true==vec1.ConstrainedCopy(vec2,2) && 
                   false==vec1.ConstrainedCopy(vec3,3) &&
                   1==vec2.Get(0) && 1==vec2.Get(1);
        }

        Bool Clone()
        {
            BitArray vec1(2);
            vec1.Set(0,1);
            vec1.Set(1,1);            
            AutoPointer<BitArray > results=vec1.Clone();
            return results && results->Count()==2 && 1==results->Get(0) &&
                   1==results->Get(1);
        }*/
};

BitArrayTest collectionsGenericBitArrayTestInstance;
