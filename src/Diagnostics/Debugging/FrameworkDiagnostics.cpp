#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Debugging/FrameworkDiagnostics.hpp"
#include "RadonFramework/System/Environment.hpp"
#include "RadonFramework/System/Memory.hpp"
#include "RadonFramework/System/IO/FileSystem.hpp"
#include "RadonFramework/System/Time.hpp"
#include "RadonFramework/System/Hardware.hpp"
#include "RadonFramework/System/Process.hpp"
#include "RadonFramework/System/String.hpp"

void RadonFramework::Diagnostics::Debugging::FrameworkDiagnostics::GetAllMissingSystemFunctions(
    RadonFramework::Collections::List<RadonFramework::Core::Types::String>& Result)
{
    if (!RF_SysEnv::IsSuccessfullyDispatched()) 
        RF_SysEnv::GetNotDispatchedFunctions(Result);
    if (!RF_SysMem::IsSuccessfullyDispatched()) 
        RF_SysMem::GetNotDispatchedFunctions(Result);
    if (!RFFILE::IsSuccessfullyDispatched()) 
        RFFILE::GetNotDispatchedFunctions(Result);
    if (!RFTIME::IsSuccessfullyDispatched()) 
        RFTIME::GetNotDispatchedFunctions(Result);
    if (!RF_SysStr::IsSuccessfullyDispatched())
        RF_SysStr::GetNotDispatchedFunctions(Result);
    if (!RFPROC::IsSuccessfullyDispatched())
        RFPROC::GetNotDispatchedFunctions(Result);
    if (!RF_SysMem::IsSuccessfullyDispatched())
        RF_SysMem::GetNotDispatchedFunctions(Result);
    if (!RFHDW::IsSuccessfullyDispatched())
        RFHDW::GetNotDispatchedFunctions(Result);
}
