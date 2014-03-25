#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Profiling/Process/ProcessInformation.hpp"
#include "RadonFramework/System/Process.hpp"

using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Diagnostics::Profiling::Process;

ProcessInformation::ProcessInformation()
{

}

AutoPointer<ProcessInformation> ProcessInformation::GetCurrentProcessInformation()
{
    AutoPointer<ProcessInformation> result(new ProcessInformation);
    UInt32 pid = RFPROC::GetCurrentProcessId();
    RFPROC::GetGeneralInfo(pid, result->m_GeneralInfo);
    RFPROC::GetIOInfo(pid, result->m_IOInfo);
    RFPROC::GetMemoryInfo(pid, result->m_MemoryInfo);
    RFPROC::GetTimingInfo(pid, result->m_TimingInfo);
    RFPROC::GetModuleInfo(pid, result->m_Modules);
    RFPROC::GetThreadInfo(pid, result->m_Threads);
    return result;
}

AutoPointerArray<ProcessInformation> ProcessInformation::GetProcessList()
{
    AutoPointerArray<UInt32> pidList = RFPROC::GetProcessList();
    AutoPointerArray<ProcessInformation> result(new ProcessInformation[pidList.Count()], pidList.Count());
    for (Size i = 0; i < pidList.Count(); ++i)
    {
        RFPROC::GetGeneralInfo(pidList[i], result[i].m_GeneralInfo);
        RFPROC::GetIOInfo(pidList[i], result[i].m_IOInfo);
        RFPROC::GetMemoryInfo(pidList[i], result[i].m_MemoryInfo);
        RFPROC::GetTimingInfo(pidList[i], result[i].m_TimingInfo);
        RFPROC::GetModuleInfo(pidList[i], result[i].m_Modules);
        RFPROC::GetThreadInfo(pidList[i], result[i].m_Threads);
    }
    return result;
}