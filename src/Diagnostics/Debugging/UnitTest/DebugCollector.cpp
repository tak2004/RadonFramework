#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Debugging/UnitTest/DebugCollector.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTestResult.hpp>

using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Diagnostics::Debugging;
using namespace RadonFramework::Core::Types;

void DebugCollector::ProcessResult(const UnitTestResult& Result)
{
#if defined(RF_DEBUG)
    if (!Result.Passed())
    {
        RF_Type::String failingTest = Result.Name();
        abort();
    }
#endif
}

void DebugCollector::CreateSuite( const RF_Type::String& Name )
{
    m_CurrentSuite = Name;
}
