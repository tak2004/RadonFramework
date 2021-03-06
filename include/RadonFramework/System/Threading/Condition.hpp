#ifndef RF_SYSTEM_THREADING_CONDITION_HPP
#define RF_SYSTEM_THREADING_CONDITION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Time
{
struct TimeSpan;
}

namespace RadonFramework::System::Threading
{
class Mutex;

class Condition
{
public:
  Condition();
  ~Condition();
  void Wait(Mutex& Lock);
  void TimedWait(Mutex& Lock, const RadonFramework::Time::TimeSpan& Delta);
  void Notify();
  void NotifyAll();

protected:
  void* m_ImplData;
};

}  // namespace RadonFramework::System::Threading

#endif  // RF_SYSTEM_THREADING_CONDITION_HPP
