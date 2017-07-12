#ifndef RF_DIAGNOSTICS_TEST_TESTRESULT_HPP
#define RF_DIAGNOSTICS_TEST_TESTRESULT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Time/TimeSpan.hpp>

namespace RadonFramework::Diagnostics::Test {

class TestResult
{
public:
	TestResult();
	TestResult(const TestResult& Copy);
    ~TestResult();
	TestResult& operator=(const TestResult& Other);
    RF_Type::Bool GetPassed() const;
    void SetPassed(RF_Type::Bool val);
    const RF_Time::TimeSpan& GetTimeRequired() const;
    RF_Time::TimeSpan& GetTimeRequired();
    void SetTimeRequired(const RF_Time::TimeSpan& val);
    const RF_Type::String& GetName() const;
    void SetName(const RF_Type::String& val);
    void SetError(RF_Type::Bool val);
    RF_Type::Bool GetError()const;
protected:
    RF_Time::TimeSpan m_TimeRequired;
    RF_Type::String m_Name;
	RF_Type::Bool m_Passed;
	RF_Type::Bool m_Error;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_TEST
#define RF_SHORTHAND_NAMESPACE_TEST
namespace RF_Test = RadonFramework::Diagnostics::Test;
#endif

#endif // RF_DIAGNOSTICS_TEST_TESTRESULT_HPP
