#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Threading/Scopelock.hpp>
#include <RadonFramework/System/Threading/Mutex.hpp>

using namespace RadonFramework::Threading;
using namespace RadonFramework::System::Threading;

Scopelock::Scopelock(){}

Scopelock::Scopelock(const Scopelock& Other){}

Scopelock::Scopelock(Mutex& Ref)
:m_Mutex(&Ref)
{
  m_Mutex->Lock();
}

Scopelock::~Scopelock()
{
  m_Mutex->Unlock();
}
