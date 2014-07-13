#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Collections/Algorithm/FindAll.hpp>

#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Collections/Enumerator.hpp>
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
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Collections::Algorithm;
using namespace RadonFramework::Collections;

class FindAllTest: public TestSuite
{
public:
    FindAllTest()
    :TestSuite("RadonFramework::Collections::Algorithm::FindAll-Test")
    {
        AddTest(MakeDelegate(this, &FindAllTest::CustomCompareFunction),
            "FindAllTest::CustomCompareFunction",
            "Search on collection with custom compare function.");

    }

    bool CustomCompareFunction()
    {
        Array<UInt32> vec(3);
        vec.Item(0, 3);
        vec.Item(1, 2);
        vec.Item(2, 3);
        RadonFramework::Memory::AutoPointerArray<Size> results;
        results = FindAll(vec, [](Array<UInt32>::EnumeratorType& Enum)->Bool {return *Enum == 3; });
        return results.Count() == 2;
    }
};

FindAllTest collectionsAlgorithmFindAllTestInstance;