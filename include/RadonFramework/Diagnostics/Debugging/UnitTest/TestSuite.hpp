#ifndef RF_DIAGNOSTICS_DEBUGGING_TESTSUITE_HPP
#define RF_DIAGNOSTICS_DEBUGGING_TESTSUITE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTestResult.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>

namespace RadonFramework { namespace Diagnostics { namespace Debugging { namespace UnitTest {

class TestSuite
{
public:
    typedef Delegate<RFTYPE::Bool> TestMethod;

    TestSuite(const RFTYPE::String& Name);
    RFTYPE::String Name() const;
    void SetTestProbes(const RFTYPE::Size Probes);
    void AddTest(TestMethod Test, const RFTYPE::String& Testname, const RFTYPE::String& Description);
    virtual void SetUp();
    virtual void TearDown();
    void IgnoreTest(const RFTYPE::String& Testname);
    void Run();
    Collections::List<Memory::AutoPointer<UnitTestResult> >& GetResults();
protected:
    struct Callback{
        RFTYPE::String Name;
        RFTYPE::String Description;
        TestMethod Method;
    };
    Collections::List<Callback> m_TestMethods;
    RFTYPE::String m_Name;
    Collections::List<RFTYPE::String> m_IgnoreTest;
    Collections::List<Memory::AutoPointer<UnitTestResult> > m_TestResults;
    RFTYPE::Size m_TestProbes;

    Memory::AutoPointer<UnitTestResult> ProcessTest(const RFTYPE::UInt32 Number);
};

} } } }

#endif // RF_DIAGNOSTICS_DEBUGGING_TESTSUITE_HPP