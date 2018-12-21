#ifndef RF_DIAGNOSTICS_DEBUGGING_DEBUGCOLLECTOR_HPP
#define RF_DIAGNOSTICS_DEBUGGING_DEBUGCOLLECTOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/Collector.hpp>

namespace RadonFramework::Diagnostics::Debugging::UnitTest
{
class DebugCollector : public Collector
{
public:
  void CreateSuite(const RF_Type::String& Name) final;
  void ProcessResult(const Test::TestResult& Result) final;

protected:
  RF_Type::String m_CurrentSuite;
};

}  // namespace RadonFramework::Diagnostics::Debugging::UnitTest

#endif  // RF_DIAGNOSTICS_DEBUGGING_DEBUGCOLLECTOR_HPP