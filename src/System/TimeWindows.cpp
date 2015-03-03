#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Time.hpp"
#include "RadonFramework/Time/DateTime.hpp"
#include <math.h>
#include <time.h>

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
    if(GetTimeZoneInformation(&tz) != TIME_ZONE_ID_INVALID)
    {
        return abs(tz.Bias) * 600000000LL;
    }
    else
    {
        return 0;
    }    
}

void GetStringFormatedTime(const RF_Time::DateTime& Time,
    const RF_Type::String& Format, RF_Type::String& FormattedString)
{
    RF_Mem::AutoPointerArray<char> buf(new char[256],256);
    struct tm time;
    time.tm_sec = Time.Second();
    time.tm_min = Time.Minute();
    time.tm_hour = Time.Hour();
    time.tm_mday = Time.Day();
    time.tm_mon = Time.Month();
    time.tm_year = Time.Year();
    time.tm_wday = Time.GetDayOfWeek();
    time.tm_yday = Time.DayOfYear();
    time.tm_isdst = -1;
    while(strftime(buf.Get(), buf.Size(), Format.c_str(), &time) == 0)
    {
        buf = RF_Mem::AutoPointerArray<char>(new char[buf.Size()+256], buf.Size()+256);
    }
    FormattedString = String(buf.Get(), buf.Size());
}

UInt64 GetHighResolutionCounter()
{
    Int64 result;
    if (QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&result)))
    {
    }
    else
    {
        result = ::GetNow();
    }
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
        // msdn say call it again till DeleteTimerQueueTimer succeed or error is ERROR_IO_PENDING
        for(; DeleteTimerQueueTimer(0, pimpl->Handle, 0) == 0 && GetLastError() != ERROR_IO_PENDING;)
        {
        }
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
    GetStringFormatedTime=::GetStringFormatedTime;
    GetHighResolutionCounter=::GetHighResolutionCounter;
    IsHighResolutionCounterSupported=::IsHighResolutionCounterSupported;
}