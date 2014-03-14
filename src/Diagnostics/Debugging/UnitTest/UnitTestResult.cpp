#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTestResult.hpp>

using namespace RadonFramework::Diagnostics::Debugging::UnitTest;

UnitTestResult::UnitTestResult(const RadonFramework::Core::Types::String& Name)
:m_Passed(true),
 m_Error(false),
 m_Name(Name)
{

}

UnitTestResult::UnitTestResult()
:m_Passed(true),
 m_Error(false)
{
}

UnitTestResult::UnitTestResult( const UnitTestResult& Copy )
:m_Passed(Copy.m_Passed),
 m_Error(Copy.m_Error),
 m_TimeRequired(Copy.m_TimeRequired),
 m_Name(Copy.m_Name)
{

}

void UnitTestResult::Error(RadonFramework::Core::Types::Bool val)
{
	m_Error=val;
}

RadonFramework::Core::Types::Bool UnitTestResult::Error() const
{
	return m_Error;
}


UnitTestResult::~UnitTestResult()
{

}

RadonFramework::Core::Types::Bool UnitTestResult::Passed() const
{
	return m_Passed;
}

void UnitTestResult::Passed(RadonFramework::Core::Types::Bool val)
{
	m_Passed = val;
}

RadonFramework::Time::TimeSpan UnitTestResult::TimeRequired() const
{
	return m_TimeRequired;
}

RadonFramework::Time::TimeSpan& UnitTestResult::TimeRequired()
{
	return m_TimeRequired;
}

void UnitTestResult::TimeRequired(RadonFramework::Time::TimeSpan val)
{
	m_TimeRequired = val;
}

RadonFramework::Core::Types::String UnitTestResult::Name() const
{
	return m_Name;
}

void UnitTestResult::Name(RadonFramework::Core::Types::String val)
{
	m_Name = val;
}
