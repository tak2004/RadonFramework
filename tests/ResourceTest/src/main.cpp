#include "precompiled.hpp"
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestResultCollector.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/BriefProgressCollector.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/JUnitOutput.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTestResult.hpp>
#include <RadonFramework/IO/Log.hpp>
#include <RadonFramework/IO/LogConsole.hpp>
#include <RadonFramework/Diagnostics/Appender.hpp>
#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/System/IO/FileSystem.hpp>
#include <RadonFramework/IO/Uri.hpp>
#include <RadonFramework/Radon.hpp>

using namespace RadonFramework::IO;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Diagnostics;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework;
using namespace RadonFramework::System::IO;

int main(int argc,char **argv)
{
    Radon framework;

    Log::AddAppender(AutoPointer<Appender>(new LogConsole));

    TestResultCollector results;
    BriefProgressCollector progress;
    Singleton<UnitTest>::GetInstance().AddCollector(results);
    Singleton<UnitTest>::GetInstance().AddCollector(progress);
    Singleton<UnitTest>::GetInstance().Run();

    JUnitOutput output;
    output.WriteToFile(Uri(FileSystem::ApplicationDirectory()).GetComponents()+"/PerformanceTest.xml",results);

    Bool res=results.WasSuccessful();
    if (res)
    {
        LogInfo("Test was successful.");
    }
    else
        LogError("Test failed.");

    return res;
}
