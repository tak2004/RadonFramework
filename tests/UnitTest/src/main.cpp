#include <RadonFramework/Radon.hpp>
#include <RadonFramework/Diagnostics/Test/UnitTest/UnitTest.hpp>
#include <RadonFramework/Diagnostics/Test/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Test/TestResultCollector.hpp>
#include <RadonFramework/Diagnostics/Test/UnitTest/BriefProgressCollector.hpp>
#include <RadonFramework/Diagnostics/Test/UnitTest/DebugCollector.hpp>
#include <RadonFramework/Diagnostics/Test/UnitTest/JUnitOutput.hpp>
#include <RadonFramework/Diagnostics/Test/TestResult.hpp>
#include <RadonFramework/IO/Log.hpp>
#include <RadonFramework/IO/LogConsole.hpp>
#include <RadonFramework/Diagnostics/Appender.hpp>
#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/System/IO/FileSystem.hpp>
#include <RadonFramework/IO/Uri.hpp>
#include <RadonFramework/Threading/ThreadPool.hpp>

using namespace RadonFramework::IO;
using namespace RadonFramework::Diagnostics::Test::UnitTest;
using namespace RadonFramework::Diagnostics;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework;
using namespace RadonFramework::System::IO;

int main(int argc, char** argv)
{
    Radon framework;

    AutoPointer<Appender> console(new LogConsole);
    AutoPointer<Appender> debugOut(new LogDebuggerOutput);
    Log::AddAppender(console);
    Log::AddAppender(debugOut);

    RF_Test::TestResultCollector results;
    BriefProgressCollector progress;
    DebugCollector debugger;
    RF_Pattern::Singleton<UnitTest>::GetInstance().AddCollector(results);
    RF_Pattern::Singleton<UnitTest>::GetInstance().AddCollector(progress);
    RF_Pattern::Singleton<UnitTest>::GetInstance().AddCollector(debugger);

    TestSuite* bitArrayTestSuite = RF_Pattern::Singleton<UnitTest>::GetInstance().GetSuite("RadonFramework::Collections::BitArray-Test"_rfs);
    if (bitArrayTestSuite)
    {
        bitArrayTestSuite->IgnoreTest("BitArrayTest::Constructor"_rfs);
        bitArrayTestSuite->IgnoreTest("BitArrayTest::Resize"_rfs);
    }

    TestSuite* bitSetTestSuite = RF_Pattern::Singleton<UnitTest>::GetInstance().GetSuite("RadonFramework::Collections::BitSet-Test"_rfs);
    if (bitSetTestSuite)
    {
        bitSetTestSuite->IgnoreTest("BitSetTest::UnequalCompareOperator"_rfs);
    }

    TestSuite* queueTestSuite = RF_Pattern::Singleton<UnitTest>::GetInstance().GetSuite("RadonFramework::Collections::Queue-Test"_rfs);
    if (queueTestSuite)
    {
        queueTestSuite->IgnoreTest("QueueTest::Dequeue"_rfs);
    }

    RF_Pattern::Singleton<UnitTest>::GetInstance().IgnoreSuite("RadonFramework::Core::Types::StringBuilder-Test"_rfs);

    RF_Pattern::Singleton<UnitTest>::GetInstance().IgnoreSuite("RadonFramework::IO::Directory-Test"_rfs);

    RF_Pattern::Singleton<UnitTest>::GetInstance().IgnoreSuite("RadonFramework::IO::File-Test"_rfs);

    RF_Pattern::Singleton<UnitTest>::GetInstance().IgnoreSuite("RadonFramework::Memory"_rfs);

    RF_Pattern::Singleton<UnitTest>::GetInstance().Run();

    JUnitOutput output;
    output.WriteToFile(Uri(FileSystem::WorkingDirectory()).GetComponents()+"/UnitTest.xml",results);

    Bool res=results.WasSuccessful();
    if (res)
    {
        LogInfo("Test was successful.");
    }
    else
        LogError("Test failed.");
    RF_Pattern::Singleton<Threading::ThreadPool>::GetInstance().DisableAndWaitTillDone();
    return 0;
}