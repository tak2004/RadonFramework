#ifndef RF_DIAGNOSTICS_DEBUGGING_TESTRESULTCOLLECTOR_HPP
#define RF_DIAGNOSTICS_DEBUGGING_TESTRESULTCOLLECTOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Diagnostics/Debugging/UnitTest/Collector.hpp>
#include <RadonFramework/Collections/List.hpp>

namespace RadonFramework { namespace Diagnostics { namespace Debugging { namespace UnitTest {

struct SuiteResult
{
    RF_Collect::List<UnitTestResult> TestResults;
    RF_Type::String SuiteName;
    RF_Type::Float32 TotalTime;
    RF_Type::UInt32 TestsWithError;
    RF_Type::UInt32 TestsWithFailure;
};

class TestResultCollector:public Collector
{
public:
    TestResultCollector();
    void CreateSuite(const RF_Type::String& Name);
    void ProcessResult(const UnitTestResult& Result);
    RF_Type::Bool WasSuccessful();
    const RF_Collect::List<SuiteResult>& TestResults()const;
protected:
    RF_Collect::List<SuiteResult> m_TestResults;
    RF_Type::Bool m_Successful;
};
            
} } } }

#ifndef RF_SHORTHAND_NAMESPACE_TEST
#define RF_SHORTHAND_NAMESPACE_TEST
namespace RF_Test = RadonFramework::Diagnostics::Debugging::UnitTest;
#endif


#endif // RF_DIAGNOSTICS_DEBUGGING_TESTRESULTCOLLECTOR_HPP