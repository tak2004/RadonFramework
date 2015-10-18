#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Time.hpp"

#include <mach/clock.h>
#include <mach/mach.h>

UInt64 GetHighResolutionCounterOSX()
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

Bool IsHighResolutionCounterSupportedOSX()
{
    return true;
}

namespace RadonFramework { namespace System { namespace Time {

void Dispatch_OSX()
{
    GetHighResolutionCounter = GetHighResolutionCounterOSX;
    IsHighResolutionCounterSupported = IsHighResolutionCounterSupportedOSX;
}

} } }