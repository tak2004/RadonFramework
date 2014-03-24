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
RFTYPE::Bool IsSuccessfullyDispatched();
    
/// This function is for debugging purpose and return all unassigned functions.
void GetNotDispatchedFunctions(Collections::List<RFTYPE::String>& Result);

typedef RadonFramework::Memory::AutoPointerArray<RFTYPE::UInt32> (*GetProcessListCallback)();
typedef RFTYPE::UInt32 (*GetCurrentProcessIdCallback)();
typedef RFTYPE::Bool (*GetGeneralInfoCallback)(RFTYPE::UInt32 PId, GeneralInfo& Info);
typedef RFTYPE::Bool (*GetIOInfoCallback)(RFTYPE::UInt32 PId, IOInfo& Info);
typedef RFTYPE::Bool (*GetMemoryInfoCallback)(RFTYPE::UInt32 PId, MemoryInfo& Info);
typedef RFTYPE::Bool (*GetTimingInfoCallback)(RFTYPE::UInt32 PId, TimingInfo& Info);
typedef RFTYPE::Bool (*GetModuleInfoCallback)(RFTYPE::UInt32 PId, ModuleInfo& Info);
typedef RFTYPE::Bool (*GetThreadInfoCallback)(RFTYPE::UInt32 PId, ThreadInfoList& Info);

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