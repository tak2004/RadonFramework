#ifndef RF_TIME_FRAMECOUNTER_HPP
#define RF_TIME_FRAMECOUNTER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Time/DateTime.hpp>
#include <RadonFramework/Time/TimeSpan.hpp>
#include <RadonFramework/Core/Pattern/Event.hpp>

namespace RadonFramework
{
  namespace Time
  {
    class Framecounter:public IObserver
    {
      protected:
        TimeSpan m_Delta;
        DateTime m_Now;
        DateTime m_LastTime;
        DateTime m_LastFPSChangedTime;
        unsigned int m_Frames;
        unsigned int m_LastFPS;
      public:
        Framecounter();
        float Delta();
        unsigned int Frames();
        unsigned int LastFPS();
        void Update();
        Event<const IObserver*> OnFPSChanged;
    };
  }
}

#endif // RF_TIME_FRAMECOUNTER_HPP
