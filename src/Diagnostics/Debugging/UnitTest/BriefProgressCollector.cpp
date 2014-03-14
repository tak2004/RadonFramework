#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Debugging/UnitTest/BriefProgressCollector.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTestResult.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/IO/Log.hpp>

using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::IO;

void BriefProgressCollector::ProcessResult(const UnitTestResult& Result)
{
	if (Result.Passed())
    {
		LogInfo("-The test \"%s\" was successful and take %u microsecond.",Result.Name().c_str(),UInt64(Result.TimeRequired().TotalMicroseconds()));
    }
	else
    {
		LogError("-The test \"%s\" failed and take %u microsecond.",Result.Name().c_str(),UInt64(Result.TimeRequired().TotalMicroseconds()));
    }
}

void BriefProgressCollector::CreateSuite( const RadonFramework::Core::Types::String& Name )
{
	LogInfo("Next Test-Suite: %s",Name.c_str());
}
