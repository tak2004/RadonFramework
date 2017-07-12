#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Test/TestResult.hpp"

namespace RadonFramework::Diagnostics::Test {

TestResult::TestResult()
:m_Passed(true),
m_Error(false)
{
}

TestResult::TestResult(const TestResult& Copy)
{
	*this = Copy;
}

void TestResult::SetError(RF_Type::Bool val)
{
	m_Error = val;
}

RF_Type::Bool TestResult::GetError() const
{
	return m_Error;
}


TestResult::~TestResult()
{

}

RF_Type::Bool TestResult::GetPassed() const
{
	return m_Passed;
}

void TestResult::SetPassed(RF_Type::Bool val)
{
	m_Passed = val;
}

const RF_Time::TimeSpan& TestResult::GetTimeRequired() const
{
	return m_TimeRequired;
}

RF_Time::TimeSpan& TestResult::GetTimeRequired()
{
	return m_TimeRequired;
}

void TestResult::SetTimeRequired(const RF_Time::TimeSpan& val)
{
	m_TimeRequired = val;
}

const RF_Type::String& TestResult::GetName() const
{
	return m_Name;
}

void TestResult::SetName(const RF_Type::String& val)
{
	m_Name = val;
}

TestResult& TestResult::operator=(const TestResult& Other)
{
	m_Passed = Other.m_Passed;
	m_Error = Other.m_Error;
	m_TimeRequired = Other.m_TimeRequired;
	m_Name = Other.m_Name;
	return *this;
}

}