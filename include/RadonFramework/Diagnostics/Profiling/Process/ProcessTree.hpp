#ifndef RF_DIAGNOSTICS_PROFILING_PROCESS_PROCESSTREE_HPP
#define RF_DIAGNOSTICS_PROFILING_PROCESS_PROCESSTREE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/AutoVector.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Profiling
        {
            namespace Process
            {
                class ProcessInformation;

                class ProcessTree
                {
                    public:
                        Collections::AutoVector<ProcessInformation> Processes;
                };
            }
        }
    }
}

#endif // RF_DIAGNOSTICS_PROFILING_PROCESS_PROCESSTREE_HPP