#ifndef RF_DIAGNOSTICS_DEBUGGING_JUNITOUTPUT_HPP
#define RF_DIAGNOSTICS_DEBUGGING_JUNITOUTPUT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace IO {
    class Uri;
} }

namespace RadonFramework { namespace Diagnostics { namespace Debugging { namespace UnitTest {

class TestResultCollector;

class JUnitOutput
{
public:
    void WriteToFile(const RadonFramework::IO::Uri& URI,
                     const TestResultCollector& Results);
};

} } } }

#ifndef RF_SHORTHAND_NAMESPACE_TEST
#define RF_SHORTHAND_NAMESPACE_TEST
namespace RF_Test = RadonFramework::Diagnostics::Debugging::UnitTest;
#endif

#endif // RF_DIAGNOSTICS_DEBUGGING_JUNITOUTPUT_HPP