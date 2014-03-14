#ifndef RF_SYSTEM_ENVIRONMENT_HPP
#define RF_SYSTEM_ENVIRONMENT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/System/MemoryArchitecture.hpp>
#include <RadonFramework/System/OperatingSystem.hpp>
#include <RadonFramework/System/OperatingSystemFamily.hpp>
#include <RadonFramework/Collections/List.hpp>
namespace RadonFramework
{
    namespace System
    {
        namespace Environment
        {
            /// This function will be called by RadonFramework_Init function.
            void Dispatch();

            /** This function will be called by RadonFraemwork_Init function to
              * check if the dispatching was successfully.
              **/
            RFTYPE::Bool IsSuccessfullyDispatched();
            
            /// This function is for debugging purpose and return all unassigned functions.
            void GetNotDispatchedFunctions(Collections::List<RFTYPE::String>& Result);

            typedef RadonFramework::System::MemoryArchitecture::Type(*MemoryArchitectureOfOSCallback)();
            typedef RFTYPE::Bool(*Is32BitEmulationCallback)();
            typedef const RadonFramework::System::OperatingSystem&(*OSVersionCallback)();
            typedef void(*GetVariableCallback)(const RFTYPE::String& Name, RFTYPE::String& Result);
            typedef RadonFramework::System::PlatformID::Type(*PlatformCallback)();
            typedef RadonFramework::System::OperatingSystemFamily::Type(*OSFamilyCallback)();

            extern MemoryArchitectureOfOSCallback MemoryArchitectureOfOS;
            extern Is32BitEmulationCallback Is32BitEmulation;
            extern OSVersionCallback OSVersion;
            extern GetVariableCallback GetVariable;
            extern PlatformCallback Platform;
            extern OSFamilyCallback OSFamily;
        }
    }
}

#endif // RF_SYSTEM_ENVIRONMENT_HPP
