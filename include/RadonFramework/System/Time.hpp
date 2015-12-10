#ifndef RF_SYSTEM_TIME_HPP
#define RF_SYSTEM_TIME_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/List.hpp>

namespace RadonFramework { namespace Time { struct DateTime; } }
namespace RF_Time = RadonFramework::Time;

namespace RadonFramework { namespace System { namespace Time {

typedef RF_Mem::PointerID TimerHandle;

typedef void (*TimerCallback)(void*);

/// This function will be called by RadonFramework_Init function.
void Dispatch();

/** This function will be called by RadonFraemwork_Init function to
    * check if the dispatching was successfully.
    **/
RF_Type::Bool IsSuccessfullyDispatched();

/// This function is for debugging purpose and return all unassigned functions.
void GetNotDispatchedFunctions(RadonFramework::Collections::List<RF_Type::String>& Result);

using CreateTimerQueueCallback = TimerHandle(*)(TimerCallback Callback, 
                                                void* Parameter, 
                                                RF_Type::Int32 DueTime, 
                                                RF_Type::Int32 Period);

using DeleteTimerQueueCallback = void(*)(TimerHandle& Handle);

/// Get time in 100 nanosecond resolution(GMT).
using GetNowCallback = RF_Type::UInt64(*)();

/// Get time offset to UTC in 10 micro second resolution.
using GetMinutesWestOfGMTCallback = RF_Type::UInt64(*)();

/// Format the time in specified string format.
using GetStringFormattedTimeCallback = void(*)(const RF_Time::DateTime& Time,
                                                const RF_Type::String& Format, 
                                                RF_Type::String& FormattedString);

/// Get time in microsecond resolution.
using GetHighResolutionCounterCallback = RF_Type::UInt64(*)();

using IsHighResolutionCounterSupportedCallback = RF_Type::Bool(*)();

extern CreateTimerQueueCallback CreateTimerQueue;
extern DeleteTimerQueueCallback DeleteTimerQueue;
extern GetNowCallback GetNow;
extern GetMinutesWestOfGMTCallback GetMinutesWestOfGMT;
extern GetStringFormattedTimeCallback GetStringFormattedTime;
extern GetHighResolutionCounterCallback GetHighResolutionCounter;
extern IsHighResolutionCounterSupportedCallback IsHighResolutionCounterSupported;

} } }

#ifndef RF_SHORTHAND_NAMESPACE_SYSTIME
#define RF_SHORTHAND_NAMESPACE_SYSTIME
namespace RF_SysTime = RadonFramework::System::Time;
#endif

#endif // RF_SYSTEM_TIME_HPP