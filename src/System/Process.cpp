#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Process.hpp"
#include "RadonFramework/Collections/List.hpp"

using namespace RadonFramework::Memory;
using namespace RadonFramework::System::Process;

AutoPointerArray<RF_Type::UInt32> GetProcessList_SystemAPIDispatcher()
{
    GetProcessList = 0;
    Dispatch();
    Assert(GetProcessList != GetProcessList_SystemAPIDispatcher &&
           GetProcessList != 0,
           "Funtion was called and couldn't be dispatched");
    return GetProcessList();
}

RF_Type::UInt32 GetCurrentProcessId_SystemAPIDispatcher()
{
    GetCurrentProcessId = 0;
    Dispatch();
    Assert(GetCurrentProcessId != GetCurrentProcessId_SystemAPIDispatcher &&
           GetCurrentProcessId != 0,
           "Funtion was called and couldn't be dispatched");
    return GetCurrentProcessId();
}

RF_Type::Bool GetGeneralInfo_SystemAPIDispatcher(RF_Type::UInt32 PId, RFPROC::GeneralInfo& Info)
{
    GetGeneralInfo = 0;
    Dispatch();
    Assert(GetGeneralInfo != GetGeneralInfo_SystemAPIDispatcher &&
           GetGeneralInfo != 0,
           "Funtion was called and couldn't be dispatched");
    return GetGeneralInfo(PId, Info);
}

RF_Type::Bool GetIOInfo_SystemAPIDispatcher(RF_Type::UInt32 PId, RFPROC::IOInfo& Info)
{
    GetIOInfo = 0;
    Dispatch();
    Assert(GetIOInfo != GetIOInfo_SystemAPIDispatcher &&
           GetIOInfo != 0,
           "Funtion was called and couldn't be dispatched");
    return GetIOInfo(PId, Info);
}

RF_Type::Bool GetMemoryInfo_SystemAPIDispatcher(RF_Type::UInt32 PId, RFPROC::MemoryInfo& Info)
{
    GetMemoryInfo = 0;
    Dispatch();
    Assert(GetMemoryInfo != GetMemoryInfo_SystemAPIDispatcher &&
           GetMemoryInfo != 0,
           "Funtion was called and couldn't be dispatched");
    return GetMemoryInfo(PId, Info);
}

RF_Type::Bool GetTimingInfo_SystemAPIDispatcher(RF_Type::UInt32 PId, RFPROC::TimingInfo& Info)
{
    GetTimingInfo = 0;
    Dispatch();
    Assert(GetTimingInfo != GetTimingInfo_SystemAPIDispatcher &&
           GetTimingInfo != 0,
           "Funtion was called and couldn't be dispatched");
    return GetTimingInfo(PId, Info);
}

RF_Type::Bool GetModuleInfo_SystemAPIDispatcher(RF_Type::UInt32 PId, RFPROC::ModuleInfo& Info)
{
    GetModuleInfo = 0;
    Dispatch();
    Assert(GetModuleInfo != GetModuleInfo_SystemAPIDispatcher &&
           GetModuleInfo != 0,
           "Funtion was called and couldn't be dispatched");
    return GetModuleInfo(PId, Info);
}

RF_Type::Bool GetThreadInfo_SystemAPIDispatcher(RF_Type::UInt32 PId, RFPROC::ThreadInfoList& Info)
{
    GetThreadInfo = 0;
    Dispatch();
    Assert(GetThreadInfo != GetThreadInfo_SystemAPIDispatcher &&
           GetThreadInfo != 0,
           "Funtion was called and couldn't be dispatched");
    return GetThreadInfo(PId, Info);
}

RF_Type::Int32 ExecuteProgram_SystemAPIDispatcher(const RF_Type::String& Executable,
    const RF_Type::String& Parameters)
{
    ExecuteProgram = 0;
    Dispatch();
    Assert(ExecuteProgram != ExecuteProgram_SystemAPIDispatcher &&
           ExecuteProgram != 0,
           "Function was called and couldn't be dispatched");
	return ExecuteProgram(Executable, Parameters);
}

