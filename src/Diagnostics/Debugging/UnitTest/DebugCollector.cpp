#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Debugging/UnitTest/DebugCollector.hpp>
#include <RadonFramework/Diagnostics/Test/TestResult.hpp>

namespace RadonFramework::Diagnostics::Debugging::UnitTest {

void DebugCollector::ProcessResult(const RF_Test::TestResult& Result)
{
#if defined(RF_DEBUG)
	if (!Result.GetPassed())
	{
		RF_Type::String failingTest = Result.GetName();
		abort();
	}
#endif
}

void DebugCollector::CreateSuite(const RF_Type::String& Name)
{
	m_CurrentSuite = Name;
}

}