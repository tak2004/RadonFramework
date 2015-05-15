#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/IO/Uri.hpp>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Memory;
using namespace RadonFramework::IO;

class UriTest:public TestSuite
{
public:
    UriTest()
    :TestSuite("RadonFramework::IO::Uri-Test")
    {
        AddTest(MakeDelegate(this,&UriTest::DefaultConstructor),
            "UriTest::DefaultConstructor", "");
        AddTest(MakeDelegate(this,&UriTest::Constructor),
            "UriTest::Constructor", "");
    }

    Bool DefaultConstructor()
    {
        Uri testInstance;
        Bool result1 = testInstance.Path() == "";
        Bool result2 = testInstance.Authority() == "";
        Bool result3 = testInstance.Fragment() == "";
        Bool result4 = testInstance.Host() == "";
        Bool result5 = testInstance.HostNameType() == UriHostNameType::Unknown;
        Bool result6 = testInstance.IsAbsolute() == false;
        Bool result7 = testInstance.IsDefaultPort() == true;
        Bool result8 = testInstance.IsDefaultUser() == true;
        Bool result9 = testInstance.OriginalString() == "";
        Bool result10 = testInstance.Port() == 0;
        Bool result11 = testInstance.Query() == "";
        Bool result12 = testInstance.Scheme() == "";
        Bool result13 = testInstance.SchemeSpecificPart() == "";
        Bool result14 = testInstance.UserEscaped() == false;
        Bool result15 = testInstance.UserInfo() == "";
        Bool result16 = testInstance.IsOpaque() == false;

        return result1 && result2 && result3 && result4 && result5 &&
            result6 && result7 && result8 && result9 && result10 &&
            result11 && result12 && result13 && result14 && result15 &&
            result16;
    }

    Bool Constructor()
    {
        Uri testInstance("http://thomas@localhost:99/test/index.html?id=1&str=2#para1");
        Bool result1 = testInstance.Path() == "test/index.html";
        Bool result2 = testInstance.Authority() == "thomas@localhost:99";
        Bool result3 = testInstance.Fragment() == "para1";
        Bool result4 = testInstance.Host() == "localhost";
        Bool result5 = testInstance.HostNameType() == UriHostNameType::DomainName;
        Bool result6 = testInstance.IsAbsolute() == true;
        Bool result7 = testInstance.IsDefaultPort() == false;
        Bool result8 = testInstance.IsDefaultUser() == false;
        Bool result9 = testInstance.OriginalString() == "http://thomas@localhost:99/test/index.html?id=1&str=2#para1";
        Bool result10 = testInstance.Port() == 99;
        Bool result11 = testInstance.Query() == "id=1&str=2";
        Bool result12 = testInstance.Scheme() == "http";
        Bool result13 = testInstance.SchemeSpecificPart() == "//thomas@localhost:99/test/index.html?id=1&str=2";
        Bool result14 = testInstance.UserEscaped() == true;
        Bool result15 = testInstance.UserInfo() == "thomas";
        Bool result16 = testInstance.IsOpaque() == false;

        return result1 && result2 && result3 && result4 && result5 &&
            result6 && result7 && result8 && result9 && result10 &&
            result11 && result12 && result13 && result14 && result15 &&
            result16;
    }
};

UriTest UriTestInstance;