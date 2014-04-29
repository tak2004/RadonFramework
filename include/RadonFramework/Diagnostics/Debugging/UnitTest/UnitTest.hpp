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
    void RegisterTestSuide(TestSuite* ATestSuite);
    void Run();
    void Run(const RFTYPE::String& Testname);
    void SetSequentialTestExecution(RFTYPE::UInt32 Rounds);
protected:
    Collections::List<TestSuite*> m_TestSuites;
    Collections::List<Collector*> m_Collector;
    RFTYPE::UInt32 m_TestRounds;
};

} } } }

#endif // RF_DIAGNOSTICS_DEBUGGING_UNITTEST_HPP