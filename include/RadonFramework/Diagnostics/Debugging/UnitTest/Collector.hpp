#ifndef RF_DIAGNOSTICS_DEBUGGING_COLLECTOR_HPP
#define RF_DIAGNOSTICS_DEBUGGING_COLLECTOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Diagnostics::Test {
class TestResult;
}

namespace RadonFramework::Diagnostics::Debugging::UnitTest {

class Collector
{
public:
    virtual void CreateSuite(const RF_Type::String& Name)=0;
    virtual void ProcessResult(const Test::TestResult& Result)=0;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_UNITTEST
#define RF_SHORTHAND_NAMESPACE_UNITTEST
namespace RF_UnitTest = RadonFramework::Diagnostics::Debugging::UnitTest;
#endif

#endif // RF_DIAGNOSTICS_DEBUGGING_COLLECTOR_HPP