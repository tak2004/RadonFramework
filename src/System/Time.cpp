#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Time.hpp"

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

CreateTimerQueueCallback RFTIME::CreateTimerQueue = CreateTimerQueue_SystemAPIDispatcher;
DeleteTimerQueueCallback RFTIME::DeleteTimerQueue = DeleteTimerQueue_SystemAPIDispatcher;
GetNowCallback RFTIME::GetNow = GetNow_SystemAPIDispatcher;
GetMinutesWestOfGMTCallback RFTIME::GetMinutesWestOfGMT = GetMinutesWestOfGMT_SystemAPIDispatcher;
GetHighResolutionCounterCallback RFTIME::GetHighResolutionCounter = GetHighResolutionCounter_SystemAPIDispatcher;
IsHighResolutionCounterSupportedCallback RFTIME::IsHighResolutionCounterSupported = IsHighResolutionCounterSupported_SystemAPIDispatcher;

Bool RFTIME::IsSuccessfullyDispatched()
{
    Bool result=true;
    result=result && CreateTimerQueue != CreateTimerQueue_SystemAPIDispatcher && CreateTimerQueue != 0;
    result=result && DeleteTimerQueue != DeleteTimerQueue_SystemAPIDispatcher && DeleteTimerQueue != 0;
    result=result && GetNow != GetNow_SystemAPIDispatcher && GetNow != 0;
    result=result && GetMinutesWestOfGMT != GetMinutesWestOfGMT_SystemAPIDispatcher && GetMinutesWestOfGMT != 0;
    result=result && GetHighResolutionCounter != GetHighResolutionCounter_SystemAPIDispatcher && GetHighResolutionCounter != 0;
    result=result && IsHighResolutionCounterSupported != IsHighResolutionCounterSupported_SystemAPIDispatcher && IsHighResolutionCounterSupported != 0;
    return result;
}

void RFTIME::GetNotDispatchedFunctions(List<RF_Type::String>& Result)
{
    if (CreateTimerQueue == CreateTimerQueue_SystemAPIDispatcher || CreateTimerQueue == 0) 
        Result.AddLast(RF_Type::String("CreateTimerQueue", sizeof("CreateTimerQueue")));
    if (DeleteTimerQueue == DeleteTimerQueue_SystemAPIDispatcher || DeleteTimerQueue == 0) 
        Result.AddLast(RF_Type::String("DeleteTimerQueue", sizeof("DeleteTimerQueue")));
    if (GetNow == GetNow_SystemAPIDispatcher || GetNow == 0) 
        Result.AddLast(RF_Type::String("GetNow", sizeof("GetNow")));
    if (GetMinutesWestOfGMT == GetMinutesWestOfGMT_SystemAPIDispatcher || GetMinutesWestOfGMT == 0) 
        Result.AddLast(RF_Type::String("GetMinutesWestOfGMT", sizeof("GetMinutesWestOfGMT")));
    if (GetHighResolutionCounter == GetHighResolutionCounter_SystemAPIDispatcher || GetHighResolutionCounter == 0) 
        Result.AddLast(RF_Type::String("GetHighResolutionCounter", sizeof("GetHighResolutionCounter")));
    if (IsHighResolutionCounterSupported == IsHighResolutionCounterSupported_SystemAPIDispatcher || IsHighResolutionCounterSupported == 0) 
        Result.AddLast(RF_Type::String("IsHighResolutionCounterSupported", sizeof("IsHighResolutionCounterSupported")));
}