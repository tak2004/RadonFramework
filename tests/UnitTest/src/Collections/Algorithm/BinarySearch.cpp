#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Collections/Algorithm/BinarySearch.hpp>
#include <RadonFramework/Collections/Array.hpp>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Collections::Algorithm;
using namespace RadonFramework::Collections;

class BinarySearchTest: public TestSuite
{
    public:
        BinarySearchTest()
        :TestSuite("RadonFramework::Collections::Algorithm::BinarySearch-Test"_rfs)
        {
            AddTest(MakeDelegate(this, &BinarySearchTest::CustomCompareFunction),
                "BinarySearchTest::CustomCompareFunction"_rfs,
                "Search on collection with custom compare function."_rfs);

        }

        bool CustomCompareFunction()
        {
            Bool result=false;
            Array<Int32> data(5);
            data(0)=1;
            data(1)=2;
            data(2)=3;
            data(3)=4;
            data(4)=5;
            ArrayEnumerator<Int32> enumerator=data.GetArrayEnumerator();
            Size index=BinarySearch<Int32>(enumerator, 2);
            return result;
        }
};