#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Time/Framecounter.hpp>

using namespace RadonFramework::Time;

void Framecounter::Update()
{
  m_Frames++;
  m_Now=DateTime::UtcNow();
  m_Delta=m_Now.AsTimeSpan().Sub(m_LastTime.AsTimeSpan());
  m_LastTime=m_Now;
  if (DateTime::LessThan(m_LastFPSChangedTime,m_Now))
  {
    m_LastFPSChangedTime=DateTime(m_Now.AsTimeSpan().Add(TimeSpan(0,0,1)).Ticks());
    m_LastFPS=m_Frames;
    m_Frames=0;
    OnFPSChanged(this);
  }
}

unsigned int Framecounter::LastFPS()
{
  return m_LastFPS;
}

unsigned int Framecounter::Frames()
{
  return m_Frames;
}

float Framecounter::Delta()
{
  return (float) m_Delta.TotalSeconds();
}

Framecounter::Framecounter()
:m_Now(0),m_LastTime(0),m_LastFPSChangedTime(0)
{

}

