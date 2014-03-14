#include "precompiled.hpp"
#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/IO/Log.hpp>
#include <RadonFramework/IO/LogConsole.hpp>
#include <RadonFramework/Radon.hpp>
#include <RadonFramework/Diagnostics/Debugging/FrameworkDiagnostics.hpp>
#include <RadonFramework/Diagnostics/Appender.hpp>

using namespace RadonFramework::IO;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework;

int main()
{
    Radon framework;

    Log::AddAppender(Memory::AutoPointer<Diagnostics::Appender>(new LogConsole));

    Collections::List<String> missingFunctions;
    Diagnostics::Debugging::FrameworkDiagnostics::GetAllMissingSystemFunctions(missingFunctions);
    for (Size i = 0; i < missingFunctions.Size(); ++i)
    {
        LogError("Missing system function: %s", missingFunctions[i].c_str());
    }

    return missingFunctions.Size();
}
