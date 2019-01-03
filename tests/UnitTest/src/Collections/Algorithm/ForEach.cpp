#include <RadonFramework/Diagnostics/Test/UnitTest/TestSuite.hpp>
#include <RadonFramework/Collections/Algorithm/ForEach.hpp>

#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Collections/AVLTree.hpp>
#include <RadonFramework/Collections/BitArray.hpp>
#include <RadonFramework/Collections/BitSet.hpp>
#include <RadonFramework/Collections/DataTree.hpp>
#include <RadonFramework/Collections/HashMap.hpp>
#include <RadonFramework/Collections/Hashtable.hpp>
#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/Collections/Pair.hpp>
#include <RadonFramework/Collections/Queue.hpp>
#include <RadonFramework/Collections/Stack.hpp>
#include <RadonFramework/Collections/Tree.hpp>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Diagnostics::Test::UnitTest;
using namespace RadonFramework::Collections::Algorithm;
using namespace RadonFramework::Collections;

class ForEachTest: public TestSuite
{
public:
    ForEachTest()
    :TestSuite("RadonFramework::Collections::Algorithm::ForEach-Test"_rfs)
    {
        AddTest(MakeDelegate(this, &ForEachTest::CustomCompareFunction),
            "ForEachTest::CustomCompareFunction"_rfs,
            "Search on collection with custom compare function."_rfs);
        AddTest(MakeDelegate(this, &ForEachTest::CustomCompareFunction2),
            "ForEachTest::CustomCompareFunction2"_rfs,
            "Search on collection with custom compare function2."_rfs);
    }

    bool CustomCompareFunction()
    {
        Array<UInt32> vec(3);
        vec.Item(0, 1);
        vec.Item(1, 2);
        vec.Item(2, 3);
        ForEach(vec, [](Array<UInt32>::EnumeratorType& Enum){++(*Enum);});
        return 2 == vec(0) && 3 == vec(1) && 4 == vec(2);
    }

    void Increase(UInt32& Value)
    {
        ++Value;
    }

    bool CustomCompareFunction2()
    {
        Array<UInt32> vec(3);
        vec.Item(0, 1);
        vec.Item(1, 2);
        vec.Item(2, 3);
        vec.ForEach(MakeDelegate(this, &ForEachTest::Increase));
        return 2 == vec(0) && 3 == vec(1) && 4 == vec(2);
    }
};

ForEachTest collectionsAlgorithmForEachTestInstance;