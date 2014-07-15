#ifndef RF_TIME_FRAMECOUNTER_HPP
#define RF_TIME_FRAMECOUNTER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Time/DateTime.hpp>
#include <RadonFramework/Time/TimeSpan.hpp>
#include <RadonFramework/Core/Pattern/Event.hpp>

namespace RadonFramework { namespace Time {

class Framecounter:public RF_Pattern::IObserver
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
    RF_Pattern::Event<const RF_Pattern::IObserver*> OnFPSChanged;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_TIME
#define RF_SHORTHAND_NAMESPACE_TIME
namespace RF_Time = RadonFramework::Time;
#endif

#endif // RF_TIME_FRAMECOUNTER_HPP
