#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Debugging/FrameworkDiagnostics.hpp"
#include "RadonFramework/System/Environment.hpp"
#include "RadonFramework/System/Memory.hpp"
#include "RadonFramework/System/IO/FileSystem.hpp"
#include "RadonFramework/System/Time.hpp"
#include "Radonframework/System/Hardware.hpp"
#include "RadonFramework/System/Process.hpp"
#include "RadonFramework/System/String.hpp"

void RadonFramework::Diagnostics::Debugging::FrameworkDiagnostics::GetAllMissingSystemFunctions(
    RadonFramework::Collections::List<RadonFramework::Core::Types::String>& Result)
{
    if (!RFENV::IsSuccessfullyDispatched()) 
        RFENV::GetNotDispatchedFunctions(Result);
    if (!RFMEM::IsSuccessfullyDispatched()) 
        RFMEM::GetNotDispatchedFunctions(Result);
    if (!RFFILE::IsSuccessfullyDispatched()) 
        RFFILE::GetNotDispatchedFunctions(Result);
    if (!RFTIME::IsSuccessfullyDispatched()) 
        RFTIME::GetNotDispatchedFunctions(Result);
    if (!RFSTR::IsSuccessfullyDispatched())
        RFSTR::GetNotDispatchedFunctions(Result);
    if (!RFPROC::IsSuccessfullyDispatched())
        RFPROC::GetNotDispatchedFunctions(Result);
    if (!RFMEM::IsSuccessfullyDispatched())
        RFMEM::GetNotDispatchedFunctions(Result);
    if (!RFHDW::IsSuccessfullyDispatched())
        RFHDW::GetNotDispatchedFunctions(Result);
}
