#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

#include <RadonFramework/Collections/HashList.hpp>
#include <type_traits>

class HashListTest:public RF_Test::TestSuite
{
public:
    HashListTest()
    :TestSuite("RadonFramework::Collections::HashList-Test")
    {
        AddTest(MakeDelegate(this, &HashListTest::Constructor),
            "HashListTest::Constructor", "Constructor");
        AddTest(MakeDelegate(this, &HashListTest::Destructor),
            "HashListTest::Destructor", "Destructor");
        AddTest(MakeDelegate(this, &HashListTest::ContainsKey),
            "HashListTest::ContainsKey", "ContainsKey");
        AddTest(MakeDelegate(this, &HashListTest::Clear),
            "HashListTest::Clear", "Clear");
        AddTest(MakeDelegate(this, &HashListTest::Count),
            "HashListTest::Count", "Count");
        AddTest(MakeDelegate(this, &HashListTest::AccessOperator),
            "HashListTest::AccessOperator", "AccessOperator");
        AddTest(MakeDelegate(this, &HashListTest::Erase),
            "HashListTest::Erase", "Erase");
        AddTest(MakeDelegate(this, &HashListTest::SetEmptyKey),
            "HashListTest::SetEmptyKey", "SetEmptyKey");
        AddTest(MakeDelegate(this, &HashListTest::Clone),
            "HashListTest::Clone", "Clone");
        AddTest(MakeDelegate(this, &HashListTest::EnsureCopyProtection),
            "HashListTest::EnsureCopyProtection", "EnsureCopyProtection");
        AddTest(MakeDelegate(this, &HashListTest::NoExceptions),
            "HashListTest::NoExceptions", "NoExceptions");
    }

    RF_Type::Bool Constructor()
    {
        RF_Type::Bool result = false;
        //result = HashList
        return result;
    }

    RF_Type::Bool Destructor()
    {
        return false;
    }

    RF_Type::Bool ContainsKey()
    {
        return false;
    }

    RF_Type::Bool Clear()
    {
        return false;
    }

    RF_Type::Bool Count()
    {
        return false;
    }

    RF_Type::Bool AccessOperator()
    {
        return false;
    }

    RF_Type::Bool Erase()
    {
        return false;
    }

    RF_Type::Bool SetEmptyKey()
    {
        return false;
    }

    RF_Type::Bool Clone()
    {
        return false;
    }

    RF_Type::Bool EnsureCopyProtection()
    {
        return std::is_copy_assignable<RF_Collect::HashList>::value == false &&
            std::is_copy_constructible<RF_Collect::HashList>::value == false &&
            std::is_move_constructible<RF_Collect::HashList>::value == false;
    }

    RF_Type::Bool NoExceptions()
    {
        return std::is_nothrow_assignable<RF_Collect::HashList, RF_Collect::HashList>::value == true &&
            std::is_nothrow_constructible<RF_Collect::HashList>::value == true &&
            std::is_nothrow_copy_assignable<RF_Collect::HashList>::value == true &&
            std::is_nothrow_copy_constructible<RF_Collect::HashList>::value == true &&
            std::is_nothrow_destructible<RF_Collect::HashList>::value == true &&
            std::is_nothrow_default_constructible<RF_Collect::HashList>::value == true &&
            std::is_nothrow_move_assignable<RF_Collect::HashList>::value == true &&
            std::is_nothrow_move_constructible<RF_Collect::HashList>::value == true;
    }
};

HashListTest HashListTestInstance;
