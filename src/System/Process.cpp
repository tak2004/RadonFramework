#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Process.hpp"
#include "RadonFramework/Collections/List.hpp"

using namespace RadonFramework::Memory;
using namespace RadonFramework::System::Process;

AutoPointerArray<RFTYPE::UInt32> GetProcessList_SystemAPIDispatcher()
{
    GetProcessList = 0;
    Dispatch();
    Assert(GetProcessList != GetProcessList_SystemAPIDispatcher &&
           GetProcessList != 0,
           "Funtion was called and couldn't be dispatched");
    return GetProcessList();
}

RFTYPE::UInt32 GetCurrentProcessId_SystemAPIDispatcher()
{
    GetCurrentProcessId = 0;
    Dispatch();
    Assert(GetCurrentProcessId != GetCurrentProcessId_SystemAPIDispatcher &&
           GetCurrentProcessId != 0,
           "Funtion was called and couldn't be dispatched");
    return GetCurrentProcessId();
}

RFTYPE::Bool GetGeneralInfo_SystemAPIDispatcher(RFTYPE::UInt32 PId, RFPROC::GeneralInfo& Info)
{
    GetGeneralInfo = 0;
    Dispatch();
    Assert(GetGeneralInfo != GetGeneralInfo_SystemAPIDispatcher &&
           GetGeneralInfo != 0,
           "Funtion was called and couldn't be dispatched");
    return GetGeneralInfo(PId, Info);
}

RFTYPE::Bool GetIOInfo_SystemAPIDispatcher(RFTYPE::UInt32 PId, RFPROC::IOInfo& Info)
{
    GetIOInfo = 0;
    Dispatch();
    Assert(GetIOInfo != GetIOInfo_SystemAPIDispatcher &&
           GetIOInfo != 0,
           "Funtion was called and couldn't be dispatched");
    return GetIOInfo(PId, Info);
}

RFTYPE::Bool GetMemoryInfo_SystemAPIDispatcher(RFTYPE::UInt32 PId, RFPROC::MemoryInfo& Info)
{
    GetMemoryInfo = 0;
    Dispatch();
    Assert(GetMemoryInfo != GetMemoryInfo_SystemAPIDispatcher &&
           GetMemoryInfo != 0,
           "Funtion was called and couldn't be dispatched");
    return GetMemoryInfo(PId, Info);
}

RFTYPE::Bool GetTimingInfo_SystemAPIDispatcher(RFTYPE::UInt32 PId, RFPROC::TimingInfo& Info)
{
    GetTimingInfo = 0;
    Dispatch();
    Assert(GetTimingInfo != GetTimingInfo_SystemAPIDispatcher &&
           GetTimingInfo != 0,
           "Funtion was called and couldn't be dispatched");
    return GetTimingInfo(PId, Info);
}

RFTYPE::Bool GetModuleInfo_SystemAPIDispatcher(RFTYPE::UInt32 PId, RFPROC::ModuleInfo& Info)
{
    GetModuleInfo = 0;
    Dispatch();
    Assert(GetModuleInfo != GetModuleInfo_SystemAPIDispatcher &&
           GetModuleInfo != 0,
           "Funtion was called and couldn't be dispatched");
    return GetModuleInfo(PId, Info);
}

RFTYPE::Bool GetThreadInfo_SystemAPIDispatcher(RFTYPE::UInt32 PId, RFPROC::ThreadInfoList& Info)
{
    GetThreadInfo = 0;
    Dispatch();
    Assert(GetThreadInfo != GetThreadInfo_SystemAPIDispatcher &&
           GetThreadInfo != 0,
           "Funtion was called and couldn't be dispatched");
    return GetThreadInfo(PId, Info);
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
