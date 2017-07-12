#ifndef RF_THREADING_TIMER_HPP
#define RF_THREADING_TIMER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Time/TimeSpan.hpp>
#include <RadonFramework/System/Time.hpp>

namespace RadonFramework::Threading {

class Timer
{
public:
    Timer();

    RF_Type::Bool Update(Time::TimeSpan DueTime, Time::TimeSpan Period, 
                        void* Parameter , System::Time::TimerCallback Callback);

    void Start();
    void Stop();

    RF_Type::Bool IsRunning();
private:
    System::Time::TimerHandle m_Handler;
    Time::TimeSpan m_DueTime;
    Time::TimeSpan m_Period;
    void* m_Parameter;
    System::Time::TimerCallback m_Callback;
};

}

#endif // RF_THREADING_TIMER_HPP