#ifndef RF_SYSTEM_TIME_HPP
#define RF_SYSTEM_TIME_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/List.hpp>

namespace RadonFramework { namespace System { namespace Time {
    typedef RadonFramework::Memory::PointerID TimerHandle;

    typedef void (*TimerCallback)(void*);

    /// This function will be called by RadonFramework_Init function.
    void Dispatch();

    /** This function will be called by RadonFraemwork_Init function to
      * check if the dispatching was successfully.
      **/
    RFTYPE::Bool IsSuccessfullyDispatched();

    /// This function is for debugging purpose and return all unassigned functions.
    void GetNotDispatchedFunctions(RadonFramework::Collections::List<RFTYPE::String>& Result);

    typedef TimerHandle (*CreateTimerQueueCallback)(TimerCallback Callback, void* Parameter, RFTYPE::Int32 DueTime, RFTYPE::Int32 Period);
    typedef void (*DeleteTimerQueueCallback)(TimerHandle& Handle);
    /// Get time in 100 nanosecond resolution(GMT).
    typedef RFTYPE::UInt64 (*GetNowCallback)();
    /// Get time offset to UTC in 10 micro second resolution.
    typedef RFTYPE::UInt64 (*GetMinutesWestOfGMTCallback)();
    /// Get time in microsecond resolution.
    typedef RFTYPE::UInt64 (*GetHighResolutionCounterCallback)();
    typedef RFTYPE::Bool (*IsHighResolutionCounterSupportedCallback)();

    extern CreateTimerQueueCallback CreateTimerQueue;
    extern DeleteTimerQueueCallback DeleteTimerQueue;
    extern GetNowCallback GetNow;
    extern GetMinutesWestOfGMTCallback GetMinutesWestOfGMT;
    extern GetHighResolutionCounterCallback GetHighResolutionCounter;
    extern IsHighResolutionCounterSupportedCallback IsHighResolutionCounterSupported;
} } }

namespace RFTIME = RadonFramework::System::Time;

#endif // RF_SYSTEM_TIME_HPP