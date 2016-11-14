#ifndef RF_DIAGNOSTICS_DEBUGGING_JUNITOUTPUT_HPP
#define RF_DIAGNOSTICS_DEBUGGING_JUNITOUTPUT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace IO {
    class Uri;
} }

namespace RadonFramework { namespace Diagnostics { namespace Test {
class TestResultCollector;
} } }

namespace RadonFramework { namespace Diagnostics { namespace Debugging { namespace UnitTest {

class TestResultCollector;

class JUnitOutput
{
public:
    void WriteToFile(const RadonFramework::IO::Uri& URI,
        const RadonFramework::Diagnostics::Test::TestResultCollector& Results);
};

} } } }

#ifndef RF_SHORTHAND_NAMESPACE_UNITTEST
#define RF_SHORTHAND_NAMESPACE_UNITTEST
namespace RF_UnitTest = RadonFramework::Diagnostics::Debugging::UnitTest;
#endif

#endif // RF_DIAGNOSTICS_DEBUGGING_JUNITOUTPUT_HPP