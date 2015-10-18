#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Process.hpp"
#include <sys/types.h>
#include <unistd.h>

// Append "Implementation" at function name to avoid name collision with windows.
RF_Type::UInt32 GetCurrentProcessIdImplementation()
{
    return getpid();
}

void RFPROC::Dispatch()
{
    GetCurrentProcessId = ::GetCurrentProcessIdImplementation;
}