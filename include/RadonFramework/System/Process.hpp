#ifndef RF_SYSTEM_PROCESS_HPP
#define RF_SYSTEM_PROCESS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/System/Process/ModuleInfo.hpp>
#include <RadonFramework/System/Process/ThreadInfo.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>

namespace RadonFramework::System::Process
{
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

using GetProcessListCallback = RF_Mem::AutoPointerArray<RF_Type::UInt32> (*)();

using GetCurrentProcessIdCallback = RF_Type::UInt32 (*)();

using GetGeneralInfoCallback = RF_Type::Bool (*)(RF_Type::UInt32 PId,
                                                 GeneralInfo& Info);

using GetIOInfoCallback = RF_Type::Bool (*)(RF_Type::UInt32 PId, IOInfo& Info);

using GetMemoryInfoCallback = RF_Type::Bool (*)(RF_Type::UInt32 PId,
                                                MemoryInfo& Info);

using GetTimingInfoCallback = RF_Type::Bool (*)(RF_Type::UInt32 PId,
                                                TimingInfo& Info);

using GetModuleInfoCallback = RF_Type::Bool (*)(RF_Type::UInt32 PId,
                                                ModuleInfo& Info);

using GetThreadInfoCallback = RF_Type::Bool (*)(RF_Type::UInt32 PId,
                                                ThreadInfoList& Info);

using ExecuteProgramCallback =
    RF_Type::Int32 (*)(const RF_Type::String& Executable,
                       const RF_Type::String& Parameters);

using OpenWithDefaultApplicationCallback =
    RF_Type::Bool (*)(const RF_Type::String& What);

extern GetProcessListCallback GetProcessList;
extern GetCurrentProcessIdCallback GetCurrentProcessId;
extern GetGeneralInfoCallback GetGeneralInfo;
extern GetIOInfoCallback GetIOInfo;
extern GetMemoryInfoCallback GetMemoryInfo;
extern GetTimingInfoCallback GetTimingInfo;
extern GetModuleInfoCallback GetModuleInfo;
extern GetThreadInfoCallback GetThreadInfo;
extern ExecuteProgramCallback ExecuteProgram;
extern OpenWithDefaultApplicationCallback OpenWithDefaultApplication;

}  // namespace RadonFramework::System::Process

namespace RFPROC = RadonFramework::System::Process;

#ifndef RF_SHORTHAND_NAMESPACE_PROC
#define RF_SHORTHAND_NAMESPACE_PROC
namespace RF_SysProc = RadonFramework::System::Process;
#endif

#endif  // RF_SYSTEM_PROCESS_HPP