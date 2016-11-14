#ifndef RF_DIAGNOSTICS_DEBUGGING_TESTSUITE_HPP
#define RF_DIAGNOSTICS_DEBUGGING_TESTSUITE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Collections/List.hpp>

namespace RadonFramework { namespace Diagnostics { namespace Test {
class TestResult;
} } }

namespace RadonFramework { namespace Diagnostics { namespace Debugging { namespace UnitTest {

class TestSuite
{
public:
    typedef Delegate<RF_Type::Bool()> TestMethod;

    TestSuite(const RF_Type::String& Name);
    const RF_Type::String& Name() const;
    void SetTestProbes(const RF_Type::Size Probes);
    void AddTest(TestMethod Test, const RF_Type::String& Testname, 
                 const RF_Type::String& Description);
    virtual void SetUp();
    virtual void TearDown();
    void IgnoreTest(const RF_Type::String& Testname);
    void Run();
    RF_Collect::List<RF_Mem::AutoPointer<Test::TestResult> >& GetResults();
protected:
    struct Callback{
        RF_Type::String Name;
        RF_Type::String Description;
        TestMethod Method;
    };
    RF_Collect::List<Callback> m_TestMethods;
    RF_Type::String m_Name;
    RF_Collect::List<RF_Type::String> m_IgnoreTest;
    RF_Collect::List<RF_Mem::AutoPointer<Test::TestResult> > m_TestResults;
    RF_Type::Size m_TestProbes;

    RF_Mem::AutoPointer<Test::TestResult> ProcessTest(const RF_Type::UInt32 Number);
};

} } } }

#ifndef RF_SHORTHAND_NAMESPACE_UNITTEST
#define RF_SHORTHAND_NAMESPACE_UNITTEST
namespace RF_UnitTest = RadonFramework::Diagnostics::Debugging::UnitTest;
#endif

#endif // RF_DIAGNOSTICS_DEBUGGING_TESTSUITE_HPP