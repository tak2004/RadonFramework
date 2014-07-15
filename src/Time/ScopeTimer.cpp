#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Time/ScopeTimer.hpp"
#include "RadonFramework/System/Time.hpp"

using namespace RadonFramework::Time;

ScopeTimer::~ScopeTimer()
{
    RF_Type::UInt64 ticks = RFTIME::GetHighResolutionCounter();
    
    // Determine the time it take to obtain the TSC
    // http://www.ccsl.carleton.ca/~jamuir/rdtscpm1.pdf
    // Intel suggest a warm-up phase of 3 rounds and take the last value.
    RF_Type::UInt64 subtime = RFTIME::GetHighResolutionCounter();
    subtime = RFTIME::GetHighResolutionCounter() - subtime;
    subtime = RFTIME::GetHighResolutionCounter();
    subtime = RFTIME::GetHighResolutionCounter() - subtime;
    subtime = RFTIME::GetHighResolutionCounter();
    subtime = RFTIME::GetHighResolutionCounter() - subtime;

    m_TimeSpan = TimeSpan::CreateByTicks(ticks - (m_Start + subtime));
}

ScopeTimer::ScopeTimer(TimeSpan& ts)
:m_TimeSpan(ts)
{
    m_Start = RFTIME::GetHighResolutionCounter();
}
