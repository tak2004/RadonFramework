#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp"
#include "RadonFramework/Diagnostics/Test/TestResult.hpp"
#include "RadonFramework/Time/ScopeTimer.hpp"

namespace RadonFramework::Diagnostics::Debugging::UnitTest {

TestSuite::TestSuite(const RF_Type::String& Name)
	:m_Name(Name)
{
	RF_Pattern::Singleton<UnitTest>::GetInstance().RegisterTestSuite(this);
}

const RF_Type::String& TestSuite::Name() const
{
	return m_Name;
}

void TestSuite::AddTest(TestMethod Test, const RF_Type::String& TestName,
	const RF_Type::String& Description)
{
	Callback cb;
	cb.Method = Test;
	cb.Name = TestName;
	cb.Description = Description;
	m_TestMethods.AddLast(cb);
}

RF_Mem::AutoPointer<RF_Test::TestResult> TestSuite::ProcessTest(const RF_Type::UInt32 Number)
{
	register RF_Type::Bool passed;
	Assert(Number < m_TestMethods.Count(), "Out of bound.");
	RF_Mem::AutoPointer<RF_Test::TestResult> result(new RF_Test::TestResult);
	result->SetName(m_TestMethods[Number].Name);
	{
		RF_Time::ScopeTimer scopetime(result->GetTimeRequired());
		passed = m_TestMethods[Number].Method();
	}
	result->SetPassed(passed);
	return result;
}

void TestSuite::SetUp()
{

}

void TestSuite::TearDown()
{

}

void TestSuite::IgnoreTest(const RF_Type::String& Testname)
{
	m_IgnoreTest.AddLast(Testname);
}

RF_Collect::List<RF_Mem::AutoPointer<RF_Test::TestResult>>& TestSuite::GetResults()
{
	return m_TestResults;
}

void TestSuite::Run()
{
	m_TestResults.Clear();
	for (RF_Type::Size i = 0; i < m_TestMethods.Count(); ++i)
	{
		if (!m_IgnoreTest.Find(m_TestMethods[i].Name))
		{
			for (RF_Type::Size k = 0; k < m_TestProbes; ++k)
			{
				RF_Mem::AutoPointer<RF_Test::TestResult> res;
				res = ProcessTest(i);
				m_TestResults.AddLast(res);
			}
		}
	}
}

void TestSuite::SetTestProbes(const RF_Type::Size Probes)
{
	m_TestProbes = Probes;
}

}