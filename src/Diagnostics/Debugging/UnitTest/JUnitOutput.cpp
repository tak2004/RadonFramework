#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/JUnitOutput.hpp"
#include "RadonFramework/Diagnostics/Test/TestResultCollector.hpp"
#include "RadonFramework/IO/Uri.hpp"
#include "RadonFramework/IO/FileStream.hpp"
#include "RadonFramework/IO/File.hpp"
#include "RadonFramework/System/IO/FileSystem.hpp"

namespace RadonFramework { namespace Diagnostics { namespace Debugging { namespace UnitTest {

void JUnitOutput::WriteToFile(const RF_IO::Uri& URI,
	const RF_Test::TestResultCollector& Results)
{
	// ensure that a new log will be written
	RF_IO::File output;
	output.SetLocation(URI);
	output.Delete();

	RF_IO::FileStream out;
	out.Open(URI, RF_SysFile::FileAccessMode::Write, RF_SysFile::FileAccessPriority::DelayReadWrite);
	if (out.CanWrite())
	{
		//start suites
		RF_Type::String tag("<testsuites>\n", sizeof("<testsuites>\n"));
		out.Write(reinterpret_cast<const RF_Type::UInt8*>(tag.c_str()), 0, tag.Length());
		for (RF_Type::UInt32 i = 0; i < Results.TestResults().Count(); ++i)
		{
			//start a suite
			tag = RF_Type::String::Format(
				"<testsuite error=\"%u\" failures=\"%u\" hostname=\"RadonFramework-TestEnvoirement\" name=\"%s\" tests=\"%u\" time=\"%.3f\" timestamp=\"%s\" id=\"%u\" package=\"%u\">\n"_rfs,
				Results.TestResults()[i].TestsWithError,
				Results.TestResults()[i].TestsWithFailure,
				Results.TestResults()[i].SuiteName.c_str(),
				Results.TestResults()[i].TestResults.Count(),
				Results.TestResults()[i].TotalTime,
				"2007-11-02T23:13:49",
				0,
				0);
			out.Write(reinterpret_cast<const RF_Type::UInt8*>(tag.c_str()), 0, tag.Length());
			for (RF_Type::UInt32 j = 0; j < Results.TestResults()[i].TestResults.Count(); ++j)
			{
				//start testcase
				tag = RF_Type::String::Format("<testcase classname=\"%s\" name=\"%s\" time=\"%d\">\n"_rfs,
					"",
					Results.TestResults()[i].TestResults[j].GetName().c_str(),
					Results.TestResults()[i].TestResults[j].GetTimeRequired().Ticks());
				out.Write(reinterpret_cast<const RF_Type::UInt8*>(tag.c_str()), 0, tag.Length());
				// test failed
				if (!Results.TestResults()[i].TestResults[j].GetPassed())
				{
					tag = RF_Type::String::Format("<error message=\"%s\" type=\"%s\">%s\n"_rfs,
						"",
						"",
						"");
					out.Write(reinterpret_cast<const RF_Type::UInt8*>(tag.c_str()), 0, tag.Length());
					tag = "</error>\n";
					out.Write(reinterpret_cast<const RF_Type::UInt8*>(tag.c_str()), 0, tag.Length());
				}
				// test raise an exception
				if (Results.TestResults()[i].TestResults[j].GetError())
				{
					tag = RF_Type::String::Format("<failure message=\"%s\" type=\"%s\">%s\n"_rfs,
						"",
						"",
						"");
					out.Write(reinterpret_cast<const RF_Type::UInt8*>(tag.c_str()), 0, tag.Length());
					tag = "</failure>\n";
					out.Write(reinterpret_cast<const RF_Type::UInt8*>(tag.c_str()), 0, tag.Length());
				}
				//end testcase
				tag = "</testcase>\n";
				out.Write(reinterpret_cast<const RF_Type::UInt8*>(tag.c_str()), 0, tag.Length());
			}
			//end the suite
			tag = "</testsuite>\n";
			out.Write(reinterpret_cast<const RF_Type::UInt8*>(tag.c_str()), 0, tag.Length());
		}
		//end suites
		tag = "</testsuites>\n";
		out.Write(reinterpret_cast<const RF_Type::UInt8*>(tag.c_str()), 0, tag.Length());
	}
}

} } } }