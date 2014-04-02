#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Time.hpp"

#include <time.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <stdlib.h>

RFTYPE::UInt64 GetHighResolutionCounter()
{
    timespec tmp;	
    RFTYPE::UInt64 result=0;
    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tmp) == 0)
        result=tmp.tv_sec*1000000000llu+tmp.tv_nsec;
    return result;
}

RFTYPE::Bool IsHighResolutionCounterSupported()
{
    timespec tmp;
    return clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tmp)==0;
}

void Dispatch_Linux()
{
    RFTIME::GetHighResolutionCounter = GetHighResolutionCounter;
    RFTIME::IsHighResolutionCounterSupported = IsHighResolutionCounterSupported;
}