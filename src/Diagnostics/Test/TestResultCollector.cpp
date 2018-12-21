#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Test/TestResultCollector.hpp"

namespace RadonFramework::Diagnostics::Test {

TestResultCollector::TestResultCollector()
:m_Successful(true)
{
}

void TestResultCollector::ProcessResult(const RF_Test::TestResult& Result)
{
	m_Successful = m_Successful && Result.GetPassed();
	RF_ASSERT(m_TestResults.Last(), "Illegal usage of null pointer.");
	m_TestResults.Last()->TestResults.AddLast(Result);
	if (Result.GetError())
		++m_TestResults.Last()->TestsWithError;
	if (!Result.GetPassed())
		++m_TestResults.Last()->TestsWithFailure;
	m_TestResults.Last()->TotalTime += static_cast<RF_Type::Float32>(Result.GetTimeRequired().TotalSeconds());
}

RF_Type::Bool TestResultCollector::WasSuccessful()
{
	return m_Successful;
}

void TestResultCollector::CreateSuite(const RF_Type::String& Name)
{
	SuiteResult& suite = m_TestResults.CreateElementAtEnd();
	suite.SuiteName = Name;
	suite.TestsWithError = 0;
	suite.TestsWithFailure = 0;
	suite.TotalTime = 0.0;
}

const RF_Collect::List<RF_Test::SuiteResult>& TestResultCollector::TestResults() const
{
	return m_TestResults;
}

}