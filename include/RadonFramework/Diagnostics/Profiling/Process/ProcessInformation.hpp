#ifndef RF_DIAGNOSTICS_PROFILING_PROCESS_PROCESSINFORMATION_HPP
#define RF_DIAGNOSTICS_PROFILING_PROCESS_PROCESSINFORMATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/System/Process/GeneralInfo.hpp>
#include <RadonFramework/System/Process/IOInfo.hpp>
#include <RadonFramework/System/Process/MemoryInfo.hpp>
#include <RadonFramework/System/Process/TimingInfo.hpp>
#include <RadonFramework/System/Process/ModuleInfo.hpp>
#include <RadonFramework/System/Process/ThreadInfo.hpp>

namespace RadonFramework { namespace Diagnostics { namespace Profiling { namespace Process {

class ProcessInformation
{
public:
    ProcessInformation();

    static RF_Mem::AutoPointer<ProcessInformation> GetCurrentProcessInformation();
    static RF_Mem::AutoPointerArray<ProcessInformation> GetProcessList();

    inline const RadonFramework::System::Process::TimingInfo& GetTimingInfo()const;
    inline const RadonFramework::System::Process::MemoryInfo& GetMemoryInfo()const;
    inline const RadonFramework::System::Process::IOInfo& GetIOInfo()const;
    inline const RadonFramework::System::Process::GeneralInfo& GetGeneralInfo()const;
    inline const RadonFramework::System::Process::ModuleInfo& GetModules()const;
    inline const RadonFramework::System::Process::ThreadInfoList& GetThreads()const;
protected:
    RadonFramework::System::Process::GeneralInfo m_GeneralInfo;
    RadonFramework::System::Process::IOInfo m_IOInfo;
    RadonFramework::System::Process::MemoryInfo m_MemoryInfo;
    RadonFramework::System::Process::TimingInfo m_TimingInfo;
    RadonFramework::System::Process::ModuleInfo m_Modules;
    RadonFramework::System::Process::ThreadInfoList m_Threads;
};

inline const RadonFramework::System::Process::TimingInfo& ProcessInformation::GetTimingInfo()const
{
    return this->m_TimingInfo;
}

inline const RadonFramework::System::Process::MemoryInfo& ProcessInformation::GetMemoryInfo()const
{
    return this->m_MemoryInfo;
}

inline const RadonFramework::System::Process::IOInfo& ProcessInformation::GetIOInfo()const
{
    return this->m_IOInfo;
}

inline const RadonFramework::System::Process::GeneralInfo& ProcessInformation::GetGeneralInfo()const
{
    return this->m_GeneralInfo;
}

inline const RadonFramework::System::Process::ModuleInfo& ProcessInformation::GetModules()const
{
    return this->m_Modules;
}

inline const RadonFramework::System::Process::ThreadInfoList& ProcessInformation::GetThreads()const
{
    return this->m_Threads;
}

} } } }

#ifndef RF_SHORTHAND_NAMESPACE_PROF
#define RF_SHORTHAND_NAMESPACE_PROF
namespace RF_Prof = RadonFramework::Diagnostics::Profiling;
#endif


#endif // RF_DIAGNOSTICS_PROFILING_PROCESS_PROCESSINFORMATION_HPP
