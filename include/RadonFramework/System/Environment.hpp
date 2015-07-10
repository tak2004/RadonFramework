#ifndef RF_SYSTEM_ENVIRONMENT_HPP
#define RF_SYSTEM_ENVIRONMENT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/System/MemoryArchitecture.hpp>
#include <RadonFramework/System/OperatingSystem.hpp>
#include <RadonFramework/System/OperatingSystemFamily.hpp>
#include <RadonFramework/Collections/List.hpp>

namespace RadonFramework { namespace Util { struct UUID; } }

namespace RadonFramework {  namespace System { namespace Environment {
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

    using FastRandomUUIDCallback = void(*)(Util::UUID& Target);
    using SecureRandomUUIDCallback = void(*)(Util::UUID& Target);
    using UUIDFromStringCallback = void(*)(const RF_Type::String& Text, Util::UUID& Target);

    // ISO 639([]_[ISO 3166/Location])
    using SystemLanguageCallback = RF_Type::String (*)();

    extern MemoryArchitectureOfOSCallback MemoryArchitectureOfOS;
    extern Is32BitEmulationCallback Is32BitEmulation;
    extern OSVersionCallback OSVersion;
    extern GetVariableCallback GetVariable;
    extern PlatformCallback Platform;
    extern OSFamilyCallback OSFamily;
    extern FastRandomUUIDCallback FastRandomUUID;
    extern SecureRandomUUIDCallback SecureRandomUUID;
    extern UUIDFromStringCallback UUIDFromString;
    extern SystemLanguageCallback ActiveLanguage;
    extern SystemLanguageCallback ActiveLanguageName;
    extern SystemLanguageCallback ActiveNativeLanguageName;
    extern SystemLanguageCallback ActiveLanguageLocation;
    extern SystemLanguageCallback ActiveNativeLanguageLocation;
} } }

#ifndef RF_SHORTHAND_NAMESPACE_SYSENV
#define RF_SHORTHAND_NAMESPACE_SYSENV
namespace RF_SysEnv = RadonFramework::System::Environment;
#endif

#endif // RF_SYSTEM_ENVIRONMENT_HPP
