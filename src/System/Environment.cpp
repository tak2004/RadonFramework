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

RF_Type::String ActiveLanguage_SystemAPIDispatcher()
{
    ActiveLanguage = 0;
    Dispatch();
    Assert(ActiveLanguage != ActiveLanguage_SystemAPIDispatcher &&
           ActiveLanguage != 0,
           "Funtion was called and couldn't be dispatched");
    return ActiveLanguage();
}

RF_Type::String ActiveLanguageName_SystemAPIDispatcher()
{
    ActiveLanguageName = 0;
    Dispatch();
    Assert(ActiveLanguageName != ActiveLanguageName_SystemAPIDispatcher &&
           ActiveLanguageName != 0,
           "Funtion was called and couldn't be dispatched");
    return ActiveLanguageName();
}

RF_Type::String ActiveNativeLanguageName_SystemAPIDispatcher()
{
    ActiveNativeLanguageName = 0;
    Dispatch();
    Assert(ActiveNativeLanguageName != ActiveNativeLanguageName_SystemAPIDispatcher &&
           ActiveNativeLanguageName != 0,
           "Funtion was called and couldn't be dispatched");
    return ActiveNativeLanguageName();
}

RF_Type::String ActiveLanguageLocation_SystemAPIDispatcher()
{
    ActiveLanguageLocation = 0;
    Dispatch();
    Assert(ActiveLanguageLocation != ActiveLanguageLocation_SystemAPIDispatcher &&
           ActiveLanguageLocation != 0,
           "Funtion was called and couldn't be dispatched");
    return ActiveLanguageLocation();
}

RF_Type::String ActiveNativeLanguageLocation_SystemAPIDispatcher()
{
    ActiveNativeLanguageLocation = 0;
    Dispatch();
    Assert(ActiveNativeLanguageLocation != ActiveNativeLanguageLocation_SystemAPIDispatcher &&
           ActiveNativeLanguageLocation != 0,
           "Funtion was called and couldn't be dispatched");
    return ActiveNativeLanguageLocation();
}

MemoryArchitectureOfOSCallback RF_SysEnv::MemoryArchitectureOfOS = MemoryArchitectureOfOS_SystemAPIDispatcher;
Is32BitEmulationCallback RF_SysEnv::Is32BitEmulation = Is32BitEmulation_SystemAPIDispatcher;
OSVersionCallback RF_SysEnv::OSVersion = OSVersion_SystemAPIDispatcher;
GetVariableCallback RF_SysEnv::GetVariable = GetVariable_SystemAPIDispatcher;
PlatformCallback RF_SysEnv::Platform = Platform_SystemAPIDispatcher;
OSFamilyCallback RF_SysEnv::OSFamily = OSFamily_SystemAPIDispatcher;
FastRandomUUIDCallback RF_SysEnv::FastRandomUUID = FastRandomUUID_SystemAPIDispatcher;
SecureRandomUUIDCallback RF_SysEnv::SecureRandomUUID = SecureRandomUUID_SystemAPIDispatcher;
UUIDFromStringCallback RF_SysEnv::UUIDFromString = UUIDFromString_SystemAPIDispatcher;
SystemLanguageCallback RF_SysEnv::ActiveLanguage = ActiveLanguage_SystemAPIDispatcher;
SystemLanguageCallback RF_SysEnv::ActiveLanguageName = ActiveLanguageName_SystemAPIDispatcher;
SystemLanguageCallback RF_SysEnv::ActiveNativeLanguageName = ActiveNativeLanguageName_SystemAPIDispatcher;
SystemLanguageCallback RF_SysEnv::ActiveLanguageLocation = ActiveLanguageLocation_SystemAPIDispatcher;
SystemLanguageCallback RF_SysEnv::ActiveNativeLanguageLocation = ActiveNativeLanguageLocation_SystemAPIDispatcher;

