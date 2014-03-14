#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;

class MemoryAutoPointerArrayTest:public TestSuite
{
public:
    MemoryAutoPointerArrayTest()
        :TestSuite("RadonFramework::Collections::Stack-Test")
    {
        AddTest(MakeDelegate(this,&MemoryAutoPointerArrayTest::Constructor),"Constructor");
        AddTest(MakeDelegate(this,&MemoryAutoPointerArrayTest::ConstructorOwnerTransfere),"ConstructorOwnerTransfere");
        AddTest(MakeDelegate(this,&MemoryAutoPointerArrayTest::ConstructorCopy),"ConstructorCopy");
    }

    Bool Constructor()
    {
        AutoPointerArray<UInt32> m_APA;
        return 0==m_APA.Count() && 0==m_APA.Get();
    }

    Bool ConstructorOwnerTransfere()
    {
        AutoPointerArray<UInt32> m_APA(new UInt32[4],4);
        return 4==m_APA.Count() && 0!=m_APA.Get();
    }

    Bool ConstructorCopy()
    {
        AutoPointerArray<UInt32> m_APA(new UInt32[4],4);
        AutoPointerArray<UInt32> m_APA1(m_APA);
        return 0==m_APA.Count() && 0==m_APA.Get() && 4==m_APA1.Count() && 0!=m_APA1.Get();
    }
};

MemoryAutoPointerArrayTest memoryAutoPointerArrayTestInstance;
