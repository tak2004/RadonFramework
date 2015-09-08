#ifndef RF_DIAGNOSTICS_DEBUGGING_UNITTEST_UNITTESTRESULT_HPP
#define RF_DIAGNOSTICS_DEBUGGING_UNITTEST_UNITTESTRESULT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Time/TimeSpan.hpp>

namespace RadonFramework { namespace Diagnostics { namespace Debugging { namespace UnitTest {

class UnitTestResult
{
public:
    UnitTestResult(const RF_Type::String& Name);
    UnitTestResult();
    UnitTestResult(const UnitTestResult& Copy);
    ~UnitTestResult();
    UnitTestResult& operator=(const UnitTestResult& Other);
    RF_Type::Bool Passed() const;
    void Passed(RF_Type::Bool val);
    RF_Time::TimeSpan TimeRequired() const;
    RF_Time::TimeSpan& TimeRequired();
    void TimeRequired(RF_Time::TimeSpan val);
    const RF_Type::String& Name() const;
    void Name(const RF_Type::String& val);
    void Error(RF_Type::Bool val);
    RF_Type::Bool Error()const;
protected:
    RF_Type::Bool m_Passed;
    RF_Type::Bool m_Error;
    RF_Time::TimeSpan m_TimeRequired;
    RF_Type::String m_Name;
};

} } } }

#ifndef RF_SHORTHAND_NAMESPACE_TEST
#define RF_SHORTHAND_NAMESPACE_TEST
namespace RF_Test = RadonFramework::Diagnostics::Debugging::UnitTest;
#endif

#endif // RF_DIAGNOSTICS_DEBUGGING_UNITTEST_UNITTESTRESULT_HPP
