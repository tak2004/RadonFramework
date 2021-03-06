#include <RadonFramework/Diagnostics/Test/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Test/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Diagnostics::Test::UnitTest;

class MemoryAutoPointerArrayTest:public TestSuite
{
public:
    MemoryAutoPointerArrayTest()
        :TestSuite("RadonFramework::Collections::Stack-Test"_rfs)
    {
        AddTest(MakeDelegate(this,&MemoryAutoPointerArrayTest::Constructor),
            "MemoryAutoPointerArrayTest::Constructor"_rfs, "Constructor"_rfs);
        AddTest(MakeDelegate(this,&MemoryAutoPointerArrayTest::ConstructorOwnerTransfere),
            "MemoryAutoPointerArrayTest::ConstructorOwnerTransfere"_rfs, "ConstructorOwnerTransfere"_rfs);
        AddTest(MakeDelegate(this,&MemoryAutoPointerArrayTest::ConstructorCopy),
            "MemoryAutoPointerArrayTest::ConstructorCopy"_rfs, "ConstructorCopy"_rfs);
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
