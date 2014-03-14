#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Debugging/FrameworkDiagnostics.hpp"
#include "RadonFramework/System/Environment.hpp"
#include "RadonFramework/System/Memory.hpp"
#include "RadonFramework/System/IO/FileSystem.hpp"
#include "RadonFramework/System/Time.hpp"

void RadonFramework::Diagnostics::Debugging::FrameworkDiagnostics::GetAllMissingSystemFunctions(
    RadonFramework::Collections::List<RadonFramework::Core::Types::String>& Result)
{
    if (!RadonFramework::System::Environment::IsSuccessfullyDispatched()) 
        RadonFramework::System::Environment::GetNotDispatchedFunctions(Result);
    if (!RFMEM::IsSuccessfullyDispatched()) 
        RFMEM::GetNotDispatchedFunctions(Result);
    if (!RadonFramework::System::IO::FileSystem::IsSuccessfullyDispatched()) 
        RadonFramework::System::IO::FileSystem::GetNotDispatchedFunctions(Result);
    if (!RadonFramework::System::Time::IsSuccessfullyDispatched()) 
        RadonFramework::System::Time::GetNotDispatchedFunctions(Result);
}
