#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Time/ScopeTimer.hpp>

using namespace RadonFramework::Time;

/** @brief ~ScopeTimer
  *
  * @todo: document this function
  */
ScopeTimer::~ScopeTimer()
{
    DateTime stop(DateTime::UtcNow());
    m_TimeSpan=stop.AsTimeSpan()-m_Start.AsTimeSpan();
}

/** @brief ScopeTimer
  *
  * @todo: document this function
  */
ScopeTimer::ScopeTimer(TimeSpan& ts)
:m_TimeSpan(ts),m_Start(DateTime::UtcNow())
{
}
