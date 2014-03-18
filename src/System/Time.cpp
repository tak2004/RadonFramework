#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Time.hpp"

using namespace RadonFramework::System;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::Time;
using namespace RadonFramework::Collections;

TimerHandle CreateTimerQueue_SystemAPIDispatcher(TimerCallback Callback, 
    void* Parameter, RFTYPE::Int32 DueTime, RFTYPE::Int32 Period)
{
    Dispatch();
    Assert(CreateTimerQueue != CreateTimerQueue_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return CreateTimerQueue(Callback, Parameter, DueTime, Period);
}

void DeleteTimerQueue_SystemAPIDispatcher(TimerHandle& Handle)
{
    Dispatch();
    Assert(DeleteTimerQueue != DeleteTimerQueue_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    DeleteTimerQueue(Handle);
}

UInt64 GetNow_SystemAPIDispatcher()
{
    Dispatch();
    Assert(GetNow != GetNow_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return GetNow();
}

UInt64 GetMinutesWestOfGMT_SystemAPIDispatcher()
{
    Dispatch();
    Assert(GetMinutesWestOfGMT != GetMinutesWestOfGMT_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return GetMinutesWestOfGMT();
}

UInt64 GetHighResolutionCounter_SystemAPIDispatcher()
{
    Dispatch();
    Assert(GetHighResolutionCounter != GetHighResolutionCounter_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return GetHighResolutionCounter();
}

Bool IsHighResolutionCounterSupported_SystemAPIDispatcher()
{
    Dispatch();
    Assert(IsHighResolutionCounterSupported != IsHighResolutionCounterSupported_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return IsHighResolutionCounterSupported();
}

CreateTimerQueueCallback RFTIME::CreateTimerQueue = CreateTimerQueue_SystemAPIDispatcher;
DeleteTimerQueueCallback RFTIME::DeleteTimerQueue = DeleteTimerQueue_SystemAPIDispatcher;
GetNowCallback RFTIME::GetNow = GetNow_SystemAPIDispatcher;
GetMinutesWestOfGMTCallback RFTIME::GetMinutesWestOfGMT = GetMinutesWestOfGMT_SystemAPIDispatcher;
GetHighResolutionCounterCallback RFTIME::GetHighResolutionCounter = GetHighResolutionCounter_SystemAPIDispatcher;
IsHighResolutionCounterSupportedCallback RFTIME::IsHighResolutionCounterSupported = IsHighResolutionCounterSupported_SystemAPIDispatcher;

Bool RFTIME::IsSuccessfullyDispatched()
{
    Bool result=true;
    result=result && CreateTimerQueue != CreateTimerQueue_SystemAPIDispatcher;
    result=result && DeleteTimerQueue != DeleteTimerQueue_SystemAPIDispatcher;
    result=result && GetNow != GetNow_SystemAPIDispatcher;
    result=result && GetMinutesWestOfGMT != GetMinutesWestOfGMT_SystemAPIDispatcher;
    result=result && GetHighResolutionCounter != GetHighResolutionCounter_SystemAPIDispatcher;
    result=result && IsHighResolutionCounterSupported != IsHighResolutionCounterSupported_SystemAPIDispatcher;
    return result;
}

void RFTIME::GetNotDispatchedFunctions(List<RFTYPE::String>& Result)
{
    if (CreateTimerQueue == CreateTimerQueue_SystemAPIDispatcher) 
        Result.AddLast("CreateTimerQueue");
    if (DeleteTimerQueue == DeleteTimerQueue_SystemAPIDispatcher) 
        Result.AddLast("DeleteTimerQueue");
    if (GetNow == GetNow_SystemAPIDispatcher) 
        Result.AddLast("GetNow");
    if (GetMinutesWestOfGMT == GetMinutesWestOfGMT_SystemAPIDispatcher) 
        Result.AddLast("GetMinutesWestOfGMT");
    if (GetHighResolutionCounter == GetHighResolutionCounter_SystemAPIDispatcher) 
        Result.AddLast("GetHighResolutionCounter");
    if (IsHighResolutionCounterSupported == IsHighResolutionCounterSupported_SystemAPIDispatcher) 
        Result.AddLast("IsHighResolutionCounterSupported");
}