RFPROC::GetProcessListCallback RFPROC::GetProcessList = GetProcessList_SystemAPIDispatcher;
RFPROC::GetCurrentProcessIdCallback RFPROC::GetCurrentProcessId = GetCurrentProcessId_SystemAPIDispatcher;
RFPROC::GetGeneralInfoCallback RFPROC::GetGeneralInfo = GetGeneralInfo_SystemAPIDispatcher;
RFPROC::GetIOInfoCallback RFPROC::GetIOInfo = GetIOInfo_SystemAPIDispatcher;
RFPROC::GetMemoryInfoCallback RFPROC::GetMemoryInfo = GetMemoryInfo_SystemAPIDispatcher;
RFPROC::GetTimingInfoCallback RFPROC::GetTimingInfo = GetTimingInfo_SystemAPIDispatcher;
RFPROC::GetModuleInfoCallback RFPROC::GetModuleInfo = GetModuleInfo_SystemAPIDispatcher;
RFPROC::GetThreadInfoCallback RFPROC::GetThreadInfo = GetThreadInfo_SystemAPIDispatcher;
RFPROC::ExecuteProgramCallback RFPROC::ExecuteProgram = ExecuteProgram_SystemAPIDispatcher;

RF_Type::Bool RFPROC::IsSuccessfullyDispatched()
{
    RF_Type::Bool result = true;
    result = result && GetProcessList != GetProcessList_SystemAPIDispatcher && GetProcessList != 0;
    result = result && GetCurrentProcessId != GetCurrentProcessId_SystemAPIDispatcher && GetCurrentProcessId != 0;
    result = result && GetGeneralInfo != GetGeneralInfo_SystemAPIDispatcher && GetGeneralInfo != 0;
    result = result && GetIOInfo != GetIOInfo_SystemAPIDispatcher && GetIOInfo != 0;
    result = result && GetMemoryInfo != GetMemoryInfo_SystemAPIDispatcher && GetMemoryInfo != 0;
    result = result && GetTimingInfo != GetTimingInfo_SystemAPIDispatcher && GetTimingInfo != 0;
    result = result && GetModuleInfo != GetModuleInfo_SystemAPIDispatcher && GetModuleInfo != 0;
    result = result && GetThreadInfo != GetThreadInfo_SystemAPIDispatcher && GetThreadInfo != 0;
	result = result && ExecuteProgram != ExecuteProgram_SystemAPIDispatcher && ExecuteProgram != 0;
    return result;
}

void RFPROC::GetNotDispatchedFunctions( RadonFramework::Collections::List<RF_Type::String>& Result )
{
    if (GetProcessList == GetProcessList_SystemAPIDispatcher || GetProcessList == 0) 
        Result.AddLast(RF_Type::String("GetProcessList", sizeof("GetProcessList")));
    if (GetCurrentProcessId == GetCurrentProcessId_SystemAPIDispatcher || GetCurrentProcessId == 0) 
        Result.AddLast(RF_Type::String("GetCurrentProcessId", sizeof("GetCurrentProcessId")));
    if (GetGeneralInfo == GetGeneralInfo_SystemAPIDispatcher || GetGeneralInfo == 0) 
        Result.AddLast(RF_Type::String("GetGeneralInfo", sizeof("GetGeneralInfo")));
    if (GetIOInfo == GetIOInfo_SystemAPIDispatcher || GetIOInfo == 0)
        Result.AddLast(RF_Type::String("GetIOInfo", sizeof("GetIOInfo")));
    if (GetMemoryInfo == GetMemoryInfo_SystemAPIDispatcher || GetMemoryInfo == 0)
        Result.AddLast(RF_Type::String("GetMemoryInfo", sizeof("GetMemoryInfo")));
    if (GetTimingInfo == GetTimingInfo_SystemAPIDispatcher || GetTimingInfo == 0)
        Result.AddLast(RF_Type::String("GetTimingInfo", sizeof("GetTimingInfo")));
    if (GetModuleInfo == GetModuleInfo_SystemAPIDispatcher || GetModuleInfo == 0)
        Result.AddLast(RF_Type::String("GetModuleInfo", sizeof("GetModuleInfo")));
    if (GetThreadInfo == GetThreadInfo_SystemAPIDispatcher || GetThreadInfo == 0)
        Result.AddLast(RF_Type::String("GetThreadInfo", sizeof("GetThreadInfo")));
	if (ExecuteProgram == ExecuteProgram_SystemAPIDispatcher || ExecuteProgram == 0)
		Result.AddLast(RF_Type::String("ExecuteProgram", sizeof("ExecuteProgram")));
}
