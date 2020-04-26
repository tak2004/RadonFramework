#include "RadonFramework/System/Environment.hpp"

#include "RadonFramework/precompiled.hpp"

using namespace RadonFramework::Collections;
using namespace RadonFramework::System;
using namespace RadonFramework::System::Environment;

MemoryArchitecture::Type MemoryArchitectureOfOS_SystemAPIDispatcher()
{
  MemoryArchitectureOfOS = nullptr;
  Dispatch();
  RF_ASSERT(
      MemoryArchitectureOfOS != MemoryArchitectureOfOS_SystemAPIDispatcher &&
          MemoryArchitectureOfOS != nullptr,
      "Funtion was called and couldn't be dispatched");
  return MemoryArchitectureOfOS();
}

RF_Type::Bool Is32BitEmulation_SystemAPIDispatcher()
{
  Is32BitEmulation = nullptr;
  Dispatch();
  RF_ASSERT(Is32BitEmulation != Is32BitEmulation_SystemAPIDispatcher &&
                Is32BitEmulation != nullptr,
            "Funtion was called and couldn't be dispatched");
  return Is32BitEmulation();
}

const OperatingSystem& OSVersion_SystemAPIDispatcher()
{
  OSVersion = nullptr;
  Dispatch();
  RF_ASSERT(OSVersion != OSVersion_SystemAPIDispatcher && OSVersion != nullptr,
            "Funtion was called and couldn't be dispatched");
  return OSVersion();
}

void GetVariable_SystemAPIDispatcher(const RF_Type::String& Name,
                                     RF_Type::String& Result)
{
  GetVariable = nullptr;
  Dispatch();
  RF_ASSERT(
      GetVariable != GetVariable_SystemAPIDispatcher && GetVariable != nullptr,
      "Funtion was called and couldn't be dispatched");
  GetVariable(Name, Result);
}

PlatformID::Type Platform_SystemAPIDispatcher()
{
  Platform = nullptr;
  Dispatch();
  RF_ASSERT(Platform != Platform_SystemAPIDispatcher && Platform != nullptr,
            "Funtion was called and couldn't be dispatched");
  return Platform();
}

OperatingSystemFamily::Type OSFamily_SystemAPIDispatcher()
{
  OSFamily = nullptr;
  Dispatch();
  RF_ASSERT(OSFamily != OSFamily_SystemAPIDispatcher && OSFamily != nullptr,
            "Funtion was called and couldn't be dispatched");
  return OSFamily();
}

void FastRandomUUID_SystemAPIDispatcher(RF_Type::UUID& Target)
{
  FastRandomUUID = nullptr;
  Dispatch();
  RF_ASSERT(FastRandomUUID != FastRandomUUID_SystemAPIDispatcher &&
                FastRandomUUID != nullptr,
            "Funtion was called and couldn't be dispatched");
  FastRandomUUID(Target);
}

void SecureRandomUUID_SystemAPIDispatcher(RF_Type::UUID& Target)
{
  SecureRandomUUID = nullptr;
  Dispatch();
  RF_ASSERT(SecureRandomUUID != SecureRandomUUID_SystemAPIDispatcher &&
                SecureRandomUUID != nullptr,
            "Funtion was called and couldn't be dispatched");
  SecureRandomUUID(Target);
}

void UUIDFromString_SystemAPIDispatcher(const RF_Type::String& Text,
                                        RF_Type::UUID& Target)
{
  UUIDFromString = nullptr;
  Dispatch();
  RF_ASSERT(UUIDFromString != UUIDFromString_SystemAPIDispatcher &&
                UUIDFromString != nullptr,
            "Funtion was called and couldn't be dispatched");
  UUIDFromString(Text, Target);
}

RF_Type::String ActiveLanguage_SystemAPIDispatcher()
{
  ActiveLanguage = nullptr;
  Dispatch();
  RF_ASSERT(ActiveLanguage != ActiveLanguage_SystemAPIDispatcher &&
                ActiveLanguage != nullptr,
            "Funtion was called and couldn't be dispatched");
  return ActiveLanguage();
}

RF_Type::String ActiveLanguageName_SystemAPIDispatcher()
{
  ActiveLanguageName = nullptr;
  Dispatch();
  RF_ASSERT(ActiveLanguageName != ActiveLanguageName_SystemAPIDispatcher &&
                ActiveLanguageName != nullptr,
            "Funtion was called and couldn't be dispatched");
  return ActiveLanguageName();
}

RF_Type::String ActiveNativeLanguageName_SystemAPIDispatcher()
{
  ActiveNativeLanguageName = nullptr;
  Dispatch();
  RF_ASSERT(ActiveNativeLanguageName !=
                    ActiveNativeLanguageName_SystemAPIDispatcher &&
                ActiveNativeLanguageName != nullptr,
            "Funtion was called and couldn't be dispatched");
  return ActiveNativeLanguageName();
}

