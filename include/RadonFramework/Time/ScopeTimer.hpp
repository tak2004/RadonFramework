#ifndef RF_TIME_SCOPETIMER_HPP
#define RF_TIME_SCOPETIMER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt64.hpp>
#include <RadonFramework/Time/TimeSpan.hpp>

namespace RadonFramework::Time
{
class ScopeTimer
{
public:
  ScopeTimer(TimeSpan& ts);
  virtual ~ScopeTimer();

protected:
  TimeSpan& m_TimeSpan;
  RF_Type::UInt64 m_Start;
};

}  // namespace RadonFramework::Time

#ifndef RF_SHORTHAND_NAMESPACE_TIME
#define RF_SHORTHAND_NAMESPACE_TIME
namespace RF_Time = RadonFramework::Time;
#endif

#endif  // RF_TIME_SCOPETIMER_HPP
