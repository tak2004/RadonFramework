#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Environment.hpp"

using namespace RadonFramework::Collections;
using namespace RadonFramework::System;
using namespace RadonFramework::System::Environment;

MemoryArchitecture::Type MemoryArchitectureOfOS_SystemAPIDispatcher()
{
    Dispatch();
    Assert(MemoryArchitectureOfOS != MemoryArchitectureOfOS_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return MemoryArchitectureOfOS();
}

RFTYPE::Bool Is32BitEmulation_SystemAPIDispatcher()
{
    Dispatch();
    Assert(Is32BitEmulation != Is32BitEmulation_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return Is32BitEmulation();
}

const OperatingSystem& OSVersion_SystemAPIDispatcher()
{
    Dispatch();
    Assert(OSVersion != OSVersion_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return OSVersion();
}

void GetVariable_SystemAPIDispatcher(const RFTYPE::String& Name, RFTYPE::String& Result)
{
    Dispatch();
    Assert(GetVariable != GetVariable_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    GetVariable(Name, Result);
}

PlatformID::Type Platform_SystemAPIDispatcher()
{
    Dispatch();
    Assert(Platform != Platform_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return Platform();
}

OperatingSystemFamily::Type OSFamily_SystemAPIDispatcher()
{
    Dispatch();
    Assert(OSFamily != OSFamily_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return OSFamily();
}

MemoryArchitectureOfOSCallback RFENV::MemoryArchitectureOfOS=MemoryArchitectureOfOS_SystemAPIDispatcher;
Is32BitEmulationCallback RFENV::Is32BitEmulation=Is32BitEmulation_SystemAPIDispatcher;
OSVersionCallback RFENV::OSVersion=OSVersion_SystemAPIDispatcher;
GetVariableCallback RFENV::GetVariable=GetVariable_SystemAPIDispatcher;
PlatformCallback RFENV::Platform=Platform_SystemAPIDispatcher;
OSFamilyCallback RFENV::OSFamily=OSFamily_SystemAPIDispatcher;

RFTYPE::Bool RFENV::IsSuccessfullyDispatched()
{
    RFTYPE::Bool result=true;
    result=result && MemoryArchitectureOfOS != MemoryArchitectureOfOS_SystemAPIDispatcher;
    result=result && Is32BitEmulation != Is32BitEmulation_SystemAPIDispatcher;
    result=result && OSVersion != OSVersion_SystemAPIDispatcher;
    result=result && GetVariable != GetVariable_SystemAPIDispatcher;
    result=result && Platform != Platform_SystemAPIDispatcher;
    result=result && OSFamily != OSFamily_SystemAPIDispatcher;
    return result;
}

void RFENV::GetNotDispatchedFunctions(List<RFTYPE::String>& Result)
{
    if (MemoryArchitectureOfOS == MemoryArchitectureOfOS_SystemAPIDispatcher) 
        Result.AddLast("MemoryArchitectureOfOS");
    if (Is32BitEmulation == Is32BitEmulation_SystemAPIDispatcher) 
        Result.AddLast("Is32BitEmulation");
    if (OSVersion == OSVersion_SystemAPIDispatcher) 
        Result.AddLast("OSVersion");
    if (GetVariable == GetVariable_SystemAPIDispatcher) 
        Result.AddLast("GetVariable");
    if (Platform == Platform_SystemAPIDispatcher) 
        Result.AddLast("Platform");
    if (OSFamily == OSFamily_SystemAPIDispatcher) 
        Result.AddLast("OSFamily");
}
