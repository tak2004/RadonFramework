#ifndef RF_SYSTEM_PROCESS_HPP
#define RF_SYSTEM_PROCESS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/System/Process/ModuleInfo.hpp>
#include <RadonFramework/System/Process/ThreadInfo.hpp>

namespace RadonFramework { namespace System { namespace Process {

// forward declaration
class GeneralInfo;
struct IOInfo;
struct MemoryInfo;
struct TimingInfo;

/// This function will be called by RadonFramework_Init function.
void Dispatch();

/** This function will be called by RadonFraemwork_Init function to
  * check if the dispatching was successfully.
  **/
RF_Type::Bool IsSuccessfullyDispatched();
    
/// This function is for debugging purpose and return all unassigned functions.
void GetNotDispatchedFunctions(Collections::List<RF_Type::String>& Result);

typedef RF_Mem::AutoPointerArray<RF_Type::UInt32> (*GetProcessListCallback)();
typedef RF_Type::UInt32 (*GetCurrentProcessIdCallback)();
typedef RF_Type::Bool (*GetGeneralInfoCallback)(RF_Type::UInt32 PId, GeneralInfo& Info);
typedef RF_Type::Bool (*GetIOInfoCallback)(RF_Type::UInt32 PId, IOInfo& Info);
typedef RF_Type::Bool (*GetMemoryInfoCallback)(RF_Type::UInt32 PId, MemoryInfo& Info);
typedef RF_Type::Bool (*GetTimingInfoCallback)(RF_Type::UInt32 PId, TimingInfo& Info);
typedef RF_Type::Bool (*GetModuleInfoCallback)(RF_Type::UInt32 PId, ModuleInfo& Info);
typedef RF_Type::Bool (*GetThreadInfoCallback)(RF_Type::UInt32 PId, ThreadInfoList& Info);

extern GetProcessListCallback GetProcessList;
extern GetCurrentProcessIdCallback GetCurrentProcessId;
extern GetGeneralInfoCallback GetGeneralInfo;
extern GetIOInfoCallback GetIOInfo;
extern GetMemoryInfoCallback GetMemoryInfo;
extern GetTimingInfoCallback GetTimingInfo;
extern GetModuleInfoCallback GetModuleInfo;
extern GetThreadInfoCallback GetThreadInfo;

} } }

namespace RFPROC = RadonFramework::System::Process;

#endif // RF_SYSTEM_PROCESS_HPP