RF_Type::String ActiveLanguageLocation_SystemAPIDispatcher()
{
  ActiveLanguageLocation = nullptr;
  Dispatch();
  RF_ASSERT(
      ActiveLanguageLocation != ActiveLanguageLocation_SystemAPIDispatcher &&
          ActiveLanguageLocation != nullptr,
      "Funtion was called and couldn't be dispatched");
  return ActiveLanguageLocation();
}

RF_Type::String ActiveNativeLanguageLocation_SystemAPIDispatcher()
{
  ActiveNativeLanguageLocation = nullptr;
  Dispatch();
  RF_ASSERT(ActiveNativeLanguageLocation !=
                    ActiveNativeLanguageLocation_SystemAPIDispatcher &&
                ActiveNativeLanguageLocation != nullptr,
            "Funtion was called and couldn't be dispatched");
  return ActiveNativeLanguageLocation();
}

RF_Type::Bool
GetUserEnvironmentVariable_SystemAPIDispatcher(const RF_Type::String& Name,
                                               RF_Type::String& Result)
{
  GetUserEnvironmentVariable = nullptr;
  Dispatch();
  RF_ASSERT(GetUserEnvironmentVariable !=
                    GetUserEnvironmentVariable_SystemAPIDispatcher &&
                GetUserEnvironmentVariable != nullptr,
            "Funtion was called and couldn't be dispatched");
  return GetUserEnvironmentVariable(Name, Result);
}

RF_Type::Bool
SetUserEnvironmentVariable_SystemAPIDispatcher(const RF_Type::String& Name,
                                               const RF_Type::String& Value)
{
  SetUserEnvironmentVariable = nullptr;
  Dispatch();
  RF_ASSERT(SetUserEnvironmentVariable !=
                    SetUserEnvironmentVariable_SystemAPIDispatcher &&
                SetUserEnvironmentVariable != nullptr,
            "Funtion was called and couldn't be dispatched");
  return SetUserEnvironmentVariable(Name, Value);
}

MemoryArchitectureOfOSCallback RF_SysEnv::MemoryArchitectureOfOS =
    MemoryArchitectureOfOS_SystemAPIDispatcher;
Is32BitEmulationCallback RF_SysEnv::Is32BitEmulation =
    Is32BitEmulation_SystemAPIDispatcher;
OSVersionCallback RF_SysEnv::OSVersion = OSVersion_SystemAPIDispatcher;
GetVariableCallback RF_SysEnv::GetVariable = GetVariable_SystemAPIDispatcher;
PlatformCallback RF_SysEnv::Platform = Platform_SystemAPIDispatcher;
OSFamilyCallback RF_SysEnv::OSFamily = OSFamily_SystemAPIDispatcher;
FastRandomUUIDCallback RF_SysEnv::FastRandomUUID =
    FastRandomUUID_SystemAPIDispatcher;
SecureRandomUUIDCallback RF_SysEnv::SecureRandomUUID =
    SecureRandomUUID_SystemAPIDispatcher;
UUIDFromStringCallback RF_SysEnv::UUIDFromString =
    UUIDFromString_SystemAPIDispatcher;
SystemLanguageCallback RF_SysEnv::ActiveLanguage =
    ActiveLanguage_SystemAPIDispatcher;
SystemLanguageCallback RF_SysEnv::ActiveLanguageName =
    ActiveLanguageName_SystemAPIDispatcher;
SystemLanguageCallback RF_SysEnv::ActiveNativeLanguageName =
    ActiveNativeLanguageName_SystemAPIDispatcher;
SystemLanguageCallback RF_SysEnv::ActiveLanguageLocation =
    ActiveLanguageLocation_SystemAPIDispatcher;
SystemLanguageCallback RF_SysEnv::ActiveNativeLanguageLocation =
    ActiveNativeLanguageLocation_SystemAPIDispatcher;
GetEnvironmentVariableCallback RF_SysEnv::GetUserEnvironmentVariable =
    GetUserEnvironmentVariable_SystemAPIDispatcher;
SetEnvironmentVariableCallback RF_SysEnv::SetUserEnvironmentVariable =
    SetUserEnvironmentVariable_SystemAPIDispatcher;

