#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/IO/File.hpp>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Memory;
using namespace RadonFramework::IO;

class FileTest:public TestSuite
{
public:
    FileTest()
    :TestSuite("RadonFramework::IO::File-Test"_rfs)
    {
        AddTest(MakeDelegate(this,&FileTest::CreateTempFile),
            "FileTest::CreateTempFile"_rfs, "CreateTempFile"_rfs);
    }

    RadonFramework::Core::Types::Bool CreateTempFile()
    {
        AutoPointer<File> tmp(File::CreateTempFile());
        return tmp && tmp->Name()!="";
    }
};

FileTest FileTestInstance;