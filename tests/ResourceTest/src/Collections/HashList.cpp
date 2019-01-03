#include "RadonFramework/Collections/HashList.hpp"
#include "RadonFramework/Diagnostics/Test/UnitTest/TestSuite.hpp"
#include "RadonFramework/Diagnostics/Test/UnitTest/UnitTest.hpp"

#pragma warning(disable : 4996)  // vc++ raise a security warning because of
                                 // uninitialized_copy
#include <RadonFramework/backend/google/dense_hash_map>
#include <RadonFramework/backend/google/sparse_hash_map>
using SPARSEHASH_HASH;

namespace RadonFramework::Diagnostics::Test::UnitTest
{
class HashListTest : public TestSuite
{
public:
  static const RF_Type::UInt32 FETCHES = 100000;

  RF_Collect::HashList hashList;
  RF_Collect::HashList hashList10;
  typedef google::sparse_hash_map<RF_Type::UInt32,
                                  void*,
                                  SPARSEHASH_HASH<RF_Type::UInt32>,
                                  STL_NAMESPACE::equal_to<RF_Type::UInt32>>
      sparseType;
  sparseType sparse;
  sparseType sparse10;
  typedef google::dense_hash_map<RF_Type::UInt32,
                                 void*,
                                 SPARSEHASH_HASH<RF_Type::UInt32>,
                                 STL_NAMESPACE::equal_to<RF_Type::UInt32>>
      denseType;
  denseType dense;
  denseType dense10;

  HashListTest() : TestSuite("RadonFramework::Collections::HashList"_rfs)
  {
    AddTest(MakeDelegate(this, &HashListTest::FetchSuccessfulTiming),
            "HashListTest::FetchSuccessfulTiming"_rfs,
            "Test successful access(100000x) on 5000 elements"_rfs);
    AddTest(
        MakeDelegate(this, &HashListTest::FetchMixedTiming),
        "HashListTest::FetchMixedTiming"_rfs,
        "Test both success and failing access(100000x) on 5000 elements"_rfs);
    AddTest(MakeDelegate(this, &HashListTest::FetchSuccessfulTimingSparse),
            "HashListTest::FetchSuccessfulTimingSparse"_rfs,
            "Test successful access(100000x) on 5000 elements"_rfs);
    AddTest(
        MakeDelegate(this, &HashListTest::FetchMixedTimingSparse),
        "HashListTest::FetchMixedTimingSparse"_rfs,
        "Test both success and failing access(100000x) on 5000 elements"_rfs);
    AddTest(MakeDelegate(this, &HashListTest::FetchSuccessfulTimingDense),
            "HashListTest::FetchSuccessfulTimingDense"_rfs,
            "Test successful access(100000x) on 5000 elements"_rfs);
    AddTest(
        MakeDelegate(this, &HashListTest::FetchMixedTimingDense),
        "HashListTest::FetchMixedTimingDense"_rfs,
        "Test both success and failing access(100000x) on 5000 elements"_rfs);

    AddTest(MakeDelegate(this, &HashListTest::FetchSuccessfulTiming10),
            "HashListTest::FetchSuccessfulTiming10"_rfs,
            "Test successful access(100000x) on 50000 elements"_rfs);
    AddTest(
        MakeDelegate(this, &HashListTest::FetchMixedTiming10),
        "HashListTest::FetchMixedTiming10"_rfs,
        "Test both success and failing access(100000x) on 50000 elements"_rfs);
    AddTest(MakeDelegate(this, &HashListTest::FetchSuccessfulTimingSparse10),
            "HashListTest::FetchSuccessfulTimingSparse10"_rfs,
            "Test successful access(100000x) on 50000 elements"_rfs);
    AddTest(
        MakeDelegate(this, &HashListTest::FetchMixedTimingSparse10),
        "HashListTest::FetchMixedTimingSparse10"_rfs,
        "Test both success and failing access(100000x) on 50000 elements"_rfs);
    AddTest(MakeDelegate(this, &HashListTest::FetchSuccessfulTimingDense10),
            "HashListTest::FetchSuccessfulTimingDense10"_rfs,
            "Test successful access(100000x) on 50000 elements"_rfs);
    AddTest(
        MakeDelegate(this, &HashListTest::FetchMixedTimingDense10),
        "HashListTest::FetchMixedTimingDense10"_rfs,
        "Test both success and failing access(100000x) on 50000 elements"_rfs);
  }

