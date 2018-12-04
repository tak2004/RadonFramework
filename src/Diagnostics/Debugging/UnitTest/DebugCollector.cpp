#include <RadonFramework/Diagnostics/Debugging/UnitTest/DebugCollector.hpp>
#include <RadonFramework/Diagnostics/Test/TestResult.hpp>
#include <cstdlib>
#include "RadonFramework/BuildInfo.hpp"
#include "RadonFramework/precompiled.hpp"

namespace RadonFramework::Diagnostics::Debugging::UnitTest
{
void DebugCollector::ProcessResult(const RF_Test::TestResult& Result)
{
  if(BuildInfo::CompileForDebugging == BuildInfo::DebugMode::True)
  {
    if(!Result.GetPassed())
    {
      RF_Type::String failingTest = Result.GetName();
      abort();
    }
  }
}

void DebugCollector::CreateSuite(const RF_Type::String& Name)
{
  m_CurrentSuite = Name;
}

}  // namespace RadonFramework::Diagnostics::Debugging::UnitTest