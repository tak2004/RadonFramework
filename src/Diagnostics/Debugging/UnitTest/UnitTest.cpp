#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/UnitTestResult.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/Collector.hpp"
#include "RadonFramework/Threading/ThreadPool.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;

UnitTest::UnitTest()
:m_TestProbes(1)
{}

void UnitTest::AddCollector(Collector& ACollector)
{
    Collector* collector = &ACollector;
    m_Collector.AddLast(collector);
}

void UnitTest::RegisterTestSuite(TestSuite* ATestSuite)
{
    m_TestSuites.AddLast(ATestSuite);
}

void UnitTest::Run()
{
    for(UInt32 i = 0; i < m_TestSuites.Count(); ++i)
    {
        if (!m_IgnoreSuite.Find(m_TestSuites[i]->Name()))
            RunSuiteAt(i);
    }
}

void UnitTest::RunSuiteWithName(const RF_Type::String& Suitename)
{
    if (!m_IgnoreSuite.Find(Suitename))
    {
        for(UInt32 i = 0; i < m_TestSuites.Count(); ++i)
        {
            if(m_TestSuites[i]->Name() == Suitename)
            {
                RunSuiteAt(i);
                break;
            }
        }
    }
}

void UnitTest::RunSuiteAt( RF_Type::Size Index )
{
    m_TestSuites[Index]->SetUp();
    for(Size i = 0; i < m_Collector.Count(); ++i)
        m_Collector[i]->CreateSuite(m_TestSuites[Index]->Name());
    // Wait till all Appender wrote the initial headline.
    RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance().WaitTillDoneWithInactiveQueue();
    // Start multi threaded test.
    m_TestSuites[Index]->SetTestProbes(m_TestProbes);
    m_TestSuites[Index]->Run();

    List<AutoPointer<UnitTestResult> >& results = m_TestSuites[Index]->GetResults();
    for(Size i = 0; i < results.Count(); ++i)
    {
        for(Size l = 0; l < m_Collector.Count(); ++l)
        {
            m_Collector[l]->ProcessResult(*results[i]);
        }
    }
    // Wait till all logging stuff of the tests are done.
    RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance().WaitTillDoneWithInactiveQueue();
}

void UnitTest::SetSequentialTestExecution(RF_Type::Size Probes)
{
    m_TestProbes = Probes;
}

void UnitTest::IgnoreSuite( const RF_Type::String& Suitename )
{
    m_IgnoreSuite.AddLast(Suitename);
}

TestSuite* UnitTest::GetSuite( const RF_Type::String& Suitename )
{
    TestSuite* result = 0;
    for(UInt32 i = 0; i < m_TestSuites.Count(); ++i)
    {
        if(m_TestSuites[i]->Name() == Suitename)
        {
            result = m_TestSuites[i];
            break;
        }
    }
    return result;
}
