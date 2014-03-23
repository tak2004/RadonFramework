#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Process.hpp"
#include <sys/types.h>
#include <unistd.h>

// Append "Implementation" at function name to avoid name collision with windows.
RFTYPE::UInt32 GetCurrentProcessIdImplementation()
{
    return getpid();
}

void RFPROC::Dispatch()
{
    GetCurrentProcessId = ::GetCurrentProcessIdImplementation;
    #ifdef RF_LINUX
    extern void Dispatch_Linux();
    Dispatch_Linux();
    #endif
    #ifdef RF_OSX
    extern void Dispatch_OSX();
    Dispatch_OSX();
    #endif
}