#ifndef RF_TIME_SCOPETIMER_HPP
#define RF_TIME_SCOPETIMER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Time/TimeSpan.hpp>
#include <RadonFramework/Time/DateTime.hpp>

namespace RadonFramework
{
	namespace Time
	{
        class ScopeTimer
        {
            protected:
                TimeSpan &m_TimeSpan;
                DateTime m_Start;
            public:
                ScopeTimer(TimeSpan& ts);
                ~ScopeTimer();
        };
	}
}

#endif // RF_TIME_SCOPETIMER_HPP
