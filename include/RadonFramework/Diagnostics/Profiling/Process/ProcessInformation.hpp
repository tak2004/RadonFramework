#ifndef RF_DIAGNOSTICS_PROFILING_PROCESS_PROCESSINFORMATION_HPP
#define RF_DIAGNOSTICS_PROFILING_PROCESS_PROCESSINFORMATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

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

    static Memory::AutoPointer<ProcessInformation> GetCurrentProcessInformation();
    static Memory::AutoPointerArray<ProcessInformation> GetProcessList();

    inline const RFPROC::TimingInfo& GetTimingInfo()const;
    inline const RFPROC::MemoryInfo& GetMemoryInfo()const;
    inline const RFPROC::IOInfo& GetIOInfo()const;
    inline const RFPROC::GeneralInfo& GetGeneralInfo()const;
    inline const RFPROC::ModuleInfo& GetModules()const;
    inline const RFPROC::ThreadInfoList& GetThreads()const;
protected:
    RFPROC::GeneralInfo m_GeneralInfo;
    RFPROC::IOInfo m_IOInfo;
    RFPROC::MemoryInfo m_MemoryInfo;
    RFPROC::TimingInfo m_TimingInfo;
    RFPROC::ModuleInfo m_Modules;
    RFPROC::ThreadInfoList m_Threads;
};

inline const RFPROC::TimingInfo& ProcessInformation::GetTimingInfo()const
{
    return this->m_TimingInfo;
}

inline const RFPROC::MemoryInfo& ProcessInformation::GetMemoryInfo()const
{
    return this->m_MemoryInfo;
}

inline const RFPROC::IOInfo& ProcessInformation::GetIOInfo()const
{
    return this->m_IOInfo;
}

inline const RFPROC::GeneralInfo& ProcessInformation::GetGeneralInfo()const
{
    return this->m_GeneralInfo;
}

inline const RFPROC::ModuleInfo& ProcessInformation::GetModules()const
{
    return this->m_Modules;
}

inline const RFPROC::ThreadInfoList& ProcessInformation::GetThreads()const
{
    return this->m_Threads;
}

} } } }

#endif // RF_DIAGNOSTICS_PROFILING_PROCESS_PROCESSINFORMATION_HPP
