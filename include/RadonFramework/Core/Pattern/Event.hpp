#ifndef RF_CORE_PATTERN_EVENT_HPP
#define RF_CORE_PATTERN_EVENT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

namespace RadonFramework { namespace Core { namespace Pattern {

class IObserver;
template<typename _ARGU=const IObserver*>
class Event;

template <typename CONAP=const IObserver*>
class Connection
{
typedef Delegate1<CONAP> DefaultMethod;
friend class IObserver;
protected:
    Connection(DefaultMethod Method)
    :m_Method(Method)
    {
    }

    DefaultMethod m_Method;
    RF_Collect::List<Event<>*> m_Events;
public:
    ~Connection()
    {
        for (typename RF_Collect::List<Event<>*>::Iterator it=m_Events.Begin();
                it!=m_Events.End(); ++it)
            ((Event<CONAP>*)(*it))->ConnectionRemoved(this);
    }

    DefaultMethod Method()
    {
        return m_Method;
    }

    void operator()(CONAP Arg)const
    {
        m_Method(Arg);
    }

    void AddEvent(Event<>* Obj)
    {
        for (typename RF_Collect::List<Event<>*>::Iterator it=m_Events.Begin();
                it!=m_Events.End(); ++it)
            if ((void*)*it==(void*)Obj)
                return;
        m_Events.AddLast(Obj);
    }

    void RemoveEvent(Event<>* Obj)
    {
        for (typename RF_Collect::List<Event<>*>::Iterator it=m_Events.Begin();
                it!=m_Events.End();)
            if ((void*)*it==(void*)Obj)
            {
                m_Events.Remove(it);
                return;
            }
    }
};

class IObserver
{
protected:
    RF_Collect::List<Connection<>*> m_Connections;
public:
    template<class T,typename AP>
    Connection<AP>* Connector(void (T::*Method)(AP))
    {
        Delegate1<AP> delegate(reinterpret_cast<T*>(this), Method);
        Connection<AP>* con=new Connection<AP>(delegate);
        m_Connections.AddLast((Connection<>*)con);
        return con;
    }
    virtual ~IObserver();
};

template<typename _ARGU>
class Event
{
protected:
    RF_Collect::List<Connection<_ARGU>*> m_EventHandler;
public:
    ~Event()
    {
        for (typename RF_Collect::List<Connection<_ARGU>*>::Iterator it=m_EventHandler.Begin();
                it!=m_EventHandler.End();)
        {
            (*it)->RemoveEvent((Event<>*)this);
            m_EventHandler.Remove(it);
        }
    }

    void Attach(Connection<_ARGU>* ConnectionHandler)
    {
        m_EventHandler.AddLast((Connection<_ARGU>*)ConnectionHandler);
        ConnectionHandler->AddEvent((Event<>*)this);
    }

    void Detach(Connection<_ARGU>* ConnectionHandler)
    {
        for (typename RF_Collect::List<Connection<_ARGU>*>::Iterator it=m_EventHandler.Begin();
                it!=m_EventHandler.End();)
            if ((void*)*it==(void*)ConnectionHandler)
            {
                ConnectionHandler->RemoveEvent((Event<>*)this);
                m_EventHandler.Remove(it);
                return;
            }
    }

    void ConnectionRemoved(Connection<_ARGU>* ConnectionHandler)
    {
        for (typename RF_Collect::List<Connection<_ARGU>*>::Iterator it=m_EventHandler.Begin();
                it!=m_EventHandler.End();)
            if ((void*)*it==(void*)ConnectionHandler)
            {
                m_EventHandler.Remove(it);
                return;
            }
    }

    void Notify(_ARGU Arg)
    {
        for (typename RF_Collect::List<Connection<_ARGU>*>::Iterator it=m_EventHandler.Begin();
                it!=m_EventHandler.End(); ++it)
            (*(*it))(Arg);
    }

    inline void operator()(_ARGU Arg)
    {
        Notify(Arg);
    }

    inline Event& operator+=(Connection<_ARGU> *Con)
    {
        Attach(Con);
        return *this;
    }

    inline Event& operator-=(Connection<_ARGU> *Con)
    {
        Detach(Con);
        return *this;
    }
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_PATTERN
#define RF_SHORTHAND_NAMESPACE_PATTERN
namespace RF_Pattern = RadonFramework::Core::Pattern;
#endif

#endif
