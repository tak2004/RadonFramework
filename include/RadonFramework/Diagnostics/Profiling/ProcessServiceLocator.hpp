#ifndef RF_DIAGNOSTICS_PROFILING_PROCESSSERVICELOCATOR_HPP
#define RF_DIAGNOSTICS_PROFILING_PROCESSSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/Diagnostics/Profiling/ProcessService.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Profiling
        {
            class NullProcessService:public ProcessService
            {
                public:
                    NullProcessService(const RadonFramework::Core::Types::String &Name):ProcessService(Name){}
                    Memory::AutoPointer<Process::ProcessTree> GetProcessTree(){return Memory::AutoPointer<Process::ProcessTree>(new Process::ProcessTree());}
                    Memory::AutoPointer<Process::ProcessInformation> GetCurrentProcess(){return Memory::AutoPointer<Process::ProcessInformation>(0);}
                    Core::Types::UInt32 GetCurrentProcessID(){return 0;}
                    Memory::AutoPointer<Process::ProcessInformation> GetProcessByID(Core::Types::UInt32 ProcessID){return Memory::AutoPointer<Process::ProcessInformation>(0);}
            };

            typedef Core::Pattern::Locator<ProcessService,NullProcessService> ProcessServiceLocator;
        }
    }
}

#endif // RF_DIAGNOSTICS_PROFILING_PROCESSSERVICELOCATOR_HPP
