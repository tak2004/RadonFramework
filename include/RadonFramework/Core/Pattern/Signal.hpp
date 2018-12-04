#ifndef RF_CORE_PATTERN_SIGNAL_HPP
#define RF_CORE_PATTERN_SIGNAL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/System/Threading/Mutex.hpp>
#include <RadonFramework/Threading/Scopelock.hpp>

namespace RadonFramework::Core::Pattern
{
class SignalReceiver;
class Signal;

class SignalConnection
{
  friend class SignalReceiver;
  using DefaultMethod = Delegate<void()>;

public:
  ~SignalConnection();

  DefaultMethod Methode();
  void operator()() const { m_Method(); }
  void AddSignal(Signal* Obj);
  void RemoveSignal(Signal* Obj);
  void UnsafeRemoveSignal(Signal* Obj);

protected:
  DefaultMethod m_Method;
  Collections::List<Signal*> m_Signals;

  SignalConnection(DefaultMethod Methode);
};

class SignalReceiver
{
protected:
  Collections::List<SignalConnection*> m_Connections;
  System::Threading::Mutex m_Mutex;

public:
  template <class T>
  SignalConnection* Connector(void (T::*Method)())
  {
    Threading::Scopelock lock(m_Mutex);
    Delegate<void()> delegate(static_cast<T*>(this), Method);
    SignalConnection* con = new SignalConnection(delegate);
    m_Connections.AddLast((SignalConnection*)con);
    return con;
  }
  virtual ~SignalReceiver();
};

class Signal
{
protected:
  Collections::List<SignalConnection*> m_EventHandler;
  System::Threading::Mutex m_Mutex;

public:
  ~Signal()
  {
    for(Collections::List<SignalConnection*>::Iterator it =
            m_EventHandler.Begin();
        it != m_EventHandler.End();)
    {
      (*it)->UnsafeRemoveSignal(this);
      m_EventHandler.Remove(it);
    }
  }

  void Attach(SignalConnection* ConnectionHandler)
  {
    Threading::Scopelock lock(m_Mutex);
    m_EventHandler.AddLast(ConnectionHandler);
    ConnectionHandler->AddSignal(this);
  }

  void Detach(SignalConnection* ConnectionHandler)
  {
    Threading::Scopelock lock(m_Mutex);
    for(Collections::List<SignalConnection*>::Iterator it =
            m_EventHandler.Begin();
        it != m_EventHandler.End();)
    {
      if(reinterpret_cast<void*>(*it) ==
         reinterpret_cast<void*>(ConnectionHandler))
      {
        ConnectionHandler->RemoveSignal(this);
        m_EventHandler.Remove(it);
        return;
      }
    }
  }

  void ConnectionRemoved(SignalConnection* ConnectionHandler)
  {
    Threading::Scopelock lock(m_Mutex);
    for(Collections::List<SignalConnection*>::Iterator it =
            m_EventHandler.Begin();
        it != m_EventHandler.End();)
    {
      if(reinterpret_cast<void*>(*it) ==
         reinterpret_cast<void*>(ConnectionHandler))
      {
        m_EventHandler.Remove(it);
        return;
      }
    }
  }

  void Notify()
  {
    Threading::Scopelock lock(m_Mutex);
    for(Collections::List<SignalConnection*>::Iterator it =
            m_EventHandler.Begin();
        it != m_EventHandler.End(); ++it)
    {
      (*(*it))();
    }
  }

  inline void operator()() { Notify(); }

  inline Signal& operator+=(SignalConnection* Con)
  {
    Attach(Con);
    return *this;
  }

  inline Signal& operator-=(SignalConnection* Con)
  {
    Detach(Con);
    return *this;
  }
};

}  // namespace RadonFramework::Core::Pattern

#ifndef RF_SHORTHAND_NAMESPACE_PATTERN
#define RF_SHORTHAND_NAMESPACE_PATTERN
namespace RF_Pattern = RadonFramework::Core::Pattern;
#endif

#endif
