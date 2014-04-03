#ifndef RF_DIAGNOSTICS_DEBUGGING_TESTSUITE_HPP
#define RF_DIAGNOSTICS_DEBUGGING_TESTSUITE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTestResult.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Debugging
        {
            namespace UnitTest
            {
                class TestSuite
                {
                    public:
                        typedef Delegate<RFTYPE::Bool> TestMethod;

                        TestSuite(const RFTYPE::String& Name);
                        RFTYPE::String Name() const;
                        RFTYPE::UInt32 TestCount();
                        void AddTest(TestMethod Test, const RFTYPE::String& TestName);
                        Memory::AutoPointer<UnitTestResult> ProcessTests(const RFTYPE::UInt32 Number);
                        virtual void SetUp();
                        virtual void TearDown();
                    protected:
                        struct Callback{
                            RFTYPE::String Name;
                            TestMethod Method;
                        };
                        Collections::List<Callback> m_TestMethods;
                        RFTYPE::String m_Name;
                };
            }
        }
    }
}

#endif // RF_DIAGNOSTICS_DEBUGGING_TESTSUITE_HPP