#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Time.hpp"

#include <time.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <stdlib.h>

RF_Type::UInt64 GetHighResolutionCounterLinux()
{
    timespec tmp;	
    RF_Type::UInt64 result=0;
    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tmp) == 0)
        result=tmp.tv_sec*1000000000llu+tmp.tv_nsec;
    return result;
}

RF_Type::Bool IsHighResolutionCounterSupportedLinux()
{
    timespec tmp;
    return clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tmp)==0;
}

namespace RadonFramework::System::Time {

void Dispatch_Linux()
{
    GetHighResolutionCounter = GetHighResolutionCounterLinux;
    IsHighResolutionCounterSupported = IsHighResolutionCounterSupportedLinux;
}

}