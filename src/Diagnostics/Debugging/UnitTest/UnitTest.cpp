#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/UnitTestResult.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/Collector.hpp"

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
    for(UInt32 i = 0; i < m_TestSuites.Size(); ++i)
    {
        if (!m_IgnoreSuite.Find(m_TestSuites[i]->Name()))
            RunSuiteAt(i);
    }
}

void UnitTest::RunSuiteWithName(const RFTYPE::String& Suitename)
{
    if (!m_IgnoreSuite.Find(Suitename))
    {
        for(UInt32 i = 0; i < m_TestSuites.Size(); ++i)
        {
            if(m_TestSuites[i]->Name() == Suitename)
            {
                RunSuiteAt(i);
                break;
            }
        }
    }
}

void UnitTest::RunSuiteAt( RFTYPE::Size Index )
{
    m_TestSuites[Index]->SetUp();
    for(Size i = 0; i < m_Collector.Size(); ++i)
        m_Collector[i]->CreateSuite(m_TestSuites[Index]->Name());

    m_TestSuites[Index]->SetTestProbes(m_TestProbes);
    m_TestSuites[Index]->Run();

    List<AutoPointer<UnitTestResult> >& results = m_TestSuites[Index]->GetResults();
    for (Size i = 0; i < results.Size(); ++i)
    {
        for(Size l = 0; l < m_Collector.Size(); ++l)
        {
            m_Collector[l]->ProcessResult(*results[i]);
        }
    }
}

void UnitTest::SetSequentialTestExecution(RFTYPE::Size Probes)
{
    m_TestProbes = Probes;
}

void UnitTest::IgnoreSuite( const RFTYPE::String& Suitename )
{
    m_IgnoreSuite.AddLast(Suitename);
}

TestSuite* UnitTest::GetSuite( const RFTYPE::String& Suitename )
{
    TestSuite* result = 0;
    for(UInt32 i = 0; i < m_TestSuites.Size(); ++i)
    {
        if(m_TestSuites[i]->Name() == Suitename)
        {
            result = m_TestSuites[i];
            break;
        }
    }
    return result;
}
