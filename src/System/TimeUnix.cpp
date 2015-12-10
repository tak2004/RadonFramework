#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Time.hpp"

#include <time.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <stdlib.h>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::Time;

UInt64 GetNow()
{
    timeval t;
    gettimeofday(&t,0);
    return t.tv_sec*10000000llu+t.tv_usec*10llu;
}

UInt64 GetMinutesWestOfGMT()
{
    struct timeb t;
    ftime(&t);
    return abs(t.timezone)*600000000llu;
}

void RF_SysTime::Dispatch()
{
    GetNow = ::GetNow;
    GetMinutesWestOfGMT = ::GetMinutesWestOfGMT;

#ifdef RF_LINUX
    extern void Dispatch_Linux();
    Dispatch_Linux();
#else
#ifdef RF_OSX
    extern void Dispatch_OSX();
    Dispatch_OSX();
#endif
#endif
}