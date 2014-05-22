#ifndef RF_TIME_SCOPETIMER_HPP
#define RF_TIME_SCOPETIMER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Time/TimeSpan.hpp>
#include <RadonFramework/Time/DateTime.hpp>

namespace RadonFramework { namespace Time {

class ScopeTimer
{
public:
    /** @brief ScopeTimer
      *
      * @todo: document this function
      */
    ScopeTimer(TimeSpan& ts);

    /** @brief ~ScopeTimer
      *
      * @todo: document this function
      */
    ~ScopeTimer();
protected:
    TimeSpan &m_TimeSpan;
    RFTYPE::UInt64 m_Start;
};

} }

#endif // RF_TIME_SCOPETIMER_HPP
