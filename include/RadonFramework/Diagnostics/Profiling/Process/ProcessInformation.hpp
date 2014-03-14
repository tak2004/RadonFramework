#ifndef RF_DIAGNOSTICS_PROFILING_PROCESS_PROCESSINFORMATION_HPP
#define RF_DIAGNOSTICS_PROFILING_PROCESS_PROCESSINFORMATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Time/TimeSpan.hpp>
#include <RadonFramework/Time/DateTime.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/UInt64.hpp>
#include <RadonFramework/Core/Types/Float32.hpp>

#include <RadonFramework/Diagnostics/Profiling/Process/ModuleInformation.hpp>
#include <RadonFramework/Diagnostics/Profiling/Process/ThreadInformation.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Profiling
        {
            namespace Process
            {
                //separate data and interpretation

                struct ProcessData
                {
                    //General
                    Core::Types::UInt32 ID;
                    Core::Types::String BinaryName;
                    Core::Types::String Name;
                    //Memory
                    Core::Types::Bool MemoryAccessRights;//allowed to read memory information
                    Core::Types::UInt64 MemoryUsage;//total memory usage
                    Core::Types::UInt64 PeakMemoryUsage;//max used memory
                    Core::Types::UInt64 UsableVirtualMemory;//available virtual memory for this process
                    Core::Types::UInt64 NonPagedPool;//number of bytes not in page pool
                    Core::Types::UInt64 PagedPool;//number of bytes in page pool(swap)
                    Core::Types::UInt64 PageFaultCount;//number of memory access on page pool
                    //Timing
                    RadonFramework::Time::DateTime CreationTime;
                    RadonFramework::Time::DateTime ExitTime;
                    RadonFramework::Time::TimeSpan KernelTime;
                    RadonFramework::Time::TimeSpan UserTime;
                    //IO
                    Core::Types::UInt64 ReadOperationCount;
                    Core::Types::UInt64 WriteOperationCount;
                    Core::Types::UInt64 OtherOperationCount;
                    Core::Types::UInt64 ReadTransferedBytes;
                    Core::Types::UInt64 WriteTransferedBytes;
                    Core::Types::UInt64 OtherTransferedBytes;

                    //not sorted
                    Core::Types::Float32 CPUUsage;
                    Core::Types::String ExecutedByUser;
                };

                class ProcessInformation
                {
                public:
                    ProcessInformation();
                    ProcessInformation(const ProcessInformation& Copy);
                    ProcessInformation(Memory::AutoPointer<ProcessData> Data,
                        Collections::AutoVector<ModuleInformation>& Modules,
                        Collections::AutoVector<ThreadInformation>& Threads);
                    const ProcessData& Data()const;
                    Core::Types::UInt32 ModuleCount()const;
                    const ModuleInformation& Module(const Core::Types::UInt32 Index)const;
                    Core::Types::UInt32 ThreadCount()const;
                    const ThreadInformation& Thread(const Core::Types::UInt32 Index)const;
                    void Swap(ProcessInformation& Other);
                protected:
                    Memory::AutoPointer<ProcessData> m_Data;
                    Collections::AutoVector<ModuleInformation> m_Modules;
                    Collections::AutoVector<ThreadInformation> m_Threads;
                };
            }
        }
    }    
}

#endif // RF_DIAGNOSTICS_PROFILING_PROCESS_PROCESSINFORMATION_HPP
