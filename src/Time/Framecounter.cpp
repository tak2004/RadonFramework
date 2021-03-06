#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Time/Framecounter.hpp>

using namespace RadonFramework::Time;

void Framecounter::Update()
{
    m_Frames++;
    m_Now = DateTime::UtcNow();
    m_Delta = m_Now.AsTimeSpan().Sub(m_LastTime.AsTimeSpan());
    m_LastTime = m_Now;
    if (DateTime::LessThan(m_LastFPSChangedTime, m_Now))
    {
        m_LastFPSChangedTime = DateTime::CreateByTicks(m_Now.AsTimeSpan().Add(TimeSpan::CreateByTime(0, 0, 1)).Ticks());
        m_LastFPS = m_Frames;
        m_Frames = 0;
        OnFPSChanged(this);
    }
}

RF_Type::Size Framecounter::LastFPS()
{
    return m_LastFPS;
}

RF_Type::Size Framecounter::Frames()
{
    return m_Frames;
}

float Framecounter::Delta()
{
    return static_cast<float>(m_Delta.TotalSeconds());
}

Framecounter::Framecounter()
:m_Now(DateTime::MinValue)
,m_LastTime(DateTime::MinValue)
,m_LastFPSChangedTime(DateTime::MinValue)
{

}

