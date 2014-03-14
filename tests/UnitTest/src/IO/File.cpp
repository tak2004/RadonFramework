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
        :TestSuite("RadonFramework::IO::File-Test")
        {
            AddTest(MakeDelegate(this,&FileTest::CreateTempFile),"CreateTempFile");
        }

        RadonFramework::Core::Types::Bool CreateTempFile()
        {
            AutoPointer<File> tmp(File::CreateTempFile());
            return tmp && tmp->Name()!="";
        }
};

FileTest FileTestInstance;