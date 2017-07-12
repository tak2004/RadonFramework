#ifndef RF_DIAGNOSTICS_DEBUGGING_DEBUGCOLLECTOR_HPP
#define RF_DIAGNOSTICS_DEBUGGING_DEBUGCOLLECTOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Diagnostics/Debugging/UnitTest/Collector.hpp>

namespace RadonFramework::Diagnostics::Debugging::UnitTest {

class DebugCollector:public Collector
{
public:
    virtual void CreateSuite(const RF_Type::String& Name) override;
    virtual void ProcessResult(const Test::TestResult& Result) override;
protected:
    RF_Type::String m_CurrentSuite;
};

}

#endif // RF_DIAGNOSTICS_DEBUGGING_DEBUGCOLLECTOR_HPP