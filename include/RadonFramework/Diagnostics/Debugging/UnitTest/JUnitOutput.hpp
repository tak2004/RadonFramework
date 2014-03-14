#ifndef RF_DIAGNOSTICS_DEBUGGING_JUNITOUTPUT_HPP
#define RF_DIAGNOSTICS_DEBUGGING_JUNITOUTPUT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace IO
    {
        class Uri;
    }

    namespace Diagnostics
    {
        namespace Debugging
        {
            namespace UnitTest
            {
                class TestResultCollector;

                class JUnitOutput
                {
                    public:
                        void WriteToFile(const RadonFramework::IO::Uri& URI,
                                         const TestResultCollector& Results);
                };
            }
        }
    }
}

#endif // RF_DIAGNOSTICS_DEBUGGING_JUNITOUTPUT_HPP