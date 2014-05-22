#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/UnitTestResult.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/Collector.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;

UnitTest::UnitTest()
:m_TestRounds(1)
{}

void UnitTest::AddCollector(Collector& ACollector)
{
    Collector* collector = &ACollector;
    m_Collector.AddLast(collector);
}

void UnitTest::RegisterTestSuide(TestSuite* ATestSuite)
{
    m_TestSuites.AddLast(ATestSuite);
}

void UnitTest::Run()
{
    for(UInt32 i = 0; i < m_TestSuites.Size(); ++i)
    {
        m_TestSuites[i]->SetUp();
        for(UInt32 k = 0; k < m_Collector.Size(); ++k)
            m_Collector[k]->CreateSuite(m_TestSuites[i]->Name());

        for(UInt32 j = 0; j < m_TestSuites[i]->TestCount(); ++j)
        {
            for(UInt32 k = 0; k < m_TestRounds; ++k)
            {
                AutoPointer<UnitTestResult> res;
                res = m_TestSuites[i]->ProcessTests(j);
                for(UInt32 l = 0; l < m_Collector.Size(); ++l)
                {
                    m_Collector[l]->ProcessResult(*res);
                }
            }
        }
    }
}

void UnitTest::Run(const RFTYPE::String& Testname)
{
    for(UInt32 i = 0; i < m_TestSuites.Size(); ++i)
    {
        if(m_TestSuites[i]->Name() == Testname)
        {
            m_TestSuites[i]->SetUp();
            for(UInt32 k = 0; k < m_Collector.Size(); ++k)
                m_Collector[k]->CreateSuite(m_TestSuites[i]->Name());

            for(UInt32 j = 0; j < m_TestSuites[i]->TestCount(); ++j)
            {
                for(UInt32 k = 0; k < m_TestRounds; ++k)
                {
                    AutoPointer<UnitTestResult> res;
                    res = m_TestSuites[i]->ProcessTests(j);
                    for(UInt32 l = 0; l < m_Collector.Size(); ++l)
                    {
                        m_Collector[l]->ProcessResult(*res);
                    }
                }
            }
            break;
        }
    }
}

void UnitTest::SetSequentialTestExecution(RFTYPE::UInt32 Rounds)
{
    m_TestRounds = Rounds;
}
