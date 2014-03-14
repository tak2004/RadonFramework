#ifndef RF_DIAGNOSTICS_DEBUGGING_UNITTEST_HPP
#define RF_DIAGNOSTICS_DEBUGGING_UNITTEST_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/Collections/List.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Debugging
        {
            namespace UnitTest
            {
                class TestSuite;
                class Collector;

                class UnitTest
                {
                    public:
                        void AddCollector(Collector& ACollector);
                        void RegisterTestSuide(TestSuite* ATestSuite);
                        void Run();
                    protected:
                        Collections::List<TestSuite*> m_TestSuites;
                        Collections::List<Collector*> m_Collector;
                };
            }
        }
    }
}

#endif // RF_DIAGNOSTICS_DEBUGGING_UNITTEST_HPP