RF_Type::Bool RF_SysEnv::IsSuccessfullyDispatched()
{
    RF_Type::Bool result = true;
    result = result && MemoryArchitectureOfOS != MemoryArchitectureOfOS_SystemAPIDispatcher && MemoryArchitectureOfOS != 0;
    result = result && Is32BitEmulation != Is32BitEmulation_SystemAPIDispatcher && Is32BitEmulation != 0;
    result = result && OSVersion != OSVersion_SystemAPIDispatcher && OSVersion != 0;
    result = result && GetVariable != GetVariable_SystemAPIDispatcher && GetVariable != 0;
    result = result && Platform != Platform_SystemAPIDispatcher && Platform != 0;
    result = result && OSFamily != OSFamily_SystemAPIDispatcher && OSFamily != 0;
    result = result && FastRandomUUID != FastRandomUUID_SystemAPIDispatcher && FastRandomUUID != 0;
    result = result && SecureRandomUUID != SecureRandomUUID_SystemAPIDispatcher && SecureRandomUUID != 0;
    result = result && UUIDFromString != UUIDFromString_SystemAPIDispatcher && UUIDFromString != 0;
    result = result && ActiveLanguage != ActiveLanguage_SystemAPIDispatcher && ActiveLanguage != 0;
    result = result && ActiveLanguageName != ActiveLanguageName_SystemAPIDispatcher && ActiveLanguageName != 0;
    result = result && ActiveNativeLanguageName != ActiveNativeLanguageName_SystemAPIDispatcher && ActiveNativeLanguageName != 0;
    result = result && ActiveLanguageLocation != ActiveLanguageLocation_SystemAPIDispatcher && ActiveLanguageLocation != 0;
    result = result && ActiveNativeLanguageLocation != ActiveNativeLanguageLocation_SystemAPIDispatcher && ActiveNativeLanguageLocation != 0;
    return result;
}

void RF_SysEnv::GetNotDispatchedFunctions(List<RF_Type::String>& Result)
{
    if(MemoryArchitectureOfOS == MemoryArchitectureOfOS_SystemAPIDispatcher || MemoryArchitectureOfOS == 0)
        Result.AddLast("MemoryArchitectureOfOS"_rfs);
    if(Is32BitEmulation == Is32BitEmulation_SystemAPIDispatcher || Is32BitEmulation == 0)
        Result.AddLast("Is32BitEmulation"_rfs);
    if(OSVersion == OSVersion_SystemAPIDispatcher || OSVersion == 0)
        Result.AddLast("OSVersion"_rfs);
    if(GetVariable == GetVariable_SystemAPIDispatcher || GetVariable == 0)
        Result.AddLast("GetVariable"_rfs);
    if(Platform == Platform_SystemAPIDispatcher || Platform == 0)
        Result.AddLast("Platform"_rfs);
    if(OSFamily == OSFamily_SystemAPIDispatcher || OSFamily == 0)
        Result.AddLast("OSFamily"_rfs);
    if(FastRandomUUID == FastRandomUUID_SystemAPIDispatcher || FastRandomUUID == 0)
        Result.AddLast("FastRandomUUID"_rfs);
    if(SecureRandomUUID == SecureRandomUUID_SystemAPIDispatcher || SecureRandomUUID == 0)
        Result.AddLast("SecureRandomUUID"_rfs);
    if(UUIDFromString == UUIDFromString_SystemAPIDispatcher || UUIDFromString == 0)
        Result.AddLast("UUIDFromString"_rfs);
    if(ActiveLanguage == ActiveLanguage_SystemAPIDispatcher || ActiveLanguage == 0)
        Result.AddLast("ActiveLanguage"_rfs);
    if(ActiveLanguageName == ActiveLanguageName_SystemAPIDispatcher || ActiveLanguageName == 0)
        Result.AddLast("ActiveLanguageName"_rfs);
    if(ActiveNativeLanguageName == ActiveNativeLanguageName_SystemAPIDispatcher || ActiveNativeLanguageName == 0)
        Result.AddLast("ActiveNativeLanguageName"_rfs);
    if(ActiveLanguageLocation == ActiveLanguageLocation_SystemAPIDispatcher || ActiveLanguageLocation == 0)
        Result.AddLast("ActiveLanguageLocation"_rfs);
    if(ActiveNativeLanguageLocation == ActiveNativeLanguageLocation_SystemAPIDispatcher || ActiveNativeLanguageLocation == 0)
        Result.AddLast("ActiveNativeLanguageLocation"_rfs);
}
