#ifndef RF_SYSTEM_THREADING_THREAD_HPP
#define RF_SYSTEM_THREADING_THREAD_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Threading/Thread.hpp>
#include <RadonFramework/Threading/ThreadError.hpp>
#include <RadonFramework/Threading/ThreadPriority.hpp>
#include <RadonFramework/Time/TimeSpan.hpp>
#include <RadonFramework/Collections/BitArray.hpp>

namespace RadonFramework { namespace System { namespace Threading {

/// This function will be called by RadonFramework_Init function.
void Dispatch();

/** This function will be called by RadonFraemwork_Init function to
* check if the dispatching was successfully.
**/
RF_Type::Bool IsSuccessfullyDispatched();

/// This function is for debugging purpose and return all unassigned functions.
void GetNotDispatchedFunctions(Collections::List<RF_Type::String>& Result);

using IsAliveCallback = RF_Type::Bool(*)(void* Data);
using IsRunningCallback = RF_Type::Bool(*)(void* Data);
using CreateCallback = void*(*)(RF_Thread::Thread& Instance, RF_Type::UInt64& PID);
using DestroyCallback = void(*)(void* Data);
using RenameCallback = void(*)(void* Data, const RF_Type::String& Name);
using SleepCallback = void(*)(const RF_Time::TimeSpan& Delta);
using GetProcessIdCallback = RF_Type::UInt64(*)();
using WaitCallback = void(*)(void* Data, const RF_Time::TimeSpan& Delta);
using JoinCallback = void(*)(void* Data);
using SetPriorityCallback = void(*)(void* Data, RF_Thread::ThreadPriority::Type Value);
using GetPriorityCallback = RF_Thread::ThreadPriority::Type(*)(void* Data);
using SetAffinityMaskCallback = RF_Type::Bool(*)(void* Data, const RF_Collect::BitArray<>& NewMask);
using GetAffinityMaskCallback = RF_Type::Bool(*)(void* Data, RF_Collect::BitArray<>& Mask);
using PostConfigurationCompleteCallback = void(*)(void* Data);
using ShortestPauseCallback = void(*)();

extern IsAliveCallback IsAlive;
extern IsRunningCallback IsRunning;
/**
* If the function succeed then Data will be unequal 0 else it will be set to 0.
* The function creates a new sub-process, execute the Instance->Run() function and
* writes the thread id to PID.
* It will return if an error occurred or after the thread started.
* Call PostConfigurationComplete afterwards to start the Instance->Run() function.
*/
extern CreateCallback Create;
/**
*
*/
extern DestroyCallback Destroy;
extern RenameCallback Rename;
extern SleepCallback Sleep;
extern GetProcessIdCallback GetProcessId;
extern WaitCallback Wait;
extern JoinCallback Join;
extern SetPriorityCallback SetPriority;
extern GetPriorityCallback GetPriority;
extern SetAffinityMaskCallback SetAffinityMask;
extern GetAffinityMaskCallback GetAffinityMask;
/**
* On some architectures it's necessary to configure the thread after it was created.
* To ensure that the configuration was applied before execute Instance->Run()
* the internal thread function will wait till this function was called.
*/
extern PostConfigurationCompleteCallback PostConfigurationComplete;
/// 
extern ShortestPauseCallback ShortestPause;
} } }

#ifndef RF_SHORTHAND_NAMESPACE_SYSTHREAD
#define RF_SHORTHAND_NAMESPACE_SYSTHREAD
namespace RF_SysThread = RadonFramework::System::Threading;
#endif

#endif // !RF_SYSTEM_THREADING_THREAD_HPP
