#ifndef RF_DIAGNOSTICS_DEBUGGING_BRIEFPROGRESSCOLLECTOR_HPP
#define RF_DIAGNOSTICS_DEBUGGING_BRIEFPROGRESSCOLLECTOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Diagnostics/Debugging/UnitTest/Collector.hpp>

namespace RadonFramework::Diagnostics::Debugging::UnitTest {

class BriefProgressCollector:public Collector
{
public:
    void CreateSuite(const RF_Type::String& Name)override;
    void ProcessResult(const Test::TestResult& Result)override;
};
 
}

#endif // RF_DIAGNOSTICS_DEBUGGING_BRIEFPROGRESSCOLLECTOR_HPP