#include "precompiled.hpp"
#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/IO/Log.hpp>
#include <RadonFramework/IO/LogConsole.hpp>
#include <RadonFramework/Radon.hpp>
#include <RadonFramework/Diagnostics/Debugging/FrameworkDiagnostics.hpp>
#include <RadonFramework/Diagnostics/Appender.hpp>
#include <RadonFramework/Threading/ThreadPool.hpp>

using namespace RadonFramework::IO;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework;

int main()
{
    Radon framework;

    RF_Mem::AutoPointer<RF_Diag::Appender> console(new LogConsole);
    Log::AddAppender(console);

    RF_Collect::List<String> missingFunctions;
    RF_Debug::FrameworkDiagnostics::GetAllMissingSystemFunctions(missingFunctions);
    for (Size i = 0; i < missingFunctions.Count(); ++i)
    {
        LogError("Missing system function: %s", missingFunctions[i].c_str());
    }
    RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance().DisableAndWaitTillDone();
    return missingFunctions.Count();
}
