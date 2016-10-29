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
    :TestSuite("RadonFramework::IO::Uri-Test"_rfs)
    {
        AddTest(MakeDelegate(this,&UriTest::DefaultConstructor),
            "UriTest::DefaultConstructor"_rfs, ""_rfs);
        AddTest(MakeDelegate(this,&UriTest::Constructor),
            "UriTest::Constructor"_rfs, ""_rfs);
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
        Uri testInstance("http://thomas@localhost:99/test/index.html?id=1&str=2#para1"_rfs);
        Bool result1 = testInstance.Path() == "/test/index.html"_rfs;
        Bool result2 = testInstance.Authority() == "thomas@localhost:99"_rfs;
        Bool result3 = testInstance.Fragment() == "para1"_rfs;
        Bool result4 = testInstance.Host() == "localhost"_rfs;
        Bool result5 = testInstance.HostNameType() == UriHostNameType::DomainName;
        Bool result6 = testInstance.IsAbsolute() == true;
        Bool result7 = testInstance.IsDefaultPort() == false;
        Bool result8 = testInstance.IsDefaultUser() == false;
        Bool result9 = testInstance.OriginalString() == "http://thomas@localhost:99/test/index.html?id=1&str=2#para1"_rfs;
        Bool result10 = testInstance.Port() == 99;
        Bool result11 = testInstance.Query() == "id=1&str=2"_rfs;
        Bool result12 = testInstance.Scheme() == "http"_rfs;
        Bool result13 = testInstance.SchemeSpecificPart() == "//thomas@localhost:99/test/index.html?id=1&str=2"_rfs;
        Bool result14 = testInstance.UserEscaped() == true;
        Bool result15 = testInstance.UserInfo() == "thomas"_rfs;
        Bool result16 = testInstance.IsOpaque() == false;

        return result1 && result2 && result3 && result4 && result5 &&
            result6 && result7 && result8 && result9 && result10 &&
            result11 && result12 && result13 && result14 && result15 &&
            result16;
    }
};

UriTest UriTestInstance;