#ifndef RF_DIAGNOSTICS_DEBUGGING_UNITTEST_HPP
#define RF_DIAGNOSTICS_DEBUGGING_UNITTEST_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/List.hpp>

namespace RadonFramework { namespace Diagnostics { namespace Debugging { namespace UnitTest {

class TestSuite;
class Collector;

class UnitTest
{
public:
    UnitTest();
    void AddCollector(Collector& ACollector);
    void RegisterTestSuite(TestSuite* ATestSuite);
    void Run();
    void RunSuiteWithName(const RFTYPE::String& Suitename);
    void SetSequentialTestExecution(RFTYPE::Size Probes);
    void IgnoreSuite(const RFTYPE::String& Suitename);
    TestSuite* GetSuite(const RFTYPE::String& Suitename);
private:
    Collections::List<RFTYPE::String> m_IgnoreSuite;
    Collections::List<TestSuite*> m_TestSuites;
    Collections::List<Collector*> m_Collector;
    RFTYPE::Size m_TestProbes;

    void RunSuiteAt(const RFTYPE::Size Index);
};

} } } }

#endif // RF_DIAGNOSTICS_DEBUGGING_UNITTEST_HPP