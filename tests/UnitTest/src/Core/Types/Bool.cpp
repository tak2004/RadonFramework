#include <RadonFramework/Diagnostics/Test/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Test/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Diagnostics::Test::UnitTest;
using namespace RadonFramework::Memory;

class BoolTest:public TestSuite
{
public:
    BoolTest()
    :TestSuite("RadonFramework::Core::Types::Bool-Test"_rfs)
    {
        AddTest(MakeDelegate(this, &BoolTest::Assign),
            "BoolTest::Assign"_rfs, "Assign"_rfs);
    }

    Bool Assign()
    {
        Bool a=true;
        Bool b=false;
        b=a;
        return b==true;
    }
};

BoolTest BoolTestInstance;