RF_Type::Bool RF_SysEnv::IsSuccessfullyDispatched()
{
  RF_Type::Bool result = true;
  result =
      result &&
      MemoryArchitectureOfOS != MemoryArchitectureOfOS_SystemAPIDispatcher &&
      MemoryArchitectureOfOS != nullptr;
  result = result && Is32BitEmulation != Is32BitEmulation_SystemAPIDispatcher &&
           Is32BitEmulation != nullptr;
  result = result && OSVersion != OSVersion_SystemAPIDispatcher &&
           OSVersion != nullptr;
  result = result && GetVariable != GetVariable_SystemAPIDispatcher &&
           GetVariable != nullptr;
  result =
      result && Platform != Platform_SystemAPIDispatcher && Platform != nullptr;
  result =
      result && OSFamily != OSFamily_SystemAPIDispatcher && OSFamily != nullptr;
  result = result && FastRandomUUID != FastRandomUUID_SystemAPIDispatcher &&
           FastRandomUUID != nullptr;
  result = result && SecureRandomUUID != SecureRandomUUID_SystemAPIDispatcher &&
           SecureRandomUUID != nullptr;
  result = result && UUIDFromString != UUIDFromString_SystemAPIDispatcher &&
           UUIDFromString != nullptr;
  result = result && ActiveLanguage != ActiveLanguage_SystemAPIDispatcher &&
           ActiveLanguage != nullptr;
  result = result &&
           ActiveLanguageName != ActiveLanguageName_SystemAPIDispatcher &&
           ActiveLanguageName != nullptr;
  result = result &&
           ActiveNativeLanguageName !=
               ActiveNativeLanguageName_SystemAPIDispatcher &&
           ActiveNativeLanguageName != nullptr;
  result =
      result &&
      ActiveLanguageLocation != ActiveLanguageLocation_SystemAPIDispatcher &&
      ActiveLanguageLocation != nullptr;
  result = result &&
           ActiveNativeLanguageLocation !=
               ActiveNativeLanguageLocation_SystemAPIDispatcher &&
           ActiveNativeLanguageLocation != nullptr;
  result = result &&
           GetUserEnvironmentVariable !=
               GetUserEnvironmentVariable_SystemAPIDispatcher &&
           GetUserEnvironmentVariable != nullptr;
  result = result &&
           SetUserEnvironmentVariable !=
               SetUserEnvironmentVariable_SystemAPIDispatcher &&
           SetUserEnvironmentVariable != nullptr;
  return result;
}

void RF_SysEnv::GetNotDispatchedFunctions(List<RF_Type::String>& Result)
{
  if(MemoryArchitectureOfOS == MemoryArchitectureOfOS_SystemAPIDispatcher ||
     MemoryArchitectureOfOS == nullptr)
    Result.AddLast("MemoryArchitectureOfOS"_rfs);
  if(Is32BitEmulation == Is32BitEmulation_SystemAPIDispatcher ||
     Is32BitEmulation == nullptr)
    Result.AddLast("Is32BitEmulation"_rfs);
  if(OSVersion == OSVersion_SystemAPIDispatcher || OSVersion == nullptr)
    Result.AddLast("OSVersion"_rfs);
  if(GetVariable == GetVariable_SystemAPIDispatcher || GetVariable == nullptr)
    Result.AddLast("GetVariable"_rfs);
  if(Platform == Platform_SystemAPIDispatcher || Platform == nullptr)
    Result.AddLast("Platform"_rfs);
  if(OSFamily == OSFamily_SystemAPIDispatcher || OSFamily == nullptr)
    Result.AddLast("OSFamily"_rfs);
  if(FastRandomUUID == FastRandomUUID_SystemAPIDispatcher ||
     FastRandomUUID == nullptr)
    Result.AddLast("FastRandomUUID"_rfs);
  if(SecureRandomUUID == SecureRandomUUID_SystemAPIDispatcher ||
     SecureRandomUUID == nullptr)
    Result.AddLast("SecureRandomUUID"_rfs);
  if(UUIDFromString == UUIDFromString_SystemAPIDispatcher ||
     UUIDFromString == nullptr)
    Result.AddLast("UUIDFromString"_rfs);
  if(ActiveLanguage == ActiveLanguage_SystemAPIDispatcher ||
     ActiveLanguage == nullptr)
    Result.AddLast("ActiveLanguage"_rfs);
  if(ActiveLanguageName == ActiveLanguageName_SystemAPIDispatcher ||
     ActiveLanguageName == nullptr)
    Result.AddLast("ActiveLanguageName"_rfs);
  if(ActiveNativeLanguageName == ActiveNativeLanguageName_SystemAPIDispatcher ||
     ActiveNativeLanguageName == nullptr)
    Result.AddLast("ActiveNativeLanguageName"_rfs);
  if(ActiveLanguageLocation == ActiveLanguageLocation_SystemAPIDispatcher ||
     ActiveLanguageLocation == nullptr)
    Result.AddLast("ActiveLanguageLocation"_rfs);
  if(ActiveNativeLanguageLocation ==
         ActiveNativeLanguageLocation_SystemAPIDispatcher ||
     ActiveNativeLanguageLocation == nullptr)
    Result.AddLast("ActiveNativeLanguageLocation"_rfs);
  if(GetUserEnvironmentVariable ==
         GetUserEnvironmentVariable_SystemAPIDispatcher ||
     GetUserEnvironmentVariable == nullptr)
    Result.AddLast("GetUserEnvironmentVariable"_rfs);
  if(SetUserEnvironmentVariable ==
         SetUserEnvironmentVariable_SystemAPIDispatcher ||
     SetUserEnvironmentVariable == nullptr)
    Result.AddLast("SetUserEnvironmentVariable"_rfs);
}
