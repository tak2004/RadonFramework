#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Time/ScopeTimer.hpp>
#include <memory>

using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Time;

TestSuite::TestSuite( const String& Name ) 
:m_Name(Name)
{
    RF_Pattern::Singleton<UnitTest>::GetInstance().RegisterTestSuite(this);
}

String TestSuite::Name() const
{
    return m_Name;
}

void TestSuite::AddTest( TestMethod Test, const String& TestName, const String& Description )
{
    Callback cb;
    cb.Method = Test;
    cb.Name = TestName;
    cb.Description = Description;
    m_TestMethods.AddLast(cb);
}

AutoPointer<UnitTestResult> TestSuite::ProcessTest( const UInt32 Number )
{
    register RF_Type::Bool passed;
    AutoPointer<UnitTestResult> result;
    Assert(Number<m_TestMethods.Count(), "Out of bound.");
    result = AutoPointer<UnitTestResult>(new UnitTestResult(m_TestMethods[Number].Name));
    {
        ScopeTimer scopetime(result->TimeRequired());
        passed = m_TestMethods[Number].Method();
    }
    result->Passed(passed);
    return result;
}

void TestSuite::SetUp()
{

}

void TestSuite::TearDown()
{

}

void TestSuite::IgnoreTest( const RF_Type::String& Testname )
{
    m_IgnoreTest.AddLast(Testname);
}

List<AutoPointer<UnitTestResult> >& TestSuite::GetResults()
{
    return m_TestResults;
}

void TestSuite::Run()
{
    m_TestResults.Clear();
    for(UInt32 i = 0; i < m_TestMethods.Count(); ++i)
    {
        if (!m_IgnoreTest.Find(m_TestMethods[i].Name))
        {
            for(UInt32 k = 0; k < m_TestProbes; ++k)
            {
                AutoPointer<UnitTestResult> res;
                res = ProcessTest(i);
                m_TestResults.AddLast(res);
            }
        }
    }
}

void TestSuite::SetTestProbes( const RF_Type::Size Probes )
{
    m_TestProbes = Probes;
}
