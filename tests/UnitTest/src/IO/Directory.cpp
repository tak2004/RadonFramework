#include <RadonFramework/Diagnostics/Test/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Test/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/IO/Directory.hpp>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Diagnostics::Test::UnitTest;
using namespace RadonFramework::Memory;
using namespace RadonFramework::IO;

class DirectoryTest:public TestSuite
{
public:
    DirectoryTest()
    :TestSuite("RadonFramework::IO::Directory-Test"_rfs)
    {
        AddTest(MakeDelegate(this,&DirectoryTest::CheckName),
            "DirectoryTest::CheckName"_rfs, "Check directory name"_rfs);
    }

    RF_Type::Bool CheckName()
    {
        Uri pathWithSeperator("file:///test/"_rfs);
        Uri pathWithoutSeperator("file:///test"_rfs);
        Directory dirWithoutSeperator;
        dirWithoutSeperator.SetLocation(pathWithoutSeperator);
        Directory dirWithSeperator;
        dirWithSeperator.SetLocation(pathWithSeperator);
        return dirWithoutSeperator.Name() == dirWithSeperator.Name();
    }

    RF_Type::Bool CheckPath()
    {
        Uri pathWithSeperator("file:///test/"_rfs);
        Uri pathWithoutSeperator("file:///test"_rfs);
        Directory dirWithoutSeperator;
        dirWithoutSeperator.SetLocation(pathWithoutSeperator);
        Directory dirWithSeperator;
        dirWithSeperator.SetLocation(pathWithSeperator);
        return dirWithoutSeperator.Location() == dirWithSeperator.Location();
    }
};

DirectoryTest DirectoryTestInstance;