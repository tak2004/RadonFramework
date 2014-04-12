#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Process.hpp"
#include "RadonFramework/Collections/List.hpp"

using namespace RadonFramework::Memory;

AutoPointerArray<RFTYPE::UInt32> GetProcessList_SystemAPIDispatcher()
{
    RFPROC::GetProcessList = 0;
    RFPROC::Dispatch();
    Assert(RFPROC::GetProcessList != GetProcessList_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFPROC::GetProcessList();
}

RFTYPE::UInt32 GetCurrentProcessId_SystemAPIDispatcher()
{
    RFPROC::GetCurrentProcessId = 0;
    RFPROC::Dispatch();
    Assert(RFPROC::GetCurrentProcessId != GetCurrentProcessId_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFPROC::GetCurrentProcessId();
}

RFTYPE::Bool GetGeneralInfo_SystemAPIDispatcher(RFTYPE::UInt32 PId, RFPROC::GeneralInfo& Info)
{
    RFPROC::GetGeneralInfo = 0;
    RFPROC::Dispatch();
    Assert(RFPROC::GetGeneralInfo != GetGeneralInfo_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFPROC::GetGeneralInfo(PId, Info);
}

RFTYPE::Bool GetIOInfo_SystemAPIDispatcher(RFTYPE::UInt32 PId, RFPROC::IOInfo& Info)
{
    RFPROC::GetIOInfo = 0;
    RFPROC::Dispatch();
    Assert(RFPROC::GetIOInfo != GetIOInfo_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFPROC::GetIOInfo(PId, Info);
}

RFTYPE::Bool GetMemoryInfo_SystemAPIDispatcher(RFTYPE::UInt32 PId, RFPROC::MemoryInfo& Info)
{
    RFPROC::GetMemoryInfo = 0;
    RFPROC::Dispatch();
    Assert(RFPROC::GetMemoryInfo != GetMemoryInfo_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFPROC::GetMemoryInfo(PId, Info);
}

RFTYPE::Bool GetTimingInfo_SystemAPIDispatcher(RFTYPE::UInt32 PId, RFPROC::TimingInfo& Info)
{
    RFPROC::GetTimingInfo = 0;
    RFPROC::Dispatch();
    Assert(RFPROC::GetTimingInfo != GetTimingInfo_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFPROC::GetTimingInfo(PId, Info);
}

RFTYPE::Bool GetModuleInfo_SystemAPIDispatcher(RFTYPE::UInt32 PId, RFPROC::ModuleInfo& Info)
{
    RFPROC::GetModuleInfo = 0;
    RFPROC::Dispatch();
    Assert(RFPROC::GetModuleInfo != GetModuleInfo_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFPROC::GetModuleInfo(PId, Info);
}

RFTYPE::Bool GetThreadInfo_SystemAPIDispatcher(RFTYPE::UInt32 PId, RFPROC::ThreadInfoList& Info)
{
    RFPROC::GetThreadInfo = 0;
    RFPROC::Dispatch();
    Assert(RFPROC::GetThreadInfo != GetThreadInfo_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFPROC::GetThreadInfo(PId, Info);
}

RFPROC::GetProcessListCallback RFPROC::GetProcessList = GetProcessList_SystemAPIDispatcher;
RFPROC::GetCurrentProcessIdCallback RFPROC::GetCurrentProcessId = GetCurrentProcessId_SystemAPIDispatcher;
RFPROC::GetGeneralInfoCallback RFPROC::GetGeneralInfo = GetGeneralInfo_SystemAPIDispatcher;
RFPROC::GetIOInfoCallback RFPROC::GetIOInfo = GetIOInfo_SystemAPIDispatcher;
RFPROC::GetMemoryInfoCallback RFPROC::GetMemoryInfo = GetMemoryInfo_SystemAPIDispatcher;
RFPROC::GetTimingInfoCallback RFPROC::GetTimingInfo = GetTimingInfo_SystemAPIDispatcher;
RFPROC::GetModuleInfoCallback RFPROC::GetModuleInfo = GetModuleInfo_SystemAPIDispatcher;
RFPROC::GetThreadInfoCallback RFPROC::GetThreadInfo = GetThreadInfo_SystemAPIDispatcher;

RFTYPE::Bool RFPROC::IsSuccessfullyDispatched()
{
    RFTYPE::Bool result = true;
    result = result && GetProcessList != GetProcessList_SystemAPIDispatcher && GetProcessList != 0;
    result = result && GetCurrentProcessId != GetCurrentProcessId_SystemAPIDispatcher && GetCurrentProcessId != 0;
    result = result && GetGeneralInfo != GetGeneralInfo_SystemAPIDispatcher && GetGeneralInfo != 0;
    result = result && GetIOInfo != GetIOInfo_SystemAPIDispatcher && GetIOInfo != 0;
    result = result && GetMemoryInfo != GetMemoryInfo_SystemAPIDispatcher && GetMemoryInfo != 0;
    result = result && GetTimingInfo != GetTimingInfo_SystemAPIDispatcher && GetTimingInfo != 0;
    result = result && GetModuleInfo != GetModuleInfo_SystemAPIDispatcher && GetModuleInfo != 0;
    result = result && GetThreadInfo != GetThreadInfo_SystemAPIDispatcher && GetThreadInfo != 0;
    return result;
}

void RFPROC::GetNotDispatchedFunctions( RadonFramework::Collections::List<RFTYPE::String>& Result )
{
    if (GetProcessList == GetProcessList_SystemAPIDispatcher || GetProcessList == 0) 
        Result.AddLast("GetProcessList");
    if (GetCurrentProcessId == GetCurrentProcessId_SystemAPIDispatcher || GetCurrentProcessId == 0) 
        Result.AddLast("GetCurrentProcessId");
    if (GetGeneralInfo == GetGeneralInfo_SystemAPIDispatcher || GetGeneralInfo == 0) 
        Result.AddLast("GetGeneralInfo");
    if (GetIOInfo == GetIOInfo_SystemAPIDispatcher || GetIOInfo == 0)
        Result.AddLast("GetIOInfo");
    if (GetMemoryInfo == GetMemoryInfo_SystemAPIDispatcher || GetMemoryInfo == 0)
        Result.AddLast("GetMemoryInfo");
    if (GetTimingInfo == GetTimingInfo_SystemAPIDispatcher || GetTimingInfo == 0)
        Result.AddLast("GetTimingInfo");
    if (GetModuleInfo == GetModuleInfo_SystemAPIDispatcher || GetModuleInfo == 0)
        Result.AddLast("GetModuleInfo");
    if (GetThreadInfo == GetThreadInfo_SystemAPIDispatcher || GetThreadInfo == 0)
        Result.AddLast("GetThreadInfo");
}
