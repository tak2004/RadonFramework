#ifndef RF_DIAGNOSTICS_DEBUGGING_TESTRESULTCOLLECTOR_HPP
#define RF_DIAGNOSTICS_DEBUGGING_TESTRESULTCOLLECTOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Diagnostics/Debugging/UnitTest/Collector.hpp>
#include <RadonFramework/Collections/List.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Debugging
        {
            namespace UnitTest
            {
                struct SuiteResult
                {
                    Collections::List<UnitTestResult> TestResults;
                    RFTYPE::String SuiteName;
                    RFTYPE::Float32 TotalTime;
                    RFTYPE::UInt32 TestsWithError;
                    RFTYPE::UInt32 TestsWithFailure;
                };

                class TestResultCollector:public Collector
                {
                    public:
                        TestResultCollector();
                        void CreateSuite(const RFTYPE::String& Name);
                        void ProcessResult(const UnitTestResult& Result);
                        RFTYPE::Bool WasSuccessful();
                        const Collections::List<SuiteResult>& TestResults()const;
                    protected:
                        Collections::List<SuiteResult> m_TestResults;
                        RFTYPE::Bool m_Successful;
                };
            }
        }
    }
}

#endif // RF_DIAGNOSTICS_DEBUGGING_TESTRESULTCOLLECTOR_HPP