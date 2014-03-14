#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Memory;

class BoolTest:public TestSuite
{
    public:
        BoolTest()
        :TestSuite("RadonFramework::Core::Types::Bool-Test")
        {
            AddTest(MakeDelegate(this,&BoolTest::Assign),"Assign");
        }

        RadonFramework::Core::Types::Bool Assign()
        {
            Bool a=true;
            Bool b=false;
            b=a;
            return b==true;
        }
};

BoolTest BoolTestInstance;
