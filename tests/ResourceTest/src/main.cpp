#include "precompiled.hpp"
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/BriefProgressCollector.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/JUnitOutput.hpp>
#include <RadonFramework/Diagnostics/Test/TestResultCollector.hpp>
#include <RadonFramework/Diagnostics/Test/TestResult.hpp>
#include <RadonFramework/IO/Log.hpp>
#include <RadonFramework/IO/LogConsole.hpp>
#include <RadonFramework/Diagnostics/Appender.hpp>
#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/System/IO/FileSystem.hpp>
#include <RadonFramework/Radon.hpp>
#include <RadonFramework/IO/Uri.hpp>
#include <RadonFramework/Threading/ThreadPool.hpp>
#include <RadonFramework/IO/OptionRule.hpp>
#include <RadonFramework/IO/Parameter.hpp>
#include <RadonFramework/IO/StandardRuleChecker.hpp>

using namespace RadonFramework::IO;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Diagnostics;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework;
using namespace RadonFramework::System::IO;

namespace ApplicationOptions
{
    enum Type
    {
        ApplicationDirectory,
        RunSpecificTestSuite,
        MAX
    };
}

int main(int argc, const char **argv)
{
    Radon framework;

    AutoPointer<Appender> console(new LogConsole);
    Log::AddAppender(console);

    TestResultCollector results;
    BriefProgressCollector progress;
    RF_Pattern::Singleton<UnitTest>::GetInstance().AddCollector(results);
    RF_Pattern::Singleton<UnitTest>::GetInstance().AddCollector(progress);
    RF_Pattern::Singleton<UnitTest>::GetInstance().SetSequentialTestExecution(10);

    AutoPointerArray<OptionRule> rules(new OptionRule[ApplicationOptions::MAX], ApplicationOptions::MAX);
    rules[ApplicationOptions::ApplicationDirectory].Init(0, 0, StandardRuleChecker::Text, 0, OptionRule::Required);
    rules[ApplicationOptions::RunSpecificTestSuite].Init(0, "run", StandardRuleChecker::Text, "Run the specified test suite.", OptionRule::Optional);
    Parameter param;
    if(param.ParsingWithLogging(argv, argc, rules))
    {
        if(param.Values()[ApplicationOptions::RunSpecificTestSuite].IsSet())
        {
            RF_Pattern::Singleton<UnitTest>::GetInstance().RunSuiteWithName(param.Values()[ApplicationOptions::RunSpecificTestSuite].Value());
        }
        else
        {
            RF_Pattern::Singleton<UnitTest>::GetInstance().Run();
        }
    }

    JUnitOutput output;
    output.WriteToFile(Uri(FileSystem::ApplicationDirectory()).GetComponents()+"/PerformanceTest.xml",results);

    Bool res=results.WasSuccessful();
    if (res)
    {
        LogInfo("Test was successful.");
    }
    else
        LogError("Test failed.");

    RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance().DisableAndWaitTillDone();
    return res;
}
