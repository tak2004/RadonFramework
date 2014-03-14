#ifndef RF_DIAGNOSTICS_PROFILING_PROCESSSERVICE_HPP
#define RF_DIAGNOSTICS_PROFILING_PROCESSSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Diagnostics/Profiling/Process/ProcessTree.hpp>
#include <RadonFramework/Diagnostics/Profiling/Process/ProcessInformation.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Profiling
        {
            class ProcessService:public Core::Pattern::Service
            {
                public:
                    ProcessService(const RadonFramework::Core::Types::String &Name);
                    virtual Memory::AutoPointer<Process::ProcessTree> GetProcessTree()=0;
                    virtual Memory::AutoPointer<Process::ProcessInformation> GetCurrentProcess()=0;
                    virtual Core::Types::UInt32 GetCurrentProcessID()=0;
                    virtual Memory::AutoPointer<Process::ProcessInformation> GetProcessByID(Core::Types::UInt32 ProcessID)=0;
            };
        }
    }
}

#endif // RF_DIAGNOSTICS_PROFILING_PROCESSSERVICE_HPP
