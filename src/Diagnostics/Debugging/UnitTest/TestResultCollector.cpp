#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestResultCollector.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTestResult.hpp>

using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Diagnostics::Debugging;
using namespace RadonFramework::Core::Types;

TestResultCollector::TestResultCollector()
:m_Successful(true)
{

}

void TestResultCollector::ProcessResult(const UnitTestResult& Result)
{
    m_Successful=m_Successful && Result.Passed();
    Assert(m_TestResults.Last(),"Illegal usage of null pointer.");
    m_TestResults.Last()->TestResults.AddLast(Result);
    if (Result.Error())
        ++m_TestResults.Last()->TestsWithError;
    if (!Result.Passed())
        ++m_TestResults.Last()->TestsWithFailure;
    m_TestResults.Last()->TotalTime+=(Float32)Result.TimeRequired().TotalSeconds();
}

Bool UnitTest::TestResultCollector::WasSuccessful()
{
    return m_Successful;
}

void UnitTest::TestResultCollector::CreateSuite( const String& Name )
{
    SuiteResult& suite=m_TestResults.CreateElementAtEnd();
    suite.SuiteName=Name;
    suite.TestsWithError=0;
    suite.TestsWithFailure=0;
    suite.TotalTime=0.0;
}

const List<SuiteResult>& UnitTest::TestResultCollector::TestResults() const
{
    return m_TestResults;
}
