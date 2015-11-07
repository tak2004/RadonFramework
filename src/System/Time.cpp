#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Time.hpp"
#include "RadonFramework/Time/DateTime.hpp"

using namespace RadonFramework::System;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::Time;
using namespace RadonFramework::Collections;

TimerHandle CreateTimerQueue_SystemAPIDispatcher(TimerCallback Callback, 
    void* Parameter, RF_Type::Int32 DueTime, RF_Type::Int32 Period)
{
    CreateTimerQueue = 0;
    Dispatch();
    Assert(CreateTimerQueue != CreateTimerQueue_SystemAPIDispatcher &&
           CreateTimerQueue != 0,
           "Funtion was called and couldn't be dispatched");
    return CreateTimerQueue(Callback, Parameter, DueTime, Period);
}

void DeleteTimerQueue_SystemAPIDispatcher(TimerHandle& Handle)
{
    DeleteTimerQueue = 0;
    Dispatch();
    Assert(DeleteTimerQueue != DeleteTimerQueue_SystemAPIDispatcher &&
           DeleteTimerQueue != 0,
           "Funtion was called and couldn't be dispatched");
    DeleteTimerQueue(Handle);
}

UInt64 GetNow_SystemAPIDispatcher()
{
    GetNow = 0;
    Dispatch();
    Assert(GetNow != GetNow_SystemAPIDispatcher &&
           GetNow != 0,
           "Funtion was called and couldn't be dispatched");
    return GetNow();
}

UInt64 GetMinutesWestOfGMT_SystemAPIDispatcher()
{
    GetMinutesWestOfGMT = 0;
    Dispatch();
    Assert(GetMinutesWestOfGMT != GetMinutesWestOfGMT_SystemAPIDispatcher &&
           GetMinutesWestOfGMT != 0,
           "Funtion was called and couldn't be dispatched");
    return GetMinutesWestOfGMT();
}

void GetStringFormattedTime_SystemAPIDispatcher(const RF_Time::DateTime& Time,
    const RF_Type::String& Format, RF_Type::String& FormattedString)
{
    GetStringFormattedTime = 0;
    Dispatch();
    Assert(GetStringFormattedTime != GetStringFormattedTime_SystemAPIDispatcher &&
           GetStringFormattedTime != 0,
           "Funtion was called and couldn't be dispatched");
    return GetStringFormattedTime(Time, Format, FormattedString);
}

UInt64 GetHighResolutionCounter_SystemAPIDispatcher()
{
    GetHighResolutionCounter = 0;
    Dispatch();
    Assert(GetHighResolutionCounter != GetHighResolutionCounter_SystemAPIDispatcher &&
           GetHighResolutionCounter != 0,
           "Funtion was called and couldn't be dispatched");
    return GetHighResolutionCounter();
}

Bool IsHighResolutionCounterSupported_SystemAPIDispatcher()
{
    IsHighResolutionCounterSupported = 0;
    Dispatch();
    Assert(IsHighResolutionCounterSupported != IsHighResolutionCounterSupported_SystemAPIDispatcher &&
           IsHighResolutionCounterSupported != 0,
           "Funtion was called and couldn't be dispatched");
    return IsHighResolutionCounterSupported();
}

CreateTimerQueueCallback RF_SysTime::CreateTimerQueue = CreateTimerQueue_SystemAPIDispatcher;
DeleteTimerQueueCallback RF_SysTime::DeleteTimerQueue = DeleteTimerQueue_SystemAPIDispatcher;
GetNowCallback RF_SysTime::GetNow = GetNow_SystemAPIDispatcher;
GetMinutesWestOfGMTCallback RF_SysTime::GetMinutesWestOfGMT = GetMinutesWestOfGMT_SystemAPIDispatcher;
GetStringFormattedTimeCallback RF_SysTime::GetStringFormattedTime = GetStringFormattedTime_SystemAPIDispatcher;
GetHighResolutionCounterCallback RF_SysTime::GetHighResolutionCounter = GetHighResolutionCounter_SystemAPIDispatcher;
IsHighResolutionCounterSupportedCallback RF_SysTime::IsHighResolutionCounterSupported = IsHighResolutionCounterSupported_SystemAPIDispatcher;

Bool RF_SysTime::IsSuccessfullyDispatched()
{
    Bool result=true;
    result=result && CreateTimerQueue != CreateTimerQueue_SystemAPIDispatcher && CreateTimerQueue != 0;
    result=result && DeleteTimerQueue != DeleteTimerQueue_SystemAPIDispatcher && DeleteTimerQueue != 0;
    result=result && GetNow != GetNow_SystemAPIDispatcher && GetNow != 0;
    result=result && GetMinutesWestOfGMT != GetMinutesWestOfGMT_SystemAPIDispatcher && GetMinutesWestOfGMT != 0;
    result=result && GetStringFormattedTime != GetStringFormattedTime_SystemAPIDispatcher && GetStringFormattedTime != 0;
    result=result && GetHighResolutionCounter != GetHighResolutionCounter_SystemAPIDispatcher && GetHighResolutionCounter != 0;
    result=result && IsHighResolutionCounterSupported != IsHighResolutionCounterSupported_SystemAPIDispatcher && IsHighResolutionCounterSupported != 0;
    return result;
}

void RF_SysTime::GetNotDispatchedFunctions(List<RF_Type::String>& Result)
{
    if (CreateTimerQueue == CreateTimerQueue_SystemAPIDispatcher || CreateTimerQueue == 0) 
        Result.AddLast(RF_Type::String("CreateTimerQueue", sizeof("CreateTimerQueue")));
    if (DeleteTimerQueue == DeleteTimerQueue_SystemAPIDispatcher || DeleteTimerQueue == 0) 
        Result.AddLast(RF_Type::String("DeleteTimerQueue", sizeof("DeleteTimerQueue")));
    if (GetNow == GetNow_SystemAPIDispatcher || GetNow == 0) 
        Result.AddLast(RF_Type::String("GetNow", sizeof("GetNow")));
    if (GetMinutesWestOfGMT == GetMinutesWestOfGMT_SystemAPIDispatcher || GetMinutesWestOfGMT == 0) 
        Result.AddLast(RF_Type::String("GetMinutesWestOfGMT", sizeof("GetMinutesWestOfGMT")));
    if(GetStringFormattedTime == GetStringFormattedTime_SystemAPIDispatcher || GetStringFormattedTime == 0)
        Result.AddLast(RF_Type::String("GetStringFormattedTime", sizeof("GetStringFormattedTime")));
    if (GetHighResolutionCounter == GetHighResolutionCounter_SystemAPIDispatcher || GetHighResolutionCounter == 0) 
        Result.AddLast(RF_Type::String("GetHighResolutionCounter", sizeof("GetHighResolutionCounter")));
    if (IsHighResolutionCounterSupported == IsHighResolutionCounterSupported_SystemAPIDispatcher || IsHighResolutionCounterSupported == 0) 
        Result.AddLast(RF_Type::String("IsHighResolutionCounterSupported", sizeof("IsHighResolutionCounterSupported")));
}