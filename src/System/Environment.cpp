#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Environment.hpp"
#include "RadonFramework/Util/UUID.hpp"

using namespace RadonFramework::Collections;
using namespace RadonFramework::System;
using namespace RadonFramework::System::Environment;

MemoryArchitecture::Type MemoryArchitectureOfOS_SystemAPIDispatcher()
{
    MemoryArchitectureOfOS = 0;
    Dispatch();
    Assert(MemoryArchitectureOfOS != MemoryArchitectureOfOS_SystemAPIDispatcher &&
           MemoryArchitectureOfOS != 0,
           "Funtion was called and couldn't be dispatched");
    return MemoryArchitectureOfOS();
}

RF_Type::Bool Is32BitEmulation_SystemAPIDispatcher()
{
    Is32BitEmulation = 0;
    Dispatch();
    Assert(Is32BitEmulation != Is32BitEmulation_SystemAPIDispatcher &&
           Is32BitEmulation != 0,
           "Funtion was called and couldn't be dispatched");
    return Is32BitEmulation();
}

const OperatingSystem& OSVersion_SystemAPIDispatcher()
{
    OSVersion = 0;
    Dispatch();
    Assert(OSVersion != OSVersion_SystemAPIDispatcher &&
           OSVersion != 0,
           "Funtion was called and couldn't be dispatched");
    return OSVersion();
}

void GetVariable_SystemAPIDispatcher(const RF_Type::String& Name, RF_Type::String& Result)
{
    GetVariable = 0;
    Dispatch();
    Assert(GetVariable != GetVariable_SystemAPIDispatcher &&
           GetVariable != 0,
           "Funtion was called and couldn't be dispatched");
    GetVariable(Name, Result);
}

PlatformID::Type Platform_SystemAPIDispatcher()
{
    Platform = 0;
    Dispatch();
    Assert(Platform != Platform_SystemAPIDispatcher &&
           Platform != 0,
           "Funtion was called and couldn't be dispatched");
    return Platform();
}

OperatingSystemFamily::Type OSFamily_SystemAPIDispatcher()
{
    OSFamily = 0;
    Dispatch();
    Assert(OSFamily != OSFamily_SystemAPIDispatcher &&
           OSFamily != 0,
           "Funtion was called and couldn't be dispatched");
    return OSFamily();
}

void FastRandomUUID_SystemAPIDispatcher(RF_Util::UUID& Target)
{
    FastRandomUUID = 0;
    Dispatch();
    Assert(FastRandomUUID != FastRandomUUID_SystemAPIDispatcher &&
           FastRandomUUID != 0,
           "Funtion was called and couldn't be dispatched");
    FastRandomUUID(Target);
}

void SecureRandomUUID_SystemAPIDispatcher(RF_Util::UUID& Target)
{
    SecureRandomUUID = 0;
    Dispatch();
    Assert(SecureRandomUUID != SecureRandomUUID_SystemAPIDispatcher &&
           SecureRandomUUID != 0,
           "Funtion was called and couldn't be dispatched");
    SecureRandomUUID(Target);
}

void UUIDFromString_SystemAPIDispatcher(const RF_Type::String& Text, RF_Util::UUID& Target)
{
    UUIDFromString = 0;
    Dispatch();
    Assert(UUIDFromString != UUIDFromString_SystemAPIDispatcher &&
           UUIDFromString != 0,
           "Funtion was called and couldn't be dispatched");
    UUIDFromString(Text, Target);
}

MemoryArchitectureOfOSCallback RFENV::MemoryArchitectureOfOS=MemoryArchitectureOfOS_SystemAPIDispatcher;
Is32BitEmulationCallback RFENV::Is32BitEmulation=Is32BitEmulation_SystemAPIDispatcher;
OSVersionCallback RFENV::OSVersion=OSVersion_SystemAPIDispatcher;
GetVariableCallback RFENV::GetVariable=GetVariable_SystemAPIDispatcher;
PlatformCallback RFENV::Platform=Platform_SystemAPIDispatcher;
OSFamilyCallback RFENV::OSFamily=OSFamily_SystemAPIDispatcher;
FastRandomUUIDCallback RFENV::FastRandomUUID = FastRandomUUID_SystemAPIDispatcher;
SecureRandomUUIDCallback RFENV::SecureRandomUUID = SecureRandomUUID_SystemAPIDispatcher;
UUIDFromStringCallback RFENV::UUIDFromString = UUIDFromString_SystemAPIDispatcher;

RF_Type::Bool RFENV::IsSuccessfullyDispatched()
{
    RF_Type::Bool result=true;
    result=result && MemoryArchitectureOfOS != MemoryArchitectureOfOS_SystemAPIDispatcher && MemoryArchitectureOfOS != 0;
    result=result && Is32BitEmulation != Is32BitEmulation_SystemAPIDispatcher && Is32BitEmulation != 0;
    result=result && OSVersion != OSVersion_SystemAPIDispatcher && OSVersion != 0;
    result=result && GetVariable != GetVariable_SystemAPIDispatcher && GetVariable != 0;
    result=result && Platform != Platform_SystemAPIDispatcher && Platform != 0;
    result=result && OSFamily != OSFamily_SystemAPIDispatcher && OSFamily != 0;
    result = result && FastRandomUUID != FastRandomUUID_SystemAPIDispatcher && FastRandomUUID != 0;
    result = result && SecureRandomUUID != SecureRandomUUID_SystemAPIDispatcher && SecureRandomUUID != 0;
    result = result && UUIDFromString != UUIDFromString_SystemAPIDispatcher && UUIDFromString != 0;
    return result;
}

void RFENV::GetNotDispatchedFunctions(List<RF_Type::String>& Result)
{
    if (MemoryArchitectureOfOS == MemoryArchitectureOfOS_SystemAPIDispatcher || MemoryArchitectureOfOS == 0) 
        Result.AddLast(RF_Type::String("MemoryArchitectureOfOS", sizeof("MemoryArchitectureOfOS")));
    if (Is32BitEmulation == Is32BitEmulation_SystemAPIDispatcher || Is32BitEmulation == 0) 
        Result.AddLast(RF_Type::String("Is32BitEmulation", sizeof("Is32BitEmulation")));
    if (OSVersion == OSVersion_SystemAPIDispatcher || OSVersion == 0) 
        Result.AddLast(RF_Type::String("OSVersion", sizeof("OSVersion")));
    if (GetVariable == GetVariable_SystemAPIDispatcher || GetVariable == 0) 
        Result.AddLast(RF_Type::String("GetVariable", sizeof("GetVariable")));
    if (Platform == Platform_SystemAPIDispatcher || Platform == 0) 
        Result.AddLast(RF_Type::String("Platform", sizeof("Platform")));
    if (OSFamily == OSFamily_SystemAPIDispatcher || OSFamily == 0) 
        Result.AddLast(RF_Type::String("OSFamily", sizeof("OSFamily")));
    if(FastRandomUUID == FastRandomUUID_SystemAPIDispatcher || FastRandomUUID == 0)
        Result.AddLast(RF_Type::String("FastRandomUUID", sizeof("FastRandomUUID")));
    if(SecureRandomUUID == SecureRandomUUID_SystemAPIDispatcher || SecureRandomUUID == 0)
        Result.AddLast(RF_Type::String("SecureRandomUUID", sizeof("SecureRandomUUID")));
    if(UUIDFromString == UUIDFromString_SystemAPIDispatcher || UUIDFromString == 0)
        Result.AddLast(RF_Type::String("UUIDFromString", sizeof("UUIDFromString")));
}
