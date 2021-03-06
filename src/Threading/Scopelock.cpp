#include <RadonFramework/System/Threading/Mutex.hpp>
#include <RadonFramework/Threading/Scopelock.hpp>
#include "RadonFramework/precompiled.hpp"

using namespace RadonFramework::System::Threading;

namespace RadonFramework::Threading
{
Scopelock::Scopelock(const Scopelock& Other) {}

Scopelock::Scopelock(Mutex& Ref) : m_Mutex(&Ref)
{
  m_Mutex->Lock();
}

Scopelock::~Scopelock()
{
  m_Mutex->Unlock();
}

Scopelock& Scopelock::operator=(const Scopelock& Other)
{
  return *this;
}

}  // namespace RadonFramework::Threading