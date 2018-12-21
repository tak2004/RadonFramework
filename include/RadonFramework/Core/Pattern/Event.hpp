#ifndef RF_CORE_PATTERN_EVENT_HPP
#define RF_CORE_PATTERN_EVENT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

namespace RadonFramework::Core::Pattern
{
class IObserver;
template <typename _ARGU = const IObserver*>
class Event;

template <typename CONAP = const IObserver*>
class EventConnection
{
  friend class IObserver;

public:
  using DefaultMethod = typename Delegate1<void(CONAP)>;

  ~EventConnection();

  DefaultMethod Method();
  void operator()(CONAP Arg) const;

  void AddEvent(Event<>* Obj);
  void RemoveEvent(Event<>* Obj);

private:
  DefaultMethod m_Method;
  RF_Collect::List<Event<>*> m_Events;

  EventConnection(DefaultMethod Method);
};

class IObserver
{
protected:
  RF_Collect::List<EventConnection<>*> m_Connections;

public:
  template <class T, typename AP>
  EventConnection<AP>* Connector(void (T::*Method)(AP));
  virtual ~IObserver();
};

template <typename _ARGU>
class Event
{
protected:
  RF_Collect::List<EventConnection<_ARGU>*> m_EventHandler;

public:
  ~Event();

  void Attach(EventConnection<_ARGU>* ConnectionHandler);
  void Detach(EventConnection<_ARGU>* ConnectionHandler);

  void ConnectionRemoved(EventConnection<_ARGU>* ConnectionHandler);
  void Notify(_ARGU Arg);

  void operator()(_ARGU Arg);
  Event& operator+=(EventConnection<_ARGU>* Con);
  Event& operator-=(EventConnection<_ARGU>* Con);
};

template <typename CONAP /*=const IObserver**/>
EventConnection<CONAP>::EventConnection(DefaultMethod Method) : m_Method(Method)
{
}

template <typename CONAP /*=const IObserver**/>
EventConnection<CONAP>::~EventConnection()
{
  for(typename RF_Collect::List<Event<>*>::Iterator it = m_Events.Begin();
      it != m_Events.End(); ++it)
  {
    reinterpret_cast<Event<CONAP>*>(*it)->ConnectionRemoved(this);
  }
}

template <typename CONAP /*=const IObserver**/>
typename EventConnection<CONAP>::DefaultMethod EventConnection<CONAP>::Method()
{
  return m_Method;
}

template <typename CONAP /*=const IObserver**/>
void EventConnection<CONAP>::operator()(CONAP Arg) const
{
  m_Method(Arg);
}

template <typename CONAP /*=const IObserver**/>
void EventConnection<CONAP>::AddEvent(Event<>* Obj)
{
  for(typename RF_Collect::List<Event<>*>::Iterator it = m_Events.Begin();
      it != m_Events.End(); ++it)
    if((void*)*it == (void*)Obj)
      return;
  m_Events.AddLast(Obj);
}

template <typename CONAP /*=const IObserver**/>
void EventConnection<CONAP>::RemoveEvent(Event<>* Obj)
{
  for(typename RF_Collect::List<Event<>*>::Iterator it = m_Events.Begin();
      it != m_Events.End();)
  {
    if(reinterpret_cast<void*>(*it) == reinterpret_cast<void*>(Obj))
    {
      m_Events.Remove(it);
      return;
    }
  }
}

template <class T, typename AP>
EventConnection<AP>* IObserver::Connector(void (T::*Method)(AP))
{
  Delegate1<void(AP)> delegate(static_cast<T*>(this), Method);
  EventConnection<AP>* con = new EventConnection<AP>(delegate);
  m_Connections.AddLast((EventConnection<>*)con);
  return con;
}

template <typename _ARGU>
Event<_ARGU>::~Event()
{
  for(typename RF_Collect::List<EventConnection<_ARGU>*>::Iterator it =
          m_EventHandler.Begin();
      it != m_EventHandler.End();)
  {
    (*it)->RemoveEvent((Event<>*)this);
    m_EventHandler.Remove(it);
  }
}

template <typename _ARGU>
void Event<_ARGU>::Attach(EventConnection<_ARGU>* ConnectionHandler)
{
  m_EventHandler.AddLast((EventConnection<_ARGU>*)ConnectionHandler);
  ConnectionHandler->AddEvent(reinterpret_cast<Event<>*>(this));
}

template <typename _ARGU>
void Event<_ARGU>::Detach(EventConnection<_ARGU>* ConnectionHandler)
{
  for(typename RF_Collect::List<EventConnection<_ARGU>*>::Iterator it =
          m_EventHandler.Begin();
      it != m_EventHandler.End();)
    if((void*)*it == (void*)ConnectionHandler)
    {
      ConnectionHandler->RemoveEvent((Event<>*)this);
      m_EventHandler.Remove(it);
      return;
    }
}

template <typename _ARGU>
void Event<_ARGU>::ConnectionRemoved(EventConnection<_ARGU>* ConnectionHandler)
{
  for(typename RF_Collect::List<EventConnection<_ARGU>*>::Iterator it =
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

template <typename _ARGU>
void Event<_ARGU>::Notify(_ARGU Arg)
{
  for(typename RF_Collect::List<EventConnection<_ARGU>*>::Iterator it =
          m_EventHandler.Begin();
      it != m_EventHandler.End(); ++it)
  {
    (*(*it))(Arg);
  }
}

template <typename _ARGU>
void Event<_ARGU>::operator()(_ARGU Arg)
{
  Notify(Arg);
}

template <typename _ARGU>
Event<_ARGU>& Event<_ARGU>::operator+=(EventConnection<_ARGU>* Con)
{
  Attach(Con);
  return *this;
}

template <typename _ARGU>
Event<_ARGU>& Event<_ARGU>::operator-=(EventConnection<_ARGU>* Con)
{
  Detach(Con);
  return *this;
}

}  // namespace RadonFramework::Core::Pattern

#ifndef RF_SHORTHAND_NAMESPACE_PATTERN
#define RF_SHORTHAND_NAMESPACE_PATTERN
namespace RF_Pattern = RadonFramework::Core::Pattern;
#endif

#endif