  void SetUp()
  {
    dense.set_empty_key(0);
    dense.set_deleted_key(-1);
    RF_Type::UInt32 hash = 33492185;
    hashList.Reserve(5000);
    sparse.resize(5000);
    dense.resize(5000);
    for(RF_Type::Size i = 0; i < 5000; ++i)
    {
      hashList.Add(hash + i * 152037, 0);
      sparse.insert(sparseType::value_type(hash + i * 152037, 0));
      dense.insert(denseType::value_type(hash + i * 152037, 0));
    }

    dense10.set_empty_key(0);
    dense10.set_deleted_key(-1);
    hashList10.Reserve(50000);
    sparse10.resize(50000);
    dense10.resize(50000);
    for(RF_Type::Size i = 0; i < 50000; ++i)
    {
      hashList10.Add(hash + i * 152037, 0);
      sparse10.insert(sparseType::value_type(hash + i * 152037, 0));
      dense10.insert(denseType::value_type(hash + i * 152037, 0));
    }
  }

  RF_Type::Bool FetchSuccessfulTiming()
  {
    for(RF_Type::Size i = 0; i < FETCHES; ++i)
      hashList.ContainsKey(33492185);
    return true;
  }

  RF_Type::Bool FetchMixedTiming()
  {
    RF_Type::UInt32 hash = 33492185;
    for(RF_Type::Size i = 0; i < FETCHES; ++i)
    {
      hashList.ContainsKey(hash + (i % 5000) * 152032 - (i % 2));
    }
    return true;
  }

  RF_Type::Bool FetchSuccessfulTimingSparse()
  {
    for(RF_Type::Size i = 0; i < FETCHES; ++i)
      sparse.find(33492185);
    return true;
  }

  RF_Type::Bool FetchMixedTimingSparse()
  {
    RF_Type::UInt32 hash = 33492185;
    for(RF_Type::Size i = 0; i < FETCHES; ++i)
    {
      sparse.find(hash + (i % 5000) * 152032 - (i % 2));
    }
    return true;
  }

  RF_Type::Bool FetchSuccessfulTimingDense()
  {
    for(RF_Type::Size i = 0; i < FETCHES; ++i)
      dense.find(33492185);
    return true;
  }

  RF_Type::Bool FetchMixedTimingDense()
  {
    RF_Type::UInt32 hash = 33492185;
    for(RF_Type::Size i = 0; i < FETCHES; ++i)
    {
      dense.find(hash + (i % 5000) * 152032 - (i % 2));
    }
    return true;
  }

  RF_Type::Bool FetchSuccessfulTiming10()
  {
    for(RF_Type::Size i = 0; i < FETCHES; ++i)
      hashList10.ContainsKey(33492185);
    return true;
  }

  RF_Type::Bool FetchMixedTiming10()
  {
    RF_Type::UInt32 hash = 33492185;
    for(RF_Type::Size i = 0; i < FETCHES; ++i)
    {
      hashList10.ContainsKey(hash + (i % 5000) * 152032 - (i % 2));
    }
    return true;
  }

  RF_Type::Bool FetchSuccessfulTimingSparse10()
  {
    for(RF_Type::Size i = 0; i < FETCHES; ++i)
      sparse10.find(33492185);
    return true;
  }

  RF_Type::Bool FetchMixedTimingSparse10()
  {
    RF_Type::UInt32 hash = 33492185;
    for(RF_Type::Size i = 0; i < FETCHES; ++i)
    {
      sparse10.find(hash + (i % 5000) * 152032 - (i % 2));
    }
    return true;
  }

  RF_Type::Bool FetchSuccessfulTimingDense10()
  {
    for(RF_Type::Size i = 0; i < FETCHES; ++i)
      dense10.find(33492185);
    return true;
  }

  RF_Type::Bool FetchMixedTimingDense10()
  {
    RF_Type::UInt32 hash = 33492185;
    for(RF_Type::Size i = 0; i < FETCHES; ++i)
    {
      dense10.find(hash + (i % 5000) * 152032 - (i % 2));
    }
    return true;
  }
};

HashListTest HashListTestInstance;

}  // namespace RadonFramework::Diagnostics::Test::UnitTest