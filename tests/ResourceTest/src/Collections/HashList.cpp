#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp"
#include "RadonFramework/Collections/HashList.hpp"

#pragma warning(disable : 4996) // vc++ raise a security warning because of uninitialized_copy
#include <RadonFramework/backend/google/sparse_hash_map>
#include <RadonFramework/backend/google/dense_hash_map>
using SPARSEHASH_HASH;

namespace RadonFramework { namespace Diagnostics { namespace Debugging { namespace UnitTest {

class HashListTest:public TestSuite
{
public:
    static const RF_Type::UInt32 FETCHES=10000000;

    RF_Collect::HashList hashList;
    typedef google::sparse_hash_map<RF_Type::UInt32, void*, SPARSEHASH_HASH<RF_Type::UInt32>, STL_NAMESPACE::equal_to<RF_Type::UInt32>> sparseType;
    sparseType sparse;
    typedef google::dense_hash_map<RF_Type::UInt32, void*, SPARSEHASH_HASH<RF_Type::UInt32>, STL_NAMESPACE::equal_to<RF_Type::UInt32>> denseType;
    denseType dense;

    HashListTest()
    :TestSuite("RadonFramework::Collections::HashList")
    {
        AddTest(MakeDelegate(this, &HashListTest::FetchSuccessfulTiming),
            "HashListTest::FetchSuccessfulTiming", 
            "Test successful access(10000000x) on 5000 elements");
        AddTest(MakeDelegate(this, &HashListTest::FetchMixedTiming),
                "HashListTest::FetchMixedTiming",
                "Test both success and failing access(10000000x) on 5000 elements");
        AddTest(MakeDelegate(this, &HashListTest::FetchSuccessfulTimingSparse),
                "HashListTest::FetchSuccessfulTimingSparse",
                "Test successful access(10000000x) on 5000 elements");
        AddTest(MakeDelegate(this, &HashListTest::FetchMixedTimingSparse),
                "HashListTest::FetchMixedTimingSparse",
                "Test both success and failing access(10000000x) on 5000 elements");
        AddTest(MakeDelegate(this, &HashListTest::FetchSuccessfulTimingDense),
                "HashListTest::FetchSuccessfulTimingDense",
                "Test successful access(10000000x) on 5000 elements");
        AddTest(MakeDelegate(this, &HashListTest::FetchMixedTimingDense),
                "HashListTest::FetchMixedTimingDense",
                "Test both success and failing access(10000000x) on 5000 elements");
    }

    void SetUp()
    {
        dense.set_empty_key(0);
        dense.set_deleted_key(-1);
        RF_Type::UInt32 hash = 33492185;
        hashList.Reserve(5000);
        sparse.resize(5000);
        dense.resize(5000);
        void* ptr;
        for (RF_Type::Size i = 0; i < 5000; ++i)
        {
            hashList.Add(hash + i * 152037,0);
            sparse.insert(sparseType::value_type(hash + i * 152037, 0));
            dense.insert(denseType::value_type(hash + i * 152037,0));
        }
    }

    RF_Type::Bool FetchSuccessfulTiming()
    {
        for(RF_Type::Size i = 0; i<FETCHES; ++i)
            hashList.ContainsKey(33492185);
        return true;
    }

    RF_Type::Bool FetchMixedTiming()
    {
        RF_Type::UInt32 hash = 33492185;
        for(RF_Type::Size i = 0; i < FETCHES; ++i){
            hashList.ContainsKey(hash + (i%5000) * 152032 - (i % 2));
        }
        return true;
    }

    RF_Type::Bool FetchSuccessfulTimingSparse()
    {
        for(RF_Type::Size i = 0; i<FETCHES; ++i)
            sparse.find(33492185);
        return true;
    }

    RF_Type::Bool FetchMixedTimingSparse()
    {
        RF_Type::UInt32 hash = 33492185;
        for(RF_Type::Size i = 0; i < FETCHES; ++i){
            sparse.find(hash + (i % 5000) * 152032 - (i % 2));
        }
        return true;
    }

    RF_Type::Bool FetchSuccessfulTimingDense()
    {
        for(RF_Type::Size i = 0; i<FETCHES; ++i)
            dense.find(33492185);
        return true;
    }

    RF_Type::Bool FetchMixedTimingDense()
    {
        RF_Type::UInt32 hash = 33492185;
        for(RF_Type::Size i = 0; i < FETCHES; ++i){
            dense.find(hash + (i % 5000) * 152032 - (i % 2));
        }
        return true;
    }
};

HashListTest HashListTestInstance;

} } } }