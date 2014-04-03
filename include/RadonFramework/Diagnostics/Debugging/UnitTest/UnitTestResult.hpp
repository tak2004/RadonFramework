#ifndef RF_DIAGNOSTICS_DEBUGGING_UNITTEST_UNITTESTRESULT_HPP
#define RF_DIAGNOSTICS_DEBUGGING_UNITTEST_UNITTESTRESULT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Time/TimeSpan.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Debugging
        {
            namespace UnitTest
            {
                class UnitTestResult
                {
                public:
                    UnitTestResult(const RFTYPE::String& Name);
                    UnitTestResult();
                    UnitTestResult(const UnitTestResult& Copy);
                    ~UnitTestResult();
                    RFTYPE::Bool Passed() const;
                    void Passed(RFTYPE::Bool val);
                    RadonFramework::Time::TimeSpan TimeRequired() const;
                    RadonFramework::Time::TimeSpan& TimeRequired();
                    void TimeRequired(RadonFramework::Time::TimeSpan val);
                    RFTYPE::String Name() const;
                    void Name(RFTYPE::String val);
                    void Error(RFTYPE::Bool val);
                    RFTYPE::Bool Error()const;
                protected:
                    RFTYPE::Bool m_Passed;
                    RFTYPE::Bool m_Error;
                    RadonFramework::Time::TimeSpan m_TimeRequired;
                    RFTYPE::String m_Name;
                };
            }
        }
    }
}

#endif // RF_DIAGNOSTICS_DEBUGGING_UNITTEST_UNITTESTRESULT_HPP
