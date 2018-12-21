#include "RadonFramework/Threading/Timer.hpp"
#include "RadonFramework/precompiled.hpp"

using namespace RadonFramework::Threading;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Time;
using namespace RadonFramework::System::Time;

Timer::Timer()
{
  m_Handler = TimerHandle::Zero();
}

Bool Timer::Update(TimeSpan DueTime,
                   TimeSpan Period,
                   void* Parameter,
                   TimerCallback Callback)
{
  Bool result = false;
  if(m_Handler.GetPointer() != nullptr)
  {
    m_Callback = Callback;
    m_Parameter = Parameter;
    m_DueTime = DueTime;
    m_Period = Period;
    result = true;
  }
  return result;
}

void Timer::Start()
{
  if(m_Handler.GetPointer() != nullptr)
  {
    m_Handler =
        CreateTimerQueue(m_Callback, m_Parameter, m_DueTime.TotalMilliseconds(),
                         m_Period.TotalMilliseconds());
  }
}

void Timer::Stop()
{
  DeleteTimerQueue(m_Handler);
}

Bool Timer::IsRunning()
{
  return m_Handler.GetPointer() == nullptr;
}