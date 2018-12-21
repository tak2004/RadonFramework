#ifndef RF_TIME_FRAMECOUNTER_HPP
#define RF_TIME_FRAMECOUNTER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Event.hpp>
#include <RadonFramework/Time/DateTime.hpp>
#include <RadonFramework/Time/TimeSpan.hpp>

namespace RadonFramework::Time
{
class Framecounter : public RF_Pattern::IObserver
{
public:
  Framecounter();
  float Delta();
  RF_Type::Size Frames();
  RF_Type::Size LastFPS();
  void Update();
  RF_Pattern::Event<const RF_Pattern::IObserver*> OnFPSChanged;

protected:
  TimeSpan m_Delta;
  DateTime m_Now;
  DateTime m_LastTime;
  DateTime m_LastFPSChangedTime;
  RF_Type::Size m_Frames = 0;
  RF_Type::Size m_LastFPS;
};

}  // namespace RadonFramework::Time

#ifndef RF_SHORTHAND_NAMESPACE_TIME
#define RF_SHORTHAND_NAMESPACE_TIME
namespace RF_Time = RadonFramework::Time;
#endif

#endif  // RF_TIME_FRAMECOUNTER_HPP
