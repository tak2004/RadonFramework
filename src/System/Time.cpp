#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Time.hpp"

using namespace RadonFramework::System;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::Time;
using namespace RadonFramework::Collections;

#include "RadonFramework/Defines.hpp"

#if defined(RF_WINDOWS)
#include "RadonFramework/Core/Types/Int64.hpp"
#include <Windows.h>

UInt64 ImplementationGetNow()
{
    FILETIME t;
    GetSystemTimeAsFileTime(&t);
    return t.dwHighDateTime*600000000LL+t.dwLowDateTime;
}

UInt64 ImplementationGetMinutesWestOfGMT()
{
    TIME_ZONE_INFORMATION tz;
    GetTimeZoneInformation(&tz);
    return abs(tz.Bias)*600000000LL;
}

UInt64 ImplementationGetHighResolutionCounter()
{
    Int64 result;
    if (QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&result)))
    {
        Int64 freq;
        QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&freq));
        result=result/freq;
    }
    else
        result=ImplementationGetNow();
    return result;
}

Bool ImplementationIsHighResolutionCounterSupported()
{
    Int64 tmp;
    return QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&tmp))!=0;
}
#endif

#if defined(RF_UNIX)
#include <time.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <stdlib.h>

UInt64 ImplementationGetNow()
{
    timeval t;
    gettimeofday(&t,0);
    return t.tv_sec*10000000llu+t.tv_usec*10llu;
}

UInt64 ImplementationGetMinutesWestOfGMT()
{
    struct timeb t;
    ftime(&t);
    return abs(t.timezone)*600000000llu;
}

#if defined(RF_MACOS)
#include <mach/clock.h>
#include <mach/mach.h>
UInt64 ImplementationGetHighResolutionCounter()
{
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    UInt64 result = 0;
    result = mts.tv_sec*1000000000llu+mts.tv_nsec;
    return result;
}

Bool ImplementationIsHighResolutionCounterSupported()
{
    return true;
}
#else
UInt64 ImplementationGetHighResolutionCounter()
{
    timespec tmp;	
    UInt64 result=0;
    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tmp) == 0)
        result=tmp.tv_sec*1000000000llu+tmp.tv_nsec;
    else
        result=ImplementationGetNow();
    return result;
}

Bool ImplementationIsHighResolutionCounterSupported()
{
    timespec tmp;
    return clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tmp)==0;
}
#endif
#endif

UInt64 Time::GetNow()
{
    return ImplementationGetNow();
}

UInt64 Time::GetMinutesWestOfGMT()
{
    return ImplementationGetMinutesWestOfGMT();
}

UInt64 Time::GetHighResolutionCounter()
{
    return ImplementationGetHighResolutionCounter();
}

Bool Time::IsHighResolutionCounterSupported()
{
    return ImplementationIsHighResolutionCounterSupported();
}

CreateTimerQueueCallback RadonFramework::System::Time::CreateTimerQueue=0;
DeleteTimerQueueCallback RadonFramework::System::Time::DeleteTimerQueue=0;

Bool RadonFramework::System::Time::IsSuccessfullyDispatched()
{
    Bool result=true;
    result=result && CreateTimerQueue!=0;
    result=result && DeleteTimerQueue!=0;
    return result;
}

void RadonFramework::System::Time::GetNotDispatchedFunctions(List<RFTYPE::String>& Result)
{
    if (CreateTimerQueue==0) 
        Result.AddLast("CreateTimerQueue");
    if (DeleteTimerQueue==0) 
        Result.AddLast("DeleteTimerQueue");
}