#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Time/ScopeTimer.hpp>
#include <memory>

using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Time;

TestSuite::TestSuite( const RadonFramework::Core::Types::String& Name ) 
:m_Name(Name)
{
	Singleton<UnitTest>::GetInstance().RegisterTestSuide(this);
}

String TestSuite::Name() const
{
	return m_Name;
}

UInt32 TestSuite::TestCount()
{
	return m_TestMethods.Size();
}

void TestSuite::AddTest( TestMethod Test, const String& TestName )
{
	Callback cb;
	cb.Method=Test;
	cb.Name=TestName;
	m_TestMethods.AddLast(cb);
}

AutoPointer<UnitTestResult> TestSuite::ProcessTests( const UInt32 Number )
{
	AutoPointer<UnitTestResult> result;
	Assert(Number<m_TestMethods.Size(),"Out of bound.");
	{
		result=AutoPointer<UnitTestResult>(new UnitTestResult(m_TestMethods[Number].Name));
		ScopeTimer scopetime(result->TimeRequired());
		result->Passed(m_TestMethods[Number].Method());
	}
	return result;
}

void TestSuite::SetUp()
{

}

void TestSuite::TearDown()
{

}