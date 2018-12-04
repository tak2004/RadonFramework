#include <RadonFramework/Core/Pattern/Signal.hpp>
#include "RadonFramework/precompiled.hpp"

using namespace RadonFramework::Core::Pattern;
using namespace RadonFramework::Threading;

SignalConnection::SignalConnection(SignalConnection::DefaultMethod Methode)
: m_Method(Methode)
{
}

SignalConnection::~SignalConnection()
{
  for(RF_Collect::List<Signal*>::Iterator it = m_Signals.Begin();
      it != m_Signals.End(); ++it)
  {
    (*it)->ConnectionRemoved(this);
  }
}

SignalConnection::DefaultMethod SignalConnection::Methode()
{
  return m_Method;
}

void SignalConnection::AddSignal(Signal* Obj)
{
  for(RF_Collect::List<Signal*>::Iterator it = m_Signals.Begin();
      it != m_Signals.End(); ++it)
  {
    if(reinterpret_cast<void*>(*it) == reinterpret_cast<void*>(Obj))
    {
      return;
    }
  }
  m_Signals.AddLast(Obj);
}

void SignalConnection::RemoveSignal(Signal* Obj)
{
  UnsafeRemoveSignal(Obj);
}

void SignalConnection::UnsafeRemoveSignal(Signal* Obj)
{
  for(RF_Collect::List<Signal*>::Iterator it = m_Signals.Begin();
      it != m_Signals.End();)
  {
    if(reinterpret_cast<void*>(*it) == reinterpret_cast<void*>(Obj))
    {
      m_Signals.Remove(it);
      return;
    }
  }
}

SignalReceiver::~SignalReceiver()
{
  for(RF_Collect::List<SignalConnection*>::Iterator it = m_Connections.Begin();
      it != m_Connections.End(); ++it)
  {
    delete *it;
  }
}