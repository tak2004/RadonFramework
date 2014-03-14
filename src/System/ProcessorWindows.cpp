#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Processor.hpp"
#include "RadonFramework/Diagnostics/ProcessorData.hpp"
#include "RadonFramework/Collections/Array.hpp"
#include "RadonFramework/System/Environment.hpp"
#include "RadonFramework/System/CPUID.hpp"
#include "RadonFramework/IO/Log.hpp"

#ifdef RF_WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
    #include <intrin.h>
#endif

using namespace RadonFramework::System;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Diagnostics;
using namespace RadonFramework::Core::Types;

void cpuid(Int32 code, UInt32 registers[4])
{
    #ifdef RF_VISUALCPP
        __cpuid(reinterpret_cast<int*>(registers),code);
    #else
        RF_COMPILER_WARNING("You are the happy one who can implement this feature");
    #endif
}

void cpuidex(Int32 code, UInt32 registers[4], Int32 ECXRegister)
{
    #ifdef RF_VISUALCPP
        __cpuidex(reinterpret_cast<int*>(registers),code,ECXRegister);
    #else
        RF_COMPILER_WARNING("You are the happy one who can implement this feature");
    #endif
}

// this function return the logical processor count used by the OS
UInt32 LogicalProcessorCount()
{
    UInt32 result=0;
    #ifdef RF_WINDOWS
        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);
        result = sysInfo.dwNumberOfProcessors;
    #else
        RF_COMPILER_WARNING("You are the happy one who can implement this feature");
    #endif
    return result;
}

UInt32 RunCodeOnLogicalProcessor(UInt32 Mask)
{
    UInt32 result=0;
    #ifdef RF_WINDOWS
        result=static_cast<UInt32>(SetThreadAffinityMask(GetCurrentThread(),Mask));
        Sleep(0);
    #else
        RF_COMPILER_WARNING("You are the happy one who can implement this feature");
    #endif
    return result;
}

Bool IsRunningOnAllProcessors()
{
    Bool result=false;
    #ifdef RF_WINDOWS
        DWORD_PTR processorAffinity;
        DWORD_PTR systemAffinity;
        GetProcessAffinityMask(GetCurrentProcess(),&processorAffinity,
                               &systemAffinity);
        result=processorAffinity == systemAffinity;
    #else
        RF_COMPILER_WARNING("You are the happy one who can implement this feature");
    #endif
    // if the number of cores is higher then 32 then it's not possible to map them
    if (Environment::Is32BitEmulation() && LogicalProcessorCount()>32)
        result=false;
    return result;
}

UInt32 clz( UInt32 x )
{
    UInt32 r = 0;
    #ifdef RF_VISUALCPP
        _BitScanReverse(reinterpret_cast<unsigned long*>(&r), x);
    #else
        RF_COMPILER_WARNING("You are the happy one who can implement this feature");
    #endif
    return r;
}