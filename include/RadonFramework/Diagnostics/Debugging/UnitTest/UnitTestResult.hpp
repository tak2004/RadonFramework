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
                    UnitTestResult(const RadonFramework::Core::Types::String& Name);
                    UnitTestResult();
                    UnitTestResult(const UnitTestResult& Copy);
                    ~UnitTestResult();
                    RadonFramework::Core::Types::Bool Passed() const;
                    void Passed(RadonFramework::Core::Types::Bool val);
                    RadonFramework::Time::TimeSpan TimeRequired() const;
                    RadonFramework::Time::TimeSpan& TimeRequired();
                    void TimeRequired(RadonFramework::Time::TimeSpan val);
                    RadonFramework::Core::Types::String Name() const;
                    void Name(RadonFramework::Core::Types::String val);
                    void Error(RadonFramework::Core::Types::Bool val);
                    RadonFramework::Core::Types::Bool Error()const;
                protected:
                    RadonFramework::Core::Types::Bool m_Passed;
                    RadonFramework::Core::Types::Bool m_Error;
                    RadonFramework::Time::TimeSpan m_TimeRequired;
                    RadonFramework::Core::Types::String m_Name;
                };
            }
        }
    }
}

#endif // RF_DIAGNOSTICS_DEBUGGING_UNITTEST_UNITTESTRESULT_HPP
