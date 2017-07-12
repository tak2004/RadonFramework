#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Debugging/UnitTest/BriefProgressCollector.hpp>
#include <RadonFramework/Diagnostics/Test/TestResult.hpp>
#include <RadonFramework/IO/Log.hpp>

namespace RadonFramework::Diagnostics::Debugging::UnitTest {

void BriefProgressCollector::ProcessResult(const RF_Test::TestResult& Result)
{
	if (Result.GetPassed())
    {
        RF_IO::LogInfo("-The test \"%s\" was successful and take %u cycles.", 
			Result.GetName().c_str(), 
			RF_Type::UInt64(Result.GetTimeRequired().Ticks()));
    }
	else
    {
		RF_IO::LogError("-The test \"%s\" failed and take %u cycles.",
			Result.GetName().c_str(), 
			RF_Type::UInt64(Result.GetTimeRequired().Ticks()));
    }
}

void BriefProgressCollector::CreateSuite( const RF_Type::String& Name )
{
	RF_IO::LogInfo("Next Test-Suite: %s", Name.c_str());
}

}