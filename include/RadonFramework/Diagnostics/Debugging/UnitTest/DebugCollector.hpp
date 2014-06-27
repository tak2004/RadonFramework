#ifndef RF_DIAGNOSTICS_DEBUGGING_DEBUGCOLLECTOR_HPP
#define RF_DIAGNOSTICS_DEBUGGING_DEBUGCOLLECTOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Diagnostics/Debugging/UnitTest/Collector.hpp>
#include <RadonFramework/Collections/List.hpp>

namespace RadonFramework { namespace Diagnostics { namespace Debugging { namespace UnitTest {

class DebugCollector:public Collector
{
public:
    virtual void CreateSuite(const RFTYPE::String& Name);
    virtual void ProcessResult(const UnitTestResult& Result);
protected:
    RFTYPE::String m_CurrentSuite;
};

} } } }

#endif // RF_DIAGNOSTICS_DEBUGGING_DEBUGCOLLECTOR_HPP