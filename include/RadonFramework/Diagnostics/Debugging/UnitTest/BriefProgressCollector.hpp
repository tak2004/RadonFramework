#ifndef RF_DIAGNOSTICS_DEBUGGING_BRIEFPROGRESSCOLLECTOR_HPP
#define RF_DIAGNOSTICS_DEBUGGING_BRIEFPROGRESSCOLLECTOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Diagnostics/Debugging/UnitTest/Collector.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Debugging
        {
            namespace UnitTest
            {
                class BriefProgressCollector:public Collector
                {
                    public:
                        void CreateSuite(const RadonFramework::Core::Types::String& Name);
                        void ProcessResult(const UnitTestResult& Result);
                };
            }
        }
    }
}

#endif // RF_DIAGNOSTICS_DEBUGGING_BRIEFPROGRESSCOLLECTOR_HPP