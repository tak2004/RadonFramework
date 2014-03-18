#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Time.hpp"
#include <math.h>

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::Time;

UInt64 GetNow()
{
    FILETIME t;
    GetSystemTimeAsFileTime(&t);
    return t.dwHighDateTime*600000000LL+t.dwLowDateTime;
}

UInt64 GetMinutesWestOfGMT()
{
    TIME_ZONE_INFORMATION tz;
    GetTimeZoneInformation(&tz);
    return abs(tz.Bias)*600000000LL;
}

UInt64 GetHighResolutionCounter()
{
    Int64 result;
    if (QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&result)))
    {
        Int64 freq;
        QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&freq));
        result=result/freq;
    }
    else
        result=::GetNow();
    return result;
}

Bool IsHighResolutionCounterSupported()
{
    Int64 tmp;
    return QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&tmp))!=0;
}

struct TimerWrapper
{
    TimerCallback Callback;
    void* Parameter;
    HANDLE Handle;
};

void CALLBACK TimerCallbackWrapper(PVOID lpParameter, BOOLEAN TimerOrWaitFired)
{
    TimerWrapper* wrapper = reinterpret_cast<TimerWrapper*>(lpParameter);
    wrapper->Callback(wrapper->Parameter);
}

TimerHandle CreateTimerQueue(TimerCallback Callback, void* Parameter,
                             Int32 DueTime, Int32 Period)
{
    TimerWrapper* wrapper = new TimerWrapper();
    wrapper->Callback = Callback;
    wrapper->Parameter = Parameter;
    TimerHandle result = TimerHandle::GenerateFromPointer(wrapper);
    CreateTimerQueueTimer(&wrapper->Handle, 0, TimerCallbackWrapper,
        wrapper, DueTime, Period, WT_EXECUTEINTIMERTHREAD);
    return result;
}

void DeleteTimerQueue(TimerHandle& Handle)
{
    if (Handle.GetPointer())
    {
        TimerWrapper* pimpl=reinterpret_cast<TimerWrapper*>(Handle.GetPointer());
        DeleteTimerQueueTimer(0, pimpl->Handle, 0);
        delete pimpl;
        Handle=TimerHandle::Zero();
    }
}

void RadonFramework::System::Time::Dispatch()
{
    CreateTimerQueue=::CreateTimerQueue;
    DeleteTimerQueue=::DeleteTimerQueue;
    GetNow=::GetNow;
    GetMinutesWestOfGMT=::GetMinutesWestOfGMT;
    GetHighResolutionCounter=::GetHighResolutionCounter;
    IsHighResolutionCounterSupported=::IsHighResolutionCounterSupported;
}