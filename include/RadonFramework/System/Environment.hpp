#ifndef RF_SYSTEM_ENVIRONMENT_HPP
#define RF_SYSTEM_ENVIRONMENT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/System/MemoryArchitecture.hpp>
#include <RadonFramework/System/OperatingSystem.hpp>
#include <RadonFramework/System/OperatingSystemFamily.hpp>
#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Text/UnicodeRangeInfo.hpp>

namespace RadonFramework::System::Environment {

/// This function will be called by RadonFramework_Init function.
void Dispatch();

/** This function will be called by RadonFraemwork_Init function to
* check if the dispatching was successfully.
**/
RF_Type::Bool IsSuccessfullyDispatched();
            
/// This function is for debugging purpose and return all unassigned functions.
void GetNotDispatchedFunctions(Collections::List<RF_Type::String>& Result);

using MemoryArchitectureOfOSCallback = MemoryArchitecture::Type(*)();

using Is32BitEmulationCallback = RF_Type::Bool(*)();

using OSVersionCallback = const OperatingSystem&(*)();

using GetVariableCallback = void(*)(const RF_Type::String& Name, 
                                    RF_Type::String& Result);

using PlatformCallback = PlatformID::Type(*)();

using OSFamilyCallback = OperatingSystemFamily::Type(*)();

using FastRandomUUIDCallback = void(*)(RF_Type::UUID& Target);
using SecureRandomUUIDCallback = void (*)(RF_Type::UUID& Target);
using UUIDFromStringCallback = void (*)(const RF_Type::String& Text,
                                        RF_Type::UUID& Target);

// ISO 639([]_[ISO 3166/Location])
using SystemLanguageCallback = RF_Type::String (*)();

/// Return the memory architecture which the OS is using e.g. 64bit.
extern MemoryArchitectureOfOSCallback MemoryArchitectureOfOS;
/// The process is running in 32bit emulation mode e.g. on Windows 64bit.
extern Is32BitEmulationCallback Is32BitEmulation;
/// Return the the description of the OS version.
extern OSVersionCallback OSVersion;
/// Return the specified environment variable e.g. %TEMP% on Windows.
extern GetVariableCallback GetVariable;
/// Return a platform identifier like Unix or MacOSX.
extern PlatformCallback Platform;
/// Return the OS family identifier like Windows.
extern OSFamilyCallback OSFamily;
/// Return an UUID with a faster algorithm and less stability.
extern FastRandomUUIDCallback FastRandomUUID;
/// Return a UUID which take longer to generate but ensure no collision.
extern SecureRandomUUIDCallback SecureRandomUUID;
/// Generate a UUID by using a String as foundation.
extern UUIDFromStringCallback UUIDFromString;
/// Return the current active user language definition e.g. de_DE.
extern SystemLanguageCallback ActiveLanguage;
/// Return the current active user language name e.g. de.
extern SystemLanguageCallback ActiveLanguageName;
/// Return the current active user language name in the native language e.g. Deutsch.
extern SystemLanguageCallback ActiveNativeLanguageName;
/// Return the current active user language location e.g. DE.
extern SystemLanguageCallback ActiveLanguageLocation;
/// Return the current active user language location in native language e.g. Deutschland.
extern SystemLanguageCallback ActiveNativeLanguageLocation;

}

#ifndef RF_SHORTHAND_NAMESPACE_SYSENV
#define RF_SHORTHAND_NAMESPACE_SYSENV
namespace RF_SysEnv = RadonFramework::System::Environment;
#endif

#endif // RF_SYSTEM_ENVIRONMENT_HPP
