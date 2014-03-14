#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/JUnitOutput.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/TestResultCollector.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/UnitTestResult.hpp"
#include "RadonFramework/IO/Uri.hpp"
#include "RadonFramework/IO/FileStream.hpp"

using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::IO;
using namespace RadonFramework;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;
using namespace RadonFramework::System::IO::FileSystem;

void JUnitOutput::WriteToFile(const Uri& URI, 
                              const TestResultCollector& Results)
{
    FileStream out;
    out.Open(URI, FileAccessMode::Write, FileAccessPriority::DelayReadWrite);
    if (out.CanWrite())
    {
        //start suites
        String tag="<testsuites>\n";
        out.Write(reinterpret_cast<const UInt8*>(tag.c_str()), 0, tag.Length());
        for (UInt32 i=0;i<Results.TestResults().Size();++i)
        {
            //start a suite
            tag=String::Format("<testsuite error=\"%u\" failures=\"%u\" hostname=\"RadonFramework-TestEnvoirement\" name=\"%s\" tests=\"%u\" time=\"%.3f\" timestamp=\"%s\" id=\"%u\" package=\"%u\">\n",
                                Results.TestResults()[i].TestsWithError,
                                Results.TestResults()[i].TestsWithFailure,
                                Results.TestResults()[i].SuiteName.c_str(),
                                Results.TestResults()[i].TestResults.Size(),
                                Results.TestResults()[i].TotalTime,
                                "2007-11-02T23:13:49",
                                0,
                                0);
            out.Write(reinterpret_cast<const UInt8*>(tag.c_str()), 0 ,tag.Length());
            for (UInt32 j=0;j<Results.TestResults()[i].TestResults.Size();++j)
            {
                //start testcase
                tag=String::Format("<testcase classname=\"%s\" name=\"%s\" time=\"%.3f\">\n",
                                    "",
                                    Results.TestResults()[i].TestResults[j].Name().c_str(),
                                    Results.TestResults()[i].TestResults[j].TimeRequired().TotalSeconds());
                out.Write(reinterpret_cast<const UInt8*>(tag.c_str()), 0, tag.Length());
                // test failed
                if (!Results.TestResults()[i].TestResults[j].Passed())
                {
                    tag=String::Format("<error message=\"%s\" type=\"%s\">%s\n",
                                        "",
                                        "",
                                        "");
                    out.Write(reinterpret_cast<const UInt8*>(tag.c_str()), 0, tag.Length());
                    tag="</error>\n";
                    out.Write(reinterpret_cast<const UInt8*>(tag.c_str()), 0, tag.Length());
                }
                // test raise an exception
                if (Results.TestResults()[i].TestResults[j].Error())
                {
                    tag=String::Format("<failure message=\"%s\" type=\"%s\">%s\n",
                        "",
                        "",
                        "");
                    out.Write(reinterpret_cast<const UInt8*>(tag.c_str()), 0, tag.Length());
                    tag="</failure>\n";
                    out.Write(reinterpret_cast<const UInt8*>(tag.c_str()), 0, tag.Length());
                }
                //end testcase
                tag="</testcase>\n";
                out.Write(reinterpret_cast<const UInt8*>(tag.c_str()), 0, tag.Length());
            }
            //end the suite
            tag="</testsuite>\n";
            out.Write(reinterpret_cast<const UInt8*>(tag.c_str()), 0, tag.Length());
        }
        //end suites
        tag="</testsuites>\n";
        out.Write(reinterpret_cast<const UInt8*>(tag.c_str()), 0, tag.Length());
    }
}