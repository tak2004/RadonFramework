#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/IO/Directory.hpp>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Memory;
using namespace RadonFramework::IO;

class DirectoryTest:public TestSuite
{
public:
    DirectoryTest()
    :TestSuite("RadonFramework::IO::Directory-Test")
    {
        AddTest(MakeDelegate(this,&DirectoryTest::CheckName),
            "DirectoryTest::CheckName", "Check directory name");
    }

    RF_Type::Bool CheckName()
    {
        Uri pathWithSeperator("file:///test/");
        Uri pathWithoutSeperator("file:///test");
        Directory dirWithoutSeperator;
        dirWithoutSeperator.SetLocation(pathWithoutSeperator);
        Directory dirWithSeperator;
        dirWithSeperator.SetLocation(pathWithSeperator);
        return dirWithoutSeperator.Name() == dirWithSeperator.Name();
    }

    RF_Type::Bool CheckPath()
    {
        Uri pathWithSeperator("file:///test/");
        Uri pathWithoutSeperator("file:///test");
        Directory dirWithoutSeperator;
        dirWithoutSeperator.SetLocation(pathWithoutSeperator);
        Directory dirWithSeperator;
        dirWithSeperator.SetLocation(pathWithSeperator);
        return dirWithoutSeperator.Location() == dirWithSeperator.Location();
    }
};

DirectoryTest DirectoryTestInstance;