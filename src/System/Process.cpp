#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Process.hpp"
#include "RadonFramework/Collections/List.hpp"

using namespace RadonFramework::Memory;

AutoPointerArray<RFTYPE::UInt32> GetProcessList_SystemAPIDispatcher()
{
    RFPROC::Dispatch();
    Assert(RFPROC::GetProcessList != GetProcessList_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFPROC::GetProcessList();
}

RFTYPE::UInt32 GetCurrentProcessId_SystemAPIDispatcher()
{
    RFPROC::Dispatch();
    Assert(RFPROC::GetCurrentProcessId != GetCurrentProcessId_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFPROC::GetCurrentProcessId();
}

RFTYPE::Bool GetGeneralInfo_SystemAPIDispatcher(RFTYPE::UInt32 PId, RFPROC::GeneralInfo& Info)
{
    RFPROC::Dispatch();
    Assert(RFPROC::GetGeneralInfo != GetGeneralInfo_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFPROC::GetGeneralInfo(PId, Info);
}

RFTYPE::Bool GetIOInfo_SystemAPIDispatcher(RFTYPE::UInt32 PId, RFPROC::IOInfo& Info)
{
    RFPROC::Dispatch();
    Assert(RFPROC::GetIOInfo != GetIOInfo_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFPROC::GetIOInfo(PId, Info);
}

RFTYPE::Bool GetMemoryInfo_SystemAPIDispatcher(RFTYPE::UInt32 PId, RFPROC::MemoryInfo& Info)
{
    RFPROC::Dispatch();
    Assert(RFPROC::GetMemoryInfo != GetMemoryInfo_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFPROC::GetMemoryInfo(PId, Info);
}

RFTYPE::Bool GetTimingInfo_SystemAPIDispatcher(RFTYPE::UInt32 PId, RFPROC::TimingInfo& Info)
{
    RFPROC::Dispatch();
    Assert(RFPROC::GetTimingInfo != GetTimingInfo_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFPROC::GetTimingInfo(PId, Info);
}

RFTYPE::Bool GetModuleInfo_SystemAPIDispatcher(RFTYPE::UInt32 PId, RFPROC::ModuleInfo& Info)
{
    RFPROC::Dispatch();
    Assert(RFPROC::GetModuleInfo != GetModuleInfo_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFPROC::GetModuleInfo(PId, Info);
}

RFTYPE::Bool GetThreadInfo_SystemAPIDispatcher(RFTYPE::UInt32 PId, RFPROC::ThreadInfoList& Info)
{
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
    result = result && GetProcessList != GetProcessList_SystemAPIDispatcher;
    result = result && GetCurrentProcessId != GetCurrentProcessId_SystemAPIDispatcher;
    result = result && GetGeneralInfo != GetGeneralInfo_SystemAPIDispatcher;
    result = result && GetIOInfo != GetIOInfo_SystemAPIDispatcher;
    result = result && GetMemoryInfo != GetMemoryInfo_SystemAPIDispatcher;
    result = result && GetTimingInfo != GetTimingInfo_SystemAPIDispatcher;
    result = result && GetModuleInfo != GetModuleInfo_SystemAPIDispatcher;
    result = result && GetThreadInfo != GetThreadInfo_SystemAPIDispatcher;
    return result;
}

void RFPROC::GetNotDispatchedFunctions( RadonFramework::Collections::List<RFTYPE::String>& Result )
{
    if (GetProcessList == GetProcessList_SystemAPIDispatcher) 
        Result.AddLast("GetProcessList");
    if (GetCurrentProcessId == GetCurrentProcessId_SystemAPIDispatcher) 
        Result.AddLast("GetCurrentProcessId");
    if (GetGeneralInfo == GetGeneralInfo_SystemAPIDispatcher) 
        Result.AddLast("GetGeneralInfo");
    if (GetIOInfo == GetIOInfo_SystemAPIDispatcher)
        Result.AddLast("GetIOInfo");
    if (GetMemoryInfo == GetMemoryInfo_SystemAPIDispatcher)
        Result.AddLast("GetMemoryInfo");
    if (GetTimingInfo == GetTimingInfo_SystemAPIDispatcher)
        Result.AddLast("GetTimingInfo");
    if (GetModuleInfo == GetModuleInfo_SystemAPIDispatcher)
        Result.AddLast("GetModuleInfo");
    if (GetThreadInfo == GetThreadInfo_SystemAPIDispatcher)
        Result.AddLast("GetThreadInfo");
}
