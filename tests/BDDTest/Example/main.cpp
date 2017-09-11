#include <RadonFramework/Radon.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Test/TestResultCollector.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/BriefProgressCollector.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/DebugCollector.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/JUnitOutput.hpp>
#include <RadonFramework/Diagnostics/Test/TestResult.hpp>
#include <RadonFramework/IO/Log.hpp>
#include <RadonFramework/IO/LogConsole.hpp>
#include <RadonFramework/Diagnostics/Appender.hpp>
#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/System/IO/FileSystem.hpp>
#include <RadonFramework/IO/Uri.hpp>
#include <RadonFramework/Threading/ThreadPool.hpp>

using namespace RadonFramework::IO;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
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

	auto specs = R"(
	The calculator is capable to add and subtract numbers.	

	{1} plus {1} is {2} $addition
	{1} minus {1} is {0} $substraction
	)"_rfsp;
	specs.AddFunction("addition"_rfs, [](const auto& Parameters) {
		RF_Type::UInt32 a, b, c;
		RF_Type::Convert::ToUInt32(Parameters(0), a);
		RF_Type::Convert::ToUInt32(Parameters(1), b);
		RF_Type::Convert::ToUInt32(Parameters(2), c);
		return a + b == c;
	});
	specs.AddFunction("substraction"_rfs, [](const auto& Parameters) {
		RF_Type::UInt32 a, b, c;
		RF_Type::Convert::ToUInt32(Parameters(0), a);
		RF_Type::Convert::ToUInt32(Parameters(1), b);
		RF_Type::Convert::ToUInt32(Parameters(2), c);
		return a - b == c;
	});
	if (specs.IsSyntaxCorrect())
	{
		specs.Test();
		RF_BDD::ConsoleOutput output;
		specs.Generate(output);
	}

    RF_Pattern::Singleton<Threading::ThreadPool>::GetInstance().DisableAndWaitTillDone();
    return 0;
}