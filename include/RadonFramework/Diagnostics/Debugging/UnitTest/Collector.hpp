#ifndef RF_DIAGNOSTICS_DEBUGGING_COLLECTOR_HPP
#define RF_DIAGNOSTICS_DEBUGGING_COLLECTOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Debugging
        {
            namespace UnitTest
            {
                class UnitTestResult;

                class Collector
                {
                    public:
                        virtual void CreateSuite(const RadonFramework::Core::Types::String& Name)=0;
                        virtual void ProcessResult(const UnitTestResult& Result)=0;
                };
            }
        }
    }
}

#endif // RF_DIAGNOSTICS_DEBUGGING_COLLECTOR_HPP